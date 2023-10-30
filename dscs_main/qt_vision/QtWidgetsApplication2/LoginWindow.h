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
        setInitialWindowSize(); // ���ó�ʼ���ڴ�С
    }

private slots:
    void handleLoginButton() {
        loadUsers(); // ��ȡ�û���Ϣ
        QString username = usernameLineEdit->text();
        QString password = passwordLineEdit->text();

        if (authenticateUser(username, password)) {
            QMessageBox::warning(this, "Login Succeed", "Welcome.");
            this->close(); // �رյ�¼����
            QtWidgetsApplication2* mainwindow = new QtWidgetsApplication2;
            mainwindow->show();
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
        this->show(); // ��ʾ��¼����
        registerWindow.hide(); // ����ע�����
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
        resize(400, 200); // ���ó�ʼ���ڴ�С
        setMinimumSize(400, 200); // ������С���ڴ�С
    }
    QLineEdit* usernameLineEdit;
    QLineEdit* passwordLineEdit;
    QMap<QString, QString> users; // Username-Password map
    RegisterWindow registerWindow; // ע�����ʵ��
};

#endif // LOGINWINDOW_H
