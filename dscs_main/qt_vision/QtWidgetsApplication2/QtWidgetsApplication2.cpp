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
            //setParentΪNULL����ֹɾ��֮����治��ʧ
            if (child0->widget())
            {
                child0->widget()->setParent(NULL);
                delete child0->widget();//�ͷ�
            }

            delete child0;
        }
        QLabel* label1 = new QLabel(QString::fromLocal8Bit("ÿѧ��ѧ�����ƣ�") + QString::number(time_limit));
        ui.layout_label->addWidget(label1);
        if (term == 9)
            return;
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
            del_redundancy();
            setCheckBox();
            return;
        }
        else {
            QMessageBox::warning(this, "hint", "you can't generate directly now");
            del_redundancy();
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
    ////�ļ��Ի���
    //QString path = QFileDialog::getOpenFileName(this, "OPEN", "../", "CSV(*.csv)");//�����ļ�·�� �ļ���ʽ

    //if (path.isEmpty() == false) {//·����ȷ
    //    //�����ļ����� ���ҹ�������
    ////    QFile file(path);
    ////    QTextStream in(&file);
    ////    //in.setEncoding(QStringConverter::Utf8);
    ////    in.setAutoDetectUnicode(true);
    ////    bool isok = file.open(QIODevice::ReadOnly);//����ֻ��ģʽ���ļ�
    ////    if (isok) {//�򿪳ɹ�
    ////        //��ȡ�ļ�����
    ////        //1.һ���Զ�ȡ file.readAll()
    ////        //QByteArray array = file.readAll();//һ���Զ�ȡ
    ////        //ui.textEdit->setText(QString(array));//���ı�������ʾ

    ////        //2.�ж�ȡ 
    ////        in.readLine();
    ////        QString array;
    ////        while (in.atEnd()==false) {
    ////            array =in.readLine();  
    ////            //ui.textEdit->append(array);//���ı�������ʾ
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
    //    istringstream sin;         //�������ַ���line���뵽�ַ���istringstream��
    //    vector<string> words; //����һ���ַ�������
    //    string word;

    //    // ��ȡ������
    //    getline(csv_data, line);
    //    // ��ȡ����
    //    while (getline(csv_data, line))
    //    {
    //        sin.clear();
    //        sin.str(line);
    //        words.clear();
    //        while (getline(sin, word, ',')) //���ַ�����sin�е��ַ�����word�ַ����У��Զ���Ϊ�ָ���
    //        {
    //            words.push_back(word); //��ÿһ���е��������push
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
        QMessageBox msgBox;
        msgBox.setWindowTitle("confirm");
        msgBox.setText(QString::fromLocal8Bit("��ѡ��α���ŷ�ʽ  "));
        msgBox.addButton(QString::fromLocal8Bit("����ѡ��  "), QMessageBox::YesRole);
        msgBox.addButton(QString::fromLocal8Bit("ϵͳ����  "), QMessageBox::NoRole);
        int check = msgBox.exec();

       // QScrollArea* scrollArea;
        QWidget* contentWidget;
        string text1 = "ȷ��ѡ�� ";
        string text2 = "ȡ��ѡ�� ";
        QPushButton* add1 = new QPushButton(QString::fromLocal8Bit(text1));
        QPushButton* add2 = new QPushButton(QString::fromLocal8Bit(text2));
        add1->setStyleSheet("background-color:rgb(255,231,235)");
        add2->setStyleSheet("background-color:rgb(255,231,235)");
        QLabel* label1 = new QLabel(QString::fromLocal8Bit("ÿѧ��ѧ�����ƣ�") + QString::number(time_limit));
        ui.layout_button->addWidget(add1);
        ui.layout_button->addWidget(add2);
        ui.layout_label->addWidget(label1);
        //scrollArea = new QScrollArea(ui.widget);
        autoScroll *scrollauto = new autoScroll(ui.widget);
        //scrollArea->setWidgetResizable(true);
        //contentWidget = new QWidget(scrollArea);
        contentWidget=new QWidget(scrollauto);
        scrollauto->setWidget(contentWidget);
       // scrollArea->setWidget(contentWidget);

        layout = new QVBoxLayout(contentWidget);

        // ���ù�������Ϊ��ǰС�������Ӷ���
        //scrollArea->setParent(ui.widget);
        scrollauto->setParent(ui.widget);

        // �� contentWidget ��ӵ���ǰС�����Ĳ�����
       // mainLayout->addWidget(scrollArea);
        mainLayout->addWidget(scrollauto);
        if (check == 0) {
            for (int i = 0; i < aGraphl->VerticesNum(); i++)
                if (aGraphl->Indegree[i] == 0) {
                    mcourse[mycourses[i].name] = mycourses[i];
                    hours_count += mycourses[i].hours;
                }
            setCheckBox();
            connect(add1, &QPushButton::clicked, this, &QtWidgetsApplication2::manage_user);
		}
        else {
            for (int i = 0; i < mycourses.size(); i++)
                if (mycourses[i].sort == "Y") {
                    mcourse[mycourses[i].name] = mycourses[i];
                }
            hint_label = new QLabel(QString::fromLocal8Bit("��ѡ��ѡ�޿�: "));
            ui.layout_label->addWidget(hint_label);
            gridLayout = new QGridLayout;
            // ������ѡ��ť����ӵ����񲼾�
            map<string, course>::iterator iter;
            iter = mcourse.begin();
            int i = 0;
            while (iter != mcourse.end()) {
                QString box_text = QString::fromLocal8Bit(iter->first) + " (" + QString::number(iter->second.hours) + ")";
                QCheckBox* checkBox = new QCheckBox(box_text);
                gridLayout->addWidget(checkBox, i / 2, i % 2); // i / 2 �У�i % 2 ��
                checkboxes.push_back(checkBox);
                iter++;
                i++;
            }
            // �����񲼾���ӵ���ֱ����
            layout->addLayout(gridLayout);
            mcourse.clear();
            connect(add1, &QPushButton::clicked, this, &QtWidgetsApplication2::manage_com);
        }
        connect(add2, &QPushButton::clicked, this, &QtWidgetsApplication2::cancel);
        ui.to_manage->setDisabled(true);
    }
    else {
        QMessageBox::warning(this, "hint", "please read in first");
    }
}

void QtWidgetsApplication2::manage_user() {
    if (!scourse.empty() || !mcourse.empty()) {
        if (term > 8) {
            QMessageBox::warning(this, "hint", "you can't graduate with such pace, please choose again!");
            cancel();
            return;
        }
        vector<string> course_names;
        if (hours_count > time_limit) {
            int hours_temp = 0;
            for (QCheckBox* checkBox : checkboxes) {
                if (checkBox->isChecked()) {
                    QString optionText = checkBox->text();
                    QStringList stringList = optionText.split(" ");
                    optionText = stringList.first();
                    course_names.push_back(optionText.toLocal8Bit().constData());   //����QString->string 
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
                if (std::find(course_names.begin(), course_names.end(), iter->first) == course_names.end()) {  //û��ѡ��
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

        table_output(0, course_names);
        checkboxes.clear();

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
        del_redundancy();
        if (term == 9) {
            QMessageBox::information(this, "hint", "the course management is done");
            for (int i = 0; i < aGraphl->VerticesNum(); i++)
                indegree[i] = aGraphl->Indegree[i];
           QPushButton *table_button = new QPushButton(QString::fromLocal8Bit("�� �� �� ��  "));
           table_button->setStyleSheet("background-color:rgb(255,231,235)");
           ui.layout_generate->addWidget(table_button);
           connect(table_button, &QPushButton::clicked, this, &QtWidgetsApplication2::generate_table);
            return;
        }
        setCheckBox();
    }
    else {
        QMessageBox::information(this, "hint", "the course management is done");
        for (int i = 0; i < aGraphl->VerticesNum(); i++)
            indegree[i] = aGraphl->Indegree[i];
    }

}

void QtWidgetsApplication2::manage_com() {
    vector<string> course_names;
    for (QCheckBox* checkBox : checkboxes) {
        if (checkBox->isChecked()) {
            QString optionText = checkBox->text();
            QStringList stringList = optionText.split(" ");
            optionText = stringList.first();
            course_names.push_back(optionText.toLocal8Bit().constData());   //����QString->string 
        }
    }
    del_redundancy();
    for (int i = 0; i < aGraphl->VerticesNum(); i++)
        if (aGraphl->Indegree[i] == 0) {
            mcourse[mycourses[i].name] = mycourses[i];
        }
    while (!scourse.empty() || !mcourse.empty()) {
        map<string, course>::iterator iter;
        vector<course> compul;
        iter = mcourse.begin();
        while (iter != mcourse.end()) {
            int no;
            for (auto& pair : index) {
                if (pair.second == iter->second.no) {
                    no = pair.first;
                    break;
                }
            }
            if (8 - aGraphl->path[no] == term) {
                compul.push_back(iter->second);
                hours_count += iter->second.hours;
            }
            iter++;
        }
        for(int i=0;i<compul.size();i++)
			mcourse.erase(compul[i].name);

        vector<course> result, tem_result;
        int max = 0;

        findMaxCombination(mcourse, result, tem_result, max, 0, time_limit-hours_count, mcourse.begin());
        for (const course &c:result) {
            scourse.push(c);
            mcourse.erase(c.name);
        }
        for(const course &c:compul){
            scourse.push(c);
        }
        table_output(1, course_names);
        hours_count = 0;

        iter = mcourse.begin();
        string warning = "In term "+to_string(term);
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
            //cancel();
            return;
        }
        //del_redundancy();
        if (term == 9) {
            QMessageBox::information(this, "hint", "the course management is done");
            for (int i = 0; i < aGraphl->VerticesNum(); i++)
                indegree[i] = aGraphl->Indegree[i];
            QPushButton* table_button = new QPushButton(QString::fromLocal8Bit("�� �� �� ��  "));
            table_button->setStyleSheet("background-color:rgb(255,231,235)");
            ui.layout_generate->addWidget(table_button);
            connect(table_button, &QPushButton::clicked, this, &QtWidgetsApplication2::generate_table);
            return;
        }
    }
}

void QtWidgetsApplication2::cancel() {

    QLayoutItem* child;
    while ((child = ui.layout_button->takeAt(0)) != 0)
    {
        //setParentΪNULL����ֹɾ��֮����治��ʧ
        if (child->widget())
        {
            child->widget()->setParent(NULL);
            delete child->widget();//�ͷ�
        }

        delete child;
    }
    //���ui.widget�ϵ����пؼ�
    QLayoutItem* child1;
    while ((child1 = mainLayout->takeAt(0)) != 0)
    {
        //setParentΪNULL����ֹɾ��֮����治��ʧ
        if (child1->widget())
        {
            child1->widget()->setParent(NULL);
            delete child1->widget();//�ͷ�
        }

        delete child1;
    }
    QLayoutItem* child2;
    while ((child2 = ui.layout_label->takeAt(0)) != 0)
    {
        //setParentΪNULL����ֹɾ��֮����治��ʧ
        if (child2->widget())
        {
            child2->widget()->setParent(NULL);
            delete child2->widget();//�ͷ�
        }

        delete child2;
    }
    QLayoutItem* child3;
    while ((child3 = ui.layout_generate->takeAt(0)) != 0)
    {
        //setParentΪNULL����ֹɾ��֮����治��ʧ
        if (child3->widget())
        {
            child3->widget()->setParent(NULL);
            delete child3->widget();//�ͷ�
        }

        delete child3;
    }
    hours_count = 0;
    term = 1;
    mcourse.clear();
    checkboxes.clear();
    //tables.clear();
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
    check = QMessageBox::question(this, "confirm", QString::fromLocal8Bit("�Ƿ񱣴���� "), QMessageBox::Yes | QMessageBox::No);
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

void QtWidgetsApplication2::generate_table() {
    string filename = "output.csv";

    // ���ļ���
    ofstream outputFile(filename);

    if (outputFile.is_open()) {
        // ������ά���鲢������д���ļ�
        for (int i = 0; i < tables.size();i++) {
            outputFile<<"term "<<tables[i]->term << "\n";
            outputFile << ","<<"Mon" <<", " << "Tue" << ", " << "Wed" << ", " << "Thu" << ", " << "Fri"<<"\n";
            for (int j = 0; j < 4; j++) {
                outputFile << j + 1 << ",";
                for (int k = 0; k < 5; k++) {
                    // д��һ��ֵ�󣬼��϶��ŷָ�
                    outputFile << tables[i]->course_table[j][k].course_name << ",";
                }
                // ��ÿ��ĩβ�Ƴ�����Ķ��ţ���ӻ��з�
                outputFile.seekp(-1, std::ios_base::cur); // �Ƴ����һ������
                outputFile << "\n";
            }
        }
        // �ر��ļ���
        outputFile.close();
    }
    QMessageBox::information(this, "hint", "the table generate is done");
    cancel();
}

bool QtWidgetsApplication2::read_in(vector<course>& mycourses) {
    mycourses.clear();
    /*QString path = QFileDialog::getOpenFileName(this, "OPEN", "../", "CSV(*.csv)");//�����ļ�·�� �ļ���ʽ

    if (path.isEmpty() == false) {//·����ȷ
        ifstream csv_data(path.toStdString(), ios::in);
        string line;

        if (!csv_data.is_open())
        {
            cout << "Error: opening file fail" << endl;
            exit(1);
        }

        istringstream sin;         //�������ַ���line���뵽�ַ���istringstream��
        vector<string> words; //����һ���ַ�������
        string word;

        // ��ȡ������
        getline(csv_data, line);
        int count = 0;
        // ��ȡ����
        while (getline(csv_data, line))
        {
            sin.clear();
            sin.str(line);
            words.clear();
            while (getline(sin, word, ',')) //���ַ�����sin�е��ַ�����word�ַ����У��Զ���Ϊ�ָ���
            {
                words.push_back(word); //��ÿһ���е��������push
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
    return false;*/

    if (!OpenDatabase()) {
        return false;
    }
    QSqlQuery query;
    if (query.exec("SELECT * FROM[course_manage].[dbo].[Table_course]"))
    {
        int count = 0;
        istringstream sin;         //�������ַ���line���뵽�ַ���istringstream��
        while (query.next())
        {
            course tmp;
            tmp.no = query.value(0).toInt();
            tmp.name = query.value(1).toString().toLocal8Bit().constData();
            tmp.credits = query.value(2).toFloat();
            tmp.hours = query.value(3).toInt();
            tmp.sort = query.value(4).toString().toStdString();
            string pres = query.value(5).toString().toLocal8Bit().constData();
            if (!pres.empty()) {
                sin.clear();
                sin.str(pres);
                string word;
                while (getline(sin, word, ',')) //���ַ�����sin�е��ַ�����word�ַ����У��Զ���Ϊ�ָ���
                {
                    tmp.prerequisites.push_back(word); //��ÿһ���е��������push
                }
            }
            mycourses.push_back(tmp);
            index[count++] = tmp.no;
        }  
        return true;
    }
    return false;
}

bool QtWidgetsApplication2::OpenDatabase(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");   //���ݿ���������ΪSQL Server
    qDebug() << "ODBC driver" << db.isValid();
    db.setHostName("localhost");                        //ѡ�񱾵�������ͨ�ã���ò�д���ݿ�ʵ������
    db.setDatabaseName("dscs");                            //��������Դ���ƣ�ODBC����Դ���ƣ�
    db.setUserName("dscs");                               //��¼�û�
    db.setPassword("134298");                           //����

    if (!db.open())                                      //�����ݿ�ʧ��
    {
        qDebug() << db.lastError().text();
        QMessageBox::critical(0, QObject::tr("Database error"), db.lastError().text());
        return false;                                   //��ʧ��
    }
    return true;
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

        // ������ѡ��ť����ӵ����񲼾�
        map<string, course>::iterator iter;
        iter = mcourse.begin();
        int i = 0;
        while (iter != mcourse.end()) {
            QString box_text = QString::fromLocal8Bit(iter->first) + " (" + QString::number(iter->second.hours) + ")";
            QCheckBox* checkBox = new QCheckBox(box_text);
            gridLayout->addWidget(checkBox, i / 2, i % 2); // i / 2 �У�i % 2 ��
            checkboxes.push_back(checkBox);
            iter++;
            i++;
        }
        // �����񲼾���ӵ���ֱ����
        layout->addLayout(gridLayout);
    }
    else {
        hint_label = new QLabel("the table can be generated directly");
        layout->addWidget(hint_label);
    }
}

void QtWidgetsApplication2::del_redundancy() {
    if (gridLayout) {
        // ��ȡ�����е��ӿؼ�
        QLayoutItem* child0;
        while ((child0 = gridLayout->takeAt(0)) != 0) {
            //setParentΪNULL����ֹɾ��֮����治��ʧ
            if (child0->widget())
            {
                child0->widget()->setParent(NULL);
                delete child0->widget();//�ͷ�
            }

            delete child0;
        }
        // ���²���
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

void QtWidgetsApplication2::table_output(int mode, vector<string> course_names) {
    //table* t = new table(term);
    dropTable *t1= new dropTable(mycourses, term, time_limit);
    while (!scourse.empty()) {
        course V = scourse.top();
        scourse.pop();                     //һ���������
        //t->set_table(V);
        t1->set_table(V);
        int no;
        for (auto& pair : index) {
            if (pair.second == V.no) {
                no = pair.first;
                break;
            }
        }
        //aGraphl->Mark[no] = VISITED;
        for (Edge e = aGraphl->FirstEdge(no); aGraphl->IsEdge(e); e = aGraphl->NextEdge(e)) {
            indegree[aGraphl->ToVertex(e)]--;  //������֮���ڵĶ������-1
            if (indegree[aGraphl->ToVertex(e)] == 0 ) {
                if (!mode) {
                    if (mycourses[aGraphl->ToVertex(e)].sort != "Y") {
                        mcourse[mycourses[aGraphl->ToVertex(e)].name] = mycourses[aGraphl->ToVertex(e)];
                        //if(mycourses[aGraphl->ToVertex(e)].sort != "ѡ�޿� ")
                        hours_count += mycourses[aGraphl->ToVertex(e)].hours;
                    }
                }
                else {
                    if (std::find(course_names.begin(), course_names.end(), mycourses[aGraphl->ToVertex(e)].name) != course_names.end() || mycourses[aGraphl->ToVertex(e)].sort != "Y") {
                        mcourse[mycourses[aGraphl->ToVertex(e)].name] = mycourses[aGraphl->ToVertex(e)];
                    }
                }
            }
        }
    }
    tables.push_back(t1);
    QLabel* spaceLabel = new QLabel(" ");
    layout->addWidget(spaceLabel);
    QString text = QString::fromLocal8Bit("�� ") + QString::number(term) + QString::fromLocal8Bit("ѧ�� ");
    QLabel* label = new QLabel(text);
    layout->addWidget(label);
    //QTableWidget* ta = t->show_table();
    //ta->setMinimumSize(QSize(920, 150));
    t1->set_item();
    //layout->addWidget(ta);
    layout->addWidget(t1->ltime);
    layout->addWidget(t1);
    for (int i = 0; i < 3; i++) {
        QLabel* spaceLabel = new QLabel(" ");
        layout->addWidget(spaceLabel);
    }
    term++;
}

void QtWidgetsApplication2::findMaxCombination(map<string, course>& data, vector<course>& result, vector<course>& tem_result, int& max, int current, int limit, map<string, course>::iterator it) {
    if (it == data.end()) {
        if (current < limit && tem_result.size() > max) {
            max = tem_result.size();
            result = tem_result;
        }
        return;
    }

    findMaxCombination(data, result, tem_result, max, current, limit, next(it));  

    if (current + it->second.hours < limit) {
        tem_result.push_back(it->second); 
        findMaxCombination(data, result, tem_result, max, current + it->second.hours, limit, next(it));
        tem_result.pop_back();
    }
}