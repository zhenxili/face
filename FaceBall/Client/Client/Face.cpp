
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


//数据初始化
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

//脸谱函数
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


//打开摄像头
void Face::openCam()
{
	V.open(0);
	V.set(CV_CAP_PROP_FRAME_WIDTH, CAM_WIDTH);
	V.set(CV_CAP_PROP_FRAME_HEIGHT, CAM_HEIGHT);
	setFace();

	timer->start(FPS);
}

//鼠标按压处理
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

//鼠标释放处理
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

//阻挡检测
void Face::isBlocked()
{
	//TODO

}

//定位函数
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

//Mat 翻转函数
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

//定时器槽函数
void Face::slotCatch()
{
	//如果当前被按压，则不计人脸移动
	if (isPressed)
		return;

	V >> frame;

	flipMat(frame);

	//如果图像需要被缩小
#ifdef NEED_BE_CUTDOWN
	cv::pyrDown(frame, frame, cv::Size(frame.cols/2, frame.rows/2));
#endif

	int i = 0;
	int scale = 2;

	//建立用于存放人脸的向量容器
	std::vector<cv::Rect> faces;
	//定义一些颜色，用来表示不同的人脸
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
	//建立缩小的图片，加快检测速度	(这里很重要）
	//cvRound(double value)函数用于对一个 double 型的数进行四舍五入，并返回一个整数
	cv::Mat gray, smallImg(cvRound(frame.rows/scale), cvRound(frame.cols/scale), CV_8UC1);
	//转成灰度图像，Haar特征分类器基于灰度图
	//此处可以参考网址http://www.opencv.org.cn/opencvdoc/2.3.2/html/doc/tutorials/objdetect/cascade_classifier/cascade_classifier.html#cascade-classifier
	//此处可以参考网址http://www.cnblogs.com/emouse/archive/2013/04/23/3037234.html
	cv::cvtColor(frame, gray, CV_BGR2GRAY);
	//改变图像大小，使用双线性差值（这里还没接触过。。。）
	cv::resize(gray, smallImg, smallImg.size(), 0, 0, cv::INTER_LINEAR);
	//变换后的图像进行直方图均值化处理
	cv::equalizeHist(smallImg, smallImg);

	//检测人脸
	//detectMultiScale函数中的smallImg表示的是要检测的输入图像为smallImg
	//faces表示检测到的人脸目标序列，  1.1表示每次图像尺寸减小的比例为1.1
	//2表示每个目标至少要被检测到3次才算是真的目标(因为周围的像素和不同的窗口大
    //小都可以检测到人脸)
	//CV_HAAR_SCALE_IMAGE表示不是缩放分类器来检测，而是缩放图像
	//Size(30, 30)为目标的最大最小尺寸
	face_cascade.detectMultiScale(smallImg, faces, 1.1,
		2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));

	for (std::vector<cv::Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, i++)
	{
		cv::Mat smallImgROI;
		cv::Point center;
		cv::Scalar color = colors[i%8];
		int radius;

		//检测到的人脸矩形宽高比，从而据此确定最终用圆或矩形标注
		//游戏最终断言人脸均为圆
		double aspect_ratio = (double)r->width/r->height;
		if (0.75 < aspect_ratio && aspect_ratio < 1.3)
		{
			//标示人脸是在缩小之前的图像上标示，所以这里根据缩放比例换算回去
			center.x = cvRound((r->x + r->width * 0.5) * scale);
			center.y = cvRound((r->y + r->height * 0.5) * scale);
			radius = cvRound((r->width + r->height) * 0.25 * scale);
			cv::circle(frame, center, radius, color, 3, 8, 0);
		}
		else
			cv::rectangle(frame, cvPoint(cvRound(r->x * scale), cvRound(r->y * scale)),
			cvPoint(cvRound((r->x + r->width - 1)*scale), cvRound((r->y + r->height - 1) * scale)),
			color, 3, 8, 0);

		//人脸数据由最后检测到的脸确定，只保存一组
		face_x = center.x;
		face_y = center.y;

		setPos(face_x, face_y);
		face_radius = radius;
	}

}