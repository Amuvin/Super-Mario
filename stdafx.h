#include <QtWidgets>
#define MAX_TIME 365	//��Ϸ����ʱ 365s
#define TIME_STEP 1000	//��λ������

#define PI 3.14159
#define MINIMUM_VALUE 1e-5		//��Сֵ�������ж��Ƿ�Ϊ0
#define FRAME 60		//ȫ��֡��
#define INVINCIBLE_TIME 60		//�޵�ʱ�䣬��֡��Ϊ��λ

#define FRAME_CONTRAL_MARIO 5		//�����ÿ��֡��һ��ͼ
#define FRAME_CONTRAL_CLOUD 16		//��ÿ����֡��һ��ͼ	�Ƶ�֡��Ҫ���ִ�������µ�֡�ʣ�����������
#define FRAME_CONTRAL_TURTLE 5		//�ڹ�ÿ����֡��һ��ͼ
#define FRAME_CONTRAL_FLOWER 8		//��
#define FRAME_CONTRAL_QUESTION 10	//�ʺ�
#define FRAME_CONTRAL_COIN_NORMAL 6	//���
#define FRAME_CONTRAL_COIN_HIDE 2	//���صĽ��
#define FRAME_CONTRAL_MUSHROOM	1	//���ص�Ģ��

#define DISTANCE 3 * SIDE_LEN		//����¾���С�ֶ���ʱС�ֿ�ʼ��

#define SIDE_LEN 42	//����ı߳�
#define BORDER_HIGTH 15		//�����������ڣ��߽磩�ĸ߶�
#define BORDER_WIDTH 20		//�����������ڣ��߽磩�Ŀ��

#define MARIO_HEIGHT_NORMAL 2		//������������������
#define MARIO_HEIGHT_SHORT 1		//��������¶��»��Ǳ䰫ʱ�����
#define MARIO_WIDTH 1		//��������µ����
#define SPORT_PARAMETER 0.04	//����������˶���һ�������������˶��Ŀ���
#define JUMP_SPEED_SHORT -8		//����±䰫ʱ�����ĳ��ٶ�
#define JUMP_SPEED_NORMAL -8	//����ʱ���������ٶ�
#define DIE_SPEED -3	//����ʱ���������ٶ�
#define FALLEN_SPEED -6		//׹��ʱ�������ٶ�

#define g 8	//��������������ٶ�


extern QVector<QPixmap> objectCell;
extern  QVector<QPixmap> mirrorCell;
extern bool collion_judge2[15][203];
extern QPointF V_MAX_NORMAL;		//�����ٶȵ����ֵ
extern QPointF V_MAX_ACCELT;		//����״̬�����ֵ
extern class RollScreen f;

extern class status status_short;
extern class status status_middle;
extern class status status_super;
extern class status *ptrStatus;

extern class Monster_Pattern turtle_green;
extern class Monster_Pattern turtle_red;
extern class Monster_Pattern mushroom_brown;
extern class Monster_Pattern mushroom_blue;

extern double min(double a, double b);
extern double max(double a, double b);