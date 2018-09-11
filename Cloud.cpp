#include "stdafx.h"
#include "Cloud.h"
#include <math.h>
#include "CharacterMario.h"

double angle_to_radian(int a)
{//½Ç¶È×ª»¡¶È
	return a * PI / 180;
}	

void Cloud::paint(QPainter & painter)
{
	if(cloud_move_contral == 0)
		painter.drawPixmap(f(r).x(), f(r).y(), width * SIDE_LEN, height * SIDE_LEN, objectCell[31]);
	else if(cloud_move_contral == 1)
		painter.drawPixmap(f(r).x(), f(r).y(), width * SIDE_LEN, height * SIDE_LEN, objectCell[40]);
	else if (cloud_move_contral == 2)
		painter.drawPixmap(f(r).x(), f(r).y(), width * SIDE_LEN, height * SIDE_LEN, objectCell[94]);
}

void Cloud::move(int time_contral)
{
	r.rx() = sinf(angle_to_radian(time_contral) + fixed_i * 400) * 0.4 + fixed_i;
	r.ry() = cosf(angle_to_radian(time_contral) + fixed_i * 400) * 0.1 + fixed_j;

	if (frame_contral >= FRAME_CONTRAL_CLOUD) {
		if (cloud_move_contral == 0)
			cloud_move_contral = 1;
		else if (cloud_move_contral == 1)
			cloud_move_contral = 2;
		else if (cloud_move_contral == 2)
			cloud_move_contral = 0;
		frame_contral = 0;
	}
	else
		frame_contral++;
}

Cloud::~Cloud()
{
}