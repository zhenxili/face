#ifndef CLIENT_H
#define CLIENT_H

#include <QtWidgets/QMainWindow>
#include "ui_client.h"
#include <QtCore\qtimer.h>

#define DEBUG_FACE_POS

class Client : public QMainWindow
{
	Q_OBJECT

public:
	Client(QWidget *parent = 0);
	~Client();

private:
	Ui::ClientClass ui;

#ifdef DEBUG_FACE_POS
	QTimer *showTimer;
#endif

	private slots :
		void slotButton_1();
		void slotButton_2();
		void slotButton_3();
		void slotButton_4();
		void slotEnter();

#ifdef DEBUG_FACE_POS
		void slotShowPos();
#endif
};

#endif // CLIENT_H
