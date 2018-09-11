#include "stdafx.h"
#include "HideCoin.h"
#include "SuperMario.h"

void HideCoin::paint(QPainter & painter)
{
	if (die_contral == 0) {
		if (move_contral == 0)
			painter.drawPixmap(f(r).x() + 0.25 * SIDE_LEN, f(r).y(), width * SIDE_LEN, height * SIDE_LEN, objectCell[201]);
		else if (move_contral == 1)
			painter.drawPixmap(f(r).x() + 0.25 * SIDE_LEN, f(r).y() - 10, width * SIDE_LEN, height * SIDE_LEN, objectCell[33]);
		else if (move_contral == 2)
			painter.drawPixmap(f(r).x() + 0.25 * SIDE_LEN, f(r).y() - 20, width * SIDE_LEN, height * SIDE_LEN, objectCell[70]);
		else if (move_contral == 3)
			painter.drawPixmap(f(r).x() + 0.25 * SIDE_LEN, f(r).y() - 30, width * SIDE_LEN, height * SIDE_LEN, objectCell[8]);
		else if (move_contral == 4)
			painter.drawPixmap(f(r).x() + 0.25 * SIDE_LEN, f(r).y() - 40, width * SIDE_LEN, height * SIDE_LEN, objectCell[2]);
		else if (move_contral == 5)
			painter.drawPixmap(f(r).x() + 0.25 * SIDE_LEN, f(r).y() - 50, width * SIDE_LEN, height * SIDE_LEN, objectCell[28]);
		else if (move_contral == 6) {
			painter.drawPixmap(f(r).x() + 0.25 * SIDE_LEN, f(r).y() - 60, width * SIDE_LEN, height * SIDE_LEN, objectCell[4]);
			die_contral = 1;
		}
	}
}

void HideCoin::move(int a)
{
	if (frame_contral >= FRAME_CONTRAL_COIN_HIDE) {
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

HideCoin::~HideCoin()
{
}