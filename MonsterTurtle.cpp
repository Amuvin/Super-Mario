#include "stdafx.h"
#include "MonsterTurtle.h"
#include "SuperMario.h"
#include "CharacterMario.h"

static Monster_Pattern *ptrMonster = &turtle_green;

void MonsterTurtle::paint(QPainter &painter)
{
	switch (monster_pattern_contral)
	{	//�жϹ��������
	case 0: ptrMonster = &turtle_green; break;
	case 1: ptrMonster = &turtle_red; break;
	case 2: ptrMonster = &mushroom_brown; break;
	case 3:	ptrMonster = &mushroom_blue; break;
	default:
		break;
	}

	if (die_contral == 1 && (monster_pattern_contral == 0 || monster_pattern_contral == 1)) {//���ȼ����
		painter.drawPixmap(f(r).x(), f(r).y(), width * SIDE_LEN, height * SIDE_LEN, objectCell[ptrMonster->die]);
	}
	else if (die_contral == 1 && (monster_pattern_contral == 2 || monster_pattern_contral == 3)) {
		painter.drawPixmap(f(r).x(), f(r).y(), width * SIDE_LEN, height * SIDE_LEN, objectCell[ptrMonster->die]);
		dont_move = 1;
	}
	else if(die_contral == 0) {
		if (direction_contral == right) {
			if (turtle_move_contral == 0 || v.x() == 0 || fly_contral == 1)
				painter.drawPixmap(f(r).x(), f(r).y(), width * SIDE_LEN, height * SIDE_LEN, objectCell[ptrMonster->stand]);
			else if (turtle_move_contral == 1 && (monster_pattern_contral == 0 || monster_pattern_contral == 1))
				painter.drawPixmap(f(r).x(), f(r).y(), width * SIDE_LEN, height * SIDE_LEN, objectCell[ptrMonster->walk]);
			else if(turtle_move_contral == 1 && (monster_pattern_contral == 2 || monster_pattern_contral == 3))
				painter.drawPixmap(f(r).x(), f(r).y(), width * SIDE_LEN, height * SIDE_LEN, mirrorCell[ptrMonster->stand]);
		}
		else {
			if (turtle_move_contral == 0 || v.x() == 0 || fly_contral == 1)
				painter.drawPixmap(f(r).x(), f(r).y(), width * SIDE_LEN, height * SIDE_LEN, mirrorCell[ptrMonster->stand]);
			else if (turtle_move_contral == 1 && (monster_pattern_contral == 0 || monster_pattern_contral == 1))
				painter.drawPixmap(f(r).x(), f(r).y(), width * SIDE_LEN, height * SIDE_LEN, mirrorCell[ptrMonster->walk]);
			else if (turtle_move_contral == 1 && (monster_pattern_contral == 2 || monster_pattern_contral == 3))
				painter.drawPixmap(f(r).x(), f(r).y(), width * SIDE_LEN, height * SIDE_LEN, objectCell[ptrMonster->stand]);
		}
	}
}

void MonsterTurtle::move(int pattern)	//�������������˶�ģʽ
{
	if (r.y() >= 15)//�����ȥ��
		die_contral = 2;
	else {
		if (dont_move == 1 && (monster_pattern_contral == 2 || monster_pattern_contral == 3)) {
			v.rx() = 0;
			v.ry() += g * SPORT_PARAMETER;
			r += v * SPORT_PARAMETER;
		}
		else {
			v += a * SPORT_PARAMETER;
			v.rx() = min(V_MAX_NORMAL.x(), max(-1 * V_MAX_NORMAL.x(), v.rx()));		//�ٶ��޶���һ����Χ

																					//��ײ���
			cell_contral[1] = int(r.ry()) + 1;
			qDebug() << cell_contral[1] << '\t' << r.ry();
			if (r.x() - int(r.x()) > MINIMUM_VALUE)
				cell_contral[0] = int(r.rx());
			else
				cell_contral[0] = int(r.rx()) - 1;

			//�������
			if (collion_judge2[cell_contral[1]][int(r.rx())] == 1 || collion_judge2[cell_contral[1]][cell_contral[0] + 1] == 1) {
				r.ry() = cell_contral[1] - 1;
				if (v.ry() > 0)
					v.ry() = 0;
				fly_contral = 0;	//���ڿ���
			}

			else {	//���û��վ�������ϣ��Ż�����ֱ�ٶ�
				v.ry() += g * SPORT_PARAMETER;
				v.ry() = min(V_MAX_NORMAL.y(), v.y());
				fly_contral = 1;		//�ڿ���
			}

			last_r = r;		//��¼�ϸ�λ�ã�������������µ���ײ�ж�
			r += v * SPORT_PARAMETER;

			if (v.rx() > 0) {//�������ҵĵ��ٶ�
				if (r.x() - int(r.x()) > MINIMUM_VALUE)
					cell_contral[0] = int(r.rx()) + 1;
				else
					cell_contral[0] = int(r.rx());
				cell_contral[1] = int(r.ry());
				if (collion_judge2[cell_contral[1] + 1 - height][cell_contral[0]] == 1) {
					r.rx() = cell_contral[0] - 1;
					v.rx() *= -1;	//����������������
					if (die_contral == 1) {
						is_kicked = 1;
					}
					direction_contral = left;
				}
			}

			else if (v.rx() < 0) {//��������ĵ��ٶ�
				if (r.x() - int(r.x()) > MINIMUM_VALUE)
					cell_contral[0] = int(r.rx());
				else
					cell_contral[0] = int(r.rx()) - 1;
				cell_contral[1] = int(r.ry());

				if (collion_judge2[int(r.ry()) + 1 - height][cell_contral[0]] == 1) {
					r.rx() = int(r.rx()) + 1;
					v.rx() *= -1;
					if (die_contral == 1) {
						is_kicked = 1;
					}
					direction_contral = right;
				}
			}

			//����
			if (r.x() - int(r.x()) < MINIMUM_VALUE)	//���������
				cell_contral[0] = int(r.rx()) - 1;
			else
				cell_contral[0] = int(r.rx());

			if (r.y() - int(r.y()) < MINIMUM_VALUE)	//���������
				cell_contral[1] = int(r.ry()) - height;
			else
				cell_contral[1] = int(r.ry()) + 1 - height;

			if (collion_judge2[cell_contral[1]][int(r.rx())] == 1 || collion_judge2[cell_contral[1]][cell_contral[0] + 1] == 1) {//�������
				if (r.ry() - int(r.ry()) > MINIMUM_VALUE)
					r.ry() = int(r.ry()) + 1;
				v.ry() = 0;
			}

			//ͼƬ����
			if (frame_contral >= FRAME_CONTRAL_TURTLE) {
				if (turtle_move_contral == 0)
					turtle_move_contral = 1;
				else if (turtle_move_contral == 1)
					turtle_move_contral = 0;
				frame_contral = 0;
			}
			else
				frame_contral++;
		}
	}
	
}

MonsterTurtle::~MonsterTurtle()
{
}