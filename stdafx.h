#include <QtWidgets>
#define MAX_TIME 365	//游戏倒计时 365s
#define TIME_STEP 1000	//单位：毫秒

#define PI 3.14159
#define MINIMUM_VALUE 1e-5		//极小值，用于判断是否为0
#define FRAME 60		//全局帧率
#define INVINCIBLE_TIME 60		//无敌时间，以帧率为单位

#define FRAME_CONTRAL_MARIO 5		//马里奥每几帧换一张图
#define FRAME_CONTRAL_CLOUD 16		//云每隔几帧换一张图	云的帧率要保持大于马里奥的帧率，否则会出问题
#define FRAME_CONTRAL_TURTLE 5		//乌龟每隔几帧换一张图
#define FRAME_CONTRAL_FLOWER 8		//花
#define FRAME_CONTRAL_QUESTION 10	//问号
#define FRAME_CONTRAL_COIN_NORMAL 6	//金币
#define FRAME_CONTRAL_COIN_HIDE 2	//隐藏的金币
#define FRAME_CONTRAL_MUSHROOM	1	//隐藏的蘑菇

#define DISTANCE 3 * SIDE_LEN		//马里奥距离小怪多少时小怪开始动

#define SIDE_LEN 42	//网格的边长
#define BORDER_HIGTH 15		//定义整个窗口（边界）的高度
#define BORDER_WIDTH 20		//定义整个窗口（边界）的宽度

#define MARIO_HEIGHT_NORMAL 2		//定义马里奥正常的身高
#define MARIO_HEIGHT_SHORT 1		//定义马里奥蹲下或是变矮时的身高
#define MARIO_WIDTH 1		//定义马里奥的身宽
#define SPORT_PARAMETER 0.04	//定义马里奥运动的一个参数，控制运动的快慢
#define JUMP_SPEED_SHORT -8		//马里奥变矮时起跳的初速度
#define JUMP_SPEED_NORMAL -8	//正常时的起跳初速度
#define DIE_SPEED -3	//死亡时的上升初速度
#define FALLEN_SPEED -6		//坠亡时的上升速度

#define g 8	//定义自由落体加速度


extern QVector<QPixmap> objectCell;
extern  QVector<QPixmap> mirrorCell;
extern bool collion_judge2[15][203];
extern QPointF V_MAX_NORMAL;		//正常速度的最大值
extern QPointF V_MAX_ACCELT;		//加速状态的最大值
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