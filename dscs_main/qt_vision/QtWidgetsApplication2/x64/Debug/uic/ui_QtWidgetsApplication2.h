/********************************************************************************
** Form generated from reading UI file 'QtWidgetsApplication2.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTWIDGETSAPPLICATION2_H
#define UI_QTWIDGETSAPPLICATION2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtWidgetsApplication2Class
{
public:
    QWidget *centralWidget;
    QPushButton *read_in;
    QPushButton *to_show;
    QPushButton *to_manage;
    QPushButton *to_exit;
    QFrame *frame;
    QWidget *widget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *layout_button;
    QPushButton *back_to;
    QLabel *label;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *layout_label;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *layout_generate;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtWidgetsApplication2Class)
    {
        if (QtWidgetsApplication2Class->objectName().isEmpty())
            QtWidgetsApplication2Class->setObjectName("QtWidgetsApplication2Class");
        QtWidgetsApplication2Class->resize(1000, 800);
        QtWidgetsApplication2Class->setFocusPolicy(Qt::StrongFocus);
        QtWidgetsApplication2Class->setContextMenuPolicy(Qt::PreventContextMenu);
        QtWidgetsApplication2Class->setStyleSheet(QString::fromUtf8(""));
        QtWidgetsApplication2Class->setToolButtonStyle(Qt::ToolButtonIconOnly);
        centralWidget = new QWidget(QtWidgetsApplication2Class);
        centralWidget->setObjectName("centralWidget");
        centralWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(232, 255, 228);\n"
""));
        read_in = new QPushButton(centralWidget);
        read_in->setObjectName("read_in");
        read_in->setGeometry(QRect(0, 150, 100, 30));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        read_in->setFont(font);
        read_in->setAutoFillBackground(false);
        read_in->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 231, 235);\n"
"alternate-background-color: rgb(255, 28, 89);"));
        to_show = new QPushButton(centralWidget);
        to_show->setObjectName("to_show");
        to_show->setGeometry(QRect(0, 190, 100, 30));
        to_show->setFont(font);
        to_show->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 231, 235);"));
        to_manage = new QPushButton(centralWidget);
        to_manage->setObjectName("to_manage");
        to_manage->setGeometry(QRect(420, 200, 160, 50));
        QFont font1;
        font1.setPointSize(12);
        to_manage->setFont(font1);
        to_manage->setCursor(QCursor(Qt::OpenHandCursor));
        to_manage->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(0, 0, 0, 0), stop:0.52 rgba(0, 0, 0, 0), stop:0.565 rgba(82, 121, 76, 33), stop:0.65 rgba(159, 235, 148, 64), stop:0.721925 rgba(255, 238, 150, 129), stop:0.77 rgba(255, 128, 128, 204), stop:0.89 rgba(191, 128, 255, 64), stop:1 rgba(0, 0, 0, 0));"));
        to_exit = new QPushButton(centralWidget);
        to_exit->setObjectName("to_exit");
        to_exit->setGeometry(QRect(900, 0, 100, 30));
        to_exit->setFont(font);
        to_exit->setCursor(QCursor(Qt::OpenHandCursor));
        to_exit->setMouseTracking(false);
        to_exit->setFocusPolicy(Qt::NoFocus);
        to_exit->setLayoutDirection(Qt::LeftToRight);
        to_exit->setAutoFillBackground(false);
        to_exit->setStyleSheet(QString::fromUtf8("background-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 rgba(255, 255, 0, 69), stop:0.375 rgba(255, 255, 0, 69), stop:0.423533 rgba(251, 255, 0, 145), stop:0.45 rgba(247, 255, 0, 208), stop:0.477581 rgba(255, 244, 71, 130), stop:0.518717 rgba(255, 218, 71, 130), stop:0.55 rgba(255, 255, 0, 255), stop:0.57754 rgba(255, 203, 0, 130), stop:0.625 rgba(255, 255, 0, 69), stop:1 rgba(255, 255, 0, 69));"));
        frame = new QFrame(centralWidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 1000, 150));
        frame->setStyleSheet(QString::fromUtf8("border-image: url(:/QtWidgetsApplication2/bg1.jpg);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        widget = new QWidget(centralWidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(40, 260, 920, 460));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 238, 203);"));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(870, 190, 91, 71));
        layout_button = new QVBoxLayout(verticalLayoutWidget);
        layout_button->setSpacing(6);
        layout_button->setContentsMargins(11, 11, 11, 11);
        layout_button->setObjectName("layout_button");
        layout_button->setSizeConstraint(QLayout::SetDefaultConstraint);
        layout_button->setContentsMargins(0, 0, 0, 0);
        back_to = new QPushButton(centralWidget);
        back_to->setObjectName("back_to");
        back_to->setGeometry(QRect(900, 50, 100, 30));
        back_to->setFont(font);
        back_to->setCursor(QCursor(Qt::OpenHandCursor));
        back_to->setMouseTracking(false);
        back_to->setFocusPolicy(Qt::NoFocus);
        back_to->setLayoutDirection(Qt::LeftToRight);
        back_to->setAutoFillBackground(false);
        back_to->setStyleSheet(QString::fromUtf8("background-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 rgba(255, 255, 0, 69), stop:0.375 rgba(255, 255, 0, 69), stop:0.423533 rgba(251, 255, 0, 145), stop:0.45 rgba(247, 255, 0, 208), stop:0.477581 rgba(255, 244, 71, 130), stop:0.518717 rgba(255, 218, 71, 130), stop:0.55 rgba(255, 255, 0, 255), stop:0.57754 rgba(255, 203, 0, 130), stop:0.625 rgba(255, 255, 0, 69), stop:1 rgba(255, 255, 0, 69));"));
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(500, 45, 281, 81));
        label->setStyleSheet(QString::fromUtf8("\n"
"color: rgb(0, 255, 255);\n"
"background-color: transparent;\n"
"font: 700 34pt \"Microsoft YaHei UI\";"));
        label->setAlignment(Qt::AlignCenter);
        verticalLayoutWidget_2 = new QWidget(centralWidget);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(40, 240, 161, 21));
        layout_label = new QVBoxLayout(verticalLayoutWidget_2);
        layout_label->setSpacing(6);
        layout_label->setContentsMargins(11, 11, 11, 11);
        layout_label->setObjectName("layout_label");
        layout_label->setContentsMargins(0, 0, 0, 0);
        verticalLayoutWidget_3 = new QWidget(centralWidget);
        verticalLayoutWidget_3->setObjectName("verticalLayoutWidget_3");
        verticalLayoutWidget_3->setGeometry(QRect(460, 720, 91, 41));
        layout_generate = new QVBoxLayout(verticalLayoutWidget_3);
        layout_generate->setSpacing(6);
        layout_generate->setContentsMargins(11, 11, 11, 11);
        layout_generate->setObjectName("layout_generate");
        layout_generate->setSizeConstraint(QLayout::SetDefaultConstraint);
        layout_generate->setContentsMargins(0, 0, 0, 0);
        QtWidgetsApplication2Class->setCentralWidget(centralWidget);
        frame->raise();
        read_in->raise();
        to_show->raise();
        to_manage->raise();
        to_exit->raise();
        widget->raise();
        verticalLayoutWidget->raise();
        back_to->raise();
        label->raise();
        verticalLayoutWidget_2->raise();
        verticalLayoutWidget_3->raise();
        menuBar = new QMenuBar(QtWidgetsApplication2Class);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1000, 22));
        QtWidgetsApplication2Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtWidgetsApplication2Class);
        mainToolBar->setObjectName("mainToolBar");
        QtWidgetsApplication2Class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtWidgetsApplication2Class);
        statusBar->setObjectName("statusBar");
        QtWidgetsApplication2Class->setStatusBar(statusBar);

        retranslateUi(QtWidgetsApplication2Class);

        QMetaObject::connectSlotsByName(QtWidgetsApplication2Class);
    } // setupUi

    void retranslateUi(QMainWindow *QtWidgetsApplication2Class)
    {
        QtWidgetsApplication2Class->setWindowTitle(QCoreApplication::translate("QtWidgetsApplication2Class", "QtWidgetsApplication2", nullptr));
        read_in->setText(QCoreApplication::translate("QtWidgetsApplication2Class", "read in", nullptr));
        to_show->setText(QCoreApplication::translate("QtWidgetsApplication2Class", "show", nullptr));
        to_manage->setText(QCoreApplication::translate("QtWidgetsApplication2Class", "\345\274\200    \345\247\213    \351\200\211    \350\257\276", nullptr));
        to_exit->setText(QCoreApplication::translate("QtWidgetsApplication2Class", "E X I T", nullptr));
        back_to->setText(QCoreApplication::translate("QtWidgetsApplication2Class", "B A C K", nullptr));
        label->setText(QCoreApplication::translate("QtWidgetsApplication2Class", "\345\255\246    \347\224\237    \347\253\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtWidgetsApplication2Class: public Ui_QtWidgetsApplication2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTWIDGETSAPPLICATION2_H
