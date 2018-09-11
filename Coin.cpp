#include "stdafx.h"
#include "Coin.h"
#include "SuperMario.h"


void Coin::paint(QPainter & painter)
{
	if (die_contral == 0) {	//Èç¹ûÃ»ËÀ
		if (move_contral == 0)
			painter.drawPixmap(f(r).x(), f(r).y(), width * SIDE_LEN, height * SIDE_LEN, objectCell[70]);
		else if (move_contral == 1)
			painter.drawPixmap(f(r).x(), f(r).y(), width * SIDE_LEN, height * SIDE_LEN, objectCell[33]);
		else if (move_contral == 2)
			painter.drawPixmap(f(r).x(), f(r).y(), width * SIDE_LEN, height * SIDE_LEN, objectCell[201]);
		else if (move_contral == 3)
			painter.drawPixmap(f(r).x() + 0.25 * SIDE_LEN, f(r).y(), width * 0.5 * SIDE_LEN, height * SIDE_LEN, objectCell[2]);
		else if (move_contral == 4)
			painter.drawPixmap(f(r).x(), f(r).y(), width * SIDE_LEN, height * SIDE_LEN, mirrorCell[201]);
		else if (move_contral == 5)
			painter.drawPixmap(f(r).x(), f(r).y(), width * SIDE_LEN, height * SIDE_LEN, mirrorCell[33]);
		else if (move_contral == 6)
			painter.drawPixmap(f(r).x(), f(r).y(), width * SIDE_LEN, height * SIDE_LEN, mirrorCell[70]);
	}
}

void Coin::move(int a)
{
	if (frame_contral >= FRAME_CONTRAL_COIN_NORMAL) {
		if (move_contral == 0)
			move_contral = 1;
		else if (move_contral == 1)
			move_contral = 2;
		else if (move_contral == 2)
			move_contral = 3;
		else if (move_contral == 3)
			move_contral = 4;
		else if (move_contral == 4)
			move_contral = 5;
		else if (move_contral == 5)
			move_contral = 6;
		else if (move_contral == 6)
			move_contral = 0;
		frame_contral = 0;
	}
	else
		frame_contral++;
}

Coin::~Coin()
{
}