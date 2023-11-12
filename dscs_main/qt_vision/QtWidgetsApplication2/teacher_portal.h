#ifndef TEACHER_PORTAL_H
#define TEACHER_PORTAL_H

#include <QtWidgets>
#include "ui_teacher_portal.h"
#include<QtSql/qsqldatabase.h>
#include<QtSql/qsqltablemodel.h>
#include<QtSql/qsqlerror.h>
#include<qsqlquery.h>//包含查询语言
#include "course.h"
#include "Graph.h"
#include "Graphl.h"
#include "table.h"
#include "drawing.h"
#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

class teacher_portal : public QMainWindow
{
	Q_OBJECT

 public:
	 teacher_portal(QWidget* parent = nullptr);
	 ~teacher_portal();

signals:
    void back();  
    void send_time_changed(int time);

private slots:
    void read();
    void show_graph();
    void shut();
    void initial(int mode);
    void add_course();
    void delete_course();
    void cancel();
    void back_to_login();
    void set_time();
    void list_student();

private:
    bool read_in(vector<course>& mycourses);
    bool graph_set(Graphl*& G, vector<course>& mycourses);
    void calpath(Graph& G, int oneVertex, int length);
    bool OpenDatabase();
    Ui::MainWindow ui;
    QVBoxLayout* mainLayout;
    QVBoxLayout* layout;
    QVector<QCheckBox*> checkboxes;
    vector<course> mycourses;
    Graphl* aGraphl;
    map<int, int> index;   
    Drawing* d;
    int time_limit;
    int* indegree;
    string filepath;  
    QVector<QLineEdit*> when_add;
    QButtonGroup* c_type;
};

#endif // TEACHER_PORTAL_H