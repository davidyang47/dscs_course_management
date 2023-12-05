#ifndef DROPTABLE_H
#define DROPTABLE_H

#include <QtWidgets>
#include "course.h"
#include "Graph.h"
#include "Graphl.h"
#include <QFile>
#include <QTextStream>
#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

struct arrange {
    string course_name;
    string course_time;
};

class dropTable : public QTableWidget
{
    Q_OBJECT
public:
    dropTable(QWidget* parent = nullptr) : QTableWidget(parent) {
        setAcceptDrops(true);
        setDragEnabled(true);
    }
    dropTable(const vector<course>& mycourses, const int term, const int time_limit, QWidget* parent = nullptr)
        :QTableWidget(parent), mycourses(mycourses), term(term), time_limit(time_limit) {
        setAcceptDrops(true);
        setDragEnabled(true);
        setRowCount(4);
        setColumnCount(5);
        QStringList rowHeaders;
        rowHeaders << "1" << "2" << "3" << "4";
        setVerticalHeaderLabels(rowHeaders);
        QStringList colHeaders;
        colHeaders << "Mon" << "Tue" << "Wed" << "Thu" << "Fri";
        setHorizontalHeaderLabels(colHeaders);
        courses.clear();
        ltime = nullptr;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 5; j++) {
                course_table[i][j].course_name = "";
                course_table[i][j].course_time = "";
            }
        }
        time_used = 0;
    }
    dropTable(const dropTable& other) {
        // 复制基类内容
        term = other.term;
        mycourses = other.mycourses;
        courses = other.courses;
        time_used = other.time_used;
        // 复制成员变量
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 5; j++) {
                course_table[i][j] = other.course_table[i][j];
            }
        }
    }
    bool set_table(course c) {
        courses.push_back(c);
        vector<int> time;
        time.clear();
        int h = c.hours;
        time_used += c.hours;
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
                    for (int k = -1; k < 2; k++) {
                        it = std::find(time.begin(), time.end(), j + k);
                        if (it != time.end())
                            break;
                    }
                else
                    it = std::find(time.begin(), time.end(), j);
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
    void set_item() {
        // Set some example data in the cells
        for (int row = 0; row < 4; ++row) {
            for (int col = 0; col < 5; ++col) {
                QString itemText = QString::fromLocal8Bit(course_table[row][col].course_name) + " " + QString::fromLocal8Bit(course_table[row][col].course_time);
                QTableWidgetItem* item = new QTableWidgetItem(itemText);
                setItem(row, col, item);
            }
        }
        if (!ltime) {
            QString content = QString::fromLocal8Bit("当前课时数为: ") + QString::number(time_used);
            ltime = new QLabel(content);
        }
        else {
            QString content = QString::fromLocal8Bit("当前课时数为: ") + QString::number(time_used);
            ltime->setText(content);
        }
        // Resize the columns to fit the content
        resizeColumnsToContents();
        setMinimumSize(QSize(920, 150));
    }
    void del_item(string name) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 5; j++) {
                if (course_table[i][j].course_name == name) {
                    course_table[i][j].course_name = "";
                    course_table[i][j].course_time = "";
                }
            }
        }
        for (int i = 0; i < mycourses.size(); i++) {
            if (mycourses[i].name == name) {
                vector<course>::iterator it = std::find(courses.begin(), courses.end(), mycourses[i]);
                courses.erase(it);
                time_used -= mycourses[i].hours;
                break;
            }
        }
        clearContents();
        set_item();
        QString content = QString::fromLocal8Bit("当前课时数为: ") + QString::number(time_used);
        ltime->setText(content);
    }
    int term;
    int time_used;
    vector<course> courses;
    arrange course_table[4][5];
    QLabel* ltime;
signals:
    void cascade_chg(course course_name, int from, int to);

protected:
    void mousePressEvent(QMouseEvent* event) {
        if (event->button() == Qt::LeftButton)
            startPos = event->pos();
        QTableWidget::mousePressEvent(event);
        connect(this, SIGNAL(itemSelectionChanged()), this, SLOT(ChangedItem()));
    }

    void mouseMoveEvent(QMouseEvent* event) {
        if (event->buttons() & Qt::LeftButton) {
            int distance = (event->pos() - startPos).manhattanLength();
            if (distance >= QApplication::startDragDistance() && currentRow() >= 0 && currentColumn() >= 0) {
                performDrag();
            }
        }
        QTableWidget::mouseMoveEvent(event);
    }

    void dragEnterEvent(QDragEnterEvent* event) {
        dropTable* source =
            qobject_cast<dropTable*>(event->source());
        if (source /* && source != this*/) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }
    }

    void dragMoveEvent(QDragMoveEvent* event) {
        dropTable* source =
            qobject_cast<dropTable*>(event->source());
        if (source /* && source != this*/) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }
    }

    void dropEvent(QDropEvent* event) {
        dropTable* source =
            qobject_cast<dropTable*>(event->source());
        if (source /* && source != this*/) {
            if (source != this) {
                QString content = "";
                bool judge = false;
                QString str = event->mimeData()->text();
                QStringList list = str.split(" ");
                str = list.first();
                string name = str.toLocal8Bit().constData();
                QMessageBox msgBox;
                msgBox.setWindowTitle("confirm");
                msgBox.setText(QString::fromLocal8Bit("请选择方式  "));
                msgBox.addButton(QString::fromLocal8Bit("单独  "), QMessageBox::YesRole);
                msgBox.addButton(QString::fromLocal8Bit("级联  "), QMessageBox::NoRole);
                int check = msgBox.exec();
                if (check == 0) {
                    if (term < source->term) {
                        for (int i = 0; i < mycourses.size(); i++) {
                            if (mycourses[i].name == name) {
                                for (int j = 0; j < mycourses[i].prerequisites.size(); j++) {
                                    for (int k = 0; k < courses.size(); k++) {
                                        if (courses[k].name == mycourses[i].prerequisites[j]) {
                                            content += QString::fromLocal8Bit("该学期有先修课: ") + QString::fromLocal8Bit(mycourses[i].prerequisites[j]) + "\n";
                                            judge = true;
                                        }
                                    }
                                }
                                if (judge) {
                                    QMessageBox::warning(this, "failed", content);
                                    //judge = false;
                                    return;
                                }
                            }
                        }
                    }
                    else {
                        vector<string>::iterator it;
                        for (int i = 0; i < courses.size(); i++) {
                            it = std::find(courses[i].prerequisites.begin(), courses[i].prerequisites.end(), name);
                            if (it != courses[i].prerequisites.end()) {
                                content += QString::fromLocal8Bit("该学期有后继课: ") + QString::fromLocal8Bit(courses[i].name) + "\n";
                                judge = true;
                            }
                        }
                        if (judge) {
                            QMessageBox::warning(this, "failed", content);
                            //judge = false;
                            return;
                        }
                    }
                    for (int i = 0; i < mycourses.size(); i++) {
                        if (mycourses[i].name == name) {
                            if (time_used + mycourses[i].hours > time_limit) {
                                content = QString::fromLocal8Bit("需要学时: ") + QString::number(mycourses[i].hours) + QString::fromLocal8Bit("，剩余可用学时: ") + QString::number(time_limit - time_used);
                                QMessageBox::warning(this, "failed", content);
                                return;
                            }
                            set_table(mycourses[i]);
                            break;
                        }
                    }
                    source->del_item(name);
                    clearContents();
                    set_item();
                    //content = QString::fromLocal8Bit("当前课时数为: ") + QString::number(time_used);
                    //ltime->setText(content);
                }
                else {
                    for (int i = 0; i < mycourses.size(); i++) {
                        if (mycourses[i].name == name) {
                            emit cascade_chg(mycourses[i], source->term, term);
                            return;
                        }
                    }
                }
            }
            else {
                if (course_table[currentRow()][currentColumn()].course_name == "") {
                    course_table[currentRow()][currentColumn()].course_name = event->mimeData()->text().toLocal8Bit().constData();
                    course_table[currentRow()][currentColumn()].course_time = "";
                    clearContents();
                    set_item();
                }
            }
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }
    }

private slots:
    void ChangedItem() {
        qDebug() << "itemSelectionChanged!";
    }
private:
    void performDrag() {
        QMimeData* mimeData = new QMimeData;
        mimeData->setText(item(currentRow(), currentColumn())->text());

        QDrag* drag = new QDrag(this);
        drag->setMimeData(mimeData);
        if (drag->exec(Qt::MoveAction) == Qt::MoveAction) {
            qDebug() << "Success!";
        }
    }

    QPoint startPos;
    //Graphl aGraphl;
    vector<course> mycourses;
    int time_limit;
};

#endif // DROPTABLE_H