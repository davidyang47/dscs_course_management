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
class LoginWindow; // ǰ������

// ע�������
class RegisterWindow : public QWidget {
    Q_OBJECT

public:
    RegisterWindow(QWidget* parent = nullptr) : QWidget(parent) {
        setupUI();
        loadUsers();
        setInitialWindowSize(); // ���ó�ʼ���ڴ�С
    }

signals:
    void registerSuccess(); // �Զ����źţ�������ע��ɹ���֪ͨ��¼����

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
            emit registerSuccess(); // ����ע��ɹ��ź�
        }
        else {
            QMessageBox::warning(this, "Registration Failed", "Username already exists.");
            emit registerSuccess(); // ����ע��ɹ��ź�
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
        QLabel* title = new QLabel(QString::fromLocal8Bit("��  ��  ��  ��  ϵ  ͳ "), wtitle);
        title->setStyleSheet("font-size: 34px; font - family: SimSun; color: rgb(170, 45, 45);"); // ���Ĵ�С����ɫ
        title->setAlignment(Qt::AlignCenter); // �����ı����ж���
        ltitle->addWidget(title);
        widget->setGeometry(QRect(300, 150, 400, 200));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 231, 235);"));

        usernameLineEdit = new QLineEdit(this);
        passwordLineEdit = new QLineEdit(this);
        passwordLineEdit->setEchoMode(QLineEdit::Password);
        group = new QButtonGroup(this);

        QPushButton* registerButton = new QPushButton("Register", this);
        QPushButton* switchToLoginButton = new QPushButton("Back to Login", this);
        string a = "��ʦ";
        string b = "ѧ��";
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
        QString id = QString::fromStdString(to_string(group->checkedId()));
        QFile file("users.txt");
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << username << " " << password <<" "<<id<<"\n";
            file.close();
            return true;
        }

        return false;
    }
    void loadUsers() {
        QFile file("users.txt");
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                QStringList parts = line.split(" ");
                if (parts.length() == 3) {
                    users[parts[0]] = parts[1];
                }
            }
            file.close();
        }
    }
    void setInitialWindowSize() {
        resize(1000, 500); // ���ó�ʼ���ڴ�С
        setMinimumSize(400, 200); // ������С���ڴ�С
    }
    QLineEdit* usernameLineEdit;
    QLineEdit* passwordLineEdit;
    QButtonGroup* group;
    QMap<QString, QString> users; // Username-Password map
   // LoginWindow* loginWindow; // ��¼����ʵ��
};

// ��¼������
class LoginWindow : public QWidget {
    Q_OBJECT

public:
    LoginWindow(QWidget* parent = nullptr) : QWidget(parent) {
        setupUI();
        setInitialWindowSize(); // ���ó�ʼ���ڴ�С
    }

private slots:
    void handleLoginButton() {
        loadUsers();
        QString username = usernameLineEdit->text();
        QString password = passwordLineEdit->text();

        if (authenticateUser(username, password)) {
            this->hide(); // �رյ�¼����
            if (identity[username] == "2") {
                usernameLineEdit->clear();
                passwordLineEdit->clear();
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
        registerWindow.show(); // ��ʾע�����
        this->hide(); // ���ص�¼����
    }

private:
    void setupUI() {
        time_limit = 450;
        QWidget* widget = new QWidget(this);
        QWidget* wtitle = new QWidget(this);
        QVBoxLayout* layout = new QVBoxLayout(widget);
        QVBoxLayout* ltitle = new QVBoxLayout(wtitle);
        wtitle->setGeometry(QRect(200, 50, 600, 50));
        QLabel* title = new QLabel(QString::fromLocal8Bit("��  ��  ��  ��  ϵ  ͳ "), wtitle);
        title->setStyleSheet("font-size: 34px; font - family: SimSun; color: rgb(170, 45, 45);"); // ���Ĵ�С����ɫ
        title->setAlignment(Qt::AlignCenter); // �����ı����ж���
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

        sp = new QtWidgetsApplication2(time_limit);
        tp = new teacher_portal();
        //setLayout(layout);

        QShortcut* key = new QShortcut(QKeySequence(Qt::Key_Return), this);//����һ����ݼ�"Key_Return"��  �س���¼
        connect(key, &QShortcut::activated, this, &LoginWindow::handleLoginButton);//���ӵ�ָ���ۺ���
        connect(loginButton, &QPushButton::clicked, this, &LoginWindow::handleLoginButton);  
        connect(switchToRegisterButton, &QPushButton::clicked, this, &LoginWindow::handleSwitchToRegister);   
        connect(&registerWindow, &RegisterWindow::registerSuccess, this, &LoginWindow::handleSwitchToLogin);  
        connect(sp, &QtWidgetsApplication2::back, this, &LoginWindow::back_to_login);
        connect(tp, &teacher_portal::back, this, &LoginWindow::back_to_login);
        connect(tp, &teacher_portal::send_time_changed, this, &LoginWindow::time_change);
    }

    void handleSwitchToLogin() {
        this->show(); // ��ʾ��¼����
        registerWindow.hide(); // ����ע�����
    }
    void back_to_login() {
		this->show();
        sp->close(); 
        tp->close();
	}
    void loadUsers() {
        QFile file("users.txt");
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                QStringList parts = line.split(" ");
                if (parts.length() == 3) {
                    users[parts[0]] = parts[1];
                    identity[parts[0]] = parts[2];
                }
            }
            file.close();
        }
    }
    bool authenticateUser(const QString& username, const QString& password) {
        return users.contains(username) && users[username] == password;
    }
    void setInitialWindowSize() {
        resize(1000, 500); // ���ó�ʼ���ڴ�С
        setMinimumSize(400, 200); // ������С���ڴ�С
    }
    void time_change(int time) {
        time_limit = time;
        sp->set_time_limit(time_limit);
    }

    int time_limit;
    QLineEdit* usernameLineEdit;
    QLineEdit* passwordLineEdit;
    QMap<QString, QString> users; // Username-Password map
    QMap<QString, QString> identity;
    RegisterWindow registerWindow; // ע�����ʵ��
    QtWidgetsApplication2* sp;
    teacher_portal* tp;
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
//        setInitialWindowSize(); // ���ó�ʼ���ڴ�С
//    }
//
//private slots:
//    void handleLoginButton() {
//        QString username = usernameLineEdit->text();
//        QString password = passwordLineEdit->text();
//
//        if (authenticateUser(username, password)) {
//            // ��¼�ɹ������´���
//            WelcomeWindow* welcomeWindow = new WelcomeWindow(username);
//            welcomeWindow->show();
//            this->close(); // �رյ�¼����
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
//        resize(400, 200); // ���ó�ʼ���ڴ�С
//        setMinimumSize(400, 200); // ������С���ڴ�С
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