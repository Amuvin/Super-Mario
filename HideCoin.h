#pragma once
#include "Spirit.h"
class HideCoin :
	public Spirit
{
public:
	HideCoin(int i, int j)		//初始位置
	{
		r.rx() = i;
		r.ry() = j;
		a = QPointF(0, 0);
		v = QPointF(0, 0);
		frame_contral = 0;
		die_contral = 0;	//默认是活着
		width = 0.5;
		height = 1;
		move_contral = 0;
		has_add = 0;
	}
	void paint(QPainter & painter) override;
	void move(int a) override;
	int move_contral;
	int has_add;	//金币已经累加过了
	double height, width;
	~HideCoin();
};