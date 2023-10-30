#ifndef QTWIDGETSAPPLICATION2_H
#define QTWIDGETSAPPLICATION2_H


#include <QtWidgets>
#include "ui_QtWidgetsApplication2.h"
#include "course.h"
#include "Graph.h"
#include "Graphl.h"
#include "table.h"
#include "drawing.h"
#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

class QtWidgetsApplication2 : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication2(const int time_limit, QWidget *parent = nullptr);
    ~QtWidgetsApplication2();
    void set_time_limit(const int t);

signals:
    void back();  //返回登录界面

private slots:
    void rc();
    void wc();
    void sh();
    void shut();
    void manage();
    void cancel();
    void back_to_login();

private:
    bool read_in(vector<course> &mycourses);
    bool graph_set(Graphl*& G, vector<course>& mycourses);
    void calpath(Graph& G, int oneVertex, int length);
    void setCheckBox();
    Ui::QtWidgetsApplication2Class ui;
    QVBoxLayout* mainLayout;
    QVBoxLayout* layout;
    vector<course> mycourses;
    Graphl* aGraphl;
    stack<course> scourse;
    map<string, course> mcourse;  // 用于暂存课程名和课程的对应关系
    map<int, int> index;   //课程编号和图中序号的对应 前：图中序号 后：课程编号
    QVector<QCheckBox*> checkboxes;
    vector<table> tables;
    Drawing* d;
    int hours_count;
    int time_limit;
    int term;
    int* indegree;
};

#endif // QTWIDGETSAPPLICATION2_H
