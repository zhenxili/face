
#include "face.h"
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <QtGui\qbitmap.h>
#include <QtGui\qpainter.h>
#include <QtGui\qevent.h>
#include "head.h"

#define FPS 33
#define CAM_WIDTH 640
#define CAM_HEIGHT 480

int temp_x = 0;
int temp_y = 0;
int first_sight_x = 0;
int first_sight_y = 0;

bool first_sight = false;

int A_X = 0;
int A_Y = 0;


//���ݳ�ʼ��
Face::Face(QWidget *parent)
	: QWidget(parent, Qt::FramelessWindowHint)
{
	isPressed = false;
	face_x = 0;
	face_y = 0;
	face_radius = 0;
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(slotCatch()));
	face_cascade_name = "haarcascade_frontalface_alt.xml";
	face_cascade.load(face_cascade_name);
}

//���׺���
void Face::setFace()
{
	face_ico_number = face_ID;
	switch (face_ico_number)
	{
	case 1:
		face_Pixmap.load(":/Client/Resources/face_1.png");
		break;
	case 2:
		face_Pixmap.load(":/Client/Resources/face_2.png");
		break;
	case 3:
		face_Pixmap.load(":/Client/Resources/face_3.png");
		break;
	case 4:
		face_Pixmap.load(":/Client/Resources/face_4.png");
		break;
	default:
		break;
	}
	resize(face_Pixmap.size());
	setMask(face_Pixmap.mask());
}


//������ͷ
void Face::openCam()
{
	V.open(0);
	V.set(CV_CAP_PROP_FRAME_WIDTH, CAM_WIDTH);
	V.set(CV_CAP_PROP_FRAME_HEIGHT, CAM_HEIGHT);
	setFace();

	timer->start(FPS);
}

//��갴ѹ����
void Face::mousePressEvent(QMouseEvent *event)
{
	temp_x = pos_x;
	temp_y = pos_y;
	first_sight_x = 0;
	first_sight_y = 0;
	isPressed = true;
}

void Face::mouseMoveEvent(QMouseEvent *event)
{
	first_sight_x = event->pos().x();
	first_sight_y = event->pos().y();
}

//����ͷŴ���
void Face::mouseReleaseEvent(QMouseEvent *event)
{
	isPressed = false;
	first_sight = true;
}

void Face::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	//QPoint point;
	//point = this->mapToParent(QPoint(0, 0));
	//painter.translate(-point.x(), -point.y());
	painter.drawPixmap(0, 0, face_Pixmap);
}

//�赲���
void Face::isBlocked()
{
	//TODO

}

//��λ����
void Face::setPos(int a, int b)
{
	//pos_x = a + temp_x;
	//pos_y = b + temp_y;
	if (first_sight == true)
	{
		first_sight_x = a;
		first_sight_y = b;
		first_sight = false;
	}

	pos_x = temp_x + a - first_sight_x;
	pos_y = temp_y + b - first_sight_y;

	A_X = pos_x;
	A_Y = pos_y;
	this->move(pos_x, pos_y);
}

//Mat ��ת����
void flipMat(cv::Mat &img)
{
	cv::Mat map_x;
	cv::Mat map_y;
	map_x.create(img.size(), CV_32FC1);
	map_y.create(img.size(), CV_32FC1);

	for (int j = 0; j < img.rows; j++)
	{
		for (int i = 0; i < img.cols; i++)
		{
			map_x.at<float>(j, i) = img.cols - i;
			map_y.at<float>(j, i) = j;
		}
	}
	remap(img, img, map_x, map_y, CV_INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
}

//��ʱ���ۺ���
void Face::slotCatch()
{
	//�����ǰ����ѹ���򲻼������ƶ�
	if (isPressed)
		return;

	V >> frame;

	flipMat(frame);

	//���ͼ����Ҫ����С
#ifdef NEED_BE_CUTDOWN
	cv::pyrDown(frame, frame, cv::Size(frame.cols/2, frame.rows/2));
#endif

	int i = 0;
	int scale = 2;

	//�������ڴ����������������
	std::vector<cv::Rect> faces;
	//����һЩ��ɫ��������ʾ��ͬ������
	const static cv::Scalar colors[] = 
	{
		CV_RGB(0,0,255),
		CV_RGB(0,128,255),
        CV_RGB(0,255,255),
        CV_RGB(0,255,0),
        CV_RGB(255,128,0),
        CV_RGB(255,255,0),
        CV_RGB(255,0,0),
        CV_RGB(255,0,255)
	};
	//������С��ͼƬ���ӿ����ٶ�	(�������Ҫ��
	//cvRound(double value)�������ڶ�һ�� double �͵��������������룬������һ������
	cv::Mat gray, smallImg(cvRound(frame.rows/scale), cvRound(frame.cols/scale), CV_8UC1);
	//ת�ɻҶ�ͼ��Haar�������������ڻҶ�ͼ
	//�˴����Բο���ַhttp://www.opencv.org.cn/opencvdoc/2.3.2/html/doc/tutorials/objdetect/cascade_classifier/cascade_classifier.html#cascade-classifier
	//�˴����Բο���ַhttp://www.cnblogs.com/emouse/archive/2013/04/23/3037234.html
	cv::cvtColor(frame, gray, CV_BGR2GRAY);
	//�ı�ͼ���С��ʹ��˫���Բ�ֵ�����ﻹû�Ӵ�����������
	cv::resize(gray, smallImg, smallImg.size(), 0, 0, cv::INTER_LINEAR);
	//�任���ͼ�����ֱ��ͼ��ֵ������
	cv::equalizeHist(smallImg, smallImg);

	//�������
	//detectMultiScale�����е�smallImg��ʾ����Ҫ��������ͼ��ΪsmallImg
	//faces��ʾ��⵽������Ŀ�����У�  1.1��ʾÿ��ͼ��ߴ��С�ı���Ϊ1.1
	//2��ʾÿ��Ŀ������Ҫ����⵽3�β��������Ŀ��(��Ϊ��Χ�����غͲ�ͬ�Ĵ��ڴ�
    //С�����Լ�⵽����)
	//CV_HAAR_SCALE_IMAGE��ʾ�������ŷ���������⣬��������ͼ��
	//Size(30, 30)ΪĿ��������С�ߴ�
	face_cascade.detectMultiScale(smallImg, faces, 1.1,
		2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));

	for (std::vector<cv::Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, i++)
	{
		cv::Mat smallImgROI;
		cv::Point center;
		cv::Scalar color = colors[i%8];
		int radius;

		//��⵽���������ο�߱ȣ��Ӷ��ݴ�ȷ��������Բ����α�ע
		//��Ϸ���ն���������ΪԲ
		double aspect_ratio = (double)r->width/r->height;
		if (0.75 < aspect_ratio && aspect_ratio < 1.3)
		{
			//��ʾ����������С֮ǰ��ͼ���ϱ�ʾ����������������ű��������ȥ
			center.x = cvRound((r->x + r->width * 0.5) * scale);
			center.y = cvRound((r->y + r->height * 0.5) * scale);
			radius = cvRound((r->width + r->height) * 0.25 * scale);
			cv::circle(frame, center, radius, color, 3, 8, 0);
		}
		else
			cv::rectangle(frame, cvPoint(cvRound(r->x * scale), cvRound(r->y * scale)),
			cvPoint(cvRound((r->x + r->width - 1)*scale), cvRound((r->y + r->height - 1) * scale)),
			color, 3, 8, 0);

		//��������������⵽����ȷ����ֻ����һ��
		face_x = center.x;
		face_y = center.y;

		setPos(face_x, face_y);
		face_radius = radius;
	}

}