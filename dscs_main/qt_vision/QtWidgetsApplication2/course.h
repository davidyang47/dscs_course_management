#ifndef COURSE_H
#define COURSE_H
#include <bits/stdc++.h>
using namespace std;
class course {
public:
	int no;
	string name;
	int credits;
	int hours;
	string sort;
	vector<string> prerequisites;
	course() {
		no = 0;
		name = "";
		credits = 0;
		hours = 0;
		sort = "";
	}
	course(int no, string name, int credits, int hours, string sort, vector<string> prerequisites) {
		this->no = no;
		this->name = name;
		this->credits = credits;
		this->hours = hours;
		this->sort = sort;
		this->prerequisites = prerequisites;
	}
	~course() {}
};

#endif // COURSE_H