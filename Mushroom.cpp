#include "stdafx.h"
#include "Mushroom.h"
#include "SuperMario.h"
#include "CharacterMario.h"

void Mushroom::paint(QPainter & painter)
{
	if (die_contral == 0) {	//���û��
		painter.drawPixmap(f(r).x(), f(r).y(), width * SIDE_LEN, height * SIDE_LEN, objectCell[218]);
		if (r.y() <= last_r.y() - 1) {
			painter.drawPixmap(f(r).x(), f(r).y() - 1, width * SIDE_LEN, height * SIDE_LEN, objectCell[218]);
			is_born = 1;
			v.rx() = 1;
		}
			
	}
}

void Mushroom::move(int a)
{
	if (r.y() >= 15)//�����ȥ��
		die_contral = 2;
	else if(is_born == 0){
		r.ry() -= 0.01;
	}
	else {
		//��ײ���
		cell_contral[1] = int(r.ry()) + 1;
		if (r.x() - int(r.x()) > MINIMUM_VALUE)
			cell_contral[0] = int(r.rx());
		else
			cell_contral[0] = int(r.rx()) - 1;

		//�������
		if (collion_judge2[cell_contral[1]][int(r.rx())] == 1 || collion_judge2[cell_contral[1]][cell_contral[0] + 1] == 1) {
			r.ry() = cell_contral[1] - 1;
			if (v.ry() > 0)
				v.ry() = 0;
		}

		else {	//���û��վ�������ϣ��Ż�����ֱ�ٶ�
			v.ry() += g * SPORT_PARAMETER;
			v.ry() = min(V_MAX_NORMAL.y(), v.y());
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
			}
		}

		else if (v.rx() < 0) {//��������ĵ��ٶ�
			if (r.x() - int(r.x()) > MINIMUM_VALUE)
				cell_contral[0] = int(r.rx());
			else
				cell_contral[0] = int(r.rx()) - 1;
			cell_contral[1] = int(r.ry());

			if (collion_judge2[int(r.ry()) + 1 - height][cell_contral[0]] == 1) {
				r.rx() = int(r.rx());
				v.rx() *= -1;
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
		if (frame_contral >= FRAME_CONTRAL_FLOWER) {
			frame_contral = 0;
		}
		else
			frame_contral++;

	}

}


Mushroom::~Mushroom()
{
}