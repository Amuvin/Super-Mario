#pragma once
#include <qkeyeventtransition.h>
#include "Spirit.h"
class RollScreen
{
public:
	RollScreen() {
		b = QPointF(0, 0);
	}
	QPointF b;

	QPointF operator()(QPointF r)
	{
		return SIDE_LEN * r + b;
	}
};

//马里奥身体状态控制
class status {
public:
	//构造函数定义
	status(int a, int b, int c, int d, int e, int f = 0, int my_g = 0, int h = 0, int i = 0, int j = 1)
	{	//由于没有0号图片，故可用0作为默认参数
		stand_face = a;
		stand_right = b;
		walk_1 = c;
		walk_2 = d;
		fly = e;
		squat = f;
		brake = my_g;
		fight = h;
		die = i;
		height = j;
	}

	int stand_face;	//正面站立
	int stand_right;	//面向右侧站立
	int walk_1;	//刚开始走
	int walk_2;	//走
	int fly;	//空中
	int squat;	//下蹲
	int brake;	//刹车
	int fight;	//发子弹
	int die;	//死亡
	int height;	//身高
};

class CharacterMario:public Spirit
{
private:
	int move_contral;	//控制显示的图片
	enum {
		work_left,	//左走：0，右走：1,左下蹲：2，右下蹲：3
		work_right,
		squat_left,
		squat_right
	};

	enum {		//力的方向 上：0，下：1，左：2，右：3
		f_up,
		f_down,
		f_left,
		f_right
	};

	int direction_contral;
	int cell_contral[2];	//控制检测的格子,0:x;1:y
	double a_friction;	//摩擦力产生的加速度


public:
	CharacterMario();
	~CharacterMario();
	void keyPressEvent(QKeyEvent *e);
	void keyReleaseEvent(QKeyEvent *e);
	void paint(QPainter &painter) override;
	void move(int a) override;
	bool connectMonster();//遇到了怪物
	QPointF last_r;
	int fly_contral;		//检测是否在空中
	int dont_move;		//死亡后不再做碰撞检测
	int invin_time;
	int start_time;		//是否进入无敌状态
	int acc_status;		//是否处于加速状态
protected:

};