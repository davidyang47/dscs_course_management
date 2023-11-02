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
	connect(ui.back_to, &QPushButton::clicked, this, &teacher_portal::back_to_login);
}

teacher_portal::~teacher_portal(){}

void teacher_portal::read() {
	if (read_in(mycourses))
	{
		graph_set(aGraphl, mycourses);
		//aGraphl = new Graphl(mycourses.size());
		//for (int i = 0; i < mycourses.size(); i++) {
		//	for (int j = 0; j < mycourses[i].prerequisites.size(); j++) {
		//		for (int k = 0; k < mycourses.size(); k++) {
		//			if (mycourses[k].name == mycourses[i].prerequisites[j]) {
		//				aGraphl->setEdge(k, i, 1);
		//			}
		//		}
		//	}
		//}
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
		//if (d) {
		//	d->close();
		//	delete d;
		//	d = nullptr;
		//}
		if(d)
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
				gridLayout->addWidget(checkBox, i / 3, i % 3); // i / 2 行，i % 2 列
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
		}
		else if (mode == 2) {
			QWidget* time_w = new QWidget(contentWidget);
			QVBoxLayout* time_v = new QVBoxLayout(time_w);
			time_w->setGeometry(QRect(150, 50, 700, 200));
			QHBoxLayout* time_h = new QHBoxLayout;
			QLabel* former_time=new QLabel(QString::fromLocal8Bit("当前学分限制为:")+QString::number(time_limit));
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
		}
		connect(add2, &QPushButton::clicked, this, &teacher_portal::cancel);
	}
	else {
		QMessageBox::warning(this, "hint", "please read in first");
	}
}

void teacher_portal::add_course() {
	int sno= when_add[0]->text().toInt();
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
	tmp.credits = when_add[2]->text().toInt();
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

	//将tmp写入文件尾部
	ofstream course_file(filepath, ios::app);
	course_file << tmp.no << "," << tmp.name << "," << tmp.credits << "," << tmp.hours << "," << tmp.sort;
	for (const string& prereq : tmp.prerequisites) {
		course_file << "," << prereq;
	}
	course_file << "\n";

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

void teacher_portal::set_time(){
	int time = when_add[0]->text().toInt();
	if (time < 0) {
		QMessageBox::warning(this, "hint", "time should be positive");
		return;
	}
	if (time < 310) {
		QMessageBox::StandardButton check;
		check = QMessageBox::question(this, "hint", "time maybe too small, are you sure ?", QMessageBox::Yes | QMessageBox::No);
		if(check==QMessageBox::No)
			return;
	}
	time_limit = time;
	emit send_time_changed(time);
	cancel();
}

bool teacher_portal::read_in(vector<course>& mycourses) {
	mycourses.clear();
	QString path = QFileDialog::getOpenFileName(this, "OPEN", "../", "CSV(*.csv)");//设置文件路径 文件格式

	if (path.isEmpty() == false) {//路径正确
		filepath = path.toStdString();
		ifstream csv_data(filepath, ios::in);
		string line;

		if (!csv_data.is_open())
		{
			cout << "Error: opening file fail" << endl;
			exit(1);
		}

		istringstream sin;         //将整行字符串line读入到字符串istringstream中
		vector<string> words; //声明一个字符串向量
		string word;

		// 读取标题行
		getline(csv_data, line);
		int count = 0;
		// 读取数据
		while (getline(csv_data, line))
		{
			sin.clear();
			sin.str(line);
			words.clear();
			while (getline(sin, word, ',')) //将字符串流sin中的字符读到word字符串中，以逗号为分隔符
			{
				words.push_back(word); //将每一格中的数据逐个push
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
	return false;
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
