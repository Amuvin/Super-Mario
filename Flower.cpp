#include "stdafx.h"
#include "Flower.h"
#include "SuperMario.h"

void Flower::paint(QPainter & painter)
{
	if (die_contral == 0) {	//Èç¹ûÃ»ËÀ
		if (move_contral == 0)
			painter.drawPixmap(f(r).x(), f(r).y(), width * SIDE_LEN, height * SIDE_LEN, objectCell[78]);
		else if (move_contral == 1)
			painter.drawPixmap(f(r).x(), f(r).y(), width * SIDE_LEN, height * SIDE_LEN, objectCell[82]);
		else if (move_contral == 2)
			painter.drawPixmap(f(r).x(), f(r).y(), width * SIDE_LEN, height * SIDE_LEN, objectCell[132]);
		else if (move_contral == 3)
			painter.drawPixmap(f(r).x(), f(r).y(), width * SIDE_LEN, height * SIDE_LEN, objectCell[154]);
	}

}

void Flower::move(int a)
{



	if (frame_contral >= FRAME_CONTRAL_FLOWER) {
		if (move_contral == 0)
			move_contral = 1;
		else if (move_contral == 1)
			move_contral = 2;
		else if (move_contral == 2)
			move_contral = 3;
		else if (move_contral == 3)
			move_contral = 0;
		frame_contral = 0;
	}
	else
		frame_contral++;
}

Flower::~Flower()
{
}