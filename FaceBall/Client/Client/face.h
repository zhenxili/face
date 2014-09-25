
#ifndef FACE_H
#define FACE_H

#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <QtCore\qtimer.h>
#include <QtWidgets\qwidget.h>
#include <QtGui\qpixmap.h>
#include <QtCore\qpoint.h>


class Face : public QWidget
{
	Q_OBJECT

private :
	int face_ico_number;
	int face_x;
	int face_y;
	int face_radius;
	int pos_x;
	int pos_y;
	cv::VideoCapture V;
	cv::Mat frame;
	std::string face_cascade_name;
	cv::CascadeClassifier face_cascade;
	QTimer *timer;
	QPixmap face_Pixmap;
	QPoint face_CurrentPos;
	bool isPressed;

public :

	//��ʼ��ֵ
	Face(QWidget *parent = 0);
	
	//������ͷ
	void openCam();
	//���׺���
	void setFace();

	//�赲���
	void isBlocked();

	//��갴ѹ����
	void mousePressEvent(QMouseEvent *event);
	//����ͷŴ���
	void mouseReleaseEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

	//��λ����
	void setPos(int a, int b);


	private slots :
		//��ʱ���ۺ���
		void slotCatch();


};

#endif //FACE_H