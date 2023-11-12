#ifndef QTWIDGETSAPPLICATION2_H
#define QTWIDGETSAPPLICATION2_H


#include <QtWidgets>
#include "ui_QtWidgetsApplication2.h"
#include<QtSql/qsqldatabase.h>
#include<QtSql/qsqltablemodel.h>
#include<QtSql/qsqlerror.h>
#include<qsqlquery.h>//包含查询语言
#include "course.h"
#include "Graph.h"
#include "Graphl.h"
//#include "table.h"
#include "droptable.h"
#include "autoScroll.h"
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
    void manage_user();
    void manage_com();
    void cancel();
    void back_to_login();
    void generate_table();

private:
    bool read_in(vector<course> &mycourses);
    bool OpenDatabase();
    bool graph_set(Graphl*& G, vector<course>& mycourses);
    void calpath(Graph& G, int oneVertex, int length);
    void setCheckBox();
    void del_redundancy();
    void table_output(int mode, vector<string> course_names);  //mode=0:手动选课 mode=1:电脑选课  course_names 电脑选课时存储选修课
    void findMaxCombination(map<string,course> &data, vector<course> &result, vector<course>& tem_result, int &max, int current, int limit, map<string,course>::iterator it);
    Ui::QtWidgetsApplication2Class ui;
    QVBoxLayout* mainLayout;
    QVBoxLayout* layout;
    vector<course> mycourses;
    Graphl* aGraphl;
    stack<course> scourse;
    map<string, course> mcourse;  // 用于暂存课程名和课程的对应关系
    map<int, int> index;   //课程编号和图中序号的对应 前：图中序号 后：课程编号
    QVector<QCheckBox*> checkboxes;
    vector<dropTable*> tables;
    Drawing* d;
    QGridLayout* gridLayout;  //放置checkbox
    QLabel* hint_label;  //提醒可直接生成课表
    int hours_count;
    int time_limit;
    int term;
    int* indegree;
};

#endif // QTWIDGETSAPPLICATION2_H
