// loginwindow.cpp

#include "LoginWindow.h"
#include "RegisterWindow.h"
#include "QtWidgetsApplication2.h"


void LoginWindow::handleLoginButton() {
    QString username = usernameLineEdit->text();
    QString password = passwordLineEdit->text();

    if (authenticateUser(username, password)) {
        QMessageBox::warning(this, "Login Succeed", "Welcome.");
    }
    else {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
    }
}

void LoginWindow::handleSwitchToRegister() {
    registerWindow.show();
    this->hide();
}

void LoginWindow::setupUI() {
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

void LoginWindow::handleSwitchToLogin() {
    this->show(); // 显示登录界面
    registerWindow.hide(); // 隐藏注册界面
}

void LoginWindow::loadUsers() {
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

void LoginWindow::setInitialWindowSize() {
    resize(400, 200); // 设置初始窗口大小
    setMinimumSize(400, 200); // 设置最小窗口大小
}

bool LoginWindow::authenticateUser(const QString& username, const QString& password) {
    return users.contains(username) && users[username] == password;
}
