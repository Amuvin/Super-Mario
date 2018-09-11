#include "stdafx.h"
#include "QuestionMark.h"
#include "SuperMario.h"

void QuestionMark::paint(QPainter & painter)
{
	if (die_contral == 0) {	//Èç¹ûÃ»ËÀ
		if (move_contral == 0)
			painter.drawPixmap(f(r).x(), f(r).y(), width * SIDE_LEN, height * SIDE_LEN, objectCell[255]);
		else if (move_contral == 1)
			painter.drawPixmap(f(r).x(), f(r).y(), width * SIDE_LEN, height * SIDE_LEN, objectCell[235]);
		else if (move_contral == 2)
			painter.drawPixmap(f(r).x(), f(r).y(), width * SIDE_LEN, height * SIDE_LEN, objectCell[204]);
	}
	else {
		painter.drawPixmap(f(r).x(), f(r).y(), width * SIDE_LEN, height * SIDE_LEN, objectCell[36]);
	}
}

void QuestionMark::move(int a)
{
	if (frame_contral >= FRAME_CONTRAL_QUESTION) {
		if (move_contral == 0)
			move_contral = 1;
		else if (move_contral == 1)
			move_contral = 2;
		else if (move_contral == 2)
			move_contral = 0;
		frame_contral = 0;
	}
	else
		frame_contral++;
}


QuestionMark::~QuestionMark()
{
}