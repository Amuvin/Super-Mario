#include "stdafx.h"
#include "Mushroom.h"
#include "SuperMario.h"
#include "CharacterMario.h"

void Mushroom::paint(QPainter & painter)
{
	if (die_contral == 0) {	//如果没死
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
	if (r.y() >= 15)//如果出去了
		die_contral = 2;
	else if(is_born == 0){
		r.ry() -= 0.01;
	}
	else {
		//碰撞检测
		cell_contral[1] = int(r.ry()) + 1;
		if (r.x() - int(r.x()) > MINIMUM_VALUE)
			cell_contral[0] = int(r.rx());
		else
			cell_contral[0] = int(r.rx()) - 1;

		//检测下面
		if (collion_judge2[cell_contral[1]][int(r.rx())] == 1 || collion_judge2[cell_contral[1]][cell_contral[0] + 1] == 1) {
			r.ry() = cell_contral[1] - 1;
			if (v.ry() > 0)
				v.ry() = 0;
		}

		else {	//如果没有站在物体上，才会有竖直速度
			v.ry() += g * SPORT_PARAMETER;
			v.ry() = min(V_MAX_NORMAL.y(), v.y());
		}

		last_r = r;		//记录上个位置，便于做与马里奥的碰撞判定
		r += v * SPORT_PARAMETER;

		if (v.rx() > 0) {//若有向右的的速度
			if (r.x() - int(r.x()) > MINIMUM_VALUE)
				cell_contral[0] = int(r.rx()) + 1;
			else
				cell_contral[0] = int(r.rx());
			cell_contral[1] = int(r.ry());
			if (collion_judge2[cell_contral[1] + 1 - height][cell_contral[0]] == 1) {
				r.rx() = cell_contral[0] - 1;
				v.rx() *= -1;	//碰到东西，方向反向
			}
		}

		else if (v.rx() < 0) {//若有向左的的速度
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

		//上面
		if (r.x() - int(r.x()) < MINIMUM_VALUE)	//如果是整数
			cell_contral[0] = int(r.rx()) - 1;
		else
			cell_contral[0] = int(r.rx());

		if (r.y() - int(r.y()) < MINIMUM_VALUE)	//如果是整数
			cell_contral[1] = int(r.ry()) - height;
		else
			cell_contral[1] = int(r.ry()) + 1 - height;

		if (collion_judge2[cell_contral[1]][int(r.rx())] == 1 || collion_judge2[cell_contral[1]][cell_contral[0] + 1] == 1) {//检测上面
			if (r.ry() - int(r.ry()) > MINIMUM_VALUE)
				r.ry() = int(r.ry()) + 1;
			v.ry() = 0;
		}

		//图片控制
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