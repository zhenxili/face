#include "client.h"
#include <QtWidgets/QApplication>
#include <QtWidgets\qsplashscreen.h>
#include <QtWidgets\qdesktopwidget.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QSplashScreen *splash = new QSplashScreen;
	splash->setPixmap(QPixmap(":/Client/Resourses/ing.jpg"));
	splash->show();

	Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
	splash->showMessage(QStringLiteral("��Ϸ������......"),
		topRight, Qt::white);
	
	Client w;

	splash->showMessage(QStringLiteral("�ؼ�������......"),
		topRight, Qt::white);

	w.show();
	w.move((QApplication::desktop()->width() - w.width())/2, 
		(QApplication::desktop()->height() - w.height())/2);

	splash->finish(&w);
	delete splash;

	return a.exec();
}
