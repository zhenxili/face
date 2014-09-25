
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

	//初始化值
	Face(QWidget *parent = 0);
	
	//打开摄像头
	void openCam();
	//脸谱函数
	void setFace();

	//阻挡检测
	void isBlocked();

	//鼠标按压处理
	void mousePressEvent(QMouseEvent *event);
	//鼠标释放处理
	void mouseReleaseEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

	//定位函数
	void setPos(int a, int b);


	private slots :
		//定时器槽函数
		void slotCatch();


};

#endif //FACE_H