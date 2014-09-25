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
	splash->showMessage(QStringLiteral("游戏启动中......"),
		topRight, Qt::white);
	
	Client w;

	splash->showMessage(QStringLiteral("控件加载中......"),
		topRight, Qt::white);

	w.show();
	w.move((QApplication::desktop()->width() - w.width())/2, 
		(QApplication::desktop()->height() - w.height())/2);

	splash->finish(&w);
	delete splash;

	return a.exec();
}
