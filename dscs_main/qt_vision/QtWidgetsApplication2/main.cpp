#pragma once

#include <bits/stdc++.h>
#include "QtWidgetsApplication2.h"
#include "teacher_portal.h"
//#include "LoginWindow.h"
//#include "RegisterWindow.h"
#include <QtWidgets>
#include <QFile>
#include <QTextStream>

using namespace std;
class LoginWindow; // 前置声明

// 注册界面类
class RegisterWindow : public QWidget {
    Q_OBJECT

public:
    RegisterWindow(QWidget* parent = nullptr) : QWidget(parent) {
        setupUI();
        loadUsers();
        setInitialWindowSize(); // 设置初始窗口大小
    }

signals:
    void registerSuccess(); // 自定义信号，用于在注册成功后通知登录界面

private slots:
    void handleRegisterButton() {
        QString username = usernameLineEdit->text();
        QString password = passwordLineEdit->text();

        if (username.isEmpty() || password.isEmpty()) {
            QMessageBox::warning(this, "Registration Failed", "Please enter both username and password.");
            return;
        }

        if (registerUser(username, password)) {
            QMessageBox::information(this, "Registration Successful", "Account created for " + username + ".");
            emit registerSuccess(); // 发送注册成功信号
        }
        else {
            QMessageBox::warning(this, "Registration Failed", "Username already exists.");
            emit registerSuccess(); // 发送注册成功信号
        }
    }
    void handleSwitchToLogin() {
        emit registerSuccess();
    }

private:
    void setupUI() {
        QWidget* widget = new QWidget(this);
        QWidget* wtitle = new QWidget(this);
        QVBoxLayout* layout = new QVBoxLayout(widget);
        QVBoxLayout* ltitle = new QVBoxLayout(wtitle);
        wtitle->setGeometry(QRect(200, 50, 600, 50));
        QLabel* title = new QLabel(QString::fromLocal8Bit("课  程  编  排  系  统 "), wtitle);
        title->setStyleSheet("font-size: 34px; font - family: SimSun; color: rgb(170, 45, 45);"); // 更改大小和颜色
        title->setAlignment(Qt::AlignCenter); // 设置文本居中对齐
        ltitle->addWidget(title);
        widget->setGeometry(QRect(300, 150, 400, 200));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 231, 235);"));

        usernameLineEdit = new QLineEdit(this);
        passwordLineEdit = new QLineEdit(this);
        passwordLineEdit->setEchoMode(QLineEdit::Password);
        group = new QButtonGroup(this);

        QPushButton* registerButton = new QPushButton("Register", this);
        QPushButton* switchToLoginButton = new QPushButton("Back to Login", this);
        string a = "教师";
        string b = "学生";
        QRadioButton* teacher = new QRadioButton(QString::fromLocal8Bit(a.c_str()), this);
        QRadioButton* student = new QRadioButton(QString::fromLocal8Bit(b.c_str()), this);

        group->addButton(teacher);
        group->addButton(student);
        group->setId(teacher, 1);
        group->setId(student, 2);

        QHBoxLayout* layout1 = new QHBoxLayout;
        layout1->addWidget(teacher);
        layout1->addWidget(student);

        layout->addWidget(new QLabel("Username:", this));
        layout->addWidget(usernameLineEdit);
        layout->addWidget(new QLabel("Password:", this));
        layout->addWidget(passwordLineEdit);
        layout->addLayout(layout1);
        layout->addWidget(registerButton);
        layout->addWidget(switchToLoginButton);

        QPixmap background("bg1.jpg");
        QPalette palette;
        palette.setBrush(this->backgroundRole(), QBrush(background));
        this->setPalette(palette);

        // setLayout(layout);

        connect(registerButton, &QPushButton::clicked, this, &RegisterWindow::handleRegisterButton);
        connect(switchToLoginButton, &QPushButton::clicked, this, &RegisterWindow::handleSwitchToLogin);
    }
    bool registerUser(const QString& username, const QString& password) {
        if (users.contains(username)) {
            return false; // Username already exists
        }
        users[username] = password;
        QString role = QString::fromStdString(to_string(group->checkedId()));
        //QFile file("users.txt");
        //if (file.open(QIODevice::Append | QIODevice::Text)) {
        //    QTextStream out(&file);
        //    out << username << " " << password <<" "<<id<<"\n";
        //    file.close();
        //    return true;
        //}
        QSqlQuery query;
        QString tmp = QString("INSERT INTO [course_manage].[dbo].[Table_login] "
            " (ID, Password, Role, [Registration time]) "
            "VALUES ('%1', %2, '%3', GETDATE())")
            .arg(username).arg(password).arg(role);

        if (query.exec(tmp)) {
            return true;
        }
        return false;
    }
    void loadUsers() {
        //QFile file("users.txt");
        //if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        //    QTextStream in(&file);
        //    while (!in.atEnd()) {
        //        QString line = in.readLine();
        //        QStringList parts = line.split(" ");
        //        if (parts.length() == 3) {
        //            users[parts[0]] = parts[1];
        //        }
        //    }
        //    file.close();
        //}
        OpenDatabase();
        QSqlQuery query;
        if (query.exec("SELECT * FROM[course_manage].[dbo].[Table_login]")) {
            while (query.next())
            {
                QString username = query.value(0).toString();
                QString password = query.value(1).toString();
                users[username] = password;
            }
        }
    }
    void setInitialWindowSize() {
        resize(1000, 500); // 设置初始窗口大小
        setMinimumSize(400, 200); // 设置最小窗口大小
    }
    bool OpenDatabase() {
        QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");   //数据库驱动类型为SQL Server
        qDebug() << "ODBC driver" << db.isValid();
        db.setHostName("localhost");                        //选择本地主机，通用（最好不写数据库实例名）
        db.setDatabaseName("dscs");                            //设置数据源名称（ODBC数据源名称）
        db.setUserName("dscs");                               //登录用户
        db.setPassword("134298");                           //密码

        if (!db.open())                                      //打开数据库失败
        {
            qDebug() << db.lastError().text();
            QMessageBox::critical(0, QObject::tr("Database error"), db.lastError().text());
            return false;                                   //打开失败
        }
        return true;
    }

    QLineEdit* usernameLineEdit;
    QLineEdit* passwordLineEdit;
    QButtonGroup* group;
    QMap<QString, QString> users; // Username-Password map
};

// 登录界面类
class LoginWindow : public QWidget {
    Q_OBJECT

public:
    LoginWindow(QWidget* parent = nullptr) : QWidget(parent) {
        setupUI();
        setInitialWindowSize(); // 设置初始窗口大小
    }

private slots:
    void handleLoginButton() {
        loadUsers();
        QString username = usernameLineEdit->text();
        QString password = passwordLineEdit->text();

        if (authenticateUser(username, password)) {
            this->hide(); // 关闭登录窗口
            if (identity[username] == "2") {
                usernameLineEdit->clear();
                passwordLineEdit->clear();
                if (!status[username]) {
                    this->show();
                    QMessageBox::warning(this, "Login Failed", QString::fromLocal8Bit("您已被禁用，请联系辅导员 "));
                    return;
                }
                else {
                    if (!page[username]) {
                        sp = new QtWidgetsApplication2(time_limit, username);
                        connect(sp, &QtWidgetsApplication2::back, this, &LoginWindow::back_to_login);
                        status[username] = true;
                        page[username] = sp;
                    }
                    else
                        sp = page[username];
                }
                sp->show();
            }
            else {
                usernameLineEdit->clear();
                passwordLineEdit->clear();
                tp->show();
            }
        }
        else {
            QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
        }
    }

    void handleSwitchToRegister() {
        registerWindow.show(); // 显示注册界面
        this->hide(); // 隐藏登录界面
    }

private:
    void setupUI() {
        time_limit = 450;
        QWidget* widget = new QWidget(this);
        QWidget* wtitle = new QWidget(this);
        QVBoxLayout* layout = new QVBoxLayout(widget);
        QVBoxLayout* ltitle = new QVBoxLayout(wtitle);
        wtitle->setGeometry(QRect(200, 50, 600, 50));
        QLabel* title = new QLabel(QString::fromLocal8Bit("课  程  编  排  系  统 "), wtitle);
        title->setStyleSheet("font-size: 34px; font - family: SimSun; color: rgb(170, 45, 45);"); // 更改大小和颜色
        title->setAlignment(Qt::AlignCenter); // 设置文本居中对齐
        ltitle->addWidget(title);
        widget->setGeometry(QRect(300, 150, 400, 200));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 231, 235);"));

        usernameLineEdit = new QLineEdit(widget);
        passwordLineEdit = new QLineEdit(widget);
        passwordLineEdit->setEchoMode(QLineEdit::Password);

        QPushButton* loginButton = new QPushButton("Login", widget);
        QPushButton* switchToRegisterButton = new QPushButton("Switch to Register", widget);

        layout->addWidget(new QLabel("Username:", widget));
        layout->addWidget(usernameLineEdit);
        layout->addWidget(new QLabel("Password:", widget));
        layout->addWidget(passwordLineEdit);
        layout->addWidget(loginButton);
        layout->addWidget(switchToRegisterButton);

        QPixmap background("bg1.jpg");
        QPalette palette;
        palette.setBrush(this->backgroundRole(), QBrush(background));
        this->setPalette(palette);

        //sp = new QtWidgetsApplication2(time_limit);
        tp = new teacher_portal();
        sp = nullptr;
        //setLayout(layout);

        QShortcut* key = new QShortcut(QKeySequence(Qt::Key_Return), this);//创建一个快捷键"Key_Return"键  回车登录
        connect(key, &QShortcut::activated, this, &LoginWindow::handleLoginButton);//连接到指定槽函数
        connect(loginButton, &QPushButton::clicked, this, &LoginWindow::handleLoginButton);
        connect(switchToRegisterButton, &QPushButton::clicked, this, &LoginWindow::handleSwitchToRegister);
        connect(&registerWindow, &RegisterWindow::registerSuccess, this, &LoginWindow::handleSwitchToLogin);
        //connect(sp, &QtWidgetsApplication2::back, this, &LoginWindow::back_to_login);
        connect(tp, &teacher_portal::back, this, &LoginWindow::back_to_login);
        connect(tp, &teacher_portal::send_time_changed, this, &LoginWindow::time_change);
        connect(tp, &teacher_portal::send_stu_status, this, &LoginWindow::status_chg);
    }

    void handleSwitchToLogin() {
        this->show(); // 显示登录界面
        registerWindow.hide(); // 隐藏注册界面
    }
    void back_to_login() {
        this->show();
        sp->close();
        tp->close();
    }
    void status_chg(QString username, bool s) {
        status[username] = s;
    }
    void loadUsers() {
        //QFile file("users.txt");
        //if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        //    QTextStream in(&file);
        //    while (!in.atEnd()) {
        //        QString line = in.readLine();
        //        QStringList parts = line.split(" ");
        //        if (parts.length() == 3) {
        //            users[parts[0]] = parts[1];
        //            identity[parts[0]] = parts[2];
        //        }
        //    }
        //    file.close();
        //}
        OpenDatabase();
        QSqlQuery query;
        if (query.exec("SELECT * FROM[course_manage].[dbo].[Table_login]")) {
            while (query.next())
            {
                QString username = query.value(0).toString();
                QString password = query.value(1).toString();
                QString role = query.value(2).toString();
                users[username] = password;
                identity[username] = role;
                if (role == '2') {
                    if (!sp) {
                        status[username] = true;
                        page[username] = nullptr;
                    }
                    else if (!status.contains(username)) {
                        status[username] = true;
                        page[username] = nullptr;
                    }
                }
            }
            tp->set_status(status);
        }
    }
    bool authenticateUser(const QString& username, const QString& password) {
        return users.contains(username) && users[username] == password;
    }
    void setInitialWindowSize() {
        resize(1000, 500); // 设置初始窗口大小
        setMinimumSize(400, 200); // 设置最小窗口大小
    }
    void time_change(int time) {
        time_limit = time;
        for (auto& pair : page.toStdMap()) {
            if (pair.second)
                pair.second->set_time_limit(time_limit);
        }
        //sp->set_time_limit(time_limit);
    }
    bool OpenDatabase() {
        QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");   //数据库驱动类型为SQL Server
        qDebug() << "ODBC driver" << db.isValid();
        db.setHostName("localhost");                        //选择本地主机，通用（最好不写数据库实例名）
        db.setDatabaseName("dscs");                            //设置数据源名称（ODBC数据源名称）
        db.setUserName("dscs");                               //登录用户
        db.setPassword("134298");                           //密码

        if (!db.open())                                      //打开数据库失败
        {
            qDebug() << db.lastError().text();
            QMessageBox::critical(0, QObject::tr("Database error"), db.lastError().text());
            return false;                                   //打开失败
        }
        return true;
    }

    int time_limit;
    QLineEdit* usernameLineEdit;
    QLineEdit* passwordLineEdit;
    QMap<QString, QString> users; // Username-Password map
    QMap<QString, QString> identity;   //1 教师 2 学生
    RegisterWindow registerWindow; // 注册界面实例
    QtWidgetsApplication2* sp;
    teacher_portal* tp;
    QMap<QString, bool> status;  //f 空指针  t 存在 用户名-状态
    QMap<QString, QtWidgetsApplication2*> page; //用户名-页面
};

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    a.setOverrideCursor(QCursor(Qt::ArrowCursor));
    LoginWindow loginWindow;
    loginWindow.show();
    return a.exec();
}

#include "main.moc"

//
//
//#include "QtWidgetsApplication2.h"
//#include <QtWidgets/QApplication>
//#include <QtWidgets/QWidget>
//#include <QtWidgets/QVBoxLayout>
//#include <QtWidgets/QLineEdit>
//#include <QtWidgets/QPushButton>
//#include <QtWidgets/QLabel>
//#include <QtWidgets/QMessageBox>
//#include <QFile>
//#include <QTextStream>
//
//
//class WelcomeWindow : public QWidget {
//    Q_OBJECT
//
//public:
//    WelcomeWindow(const QString& username, QWidget* parent = nullptr) : QWidget(parent) {
//        QVBoxLayout* layout = new QVBoxLayout;
//        QLabel* welcomeLabel = new QLabel("Welcome, " + username + "!", this);
//        layout->addWidget(welcomeLabel);
//        setLayout(layout);
//    }
//};
//
//class LoginRegisterSystem : public QWidget {
//    Q_OBJECT
//
//public:
//    LoginRegisterSystem(QWidget* parent = nullptr) : QWidget(parent) {
//        setupUI();
//        loadUsers();
//        setInitialWindowSize(); // 设置初始窗口大小
//    }
//
//private slots:
//    void handleLoginButton() {
//        QString username = usernameLineEdit->text();
//        QString password = passwordLineEdit->text();
//
//        if (authenticateUser(username, password)) {
//            // 登录成功，打开新窗口
//            WelcomeWindow* welcomeWindow = new WelcomeWindow(username);
//            welcomeWindow->show();
//            this->close(); // 关闭登录窗口
//        }
//        else {
//            QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
//        }
//    }
//
//    void handleRegisterButton() {
//        QString username = usernameLineEdit->text();
//        QString password = passwordLineEdit->text();
//
//        if (username.isEmpty() || password.isEmpty()) {
//            QMessageBox::warning(this, "Registration Failed", "Please enter both username and password.");
//            return;
//        }
//
//        if (registerUser(username, password)) {
//            QMessageBox::information(this, "Registration Successful", "Account created for " + username + ".");
//        }
//        else {
//            QMessageBox::warning(this, "Registration Failed", "Username already exists.");
//        }
//    }
//
//private:
//    void setupUI() {
//        QVBoxLayout* layout = new QVBoxLayout;
//
//        usernameLineEdit = new QLineEdit(this);
//        passwordLineEdit = new QLineEdit(this);
//        passwordLineEdit->setEchoMode(QLineEdit::Password);
//
//        QPushButton* loginButton = new QPushButton("Login", this);
//        QPushButton* registerButton = new QPushButton("Register", this);
//
//        layout->addWidget(new QLabel("Username:", this));
//        layout->addWidget(usernameLineEdit);
//        layout->addWidget(new QLabel("Password:", this));
//        layout->addWidget(passwordLineEdit);
//        layout->addWidget(loginButton);
//        layout->addWidget(registerButton);
//
//        setLayout(layout);
//
//        connect(loginButton, &QPushButton::clicked, this, &LoginRegisterSystem::handleLoginButton);
//        connect(registerButton, &QPushButton::clicked, this, &LoginRegisterSystem::handleRegisterButton);
//    }
//
//    void loadUsers() {
//        QFile file("users.txt");
//        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//            QTextStream in(&file);
//            while (!in.atEnd()) {
//                QString line = in.readLine();
//                QStringList parts = line.split(" ");
//                if (parts.length() == 2) {
//                    users[parts[0]] = parts[1];
//                }
//            }
//            file.close();
//        }
//    }
//
//    bool authenticateUser(const QString& username, const QString& password) {
//        return users.contains(username) && users[username] == password;
//    }
//
//    bool registerUser(const QString& username, const QString& password) {
//        if (users.contains(username)) {
//            return false; // Username already exists
//        }
//
//        users[username] = password;
//
//        QFile file("users.txt");
//        if (file.open(QIODevice::Append | QIODevice::Text)) {
//            QTextStream out(&file);
//            out << username << " " << password << "\n";
//            file.close();
//            return true;
//        }
//
//        return false;
//    }
//
//    void setInitialWindowSize() {
//        resize(400, 200); // 设置初始窗口大小
//        setMinimumSize(400, 200); // 设置最小窗口大小
//    }
//
//    QLineEdit* usernameLineEdit;
//    QLineEdit* passwordLineEdit;
//    QMap<QString, QString> users; // Username-Password map
//};
//
//int main(int argc, char* argv[]) {
//    QApplication app(argc, argv);
//
//    LoginRegisterSystem loginRegisterSystem;
//    loginRegisterSystem.show();
//
//    return app.exec();
//}
//
//#include "main.moc"
//
