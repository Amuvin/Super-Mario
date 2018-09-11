/*
*提交版本需改掉图片的绝对路径
*窗口的缩放问题
*初始位置修改

*/
#pragma once

#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

#include <QtWidgets/QWidget>
#include "ui_SuperMario.h"
#include "CharacterMario.h"
#include "Cloud.h"
#include "MonsterTurtle.h"
#include "Flower.h"
#include "QuestionMark.h"
#include "Coin.h"
#include "HideCoin.h"
#include "Mushroom.h"


class SuperMario : public QWidget
{
	Q_OBJECT
		
public:
	SuperMario(QWidget *parent = Q_NULLPTR);
	QAction actionReboot;
	void game_over();
	void you_win();
	void start_game();

protected:

	//重写绘图事件
	void paintEvent(QPaintEvent *pt);

	void closeEvent(QCloseEvent * e);

	//键盘按下
	void keyPressEvent(QKeyEvent *ev) override;

	//松开
	void keyReleaseEvent(QKeyEvent *ev) override;

	//倒计时
	void timerEvent(QTimerEvent *ev) override;
private:
	Ui::SuperMarioClass ui;
	int id1, id2;	//计数器
};