/********************************************************************************
** Form generated from reading UI file 'teacher_portal.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEACHER_PORTAL_H
#define UI_TEACHER_PORTAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *frame;
    QPushButton *read_in;
    QPushButton *to_show;
    QPushButton *to_exit;
    QPushButton *back_to;
    QLabel *label;
    QWidget *widget;
    QPushButton *add;
    QPushButton *to_set;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1000, 800);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 1000, 150));
        frame->setStyleSheet(QString::fromUtf8("border-image: url(:/teacher_portal/bg2.jpg);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        read_in = new QPushButton(centralwidget);
        read_in->setObjectName("read_in");
        read_in->setGeometry(QRect(0, 150, 100, 30));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        read_in->setFont(font);
        read_in->setAutoFillBackground(false);
        read_in->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 231, 235);\n"
"alternate-background-color: rgb(255, 28, 89);"));
        to_show = new QPushButton(centralwidget);
        to_show->setObjectName("to_show");
        to_show->setGeometry(QRect(0, 190, 100, 30));
        to_show->setFont(font);
        to_show->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 231, 235);"));
        to_exit = new QPushButton(centralwidget);
        to_exit->setObjectName("to_exit");
        to_exit->setGeometry(QRect(900, 0, 100, 30));
        to_exit->setFont(font);
        to_exit->setCursor(QCursor(Qt::OpenHandCursor));
        to_exit->setMouseTracking(false);
        to_exit->setFocusPolicy(Qt::NoFocus);
        to_exit->setLayoutDirection(Qt::LeftToRight);
        to_exit->setAutoFillBackground(false);
        to_exit->setStyleSheet(QString::fromUtf8("background-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 rgba(255, 255, 0, 69), stop:0.375 rgba(255, 255, 0, 69), stop:0.423533 rgba(251, 255, 0, 145), stop:0.45 rgba(247, 255, 0, 208), stop:0.477581 rgba(255, 244, 71, 130), stop:0.518717 rgba(255, 218, 71, 130), stop:0.55 rgba(255, 255, 0, 255), stop:0.57754 rgba(255, 203, 0, 130), stop:0.625 rgba(255, 255, 0, 69), stop:1 rgba(255, 255, 0, 69));"));
        back_to = new QPushButton(centralwidget);
        back_to->setObjectName("back_to");
        back_to->setGeometry(QRect(900, 50, 100, 30));
        back_to->setFont(font);
        back_to->setCursor(QCursor(Qt::OpenHandCursor));
        back_to->setMouseTracking(false);
        back_to->setFocusPolicy(Qt::NoFocus);
        back_to->setLayoutDirection(Qt::LeftToRight);
        back_to->setAutoFillBackground(false);
        back_to->setStyleSheet(QString::fromUtf8("background-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 rgba(255, 255, 0, 69), stop:0.375 rgba(255, 255, 0, 69), stop:0.423533 rgba(251, 255, 0, 145), stop:0.45 rgba(247, 255, 0, 208), stop:0.477581 rgba(255, 244, 71, 130), stop:0.518717 rgba(255, 218, 71, 130), stop:0.55 rgba(255, 255, 0, 255), stop:0.57754 rgba(255, 203, 0, 130), stop:0.625 rgba(255, 255, 0, 69), stop:1 rgba(255, 255, 0, 69));"));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(500, 45, 281, 81));
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);\n"
"background-color: transparent;\n"
"font: 700 34pt \"Microsoft YaHei UI\";"));
        label->setAlignment(Qt::AlignCenter);
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 240, 1000, 560));
        add = new QPushButton(centralwidget);
        add->setObjectName("add");
        add->setGeometry(QRect(260, 170, 100, 30));
        add->setFont(font);
        add->setAutoFillBackground(false);
        add->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 231, 235);\n"
"alternate-background-color: rgb(255, 28, 89);"));
        to_set = new QPushButton(centralwidget);
        to_set->setObjectName("to_set");
        to_set->setGeometry(QRect(660, 170, 100, 30));
        to_set->setFont(font);
        to_set->setAutoFillBackground(false);
        to_set->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 231, 235);\n"
"alternate-background-color: rgb(255, 28, 89);"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(910, 180, 91, 71));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        read_in->setText(QCoreApplication::translate("MainWindow", "read in", nullptr));
        to_show->setText(QCoreApplication::translate("MainWindow", "show", nullptr));
        to_exit->setText(QCoreApplication::translate("MainWindow", "E X I T", nullptr));
        back_to->setText(QCoreApplication::translate("MainWindow", "B A C K", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\346\225\231    \345\270\210    \347\253\257", nullptr));
        add->setText(QCoreApplication::translate("MainWindow", "\345\212\240 \350\257\276", nullptr));
        to_set->setText(QCoreApplication::translate("MainWindow", "\351\200\211 \350\257\276 \350\256\276 \347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEACHER_PORTAL_H
