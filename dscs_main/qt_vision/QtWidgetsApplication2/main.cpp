#pragma once

#include <bits/stdc++.h>
#include "QtWidgetsApplication2.h"
#include "teacher_portal.h"
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

        connect(registerButton, &QPushButton::clicked, this, &RegisterWindow::handleRegisterButton);
        connect(switchToLoginButton, &QPushButton::clicked, this, &RegisterWindow::handleSwitchToLogin);
    }
    bool registerUser(const QString& username, const QString& password) {
        if (users.contains(username)) {
            return false; // Username already exists
        }
        users[username] = password;
        QString role = QString::fromStdString(to_string(group->checkedId()));
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
        resize(1000, 500); // ���ó�ʼ���ڴ�С
        setMinimumSize(400, 200); // ������С���ڴ�С
    }
    bool OpenDatabase() {
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

    QLineEdit* usernameLineEdit;
    QLineEdit* passwordLineEdit;
    QButtonGroup* group;
    QMap<QString, QString> users; // Username-Password map
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
                if (!status[username]) {
                    this->show();
                    QMessageBox::warning(this, "Login Failed", QString::fromLocal8Bit("���ѱ����ã�����ϵ����Ա "));
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

        tp = new teacher_portal();
        sp = nullptr;

        QShortcut* key = new QShortcut(QKeySequence(Qt::Key_Return), this);//����һ����ݼ�"Key_Return"��  �س���¼
        connect(key, &QShortcut::activated, this, &LoginWindow::handleLoginButton);//���ӵ�ָ���ۺ���
        connect(loginButton, &QPushButton::clicked, this, &LoginWindow::handleLoginButton);
        connect(switchToRegisterButton, &QPushButton::clicked, this, &LoginWindow::handleSwitchToRegister);
        connect(&registerWindow, &RegisterWindow::registerSuccess, this, &LoginWindow::handleSwitchToLogin);
        connect(tp, &teacher_portal::back, this, &LoginWindow::back_to_login);
        connect(tp, &teacher_portal::send_time_changed, this, &LoginWindow::time_change);
        connect(tp, &teacher_portal::send_stu_status, this, &LoginWindow::status_chg);
    }

    void handleSwitchToLogin() {
        this->show(); // ��ʾ��¼����
        registerWindow.hide(); // ����ע�����
    }
    void back_to_login() {
        this->show();
        sp->close();
        tp->hide();
    }
    void status_chg(QString username, bool s) {
        status[username] = s;
    }
    void loadUsers() {
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
        resize(1000, 500); // ���ó�ʼ���ڴ�С
        setMinimumSize(400, 200); // ������С���ڴ�С
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

    int time_limit;
    QLineEdit* usernameLineEdit;
    QLineEdit* passwordLineEdit;
    QMap<QString, QString> users; // Username-Password map
    QMap<QString, QString> identity;   //1 ��ʦ 2 ѧ��
    RegisterWindow registerWindow; // ע�����ʵ��
    QtWidgetsApplication2* sp;
    teacher_portal* tp;
    QMap<QString, bool> status;  //f ��ָ��  t ���� �û���-״̬
    QMap<QString, QtWidgetsApplication2*> page; //�û���-ҳ��
};

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    a.setOverrideCursor(QCursor(Qt::ArrowCursor));
    LoginWindow loginWindow;
    loginWindow.show();
    return a.exec();
}

#include "main.moc"
