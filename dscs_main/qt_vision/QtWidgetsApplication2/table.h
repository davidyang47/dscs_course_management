#ifndef TABLE_H
#define TABLE_H

#include <bits/stdc++.h>
#include "course.h"
#include <QtWidgets>
#include <QFile>
#include <QTextStream>
#include <windows.h>
using namespace std;

struct arrange {
    string course_name;
    //string teacher_name;
    string course_time;
};

class table {
public:
    int term;
    vector<course> courses;
    arrange course_table[4][5];
    table() {
        term = 0;
        courses.clear();
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 5; j++) {
                course_table[i][j].course_name = "";
                course_table[i][j].course_time = "";
            }
        }
    }
    table(int term) {
        this->term = term;
        courses.clear();
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 5; j++) {
                course_table[i][j].course_name = "";
                course_table[i][j].course_time = "";
            }
        }
    }
    bool set_table(course c) {
        courses.push_back(c);
        vector<int> time;
        time.clear();
        int h = c.hours;
        int i, j, end_week;
        while (h > 0) {
            vector<int>::iterator it;
            do {
                i = rand() % 4;
                if (c.hours > 64 && c.hours < 96)
                    j = (rand() % 3) * 2;
                else
                    j = rand() % 5;
                if (c.hours < 96)
                    for (int k = -1; k < 1; k++) {
                        it = find(time.begin(), time.end(), j + k);
                        if (it != time.end())
                            break;
                    }
                else
                    it = find(time.begin(), time.end(), j);
            } while ((it != time.end()) || (course_table[i][j].course_name != ""));
            if (h % 32 != 0) {
                end_week = h % 32 / 2;
                h -= end_week * 2;
            }
            else {
                end_week = 16;
                h -= 32;
            }
            course_table[i][j].course_name = c.name;
            course_table[i][j].course_time = " Week 1-" + to_string(end_week);
            time.push_back(j);
        }
        time.clear();
        return true;
    }
    QTableWidget* show_table() {
        //cout << "the classtable of term " << term << " is:" << endl;
        //for (int i = 0; i < 4; i++) {
        //    for (int j = 0; j < 5; j++) {
        //        if (course_table[i][j].course_name != "")
        //            cout << course_table[i][j].course_name << ":" << course_table[i][j].course_time;
        //        cout << "     ";
        //    }
        //    cout << endl;
        //}
        //return true;
        QTableWidget* tableWidget = new QTableWidget(4, 5);

        // Set headers for rows and columns
        QStringList rowHeaders;
        rowHeaders << "1" << "2" << "3" << "4";
        tableWidget->setVerticalHeaderLabels(rowHeaders);

        QStringList colHeaders;
        colHeaders << "Mon" << "Tue" << "Wed" << "Thu" << "Fri";
        tableWidget->setHorizontalHeaderLabels(colHeaders);

        // Set some example data in the cells
        for (int row = 0; row < 4; ++row) {
            for (int col = 0; col < 5; ++col) {
                QString itemText = QString::fromLocal8Bit(course_table[row][col].course_name)+QString::fromLocal8Bit(course_table[row][col].course_time);
                QTableWidgetItem* item = new QTableWidgetItem(itemText);
                tableWidget->setItem(row, col, item);
            }
        }

        // Resize the columns to fit the content
        tableWidget->resizeColumnsToContents();
        // Show the table
        return tableWidget;
    }
    ~table() {}
};

#endif // TABLE_H