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
	case Qt::Key_Up:	//跳
		//只有站在物体上才能起跳，空中不能起跳
		if (collion_judge2[int(r.ry() + MARIO_HEIGHT_NORMAL)][int(r.rx())] == 1 || collion_judge2[int(r.ry() + MARIO_HEIGHT_NORMAL)][int(r.rx()) + 1] == 1) {
			if (ptrStatus == &status_short)
				v.ry() = JUMP_SPEED_SHORT;	//给定一个向上的初速度
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
		break;	//蹲下

	case Qt::Key_A:
	case Qt::Key_Left:
		if (abs(v.x()) <= MINIMUM_VALUE)	//防止还未减速到零就转头
			direction_contral = 0;
		a.rx() = -5; 
		break;	//左

	case Qt::Key_D:
	case Qt::Key_Right:
		if (abs(v.x()) <= MINIMUM_VALUE)	//防止还未减速到零就转头
			direction_contral = 1;
		a.rx() = 5; 
		break;	//右

	case Qt::Key_X:
	case Qt::Key_Shift:
		acc_status = 1;	//开启加速状态
		if (v.x() > 0)
			a.rx() = 8;
		else if (v.x() < 0)
			a.rx() = -8;
		break;	//加速
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
		a_friction = 0;		//松开后给予一个额外的向下的加速度
		break;		//jump

	case Qt::Key_S:
	case Qt::Key_Down:		//蹲下
		if (direction_contral == squat_left)
			direction_contral = work_left;
		else if (direction_contral == squat_right)
			direction_contral = work_right;
		break;

	case Qt::Key_A:
	case Qt::Key_Left:		//左
		if (abs(v.x()) <= MINIMUM_VALUE)	//防止还未减速到零就转头
			direction_contral = work_left;
		a.rx() = 0; a_friction = 5; break;

	case Qt::Key_D:
	case Qt::Key_Right:		//右
		if (abs(v.x()) <= MINIMUM_VALUE)	//防止还未减速到零就转头
			direction_contral = work_right;
		a.rx() = 0; a_friction = -5; break;	

	case Qt::Key_X:
	case Qt::Key_Shift:
		acc_status = 0;	//加速状态结束
		a.rx() = 0; 
		if (v.x() > 0)
			a_friction = -8;
		else if (v.x() < 0)
			a_friction = 8;
		 break;	//加速

	default:
		a.rx() = 0;
		break;
	}
}

void CharacterMario::paint(QPainter &painter)
{
	if (die_contral == 1) {
		painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->die]);
		dont_move = 1;	//死后不再做碰撞判定
	}

	else if (die_contral == 0) {
		if (start_time == 1) {		//如果进入无敌状态
			if (direction_contral == squat_right && ptrStatus != &status_short && invin_time % 4 == 0) {//向右蹲	制造闪烁的效果
				painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->squat]);
			}
			else if (direction_contral == squat_left && ptrStatus != &status_short && invin_time % 4 == 0) {//向左蹲
				painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, mirrorCell[ptrStatus->squat]);
			}

			else if ((direction_contral == squat_right || direction_contral == squat_left) && ptrStatus == &status_short  && invin_time % 4 == 0) {	//处于矮小状态不能蹲
				if (direction_contral == squat_right) {//向右
					if (fly_contral == 1)	//先检测是否在空中
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->fly]);
					else if (move_contral == 0 || v.x() == 0)
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->stand_right]);
					else if (move_contral == 1)
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->walk_1]);
					else
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->walk_2]);
				}
				else if (direction_contral == squat_left) {//向左
					if (fly_contral == 1)	//先检测是否在空中
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
				if (direction_contral == work_right) {//向右
					if (fly_contral == 1)	//先检测是否在空中
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->fly]);
					else if (move_contral == 0 || v.x() == 0)
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->stand_right]);
					else if (move_contral == 1)
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->walk_1]);
					else
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->walk_2]);
				}
				else if (direction_contral == work_left) {//向左
					if (fly_contral == 1)	//先检测是否在空中
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
			if (direction_contral == squat_right && ptrStatus != &status_short) {//向右蹲	
				painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->squat]);
			}
			else if (direction_contral == squat_left && ptrStatus != &status_short) {//向左蹲
				painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, mirrorCell[ptrStatus->squat]);
			}

			else if ((direction_contral == squat_right || direction_contral == squat_left) && ptrStatus == &status_short) {	//处于矮小状态不能蹲
				if (direction_contral == squat_right) {//向右
					if (fly_contral == 1)	//先检测是否在空中
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->fly]);
					else if (move_contral == 0 || v.x() == 0)
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->stand_right]);
					else if (move_contral == 1)
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->walk_1]);
					else
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->walk_2]);
				}
				else if (direction_contral == squat_left) {//向左
					if (fly_contral == 1)	//先检测是否在空中
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
				if (direction_contral == work_right) {//向右
					if (fly_contral == 1)	//先检测是否在空中
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->fly]);
					else if (move_contral == 0 || v.x() == 0)
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->stand_right]);
					else if (move_contral == 1)
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->walk_1]);
					else
						painter.drawPixmap(f(r).x(), f(r).y(), 1 * SIDE_LEN, 2 * SIDE_LEN, objectCell[ptrStatus->walk_2]);
				}
				else if (direction_contral == work_left) {//向左
					if (fly_contral == 1)	//先检测是否在空中
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
				v.rx() = min(V_MAX_ACCELT.x(), max(-1 * V_MAX_ACCELT.x(), v.rx()));		//速度限定在一个范围
			else
				v.rx() = min(V_MAX_NORMAL.x(), max(-1 * V_MAX_NORMAL.x(), v.rx()));	//速度限定在一个范围
		}
		else if (a_friction > 0) {
			v.rx() += (a_friction + a.x()) * SPORT_PARAMETER;
			if (v.x() >= 0) {	//减速至0后不再继续反向加速
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

		//碰撞检测
		cell_contral[1] = int(r.ry()) + 2;
		if (r.x() - int(r.x()) > MINIMUM_VALUE)
			cell_contral[0] = int(r.rx());
		else
			cell_contral[0] = int(r.rx()) - 1;

		//检测下面
		if (collion_judge2[cell_contral[1]][int(r.rx())] == 1 || collion_judge2[cell_contral[1]][cell_contral[0] + 1] == 1) {
			r.ry() = int(r.ry());
			if (v.ry() > 0)
				v.ry() = 0;
			fly_contral = 0;	//不在空中
		}

		else {	//如果没有站在物体上，才会有竖直速度
			v.ry() += (g + a_friction) * SPORT_PARAMETER;
			if (acc_status == 1)
				v.ry() = min(V_MAX_ACCELT.y(), v.y());
			else
				v.ry() = min(V_MAX_NORMAL.y(), v.y());
			fly_contral = 1;		//在空中
		}

		last_r = r;		//用于做与怪物的碰撞判定
		r += v * SPORT_PARAMETER;

		if (v.rx() > 0) {//若有向右的的速度
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

		else if (v.rx() < 0) {//若有向左的的速度
			if (collion_judge2[int(r.ry()) + 2 - ptrStatus->height][int(r.rx())] == 1 || collion_judge2[int(r.ry()) + 1][int(r.rx())] == 1) {
				r.rx() = int(r.rx()) + 1;
				v.rx() = 0;
			}
		}

		//上面
		if (r.x() - int(r.x()) < MINIMUM_VALUE)	//如果是整数
			cell_contral[0] = int(r.rx()) - 1;
		else
			cell_contral[0] = int(r.rx());

		if (r.y() - int(r.y()) < MINIMUM_VALUE)	//如果是整数
			cell_contral[1] = int(r.ry()) + 1 - ptrStatus->height;
		else
			cell_contral[1] = int(r.ry()) + 2 - ptrStatus->height;

		if (collion_judge2[cell_contral[1]][int(r.rx())] == 1 || collion_judge2[cell_contral[1]][cell_contral[0] + 1] == 1) {//检测上面
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