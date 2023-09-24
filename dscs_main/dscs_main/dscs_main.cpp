#include <bits/stdc++.h>
#include "Graph.h"
#include "Graphl.h"
using namespace std;

struct course{
    int no;
    string name;
    int credits;
    int hours;
    vector<string> prerequisites;
};
vector<course> mycourses;

bool write_in(){
    ofstream csv_data("test.csv", ios::app);
    if (!csv_data.is_open())
    {
        cout << "Error: opening file fail" << endl;
        exit(1);
    }
    string line;
    while(getline(cin, line)){
        if(line=="end")
            break;
        else if(line=="")
            continue;
        else
            csv_data<<line<<endl;
    }
    return true;
}

bool read_in(vector<course> &mycourses){
    ifstream csv_data("test.csv", ios::in);
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
        for (int i = 4; i < words.size(); i++)
        {
            tmp.prerequisites.push_back(words[i]);
        }
        mycourses.push_back(tmp);
    }
    csv_data.close();
    return true;
}

int main()
{
    write_in();
    read_in(mycourses);
    for(int i=0;i<mycourses.size();i++){
        cout<<mycourses[i].no<<" "<<mycourses[i].name<<" "<<mycourses[i].credits<<" "<<mycourses[i].hours<<" ";
        for(int j=0;j<mycourses[i].prerequisites.size();j++){
            cout<<mycourses[i].prerequisites[j]<<" ";
        }
        cout<<endl;
    }
    Graphl aGraphl(mycourses.size());
    for (int i = 0; i < mycourses.size(); i++) {
        for (int j = 0; j < mycourses[i].prerequisites.size(); j++) {
            for (int k = 0; k < mycourses.size(); k++) {
                if (mycourses[k].name == mycourses[i].prerequisites[j]) {
					aGraphl.setEdge(k, i, 1);
				}
			}
		}
	}
    cout << "DFS: ";
    aGraphl.DFS(aGraphl, 0);
    cout << endl;
    return 0;
}
