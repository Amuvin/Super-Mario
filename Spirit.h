#pragma once
class Spirit
{
public:
	virtual void paint(QPainter &painter){}
	virtual void move(int a){}	//�������������˶�ģʽ
	Spirit();
	~Spirit();
	QPointF r, v, a;
	int frame_contral;	//֡�ʿ��ƣ�����ÿ����֡��һ��ͼƬ
	int die_contral;	//�����ж�
};