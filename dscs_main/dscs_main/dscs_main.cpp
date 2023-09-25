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

void Visit(Graph& G, course v) {
    cout << v.name<< " ";
}

bool write_in(){
    ofstream csv_data("test1.csv", ios::app);
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
    ifstream csv_data("test1.csv", ios::in);
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

bool graph_set(Graphl& aGraphl, vector<course>& mycourses) {
    for (int i = 0; i < mycourses.size(); i++) {
        for (int j = 0; j < mycourses[i].prerequisites.size(); j++) {
            for (int k = 0; k < mycourses.size(); k++) {
                if (mycourses[k].name == mycourses[i].prerequisites[j]) {
					aGraphl.setEdge(k, i, 1);
				}
			}
		}
	}
	return true;
}

bool TopsortbyStack(Graph& G) {     
    for (int i = 0; i < G.VerticesNum(); i++)
        G.Mark[i] = UNVISITED;
    stack<course> s1;
    map<string, course> m1;  // 用于暂存课程名和课程的对应关系
    int hours_count = 0;
    int term = 1;
    for (int i = 0; i < G.VerticesNum(); i++)
        if (G.Indegree[i] == 0) {
            m1[mycourses[i].name] = mycourses[i];
            hours_count += mycourses[i].hours;
        }
    while (!s1.empty() || !m1.empty()) {              //如果队列中还有图的顶点
        if (hours_count > 280) {
            map<string, course>::iterator iter;
            iter = m1.begin();
            while (iter != m1.end()) {
                string key = iter->first;
                cout << key << " ";
                iter++;
            }
            cout << endl;
            int hours_tmp=hours_count;  
            vector<string> course_names;
            while(hours_tmp>280){
                cout << "input the course you want to choose:";
                hours_tmp = 0;
                string select;
                getline(cin, select);
                istringstream sin;
                string course_name;
                sin.clear();
                sin.str(select);
                course_names.clear();
                while (getline(sin, course_name, ' ')) {
                    if (!m1.count(course_name)) {
						cout<<"the course you input is not in the list! Please input again"<<endl;
                        hours_tmp = 285;
						break;
					}
                    course_names.push_back(course_name);
                    hours_tmp += m1[course_name].hours;
                }
            }
            hours_count -= hours_tmp;
            for (int i = 0; i < course_names.size(); i++) {
                s1.push(m1[course_names[i]]);
                m1.erase(course_names[i]);
            }
        }
        else {
            map<string, course>::iterator iter;
            iter = m1.begin();
            while (iter != m1.end()) {
                s1.push(iter->second);
                iter++;
            }
            m1.clear();
            hours_count = 0;
        } 
        cout << "the classtable of term " << term << " is:";
        while(!s1.empty()){         
            course V = s1.top();
            s1.pop();                     //一个顶点出队
            Visit(G, V);
            int no = V.no - 1;
            G.Mark[no] = VISITED;
            for (Edge e = G.FirstEdge(no); G.IsEdge(e); e = G.NextEdge(e)) {
                G.Indegree[G.ToVertex(e)]--;  //所有与之相邻的顶点入度-1
                if (G.Indegree[G.ToVertex(e)] == 0) {
                    m1[mycourses[G.ToVertex(e)].name] = mycourses[G.ToVertex(e)];
                    hours_count += mycourses[G.ToVertex(e)].hours;
                }
            }
        }
        term++;
        cout<< endl;
    }
    for (int i = 0; i < G.VerticesNum(); i++)
        if (G.Mark[i] == UNVISITED) {
            cout << " 此图有环！";        //图有环
            return false;
        }
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
    graph_set(aGraphl, mycourses);
    TopsortbyStack(aGraphl);
    return 0;
}
