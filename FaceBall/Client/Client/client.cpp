
#include "client.h"
#include "head.h"

int face_ID;

#define SHOW_FPS 33


Client::Client(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

#ifdef DEBUG_FACE_POS
	showTimer = new QTimer(this);
	connect(showTimer, SIGNAL(timeout()), this, SLOT(slotShowPos()));
	showTimer->start(SHOW_FPS);
	ui.lineEdit->setEnabled(false);
	ui.lineEdit_3->setEnabled(false);
	ui.lineEdit_4->setEnabled(false);
#endif


	connect(ui.pushButton_1, SIGNAL(clicked()), this, SLOT(slotButton_1()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(slotButton_2()));
	connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(slotButton_3()));
	connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(slotButton_4()));
	connect(ui.enterButton,  SIGNAL(clicked()), this, SLOT(slotEnter()));
}

#ifdef DEBUG_FACE_POS
void Client::slotShowPos()
{
	ui.lineEdit->setText(QString::number(A_X) + " , " + QString::number(A_Y));
	ui.lineEdit_3->setText(QString::number(temp_x) + " , " + QString::number(temp_y));
	ui.lineEdit_4->setText(QString::number(first_sight_x) + " , " + QString::number(first_sight_y));
}
#endif

void Client::slotButton_1()
{
	face_ID = 1;
	ui.pushButton_1->setEnabled(false);
	ui.pushButton_2->setEnabled(true);
	ui.pushButton_3->setEnabled(true);
	ui.pushButton_4->setEnabled(true);
}

void Client::slotButton_2()
{
	face_ID = 2;
	ui.pushButton_1->setEnabled(true);
	ui.pushButton_2->setEnabled(false);
	ui.pushButton_3->setEnabled(true);
	ui.pushButton_4->setEnabled(true);
}

void Client::slotButton_3()
{
	face_ID = 3;
	ui.pushButton_1->setEnabled(true);
	ui.pushButton_2->setEnabled(true);
	ui.pushButton_3->setEnabled(false);
	ui.pushButton_4->setEnabled(true);
}

void Client::slotButton_4()
{
	face_ID = 4;
	ui.pushButton_1->setEnabled(true);
	ui.pushButton_2->setEnabled(true);
	ui.pushButton_3->setEnabled(true);
	ui.pushButton_4->setEnabled(false);
}

void Client::slotEnter()
{
	ui.stackedWidget->setCurrentIndex(1);
	ui.face->openCam();
}


Client::~Client()
{

}
