#ifndef TEACHER_PORTAL_H
#define TEACHER_PORTAL_H

#include "ui_teacher_portal.h"
#include <QtWidgets>
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
    void back();  //���ص�¼����
    void send_time_changed(int time);

private slots:
    void read();
    void show_graph();
    void shut();
    void initial(int mode);
    void add_course();
    void cancel();
    void back_to_login();
    void set_time();

private:
    bool read_in(vector<course>& mycourses);
    bool graph_set(Graphl*& G, vector<course>& mycourses);
    void calpath(Graph& G, int oneVertex, int length);
    Ui::MainWindow ui;
    QVBoxLayout* mainLayout;
    QVBoxLayout* layout;
    QVector<QCheckBox*> checkboxes;
    vector<course> mycourses;
    Graphl* aGraphl;
    map<int, int> index;   //�γ̱�ź�ͼ����ŵĶ�Ӧ ǰ��ͼ����� �󣺿γ̱��
    Drawing* d;
    int time_limit;
    int* indegree;
    string filepath;  //�ļ���ַ
    QVector<QLineEdit*> when_add;
    QButtonGroup* c_type;
};

#endif // TEACHER_PORTAL_H