/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>
#include "ball.h"
#include "face.h"

QT_BEGIN_NAMESPACE

class Ui_ClientClass
{
public:
    QWidget *centralWidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *pushButton_1;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *enterButton;
    QWidget *page_2;
    Face *face;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    Ball *ball;

    void setupUi(QMainWindow *ClientClass)
    {
        if (ClientClass->objectName().isEmpty())
            ClientClass->setObjectName(QStringLiteral("ClientClass"));
        ClientClass->resize(1280, 720);
        centralWidget = new QWidget(ClientClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 1280, 720));
        stackedWidget->setStyleSheet(QStringLiteral("image: url(:/Client/Resources/scene.jpg);"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        label = new QLabel(page);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(200, 160, 361, 331));
        label->setStyleSheet(QStringLiteral("image: url(:/Client/Resources/face_1.png);"));
        label_2 = new QLabel(page);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(390, 160, 361, 331));
        label_2->setStyleSheet(QStringLiteral("image: url(:/Client/Resources/face_2.png);"));
        label_3 = new QLabel(page);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(620, 160, 361, 331));
        label_3->setStyleSheet(QStringLiteral("image: url(:/Client/Resources/face_3.png);"));
        label_4 = new QLabel(page);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(840, 160, 361, 331));
        label_4->setStyleSheet(QStringLiteral("image: url(:/Client/Resources/face_4.png);"));
        pushButton_1 = new QPushButton(page);
        pushButton_1->setObjectName(QStringLiteral("pushButton_1"));
        pushButton_1->setGeometry(QRect(320, 450, 131, 51));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        pushButton_1->setFont(font);
        pushButton_2 = new QPushButton(page);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(510, 450, 131, 51));
        pushButton_2->setFont(font);
        pushButton_3 = new QPushButton(page);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(750, 450, 131, 51));
        pushButton_3->setFont(font);
        pushButton_4 = new QPushButton(page);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(970, 450, 131, 51));
        pushButton_4->setFont(font);
        enterButton = new QPushButton(page);
        enterButton->setObjectName(QStringLiteral("enterButton"));
        enterButton->setGeometry(QRect(610, 580, 181, 111));
        QFont font1;
        font1.setPointSize(30);
        font1.setBold(true);
        font1.setWeight(75);
        enterButton->setFont(font1);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        face = new Face(page_2);
        face->setObjectName(QStringLiteral("face"));
        face->setGeometry(QRect(690, 640, 120, 80));
        lineEdit = new QLineEdit(page_2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(60, 150, 241, 31));
        lineEdit_3 = new QLineEdit(page_2);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(60, 200, 241, 31));
        lineEdit_4 = new QLineEdit(page_2);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(60, 250, 241, 31));
        ball = new Ball(page_2);
        ball->setObjectName(QStringLiteral("ball"));
        ball->setGeometry(QRect(1100, 330, 120, 80));
        stackedWidget->addWidget(page_2);
        ClientClass->setCentralWidget(centralWidget);

        retranslateUi(ClientClass);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ClientClass);
    } // setupUi

    void retranslateUi(QMainWindow *ClientClass)
    {
        ClientClass->setWindowTitle(QApplication::translate("ClientClass", "Client", 0));
        label->setText(QString());
        label_2->setText(QString());
        label_3->setText(QString());
        label_4->setText(QString());
        pushButton_1->setText(QApplication::translate("ClientClass", "Got it", 0));
        pushButton_2->setText(QApplication::translate("ClientClass", "Got it", 0));
        pushButton_3->setText(QApplication::translate("ClientClass", "Got it", 0));
        pushButton_4->setText(QApplication::translate("ClientClass", "Got it", 0));
        enterButton->setText(QApplication::translate("ClientClass", "ENTER", 0));
    } // retranslateUi

};

namespace Ui {
    class ClientClass: public Ui_ClientClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
