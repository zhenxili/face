

#include "ball.h"
#include <cmath>
#include <QtCore\qtimer.h>
#include <QtGui\qpainter.h>
#include <QtGui\qbitmap.h>

//������������
int faces[2][3] = {0};

#define FPS 50
#define SPACE 10	//������ǽ�����С���

Ball::Ball(QWidget *parent)
	: QWidget(parent, Qt::FramelessWindowHint)
{
	m_Pixmap.load(":/Client/Resources/ball.png");
	resize(m_Pixmap.size());
	setMask(m_Pixmap.mask());
	move_timer = new QTimer(this);
	slowdown_timer = new QTimer(this);
	connect(move_timer, SIGNAL(timeout()), this, SLOT(slotMove()));
	connect(slowdown_timer, SIGNAL(timeout()), this, SLOT(speedDeal()));

	move_timer->start(FPS);
	setWindowFlags(Qt::WindowStaysOnTopHint);

	quality = 100;
	radio   = 30;
	speed   = 20;
	move_direction     = 60;
	attacked_direction = 0;
	ball_x = 300;
	ball_y = 300;
	type = 0;
}

void Ball::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_CurrentPos = event->globalPos() - frameGeometry().topLeft();
		event->accept();
	}
	else if (event->button() == Qt::RightButton)
		close();
}

void Ball::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() && Qt::LeftButton)
	{
		move(event->globalPos() - m_CurrentPos);
		event->accept();
	}
}

void Ball::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.drawPixmap(0, 0, m_Pixmap);
}

void Ball::leaveEvent(QEvent *event)
{
	setCursor(Qt::ArrowCursor);
}

void Ball::enterEvent(QEvent *event)
{
	setCursor(Qt::PointingHandCursor);
}

//����˶��ۺ���
void Ball::slotMove()
{
	ball_x = ball_x + speed * cos((move_direction * 3.1415926)/180);
	ball_y = ball_y + speed * sin((move_direction * 3.1415926)/180);
	this->move(ball_x-radio, ball_y-radio);
	if (speed > 20)
	{
		move_timer->stop();
		slowdown_timer->start(FPS);
	}

	isAttacked();
}

//��ļ��ٲۺ���
void Ball::speedDeal()
{
	speed = speed - 3;
	ball_x = ball_x + speed * cos((move_direction * 3.1415926)/180);
	ball_y = ball_y + speed * sin((move_direction * 3.1415926)/180);
	this->move(ball_x-radio, ball_y-radio);
	if (speed <=20)
	{
		speed = 20;
		slowdown_timer->stop();
		move_timer->start(FPS);
	}
}

//��λ����
void Ball::setXY(int a, int b)
{
	ball_x = a;
	ball_y = b;
	this->move(a-radio, b-radio);
}

int Ball::getX() const
{
	return ball_x;
}

int Ball::getY() const
{
	return ball_y;
}

bool Ball::isAttacked()
{
	//������ײ���
	//�������ѭ��
	for (int i = 0; i < 2; i++)
	{
		//������ֱ������
		if (faces[i][2] == 0)
			break;
		int distance = (int)(abs(faces[i][0] - ball_x) * abs(faces[i][0] - ball_x) + abs(faces[i][1] - ball_y) * abs(faces[i][1] - ball_y));
		if (distance < (faces[i][2] + radio) * (faces[i][2] + radio))
		{	
			switch (i)
			{
			case 0:
				type = 10;
				break;
			case 1:
				type = 11;
				break;
			default:
				break;
			}

			speedUp(type);
			return true;
		}
	}

	//��ǽ��ײ���
	if ((ball_x + radio + SPACE) > WINDOW_WIDTH)
	{
		//��ֹ����������ײ
		if (type == 1)
			return false;
		type = 1;
		speedUp(type);
		return true;
	}
	//��ǽ��ײ���
	if ((ball_y + radio + SPACE) > WINDOW_HEIGHT)
	{
		if (type == 2)
			return false;
		type = 2;
		speedUp(type);
		return true;
	}
	//��ǽ��ײ���
	if ((ball_x - radio - SPACE) < 0)
	{
		if (type == 3)
			return false;
		type = 3;
		speedUp(type);
		return true;
	}
	//��ǽ��ײ���
	if ((ball_y - radio - SPACE) < 0)
	{
		if (type == 4)
			return false;
		type = 4;
		speedUp(type);
		return true;
	}
		

	return false;
}

//���ܹ���ʱ�ٵ���
void Ball::speedUp(int type)
{
	switch (type)
	{
	case 10:
		//������Ϊԭ�㣬X��Ϊ����
		//Y����
		if (ball_x == faces[0][0])
		{
			if (ball_y <= faces[0][1])
			{
				move_direction = 90;
			}
			else
			{
				move_direction = 270;
			}
		}
		else
		{
			//1��4 ����
			if (ball_x > faces[0][0])
			{
				if (ball_y <= faces[0][1])
					move_direction = (atan((double)(faces[0][1] - ball_y)/(ball_x - faces[0][0])) * 180)/3.1415926;
				else
					move_direction = 360 - (atan((double)(ball_y - faces[0][1])/(ball_x - faces[0][0])) * 180)/3.1415926;
			}
			else
			//2��3����
			{
				if (ball_y <= faces[0][1])
					move_direction = 180 - (atan((double)(faces[0][1] - ball_y)/(faces[0][0] - ball_x)) * 180)/3.1415926;
				else
					move_direction = 180 + (atan((double)(ball_y - faces[0][1])/(faces[0][0] - ball_x)) *180)/3.1415926;
			}
		}
		speed = (2.5 * faces[0][2] * speed)/quality;
		break;
	case 11:
		//������Ϊԭ�㣬X��Ϊ����
		//Y����
		if (ball_x == faces[1][0])
		{
			if (ball_y <= faces[1][1])
			{
				move_direction = 90;
			}
			else
			{
				move_direction = 270;
			}
		}
		else
		{
			//1��4 ����
			if (ball_x > faces[1][0])
			{
				if (ball_y <= faces[1][1])
					move_direction = (atan((double)(faces[1][1] - ball_y)/(ball_x - faces[1][0])) * 180)/3.1415926;
				else
					move_direction = 360 - (atan((double)(ball_y - faces[1][1])/(ball_x - faces[1][0])) * 180)/3.1415926;
			}
			else
			//2��3����
			{
				if (ball_y <= faces[1][1])
					move_direction = 180 - (atan((double)(faces[1][1] - ball_y)/(faces[1][0] - ball_x)) * 180)/3.1415926;
				else
					move_direction = 180 + (atan((double)(ball_y - faces[1][1])/(faces[1][0] - ball_x)) * 180)/3.1415926;
			}
		}
		speed = (2.5 * faces[1][2] * speed)/quality;
		break;
	case 1:
		if (move_direction < 90)
			move_direction = 180 - move_direction;
		else
			if ((move_direction == 45) && ((ball_y - radio - SPACE) < 0))
				move_direction = 225;
			else
				if ((move_direction == 315) && ((ball_y + radio + SPACE) > WINDOW_HEIGHT))
					move_direction = 135;
				else
					move_direction = 540 - move_direction;
		break;
	case 2:
		if (move_direction <= 270)
			move_direction = 360 - move_direction;
		else
			if ((move_direction == 225) && ((ball_x - radio - SPACE) < 0))
				move_direction = 45;
			else
				move_direction = 360 - move_direction;
		break;
	case 3:
		if ((move_direction == 135) && ((ball_y - radio - SPACE) < 0))
			move_direction = 315;
		else
			if (move_direction <= 180)
				move_direction = 180 - move_direction;
			else
				move_direction = 540 - move_direction;
		break;
	case 4:
		if (move_direction <= 90)
			move_direction = 360 - move_direction;
		else
			move_direction = 360 - move_direction;
	default:
		break;
	}
}
