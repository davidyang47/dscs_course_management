#ifndef QTWIDGETSAPPLICATION2_H
#define QTWIDGETSAPPLICATION2_H


#include <QtWidgets>
#include "ui_QtWidgetsApplication2.h"
#include<QtSql/qsqldatabase.h>
#include<QtSql/qsqltablemodel.h>
#include<QtSql/qsqlerror.h>
#include<qsqlquery.h>//������ѯ����
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
    void back();  //���ص�¼����

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
    void table_output(int mode, vector<string> course_names);  //mode=0:�ֶ�ѡ�� mode=1:����ѡ��  course_names ����ѡ��ʱ�洢ѡ�޿�
    void findMaxCombination(map<string,course> &data, vector<course> &result, vector<course>& tem_result, int &max, int current, int limit, map<string,course>::iterator it);
    Ui::QtWidgetsApplication2Class ui;
    QVBoxLayout* mainLayout;
    QVBoxLayout* layout;
    vector<course> mycourses;
    Graphl* aGraphl;
    stack<course> scourse;
    map<string, course> mcourse;  // �����ݴ�γ����Ϳγ̵Ķ�Ӧ��ϵ
    map<int, int> index;   //�γ̱�ź�ͼ����ŵĶ�Ӧ ǰ��ͼ����� �󣺿γ̱��
    QVector<QCheckBox*> checkboxes;
    vector<dropTable*> tables;
    Drawing* d;
    QGridLayout* gridLayout;  //����checkbox
    QLabel* hint_label;  //���ѿ�ֱ�����ɿα�
    int hours_count;
    int time_limit;
    int term;
    int* indegree;
};

#endif // QTWIDGETSAPPLICATION2_H
