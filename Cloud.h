#pragma once
#include "Spirit.h"
class Cloud :
	public Spirit
{
private:
	int cloud_move_contral;	//图片控制

public:
	void paint(QPainter &painter) override;
	void move(int time) override;
	double width, height;
	int fixed_i, fixed_j;

	Cloud(int i, int j)		//初始化坐标
	{
		r.rx() = fixed_i = i;
		r.ry() = fixed_j = j;
		cloud_move_contral = 0;
		width = 2;
		height = 1.5;
		frame_contral = 0;
	}

	~Cloud();
};