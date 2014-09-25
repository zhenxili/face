
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
	//���ٴ���
	void speedDeal();

private :
	QPoint m_CurrentPos;
	QPixmap m_Pixmap;

public :
	QTimer *move_timer;
	QTimer *slowdown_timer;

private :
	//����
	int ball_x;
	int ball_y;
	//�ƶ�������X������нǣ�
	int move_direction;
	//�ܻ�������X������нǣ�
	int attacked_direction;
	//�ƶ��ٶ�
	int speed;
	//�������,����Ӱ�첻ͬ������Сʱ�ٶȱ仯
	double quality;
	//��İ뾶
	double radio;
	//��ײ����
	int type;

public :
	//����ϵ��
	void setXY(int a, int b);
	int getX() const;
	int getY() const;
	//�ж��Ƿ��ܵ���������slotmove�б�����
	bool isAttacked();
	//�ܹ������ڵ��ٶ�
	void speedUp(int t);

};

#endif //BALL_H