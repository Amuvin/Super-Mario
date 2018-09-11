#pragma once
class Spirit
{
public:
	virtual void paint(QPainter &painter){}
	virtual void move(int a){}	//参数用来控制运动模式
	Spirit();
	~Spirit();
	QPointF r, v, a;
	int frame_contral;	//帧率控制，设置每多少帧换一张图片
	int die_contral;	//死亡判定
};