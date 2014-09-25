
#ifndef BALL_H
#define BALL_H

#include "head.h"
#include <QtWidgets\qwidget.h>
#include <qevent.h>

class Ball : public QWidget
{
	Q_OBJECT

public :
	Ball(QWidget *parent = 0);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);
	void enterEvent(QEvent *event);
	void leaveEvent(QEvent *event);

private slots :
	void slotMove();
	//减速处理
	void speedDeal();

private :
	QPoint m_CurrentPos;
	QPixmap m_Pixmap;

public :
	QTimer *move_timer;
	QTimer *slowdown_timer;

private :
	//坐标
	int ball_x;
	int ball_y;
	//移动方向（与X轴正向夹角）
	int move_direction;
	//受击方向（与X轴正向夹角）
	int attacked_direction;
	//移动速度
	int speed;
	//球的质量,用于影响不同人脸大小时速度变化
	double quality;
	//球的半径
	double radio;
	//碰撞类型
	int type;

public :
	//坐标系列
	void setXY(int a, int b);
	int getX() const;
	int getY() const;
	//判断是否受到攻击，在slotmove中被调用
	bool isAttacked();
	//受攻击初期的速度
	void speedUp(int t);

};

#endif //BALL_H