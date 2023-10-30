#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

//#include "QtWidgetsApplication2.h"
//#include "LoginWindow.h"
//#include "RegisterWindow.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <QFile>
#include <QTextStream>

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
        QVBoxLayout* layout = new QVBoxLayout;

        usernameLineEdit = new QLineEdit(this);
        passwordLineEdit = new QLineEdit(this);
        passwordLineEdit->setEchoMode(QLineEdit::Password);

        QPushButton* registerButton = new QPushButton("Register", this);
        QPushButton* switchToLoginButton = new QPushButton("Back to Login", this);

        layout->addWidget(new QLabel("Username:", this));
        layout->addWidget(usernameLineEdit);
        layout->addWidget(new QLabel("Password:", this));
        layout->addWidget(passwordLineEdit);
        layout->addWidget(registerButton);
        layout->addWidget(switchToLoginButton);

        setLayout(layout);

        connect(registerButton, &QPushButton::clicked, this, &RegisterWindow::handleRegisterButton);
        connect(switchToLoginButton, &QPushButton::clicked, this, &RegisterWindow::handleSwitchToLogin);
    }
    bool registerUser(const QString& username, const QString& password) {
        if (users.contains(username)) {
            return false; // Username already exists
        }

        users[username] = password;

        QFile file("users.txt");
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << username << " " << password << "\n";
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
                if (parts.length() == 2) {
                    users[parts[0]] = parts[1];
                }
            }
            file.close();
        }
    }
    void setInitialWindowSize() {
        resize(400, 200); // 设置初始窗口大小
        setMinimumSize(400, 200); // 设置最小窗口大小
    }
    QLineEdit* usernameLineEdit;
    QLineEdit* passwordLineEdit;
    QMap<QString, QString> users; // Username-Password map
    // LoginWindow* loginWindow; // 登录界面实例
};

#endif // REGISTERWINDOW_H
