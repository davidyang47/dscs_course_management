#include "teacher_portal.h"
extern int maxn;

teacher_portal::teacher_portal(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	mainLayout = new QVBoxLayout(ui.widget);
	aGraphl = nullptr;
	filepath = "";
	d = nullptr;
	time_limit = 450;
	connect(ui.read_in, &QPushButton::clicked, this, &teacher_portal::read);
	connect(ui.to_show, &QPushButton::clicked, this, &teacher_portal::show_graph);
	connect(ui.to_exit, &QPushButton::clicked, this, &teacher_portal::shut);
	connect(ui.add, &QPushButton::clicked, this, [this]() {initial(1); });
	connect(ui.to_set, &QPushButton::clicked, this, [this]() {initial(2); });
	connect(ui.del, &QPushButton::clicked, this, [this]() {initial(3); });
	connect(ui.list, &QPushButton::clicked, this, &teacher_portal::list_student);
	connect(ui.back_to, &QPushButton::clicked, this, &teacher_portal::back_to_login);
}

teacher_portal::~teacher_portal() {}

void teacher_portal::set_status(QMap<QString, bool> status) {
	this->status = status;
}

void teacher_portal::read() {
	if (read_in(mycourses))
	{
		graph_set(aGraphl, mycourses);
		for (int i = 0; i < aGraphl->VerticesNum(); i++) {
			calpath(*aGraphl, i, 0);
			aGraphl->path[i] = maxn;
			maxn = -1;
		}
		indegree = new int[aGraphl->VerticesNum()];
		for (int i = 0; i < aGraphl->VerticesNum(); i++)
			indegree[i] = aGraphl->Indegree[i];
		QMessageBox::information(this, "hint", "succeed", QMessageBox::Ok);
	}
	else
	{
		QMessageBox::warning(this, "hint", "failed");
	}
}

void teacher_portal::show_graph() {
	if (!mycourses.empty()) {
		if (d)
			d->close();
		d = new Drawing(*aGraphl, mycourses, index);
		d->show();
	}
	else {
		QMessageBox::warning(this, "hint", "please read in first");
	}
}

void teacher_portal::shut() {
	if (d)
		d->close();
	this->close();
}

void teacher_portal::initial(int mode) {
	if (!mycourses.empty()) {
		QScrollArea* scrollArea;
		QWidget* contentWidget;
		string text1 = "确认 ";
		string text2 = "取消 ";
		QPushButton* add1 = new QPushButton(QString::fromLocal8Bit(text1));
		QPushButton* add2 = new QPushButton(QString::fromLocal8Bit(text2));
		add1->setStyleSheet("background-color:rgb(255,231,235)");
		add2->setStyleSheet("background-color:rgb(255,231,235)");
		ui.verticalLayout->addWidget(add1);
		ui.verticalLayout->addWidget(add2);
		scrollArea = new QScrollArea(ui.widget);
		scrollArea->setWidgetResizable(true);
		contentWidget = new QWidget(scrollArea);
		scrollArea->setWidget(contentWidget);

		layout = new QVBoxLayout(contentWidget);

		// 设置滚动区域为当前小部件的子对象
		scrollArea->setParent(ui.widget);

		// 将 contentWidget 添加到当前小部件的布局中
		mainLayout->addWidget(scrollArea);
		if (mode == 1) {
			QWidget* wadd = new QWidget(contentWidget);
			QVBoxLayout* vadd = new QVBoxLayout(wadd);
			wadd->setGeometry(QRect(150, 50, 700, 200));
			c_type = new QButtonGroup(wadd);

			QHBoxLayout* hno = new QHBoxLayout;
			QLabel* lno = new QLabel(QString::fromLocal8Bit("课程编号 "));
			QLineEdit* eno = new QLineEdit;
			hno->addWidget(lno);
			hno->addWidget(eno);
			hno->addItem(new QSpacerItem(40, 15, QSizePolicy::Expanding, QSizePolicy::Minimum));
			when_add.push_back(eno);

			QHBoxLayout* hname = new QHBoxLayout;
			QLabel* lname = new QLabel(QString::fromLocal8Bit("课程名称 "));
			QLineEdit* ename = new QLineEdit;
			hname->addWidget(lname);
			hname->addWidget(ename);
			hname->addItem(new QSpacerItem(40, 15, QSizePolicy::Expanding, QSizePolicy::Minimum));
			when_add.push_back(ename);

			QHBoxLayout* hcredits = new QHBoxLayout;
			QLabel* lcredits = new QLabel(QString::fromLocal8Bit("课程学分 "));
			QLineEdit* ecredits = new QLineEdit;
			hcredits->addWidget(lcredits);
			hcredits->addWidget(ecredits);
			hcredits->addItem(new QSpacerItem(40, 15, QSizePolicy::Expanding, QSizePolicy::Minimum));
			when_add.push_back(ecredits);

			QHBoxLayout* htype = new QHBoxLayout;
			QLabel* ltype = new QLabel(QString::fromLocal8Bit("课程类别 "));
			QRadioButton* ele = new QRadioButton(QString::fromLocal8Bit("必修课 "));
			QRadioButton* com = new QRadioButton(QString::fromLocal8Bit("选修课 "));
			c_type->addButton(ele);
			c_type->addButton(com);
			c_type->setId(ele, 0);
			c_type->setId(com, 1);
			htype->addWidget(ltype);
			htype->addWidget(ele);
			htype->addWidget(com);
			htype->addItem(new QSpacerItem(40, 15, QSizePolicy::Expanding, QSizePolicy::Minimum));

			QLabel* lpre = new QLabel(QString::fromLocal8Bit("先修课:"));
			QGridLayout* gridLayout = new QGridLayout;

			// 创建多选按钮并添加到网格布局
			for (int i = 0; i < mycourses.size(); i++) {
				QCheckBox* checkBox = new QCheckBox(QString::fromLocal8Bit(mycourses[i].name));
				gridLayout->addWidget(checkBox, i / 3, i % 3); // i / 3 行，i % 3 列
				checkboxes.push_back(checkBox);
			}

			vadd->addLayout(hno);
			vadd->addLayout(hname);
			vadd->addLayout(hcredits);
			vadd->addLayout(htype);
			vadd->addWidget(lpre);
			vadd->addLayout(gridLayout);
			layout->addWidget(wadd);

			connect(add1, &QPushButton::clicked, this, &teacher_portal::add_course);
			ui.add->setDisabled(true);
			ui.to_set->setDisabled(true);
			ui.del->setDisabled(true);
			ui.list->setDisabled(true);
		}
		else if (mode == 2) {
			QWidget* time_w = new QWidget(contentWidget);
			QVBoxLayout* time_v = new QVBoxLayout(time_w);
			time_w->setGeometry(QRect(150, 50, 700, 200));
			QHBoxLayout* time_h = new QHBoxLayout;
			QLabel* former_time = new QLabel(QString::fromLocal8Bit("当前学分限制为:") + QString::number(time_limit));
			QLabel* change_time = new QLabel(QString::fromLocal8Bit("更改学分限制为:"));
			QLineEdit* time_edit = new QLineEdit;
			time_h->addWidget(change_time);
			time_h->addWidget(time_edit);
			time_h->addItem(new QSpacerItem(40, 15, QSizePolicy::Expanding, QSizePolicy::Minimum));
			time_v->addWidget(former_time);
			time_v->addLayout(time_h);
			layout->addWidget(time_w);
			when_add.push_back(time_edit);
			connect(add1, &QPushButton::clicked, this, &teacher_portal::set_time);
			ui.add->setDisabled(true);
			ui.to_set->setDisabled(true);
			ui.del->setDisabled(true);
			ui.list->setDisabled(true);
		}
		else {
			QLabel* ldel = new QLabel(QString::fromLocal8Bit("选择想要删除的课: "));
			QGridLayout* gridLayout = new QGridLayout;

			// 创建多选按钮并添加到网格布局
			for (int i = 0; i < mycourses.size(); i++) {
				QCheckBox* checkBox = new QCheckBox(QString::fromLocal8Bit(mycourses[i].name));
				gridLayout->addWidget(checkBox, i / 3, i % 3); // i / 3 行，i % 3 列
				checkboxes.push_back(checkBox);
			}
			layout->addWidget(ldel);
			layout->addLayout(gridLayout);
			connect(add1, &QPushButton::clicked, this, &teacher_portal::delete_course);
			ui.add->setDisabled(true);
			ui.to_set->setDisabled(true);
			ui.del->setDisabled(true);
			ui.list->setDisabled(true);
		}
		connect(add2, &QPushButton::clicked, this, &teacher_portal::cancel);
	}
	else {
		QMessageBox::warning(this, "hint", "please read in first");
	}
}

void teacher_portal::add_course() {
	if (when_add[0]->text().isEmpty() || when_add[1]->text().isEmpty() || when_add[2]->text().isEmpty()) {
		QMessageBox::warning(this, "hint", "please fill in all blanks");
		return;
	}
	int sno = when_add[0]->text().toInt();
	string sname = when_add[1]->text().toLocal8Bit().constData();
	for (int i = 0; i < mycourses.size(); i++) {
		if (mycourses[i].no == sno) {
			QMessageBox::warning(this, "hint", "course already exists");
			return;
		}
		if (mycourses[i].name == sname) {
			QMessageBox::warning(this, "hint", "same course with different no");
			return;
		}
	}
	course tmp;
	tmp.no = sno;
	tmp.name = sname;
	tmp.credits = when_add[2]->text().toFloat();
	tmp.hours = tmp.credits * 16;
	tmp.sort = (c_type->checkedId()) ? "Y" : "N";
	for (int i = 0; i < checkboxes.size(); i++) {
		if (checkboxes[i]->isChecked()) {
			tmp.prerequisites.push_back(checkboxes[i]->text().toLocal8Bit().constData());
		}
	}
	mycourses.push_back(tmp);
	index[mycourses.size() - 1] = tmp.no;
	//delete aGraphl;
	graph_set(aGraphl, mycourses);
	for (int i = 0; i < aGraphl->VerticesNum(); i++) {
		calpath(*aGraphl, i, 0);
		aGraphl->path[i] = maxn;
		maxn = -1;
	}
	//delete indegree;
	indegree = new int[aGraphl->VerticesNum()];
	for (int i = 0; i < aGraphl->VerticesNum(); i++)
		indegree[i] = aGraphl->Indegree[i];

	QSqlQuery query;
	string pres = "";
	for (int i = 0; i < tmp.prerequisites.size(); i++) {
		pres += tmp.prerequisites[i];
		if (i != tmp.prerequisites.size() - 1)
			pres += ",";
	}
	QString sql = QString("INSERT INTO [course_manage].[dbo].[Table_course] VALUES(%1,'%2',%3,%4,'%5','%6')")
		.arg(tmp.no).arg(QString::fromLocal8Bit(tmp.name.c_str())).arg(tmp.credits).arg(tmp.hours).arg(QString::fromLocal8Bit(tmp.sort.c_str())).arg(QString::fromLocal8Bit(pres.c_str()));
	query.exec(sql);
	QMessageBox::information(this, "hint", "add succeed", QMessageBox::Ok);
	cancel();
}

void teacher_portal::cancel() {
	QLayoutItem* child;
	while ((child = ui.verticalLayout->takeAt(0)) != 0)
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
	checkboxes.clear();
	when_add.clear();
	for (int i = 0; i < aGraphl->VerticesNum(); i++)
		indegree[i] = aGraphl->Indegree[i];
	ui.add->setDisabled(false);
	ui.to_set->setDisabled(false);
	ui.del->setDisabled(false);
	ui.list->setDisabled(false);
}

void teacher_portal::back_to_login() {
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
	emit back();
}

void teacher_portal::set_time() {
	int time = when_add[0]->text().toInt();
	if (time < 0) {
		QMessageBox::warning(this, "hint", "time should be positive");
		return;
	}
	if (time < 310) {
		QMessageBox::StandardButton check;
		check = QMessageBox::question(this, "hint", "time maybe too small, are you sure ?", QMessageBox::Yes | QMessageBox::No);
		if (check == QMessageBox::No)
			return;
	}
	time_limit = time;
	emit send_time_changed(time);
	cancel();
}

void teacher_portal::delete_course() {
	vector<string> del_course;
	for (int i = 0; i < checkboxes.size(); i++) {
		if (checkboxes[i]->isChecked()) {
			del_course.push_back(checkboxes[i]->text().toLocal8Bit().constData());
		}
	}
	if (del_course.empty()) {
		QMessageBox::warning(this, "hint", "please choose at least one course");
		return;
	}
	for (int i = 0; i < del_course.size(); i++) {
		for (int j = 0; j < mycourses.size(); j++) {
			if (del_course[i] == mycourses[j].name) {
				QSqlQuery query;
				for (int k = 0; k < mycourses[j].prerequisites.size(); k++) {
					for (int l = 0; l < mycourses.size(); l++) {
						for (int m = 0; m < mycourses[l].prerequisites.size(); m++)
							if (mycourses[l].prerequisites[m] == del_course[i]) {
								mycourses[l].prerequisites.erase(mycourses[l].prerequisites.begin() + m);
								m--;
								mycourses[l].prerequisites.push_back(mycourses[j].prerequisites[k]);
								string pres = "";
								for (int n = 0; n < mycourses[l].prerequisites.size(); n++) {
									pres += mycourses[l].prerequisites[n];
									if (n != mycourses[l].prerequisites.size() - 1)
										pres += ",";
								}
								QString sql = QString("UPDATE [course_manage].[dbo].[Table_course] SET Prerequisites = '%1' WHERE No = %2")
									.arg(QString::fromLocal8Bit(pres.c_str())).arg(mycourses[l].no);
								query.exec(sql);
								break;
							}
					}
				}
				QString sql = QString("DELETE FROM [course_manage].[dbo].[Table_course] WHERE No = %1").arg(mycourses[j].no);
				query.exec(sql);
				mycourses.erase(mycourses.begin() + j);
				j--;
			}
		}
	}
	index.clear();
	for (int i = 0; i < mycourses.size(); i++) {
		index[i] = mycourses[i].no;
	}
	graph_set(aGraphl, mycourses);
	for (int i = 0; i < aGraphl->VerticesNum(); i++) {
		calpath(*aGraphl, i, 0);
		aGraphl->path[i] = maxn;
		maxn = -1;
	}
	indegree = new int[aGraphl->VerticesNum()];
	for (int i = 0; i < aGraphl->VerticesNum(); i++)
		indegree[i] = aGraphl->Indegree[i];
	QMessageBox::information(this, "hint", "delete succeed", QMessageBox::Ok);
	cancel();
}

void teacher_portal::list_student() {
	string text1 = "取消 ";
	QPushButton* add1 = new QPushButton(QString::fromLocal8Bit(text1));
	add1->setStyleSheet("background-color:rgb(255,231,235)");
	ui.verticalLayout->addWidget(add1);
	connect(add1, &QPushButton::clicked, this, &teacher_portal::cancel);
	QSqlQuery query;
	query.exec("SELECT COUNT(*) FROM [course_manage].[dbo].[Table_login] WHERE Role='2'");
	QTableWidget* tablelist = new QTableWidget(4, 4);
	while (query.next()) {
		tablelist->setRowCount(query.value(0).toInt());
	}
	QStringList colHeaders;
	colHeaders << "ID" << "Password" << "Registration time" << "status";
	tablelist->setHorizontalHeaderLabels(colHeaders);
	int i = 0;
	if (query.exec("SELECT * FROM[course_manage].[dbo].[Table_login]")) {
		while (query.next()) {
			if (query.value(2).toString() == "2") {
				QString stu_id = query.value(0).toString();
				tablelist->setItem(i, 0, new QTableWidgetItem(query.value(0).toString()));
				tablelist->setItem(i, 1, new QTableWidgetItem(query.value(1).toString()));
				tablelist->setItem(i, 2, new QTableWidgetItem(query.value(3).toDate().toString()));
				QPushButton* forbid = new QPushButton(QString::fromLocal8Bit("禁用 "));
				connect(forbid, &QPushButton::clicked, this, [=]() {stu_forbid(stu_id); });
				tablelist->setCellWidget(i, 3, forbid);
				i++;
			}
		}
	}
	//tablelist->resizeColumnsToContents();
	tablelist->setColumnWidth(0, 200);
	tablelist->setColumnWidth(1, 200);
	tablelist->setColumnWidth(2, 300);
	tablelist->setColumnWidth(3, 200);
	tablelist->setMinimumSize(QSize(920, 150));
	mainLayout->addWidget(tablelist);
	ui.add->setDisabled(true);
	ui.to_set->setDisabled(true);
	ui.del->setDisabled(true);
	ui.list->setDisabled(true);
}

bool teacher_portal::read_in(vector<course>& mycourses) {
	mycourses.clear();
	if (!OpenDatabase()) {
		return false;
	}
	QSqlQuery query;
	if (query.exec("SELECT * FROM[course_manage].[dbo].[Table_course]"))
	{
		int count = 0;
		istringstream sin;         //将整行字符串line读入到字符串istringstream中
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
				while (getline(sin, word, ',')) //将字符串流sin中的字符读到word字符串中，以逗号为分隔符
				{
					tmp.prerequisites.push_back(word); //将每一格中的数据逐个push
				}
			}
			mycourses.push_back(tmp);
			index[count++] = tmp.no;
		}
		return true;
	}
	return false;
}

void teacher_portal::stu_forbid(QString name) {
	if (status[name]) {
		status[name] = false;
		QMessageBox::warning(this, "", QString::fromLocal8Bit("已禁用 "));
		emit send_stu_status(name, false);
		return;
	}
	else {
		QMessageBox::StandardButton check;
		check = QMessageBox::question(this, "confirm", QString::fromLocal8Bit("该学生已被禁用，是否解除? "), QMessageBox::Yes | QMessageBox::No);
		if (check == QMessageBox::No) {
			return;
		}
		status[name] = true;
		emit send_stu_status(name, true);
		return;
	}
}

bool teacher_portal::OpenDatabase() {
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

void teacher_portal::calpath(Graph& G, int oneVertex, int length) {
	if (G.Outdegree[oneVertex] == 0) {
		maxn = max(length, maxn);
		return;
	}
	for (int i = 0; i < G.Outdegree[oneVertex]; i++) {
		Edge e = G.GetEdge(oneVertex, i + 1);
		calpath(G, e.to, length + 1);
	}
}

bool teacher_portal::graph_set(Graphl*& G, vector<course>& mycourses) {
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
