#include "stdafx.h"
#include "CharacterMario.h"
#include "SuperMario.h"
#include <QGraphicsItem>

CharacterMario::CharacterMario()
{
	last_r = r = QPointF(1, 5);
	v = QPointF(0, 0);
	a = QPointF(0, 0);
	a_friction = 0;
	move_contral = 0;
	fly_contral = 0;
	direction_contral = 1;
	frame_contral = 0;
	die_contral = 0;
	dont_move = 0;
	invin_time = 0;
	start_time = 0;
	acc_status = 0;
}


CharacterMario::~CharacterMario()
{
}

void CharacterMario::keyPressEvent(QKeyEvent * e)
{
	a_friction = 0;
	switch (e->key()) {
	case Qt::Key_Space:
	case Qt::Key_W:
	case Qt::Key_Z:
	case Qt::Key_Up:	//��
		//ֻ��վ�������ϲ������������в�������
		if (collion_judge2[int(r.ry() + MARIO_HEIGHT_NORMAL)][int(r.rx())] == 1 || collion_judge2[int(r.ry() + MARIO_HEIGHT_NORMAL)][int(r.rx()) + 1] == 1) {
			if (ptrStatus == &status_short)
				v.ry() = JUMP_SPEED_SHORT;	//����һ�����ϵĳ��ٶ�
			else
				v.ry() = JUMP_SPEED_NORMAL;
		}
		break;

	case Qt::Key_S:
	case Qt::Key_Down:
		if (direction_contral == work_left) {
			a_friction = 10;
			direction_contral = squat_left;
		}
		else if (direction_contral == work_right) {
			a_friction = -10;
			direction_contral = squat_right;
		}
		break;	//����

	case Qt::Key_A:
	case Qt::Key_Left:
		if (abs(v.x()) <= MINIMUM_VALUE)	//��ֹ��δ���ٵ����תͷ
			direction_contral = 0;
		a.rx() = -5; 
		break;	//��

	case Qt::Key_D:
	case Qt::Key_Right:
		if (abs(v.x()) <= MINIMUM_VALUE)	//��ֹ��δ���ٵ����תͷ
			direction_contral = 1;
		a.rx() = 5; 
		break;	//��

	case Qt::Key_X:
	case Qt::Key_Shift:
		acc_status = 1;	//��������״̬
		if (v.x() > 0)
			a.rx() = 8;
		else if (v.x() < 0)
			a.rx() = -8;
		break;	//����
	default:
		break;
	}
}

void CharacterMario::keyReleaseEvent(QKeyEvent * e)
{
	switch (e->key()) {
	case Qt::Key_Space:
	case Qt::Key_W:
	case Qt::Key_Z:
	case Qt::Key_Up:
		a_friction = 0;		//�ɿ������һ����������µļ��ٶ�
		break;		//jump

	case Qt::Key_S:
	case Qt::Key_Down:		//����
		if (direction_contral == squat_left)
			direction_contral = work_left;
		else if (direction_contral == squat_right)
			direction_contral = work_right;
		break;

	case Qt::Key_A:
	case Qt::Key_Left:		//��
		if (abs(v.x()) <= MINIMUM_VALUE)	//��ֹ��δ���ٵ����תͷ
			direction_contral = work_left;
		a.rx() = 0; a_friction = 5; break;

	case Qt::Key_D:
	case Qt::Key_Right:		//��
		if (abs(v.x()) <= MINIMUM_VALUE)	//��ֹ��δ���ٵ����תͷ
			direction_contral = work_right;
		a.rx() = 0; a_friction = -5; break;	

	case Qt::Key_X:
	case Qt::Key_Shift:
		acc_status = 0;	//����״̬����
		a.rx() = 0; 
		if (v.x() > 0)
			a_friction = -8;
		else if (v.x() < 0)
			a_friction = 8;
		 break;	//����

	default:
		a.rx() = 0;
		break;
	}
}

void CharacterMario::paint(QPainter &painter)
{
	if (die_contral == 1) {
		painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->die]);
		dont_move = 1;	//����������ײ�ж�
	}

	else if (die_contral == 0) {
		if (start_time == 1) {		//��������޵�״̬
			if (direction_contral == squat_right && ptrStatus != &status_short && invin_time % 4 == 0) {//���Ҷ�	������˸��Ч��
				painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->squat]);
			}
			else if (direction_contral == squat_left && ptrStatus != &status_short && invin_time % 4 == 0) {//�����
				painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, mirrorCell[ptrStatus->squat]);
			}

			else if ((direction_contral == squat_right || direction_contral == squat_left) && ptrStatus == &status_short  && invin_time % 4 == 0) {	//���ڰ�С״̬���ܶ�
				if (direction_contral == squat_right) {//����
					if (fly_contral == 1)	//�ȼ���Ƿ��ڿ���
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->fly]);
					else if (move_contral == 0 || v.x() == 0)
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->stand_right]);
					else if (move_contral == 1)
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->walk_1]);
					else
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->walk_2]);
				}
				else if (direction_contral == squat_left) {//����
					if (fly_contral == 1)	//�ȼ���Ƿ��ڿ���
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, mirrorCell[ptrStatus->fly]);
					else if (move_contral == 0 || v.x() == 0)
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, mirrorCell[ptrStatus->stand_right]);
					else if (move_contral == 1)
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, mirrorCell[ptrStatus->walk_1]);
					else
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, mirrorCell[ptrStatus->walk_2]);
				}
			}
			else if(invin_time % 4 == 0) {
				if (v.x() > 0)
					direction_contral = work_right;
				if (v.x() < 0)
					direction_contral = work_left;
				if (direction_contral == work_right) {//����
					if (fly_contral == 1)	//�ȼ���Ƿ��ڿ���
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->fly]);
					else if (move_contral == 0 || v.x() == 0)
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->stand_right]);
					else if (move_contral == 1)
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->walk_1]);
					else
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->walk_2]);
				}
				else if (direction_contral == work_left) {//����
					if (fly_contral == 1)	//�ȼ���Ƿ��ڿ���
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, mirrorCell[ptrStatus->fly]);
					else if (move_contral == 0 || v.x() == 0)
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, mirrorCell[ptrStatus->stand_right]);
					else if (move_contral == 1)
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, mirrorCell[ptrStatus->walk_1]);
					else
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, mirrorCell[ptrStatus->walk_2]);
				}
			}
		}
		else {
			if (direction_contral == squat_right && ptrStatus != &status_short) {//���Ҷ�	
				painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->squat]);
			}
			else if (direction_contral == squat_left && ptrStatus != &status_short) {//�����
				painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, mirrorCell[ptrStatus->squat]);
			}

			else if ((direction_contral == squat_right || direction_contral == squat_left) && ptrStatus == &status_short) {	//���ڰ�С״̬���ܶ�
				if (direction_contral == squat_right) {//����
					if (fly_contral == 1)	//�ȼ���Ƿ��ڿ���
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->fly]);
					else if (move_contral == 0 || v.x() == 0)
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->stand_right]);
					else if (move_contral == 1)
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->walk_1]);
					else
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->walk_2]);
				}
				else if (direction_contral == squat_left) {//����
					if (fly_contral == 1)	//�ȼ���Ƿ��ڿ���
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, mirrorCell[ptrStatus->fly]);
					else if (move_contral == 0 || v.x() == 0)
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, mirrorCell[ptrStatus->stand_right]);
					else if (move_contral == 1)
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, mirrorCell[ptrStatus->walk_1]);
					else
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, mirrorCell[ptrStatus->walk_2]);
				}
			}
			else {
				if (v.x() > 0)
					direction_contral = work_right;
				if (v.x() < 0)
					direction_contral = work_left;
				if (direction_contral == work_right) {//����
					if (fly_contral == 1)	//�ȼ���Ƿ��ڿ���
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->fly]);
					else if (move_contral == 0 || v.x() == 0)
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->stand_right]);
					else if (move_contral == 1)
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->walk_1]);
					else
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->walk_2]);
				}
				else if (direction_contral == work_left) {//����
					if (fly_contral == 1)	//�ȼ���Ƿ��ڿ���
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, mirrorCell[ptrStatus->fly]);
					else if (move_contral == 0 || v.x() == 0)
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, mirrorCell[ptrStatus->stand_right]);
					else if (move_contral == 1)
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, mirrorCell[ptrStatus->walk_1]);
					else
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, mirrorCell[ptrStatus->walk_2]);
				}
			}
		}
		
	}
}

void CharacterMario::move(int )
{
	if (dont_move == 1) {	
		v.rx() = 0;
		v.ry() += (g + a_friction) * SPORT_PARAMETER;
		r += v * SPORT_PARAMETER;
		if (r.y() >= 15){
			die_contral = 2;
		}
			
	}

	else if (dont_move == 0 && r.y() >= 13) {
		v.ry() = FALLEN_SPEED;
		die_contral = 1;
	}

	else {
		if (a_friction == 0) {
			v += a * SPORT_PARAMETER;
			if (acc_status == 1)
				v.rx() = min(V_MAX_ACCELT.x(), max(-1 * V_MAX_ACCELT.x(), v.rx()));		//�ٶ��޶���һ����Χ
			else
				v.rx() = min(V_MAX_NORMAL.x(), max(-1 * V_MAX_NORMAL.x(), v.rx()));	//�ٶ��޶���һ����Χ
		}
		else if (a_friction > 0) {
			v.rx() += (a_friction + a.x()) * SPORT_PARAMETER;
			if (v.x() >= 0) {	//������0���ټ����������
				a_friction = 0;
				v.rx() = 0;
			}
		}
		else {
			v.rx() += (a_friction + a.x()) * SPORT_PARAMETER;
			if (v.x() <= 0) {
				a_friction = 0;
				v.rx() = 0;
			}
		}

		//��ײ���
		cell_contral[1] = int(r.ry()) + 2;
		if (r.x() - int(r.x()) > MINIMUM_VALUE)
			cell_contral[0] = int(r.rx());
		else
			cell_contral[0] = int(r.rx()) - 1;

		//�������
		if (collion_judge2[cell_contral[1]][int(r.rx())] == 1 || collion_judge2[cell_contral[1]][cell_contral[0] + 1] == 1) {
			r.ry() = int(r.ry());
			if (v.ry() > 0)
				v.ry() = 0;
			fly_contral = 0;	//���ڿ���
		}

		else {	//���û��վ�������ϣ��Ż�����ֱ�ٶ�
			v.ry() += (g + a_friction) * SPORT_PARAMETER;
			if (acc_status == 1)
				v.ry() = min(V_MAX_ACCELT.y(), v.y());
			else
				v.ry() = min(V_MAX_NORMAL.y(), v.y());
			fly_contral = 1;		//�ڿ���
		}

		last_r = r;		//��������������ײ�ж�
		r += v * SPORT_PARAMETER;

		if (v.rx() > 0) {//�������ҵĵ��ٶ�
			if (r.x() - int(r.x()) > MINIMUM_VALUE)
				cell_contral[0] = int(r.rx()) + 1;
			else
				cell_contral[0] = int(r.rx());
			cell_contral[1] = int(r.ry());
			if (collion_judge2[cell_contral[1] + 2 - ptrStatus->height][cell_contral[0]] == 1 || collion_judge2[cell_contral[1] + 1][cell_contral[0]] == 1) {
				r.rx() = cell_contral[0] - 1;
				v.rx() = 0;
			}
		}

		else if (v.rx() < 0) {//��������ĵ��ٶ�
			if (collion_judge2[int(r.ry()) + 2 - ptrStatus->height][int(r.rx())] == 1 || collion_judge2[int(r.ry()) + 1][int(r.rx())] == 1) {
				r.rx() = int(r.rx()) + 1;
				v.rx() = 0;
			}
		}

		//����
		if (r.x() - int(r.x()) < MINIMUM_VALUE)	//���������
			cell_contral[0] = int(r.rx()) - 1;
		else
			cell_contral[0] = int(r.rx());

		if (r.y() - int(r.y()) < MINIMUM_VALUE)	//���������
			cell_contral[1] = int(r.ry()) + 1 - ptrStatus->height;
		else
			cell_contral[1] = int(r.ry()) + 2 - ptrStatus->height;

		if (collion_judge2[cell_contral[1]][int(r.rx())] == 1 || collion_judge2[cell_contral[1]][cell_contral[0] + 1] == 1) {//�������
			if (r.ry() - int(r.ry()) > MINIMUM_VALUE)
				r.ry() = int(r.ry()) + 1;
			v.ry() = 0;
		}

		if (frame_contral >= FRAME_CONTRAL_MARIO) {
			if (move_contral == 1)
				move_contral = 2;
			else if (move_contral == 2)
				move_contral = 0;
			else if (move_contral == 0)
				move_contral = 1;
			frame_contral = 0;
		}
		else
			frame_contral++;
	}
}

bool CharacterMario::connectMonster()
{

	return false;
}