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

//���������״̬����
class status {
public:
	//���캯������
	status(int a, int b, int c, int d, int e, int f = 0, int my_g = 0, int h = 0, int i = 0, int j = 1)
	{	//����û��0��ͼƬ���ʿ���0��ΪĬ�ϲ���
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

	int stand_face;	//����վ��
	int stand_right;	//�����Ҳ�վ��
	int walk_1;	//�տ�ʼ��
	int walk_2;	//��
	int fly;	//����
	int squat;	//�¶�
	int brake;	//ɲ��
	int fight;	//���ӵ�
	int die;	//����
	int height;	//���
};

class CharacterMario:public Spirit
{
private:
	int move_contral;	//������ʾ��ͼƬ
	enum {
		work_left,	//���ߣ�0�����ߣ�1,���¶ף�2�����¶ף�3
		work_right,
		squat_left,
		squat_right
	};

	enum {		//���ķ��� �ϣ�0���£�1����2���ң�3
		f_up,
		f_down,
		f_left,
		f_right
	};

	int direction_contral;
	int cell_contral[2];	//���Ƽ��ĸ���,0:x;1:y
	double a_friction;	//Ħ���������ļ��ٶ�


public:
	CharacterMario();
	~CharacterMario();
	void keyPressEvent(QKeyEvent *e);
	void keyReleaseEvent(QKeyEvent *e);
	void paint(QPainter &painter) override;
	void move(int a) override;
	bool connectMonster();//�����˹���
	QPointF last_r;
	int fly_contral;		//����Ƿ��ڿ���
	int dont_move;		//������������ײ���
	int invin_time;
	int start_time;		//�Ƿ�����޵�״̬
	int acc_status;		//�Ƿ��ڼ���״̬
protected:

};