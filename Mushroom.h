#pragma once
#include "Spirit.h"
class Mushroom :
	public Spirit
{
private:
	int cell_contral[2];	//控制检测的格子,0:x;1:y
public:
	Mushroom(int i, int j)		//初始位置
	{
		r.rx() = i;
		r.ry() = j;
		last_r = r;
		a = QPointF(0, 0);
		v = QPointF(0, 0);
		frame_contral = 0;
		die_contral = 0;	//默认是活着
		width = 1;
		height = 1;
		move_contral = 0;
		is_born = 0;
	}
	void paint(QPainter & painter) override;
	void move(int a) override;
	QPointF last_r;
	int is_born;	//是否已经完全出来

	int width, height, move_contral;
	~Mushroom();
};