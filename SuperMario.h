/*
*�ύ�汾��ĵ�ͼƬ�ľ���·��
*���ڵ���������
*��ʼλ���޸�

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

	//��д��ͼ�¼�
	void paintEvent(QPaintEvent *pt);

	void closeEvent(QCloseEvent * e);

	//���̰���
	void keyPressEvent(QKeyEvent *ev) override;

	//�ɿ�
	void keyReleaseEvent(QKeyEvent *ev) override;

	//����ʱ
	void timerEvent(QTimerEvent *ev) override;
private:
	Ui::SuperMarioClass ui;
	int id1, id2;	//������
};