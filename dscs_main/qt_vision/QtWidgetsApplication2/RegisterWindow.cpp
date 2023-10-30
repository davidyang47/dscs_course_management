// registerwindow.cpp

#include "RegisterWindow.h"
#include "LoginWindow.h"

void RegisterWindow::handleRegisterButton() {
    QString username = usernameLineEdit->text();
    QString password = passwordLineEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Registration Failed", "Please enter both username and password.");
        return;
    }

    if (registerUser(username, password)) {
        QMessageBox::information(this, "Registration Successful", "Account created for " + username + ".");
        emit registerSuccess();
    }
    else {
        QMessageBox::warning(this, "Registration Failed", "Username already exists.");
        emit registerSuccess();
    }
}

void RegisterWindow::handleSwitchToLogin() {
    emit registerSuccess();
}

void RegisterWindow::setupUI() {
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

void RegisterWindow::loadUsers() {
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

void RegisterWindow::setInitialWindowSize() {
    resize(400, 200); // 设置初始窗口大小
    setMinimumSize(400, 200); // 设置最小窗口大小
}

bool RegisterWindow::registerUser(const QString& username, const QString& password) {
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
