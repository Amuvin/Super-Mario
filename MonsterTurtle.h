#pragma once
#include "Spirit.h"

class Monster_Pattern {
	//构造函数定义
public:
	Monster_Pattern(int a, int b, int c, int d, int e, int f)
	{
		stand = a;
		walk = b;
		die = c;
		shell_1 = d;
		shell_2 = e;
		shell_3 = f;
	}
	int stand;	//面向右侧站立
	int walk;	//刚开始走
	int die;	//死亡
	int shell_1;	//死亡后变成的龟壳
	int shell_2;
	int shell_3;
};

class MonsterTurtle :
	public Spirit
{
private:
	enum {	//方向，左：0，右：1
		left,
		right
	};
	int turtle_move_contral;
	int direction_contral;
	int cell_contral[2];	//控制检测的格子,0:x;1:y
	int fly_contral;		//检测是否在空中
	
	
public:
	MonsterTurtle(int i, int j,int species)		//初始位置
	{
		r.rx() = i;
		r.ry() = j;
		last_r = r;
		a = QPointF(0, 0);
		v = QPointF(-0.3, 0);

		monster_pattern_contral = species;
		turtle_move_contral = 0;
		fly_contral = 0;
		direction_contral = left;	//默认向右
		frame_contral = 0;
		width = 1;
		height = 1;
		die_contral = 0;	//默认是活着
		dont_move = 0;
		is_kicked = 0;
	}

	int is_kicked;
	//怪物的状态控制，0：turtle_green，1：turtle_red，2：mushroom_brown，3：mushroom_blue
	int monster_pattern_contral;
	void paint(QPainter & painter) override;
	void move(int a) override;
	QPointF last_r;
	int width, height;
	int dont_move;
	~MonsterTurtle();
};