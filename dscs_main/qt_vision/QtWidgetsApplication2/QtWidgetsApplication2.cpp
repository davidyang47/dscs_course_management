#include "QtWidgetsApplication2.h"
#include <bits/stdc++.h>
#include <QtWidgets>
#include <QFile>
#include <QTextStream>
using namespace std;
int maxn = -1;

QtWidgetsApplication2::QtWidgetsApplication2(const int time_limit, QWidget *parent)
    : QMainWindow(parent), time_limit(time_limit)
{
    ui.setupUi(this);
    mainLayout = new QVBoxLayout(ui.widget);
    aGraphl = nullptr;
    d=nullptr;
    gridLayout = nullptr;
    hint_label = nullptr;
    hours_count = 0;
    term = 1;
    connect(ui.read_in, &QPushButton::clicked, this, &QtWidgetsApplication2::rc);
    connect(ui.to_show, &QPushButton::clicked, this, &QtWidgetsApplication2::wc);
    connect(ui.to_manage, &QPushButton::clicked, this, &QtWidgetsApplication2::sh);
    connect(ui.to_exit, &QPushButton::clicked, this, &QtWidgetsApplication2::shut);
    connect(ui.back_to, &QPushButton::clicked, this, &QtWidgetsApplication2::back_to_login);
}

QtWidgetsApplication2::~QtWidgetsApplication2()
{}

void QtWidgetsApplication2::set_time_limit(const int t) {
	time_limit = t;
    QLayoutItem* child0;
    if (ui.layout_label->takeAt(0) != 0) {
        while ((child0 = ui.layout_label->takeAt(0)) != 0)
        {
            //setParent为NULL，防止删除之后界面不消失
            if (child0->widget())
            {
                child0->widget()->setParent(NULL);
                delete child0->widget();//释放
            }

            delete child0;
        }
        QLabel* label1 = new QLabel(QString::fromLocal8Bit("每学期学分限制：") + QString::number(time_limit));
        ui.layout_label->addWidget(label1);
        map<string, course>::iterator iter;
        iter = mcourse.begin();
        string warning = "In next term:";
        warning += "\n";
        int course_time = 0;
        int total_time = 0;
        while (iter != mcourse.end()) {
            int no;
            for (auto& pair : index) {
                if (pair.second == iter->second.no) {
                    no = pair.first;
                    break;
                }
            }
            if (8 - aGraphl->path[no] == term) {
                warning += iter->first + " has to be chosen" + "\n";
                course_time += iter->second.hours;
            }
            total_time += iter->second.hours;
            iter++;
        }
        if (course_time > time_limit) {
            warning += "but you can't choose them all, so you can't graduate with such pace, please reset or choose again!";
            QMessageBox::warning(this, "hint", QString::fromLocal8Bit(warning));
            return;
        }
        if (total_time < time_limit) {
            QMessageBox::warning(this, "hint", "you can choose all the course with such limit");
            return;
        }
        else {
            setCheckBox();
        }
    }
}

void QtWidgetsApplication2::rc()
{
    if(read_in(mycourses))
	{
        graph_set(aGraphl, mycourses);
        //aGraphl = new Graphl(mycourses.size());
        //for (int i = 0; i < mycourses.size(); i++) {
        //    for (int j = 0; j < mycourses[i].prerequisites.size(); j++) {
        //        for (int k = 0; k < mycourses.size(); k++) {
        //            if (mycourses[k].name == mycourses[i].prerequisites[j]) {
        //                aGraphl->setEdge(k, i, 1);
        //            }
        //        }
        //    }
        //}
        for (int i = 0; i < aGraphl->VerticesNum(); i++) {
            calpath(*aGraphl, i, 0);
            aGraphl->path[i] = maxn;
            maxn = -1;
        }
        indegree = new int[aGraphl->VerticesNum()];
        for (int i = 0; i < aGraphl->VerticesNum(); i++)
            indegree[i] = aGraphl->Indegree[i];
        ui.to_show->setDisabled(false);
		QMessageBox::information(this, "hint", "succeed", QMessageBox::Ok);
	}
	else
	{
        ui.to_show->setDisabled(false);
		QMessageBox::warning(this, "hint", "failed");
	}
    ////文件对话框
    //QString path = QFileDialog::getOpenFileName(this, "OPEN", "../", "CSV(*.csv)");//设置文件路径 文件格式

    //if (path.isEmpty() == false) {//路径正确
    //    //创建文件对象 并且关联起来
    ////    QFile file(path);
    ////    QTextStream in(&file);
    ////    //in.setEncoding(QStringConverter::Utf8);
    ////    in.setAutoDetectUnicode(true);
    ////    bool isok = file.open(QIODevice::ReadOnly);//利用只读模式打开文件
    ////    if (isok) {//打开成功
    ////        //读取文件内容
    ////        //1.一次性读取 file.readAll()
    ////        //QByteArray array = file.readAll();//一次性读取
    ////        //ui.textEdit->setText(QString(array));//在文本区域显示

    ////        //2.行读取 
    ////        in.readLine();
    ////        QString array;
    ////        while (in.atEnd()==false) {
    ////            array =in.readLine();  
    ////            //ui.textEdit->append(array);//在文本区域显示
    ////           // QDebug(array);
    ////        }
    ////    }
    ////    file.close();
    ////}
    //    ifstream csv_data(path.toStdString(), ios::in);
    //    string line;

    //    if (!csv_data.is_open())
    //    {
    //        cout << "Error: opening file fail" << endl;
    //        exit(1);
    //    }
    //    istringstream sin;         //将整行字符串line读入到字符串istringstream中
    //    vector<string> words; //声明一个字符串向量
    //    string word;

    //    // 读取标题行
    //    getline(csv_data, line);
    //    // 读取数据
    //    while (getline(csv_data, line))
    //    {
    //        sin.clear();
    //        sin.str(line);
    //        words.clear();
    //        while (getline(sin, word, ',')) //将字符串流sin中的字符读到word字符串中，以逗号为分隔符
    //        {
    //            words.push_back(word); //将每一格中的数据逐个push
    //        }
    //        course tmp;
    //        tmp.no = stoi(words[0]);
    //        tmp.name = words[1];
    //        tmp.credits = stoi(words[2]);
    //        tmp.hours = stoi(words[3]);
    //        tmp.sort = words[4];
    //        for (int i = 5; i < words.size(); i++)
    //        {
    //            tmp.prerequisites.push_back(words[i]);
    //        }
    //        mycourses.push_back(tmp);
    //    }
    //    csv_data.close();
    //}
}

void QtWidgetsApplication2::wc()
{
    if (!mycourses.empty()) {
        d = new Drawing(*aGraphl, mycourses, index);
        d->show();
        ui.to_show->setDisabled(true);
    }
	else {
		QMessageBox::warning(this, "hint", "please read in first");
	}
}

void QtWidgetsApplication2::sh(){
    if (!mycourses.empty()) {
        //table* t = new table();
        //ui.verticalLayout->addWidget(t->show_table());
        QScrollArea* scrollArea;
        QWidget* contentWidget;
        string text1 = "确认选课 ";
        string text2 = "取消选课 ";
        QPushButton* add1 = new QPushButton(QString::fromLocal8Bit(text1));
        QPushButton* add2 = new QPushButton(QString::fromLocal8Bit(text2));
        add1->setStyleSheet("background-color:rgb(255,231,235)");
        add2->setStyleSheet("background-color:rgb(255,231,235)");
        QLabel* label1 = new QLabel(QString::fromLocal8Bit("每学期学分限制：") + QString::number(time_limit));
        ui.layout_button->addWidget(add1);
        ui.layout_button->addWidget(add2);
        ui.layout_label->addWidget(label1);
        scrollArea = new QScrollArea(ui.widget);
        scrollArea->setWidgetResizable(true);
        contentWidget = new QWidget(scrollArea);
        scrollArea->setWidget(contentWidget);

        layout = new QVBoxLayout(contentWidget);

        // 设置滚动区域为当前小部件的子对象
        scrollArea->setParent(ui.widget);

        // 将 contentWidget 添加到当前小部件的布局中
        mainLayout->addWidget(scrollArea);

        //for (int i = 0; i < aGraphl->VerticesNum(); i++)
        //    aGraphl->Mark[i] = UNVISITED;
        for (int i = 0; i < aGraphl->VerticesNum(); i++)
            if (aGraphl->Indegree[i] == 0) {
                mcourse[mycourses[i].name] = mycourses[i];
                hours_count += mycourses[i].hours;
            }
        setCheckBox();
        connect(add1, &QPushButton::clicked, this, &QtWidgetsApplication2::manage);
        connect(add2, &QPushButton::clicked, this, &QtWidgetsApplication2::cancel);
        ui.to_manage->setDisabled(true);
    }
    else {
        QMessageBox::warning(this, "hint", "please read in first");
    }
}

void QtWidgetsApplication2::manage() {
    if (!scourse.empty() || !mcourse.empty()) {
        if (term > 8) {
            QMessageBox::warning(this, "hint", "you can't graduate with such pace, please choose again!");
            cancel();
            return;
        }
        if (hours_count > time_limit) {
            vector<string> course_names;
            int hours_temp = 0;
            for (QCheckBox* checkBox : checkboxes) {
                if (checkBox->isChecked()) {
                    QString optionText = checkBox->text();
                    QStringList stringList = optionText.split(" ");
                    optionText = stringList.first();
                    course_names.push_back(optionText.toLocal8Bit().constData());   //中文QString->string 
                    hours_temp += mcourse[optionText.toLocal8Bit().constData()].hours;
                }
            }
            if (hours_temp > time_limit) {
                QString message = "hours exceed. Value of hours_temp: " + QString::number(hours_temp);
                QMessageBox::warning(this, "hint", message);
                return;
            }
            map<string, course>::iterator iter;
            iter = mcourse.begin();
            string warning = "";
            while (iter != mcourse.end()) {
                if (std::find(course_names.begin(), course_names.end(), iter->first) == course_names.end()) {  //没被选中
                    int no;
                    for (auto& pair : index) {
                        if (pair.second == iter->second.no) {
                            no = pair.first;
                            break;
                        }
                    }
                    if (8 - aGraphl->path[no] == term) {
                        warning += iter->first + " has to be chosen this term or you can't graduate on time" + "\n";
                    }
                }
                iter++;
            }
            if (warning != "") {
                QMessageBox::warning(this, "hint", QString::fromLocal8Bit(warning));
                return;
            }
            hours_count -= hours_temp;
            for (int i = 0; i < course_names.size(); i++) {
                scourse.push(mcourse[course_names[i]]);
                mcourse.erase(course_names[i]);
            }
        }
        else {
            map<string, course>::iterator iter;
            iter = mcourse.begin();
            while (iter != mcourse.end()) {
                scourse.push(iter->second);
                iter++;
            }
            mcourse.clear();
            hours_count = 0;
        }
        table* t = new table(term);
        while (!scourse.empty()) {
            course V = scourse.top();
            scourse.pop();                     //一个顶点出队
            t->set_table(V);
            //Visit(G, V);
            /*   int no = V.no - 1;
            G.Mark[no] = VISITED;*/
            int no;
            for (auto& pair : index) {
                if (pair.second == V.no) {
                    no = pair.first;
                    break;
                }
            }
            //aGraphl->Mark[no] = VISITED;
            for (Edge e = aGraphl->FirstEdge(no); aGraphl->IsEdge(e); e = aGraphl->NextEdge(e)) {
                indegree[aGraphl->ToVertex(e)]--;  //所有与之相邻的顶点入度-1
                if (indegree[aGraphl->ToVertex(e)] == 0 && mycourses[aGraphl->ToVertex(e)].sort != "Y") {

                    mcourse[mycourses[aGraphl->ToVertex(e)].name] = mycourses[aGraphl->ToVertex(e)];
                    //if(mycourses[aGraphl->ToVertex(e)].sort != "选修课 ")
                    hours_count += mycourses[aGraphl->ToVertex(e)].hours;
                }
            }
        }
        tables.push_back(*t);
        QLabel* spaceLabel = new QLabel(" ");
        layout->addWidget(spaceLabel);
        QString text = QString::fromLocal8Bit("第 ") + QString::number(term) + QString::fromLocal8Bit("学期 ");
        QLabel* label = new QLabel(text);
        layout->addWidget(label);
        QTableWidget* ta = t->show_table();
        ta->setMinimumSize(QSize(920, 150));
        layout->addWidget(ta);
        for (int i = 0; i < 3; i++) {
            QLabel* spaceLabel = new QLabel(" ");
            layout->addWidget(spaceLabel);
        }
        checkboxes.clear();
        term++;
        map<string, course>::iterator iter;
        iter = mcourse.begin();
        string warning = "In next term:";
        warning += "\n";
        int course_time = 0;
        while (iter != mcourse.end()) {
            int no;
            for (auto& pair : index) {
                if (pair.second == iter->second.no) {
                    no = pair.first;
                    break;
                }
            }
            if (8 - aGraphl->path[no] == term) {
                warning += iter->first + " has to be chosen" + "\n";
                course_time += iter->second.hours;
            }
            iter++;
        }
        if (course_time > time_limit) {
            warning += "but you can't choose them all, so you can't graduate with such pace, please choose again!";
            QMessageBox::warning(this, "hint", QString::fromLocal8Bit(warning));
            cancel();
            return;
        }
        if (term == 9) {
            QMessageBox::information(this, "hint", "the course management is done");
            for (int i = 0; i < aGraphl->VerticesNum(); i++)
                indegree[i] = aGraphl->Indegree[i];
            return;
        }
        del_redundancy();
        setCheckBox();
    }
    else {
        QMessageBox::information(this, "hint", "the course management is done");
        for (int i = 0; i < aGraphl->VerticesNum(); i++)
            indegree[i] = aGraphl->Indegree[i];
    }

}

void QtWidgetsApplication2::cancel() {

    QLayoutItem* child;
    while ((child = ui.layout_button->takeAt(0)) != 0)
    {
        //setParent为NULL，防止删除之后界面不消失
        if (child->widget())
        {
            child->widget()->setParent(NULL);
            delete child->widget();//释放
        }

        delete child;
    }
    //清空ui.widget上的所有控件
    QLayoutItem* child1;
    while ((child1 = mainLayout->takeAt(0)) != 0)
    {
		//setParent为NULL，防止删除之后界面不消失
        if (child1->widget())
        {
			child1->widget()->setParent(NULL);
			delete child1->widget();//释放
		}

		delete child1;
	}
    QLayoutItem* child2;
    while ((child2 = ui.layout_label->takeAt(0)) != 0)
    {
        //setParent为NULL，防止删除之后界面不消失
        if (child2->widget())
        {
            child2->widget()->setParent(NULL);
            delete child2->widget();//释放
        }

        delete child2;
    }
    hours_count = 0;
	term = 1;
	mcourse.clear();
    checkboxes.clear();
    tables.clear();
	scourse = stack<course>();
    for (int i = 0; i < aGraphl->VerticesNum(); i++)
        indegree[i] = aGraphl->Indegree[i];
	ui.to_manage->setDisabled(false);
}

void QtWidgetsApplication2::shut() {
    if(d)
        d->close();
	this->close();
}

void QtWidgetsApplication2::back_to_login() {
    QMessageBox::StandardButton check;
    check = QMessageBox::question(this, "confirm", QString::fromLocal8Bit("是否保存进度 "), QMessageBox::Yes | QMessageBox::No);
    if (check == QMessageBox::No) {
        if (!mycourses.empty()) {
            cancel();
            mycourses.clear();
        }
    }
    if (d)
        d->close();
    ui.to_show->setDisabled(false);
    emit back();
}

bool QtWidgetsApplication2::read_in(vector<course>& mycourses) {
    mycourses.clear();
    QString path = QFileDialog::getOpenFileName(this, "OPEN", "../", "CSV(*.csv)");//设置文件路径 文件格式

    if (path.isEmpty() == false) {//路径正确
        ifstream csv_data(path.toStdString(), ios::in);
        string line;

        if (!csv_data.is_open())
        {
            cout << "Error: opening file fail" << endl;
            exit(1);
        }

        istringstream sin;         //将整行字符串line读入到字符串istringstream中
        vector<string> words; //声明一个字符串向量
        string word;

        // 读取标题行
        getline(csv_data, line);
        int count = 0;
        // 读取数据
        while (getline(csv_data, line))
        {
            sin.clear();
            sin.str(line);
            words.clear();
            while (getline(sin, word, ',')) //将字符串流sin中的字符读到word字符串中，以逗号为分隔符
            {
                words.push_back(word); //将每一格中的数据逐个push
            }
            course tmp;
            tmp.no = stoi(words[0]);
            tmp.name = words[1];
            tmp.credits = stoi(words[2]);
            tmp.hours = stoi(words[3]);
            tmp.sort = words[4];
            for (int i = 5; i < words.size(); i++)
            {
                tmp.prerequisites.push_back(words[i]);
            }
            mycourses.push_back(tmp);
            index[count++] = tmp.no;
        }
        csv_data.close();
        return true;
    }
    return false;
}

bool QtWidgetsApplication2::graph_set(Graphl*& G, vector<course>& mycourses) {
    G = new Graphl(mycourses.size());
    for (int i = 0; i < mycourses.size(); i++) {
        for (int j = 0; j < mycourses[i].prerequisites.size(); j++) {
            for (int k = 0; k < mycourses.size(); k++) {
                if (mycourses[k].name == mycourses[i].prerequisites[j]) {
                    G->setEdge(k, i, 1);
                }
            }
        }
    }
    return true;
}

void QtWidgetsApplication2::calpath(Graph& G, int oneVertex, int length) {
    if (G.Outdegree[oneVertex] == 0) {
        maxn = max(length, maxn);
        return;
    }
    for (int i = 0; i < G.Outdegree[oneVertex]; i++) {
        Edge e = G.GetEdge(oneVertex, i + 1);
        calpath(G, e.to, length + 1);
    }
}

void QtWidgetsApplication2::setCheckBox() {
    if (hours_count > time_limit) {
        gridLayout = new QGridLayout;

        // 创建多选按钮并添加到网格布局
        map<string, course>::iterator iter;
        iter = mcourse.begin();
        int i = 0;
        while (iter != mcourse.end()) {
            QString box_text = QString::fromLocal8Bit(iter->first) + " (" + QString::number(iter->second.hours) + ")";
            QCheckBox* checkBox = new QCheckBox(box_text);
            gridLayout->addWidget(checkBox, i / 2, i % 2); // i / 2 行，i % 2 列
            checkboxes.push_back(checkBox);
            iter++;
            i++;
        }
        // 将网格布局添加到垂直布局
        layout->addLayout(gridLayout);
    }
    else {
        hint_label = new QLabel("the table can be generated directly");
        layout->addWidget(hint_label);
    }
}

void QtWidgetsApplication2::del_redundancy() {
    if (gridLayout) {
        // 获取布局中的子控件
        QLayoutItem* child0;
        while ((child0 = gridLayout->takeAt(0)) != 0) {
            //setParent为NULL，防止删除之后界面不消失
            if (child0->widget())
            {
                child0->widget()->setParent(NULL);
                delete child0->widget();//释放
            }

            delete child0;
        }
        // 重新布局
        delete gridLayout;
        gridLayout = nullptr;
    }
    if (hint_label) {
        hint_label->setParent(NULL);
        delete hint_label;
        hint_label = nullptr;
    }
    layout->update();
}