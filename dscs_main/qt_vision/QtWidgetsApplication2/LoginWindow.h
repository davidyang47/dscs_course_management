#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "QtWidgetsApplication2.h"
//#include "LoginWindow.h"
#include "RegisterWindow.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <QFile>
#include <QTextStream>

class LoginWindow : public QWidget {
    Q_OBJECT

public:
    LoginWindow(QWidget* parent = nullptr) : QWidget(parent) {
        setupUI();
        setInitialWindowSize(); // 设置初始窗口大小
    }

private slots:
    void handleLoginButton() {
        loadUsers(); // 读取用户信息
        QString username = usernameLineEdit->text();
        QString password = passwordLineEdit->text();

        if (authenticateUser(username, password)) {
            QMessageBox::warning(this, "Login Succeed", "Welcome.");
            this->close(); // 关闭登录窗口
            QtWidgetsApplication2* mainwindow = new QtWidgetsApplication2;
            mainwindow->show();
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
        QVBoxLayout* layout = new QVBoxLayout;

        usernameLineEdit = new QLineEdit(this);
        passwordLineEdit = new QLineEdit(this);
        passwordLineEdit->setEchoMode(QLineEdit::Password);

        QPushButton* loginButton = new QPushButton("Login", this);
        QPushButton* switchToRegisterButton = new QPushButton("Switch to Register", this);

        layout->addWidget(new QLabel("Username:", this));
        layout->addWidget(usernameLineEdit);
        layout->addWidget(new QLabel("Password:", this));
        layout->addWidget(passwordLineEdit);
        layout->addWidget(loginButton);
        layout->addWidget(switchToRegisterButton);

        setLayout(layout);

        connect(loginButton, &QPushButton::clicked, this, &LoginWindow::handleLoginButton);
        connect(switchToRegisterButton, &QPushButton::clicked, this, &LoginWindow::handleSwitchToRegister);
        connect(&registerWindow, &RegisterWindow::registerSuccess, this, &LoginWindow::handleSwitchToLogin);
    }

    void handleSwitchToLogin() {
        this->show(); // 显示登录界面
        registerWindow.hide(); // 隐藏注册界面
    }
    void loadUsers() {
        QFile file("users.txt");
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                QStringList parts = line.split(" ");
                if (parts.length() == 2) {
                    users[parts[0]] = parts[1];
                }
            }
            file.close();
        }
    }
    bool authenticateUser(const QString& username, const QString& password) {
        return users.contains(username) && users[username] == password;
    }
    void setInitialWindowSize() {
        resize(400, 200); // 设置初始窗口大小
        setMinimumSize(400, 200); // 设置最小窗口大小
    }
    QLineEdit* usernameLineEdit;
    QLineEdit* passwordLineEdit;
    QMap<QString, QString> users; // Username-Password map
    RegisterWindow registerWindow; // 注册界面实例
};

#endif // LOGINWINDOW_H
