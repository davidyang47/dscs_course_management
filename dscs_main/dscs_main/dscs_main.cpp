#include <bits/stdc++.h>
#include "Graph.h"
#include "Graphl.h"
using namespace std;

int maxn = -1;

struct arrange {
    string course_name;
    //string teacher_name;
    string course_time;
};

class course{
 public:
    int no;
    string name;
    int credits;
    int hours;
    string sort;
    vector<string> prerequisites;
    course() {
		no=0;
		name="";
		credits=0;
		hours=0;
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
vector<course> mycourses;

class table {
 public:
	int term;
	vector<course> courses;
    arrange course_table[4][5];
    table() {
		term = 0;
        courses.clear();
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 5; j++) {
               course_table[i][j].course_name = "";
               course_table[i][j].course_time = "";
            }
        }
	}
    table(int term, vector<course> courses) {
		this->term = term;
		this->courses = courses;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 5; j++) {
                course_table[i][j].course_name = "";
                course_table[i][j].course_time = "";
            }
        }
	}
    bool set_table(course c) {
        courses.push_back(c);
        vector<int> time;
        time.clear();
        int h= c.hours;
        int i, j, end_week;
        while (h > 0) {
            vector<int>::iterator it;
            do {
                i = rand() % 4;
                j = rand() % 5;
                it = find(time.begin(), time.end(), j);
            } while ((it != time.end()) || (course_table[i][j].course_name != ""));
            if (h % 32 != 0) {
                end_week = h % 32 / 2;
                h -= end_week * 2;
            }
            else {
                end_week = 16;
                h -= 32;
            }
            course_table[i][j].course_name = c.name;
            course_table[i][j].course_time = "1-" + to_string(end_week) + "周"+to_string(j+1)+"第"+to_string(i+1)+"节";
            time.push_back(j);
        }
        time.clear();
        return true;
    }
    bool show_table() {
        cout << "the classtable of term " << term << " is:"<<endl;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 5; j++) {
                if(course_table[i][j].course_name!="")
                    cout << course_table[i][j].course_name << ":" << course_table[i][j].course_time ;
                cout << "     ";
			}
			cout << endl;
        }
        return true;
    }
	~table() {}
};

void Visit(Graph& G, course v) {
    cout << v.name<< " ";
}

void calpath(Graph &G, int oneVertex, int length) {
    if (G.Outdegree[oneVertex] == 0) {
        maxn = max(length, maxn);
        return;
    }
    for (int i = 0; i < G.Outdegree[oneVertex]; i++) {
        Edge e = G.GetEdge(oneVertex, i + 1);
        calpath(G, e.to, length + 1);
    }
}

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
        tmp.sort = words[4];
        for (int i = 5; i < words.size(); i++)
        {
            tmp.prerequisites.push_back(words[i]);
        }
        mycourses.push_back(tmp);
    }
    csv_data.close();
    return true;
}

bool graph_set(Graph& G, vector<course>& mycourses) {
    for (int i = 0; i < mycourses.size(); i++) {
        for (int j = 0; j < mycourses[i].prerequisites.size(); j++) {
            for (int k = 0; k < mycourses.size(); k++) {
                if (mycourses[k].name == mycourses[i].prerequisites[j]) {
					G.setEdge(k, i, 1);
				}
			}
		}
	}
	return true;
}

bool draw_graph(Graph& G) {
    for (int i = 0; i < G.VerticesNum(); i++)
        G.Mark[i] = UNVISITED;
    stack<course> s1;
    map<string, course> m1;
    vector<vector<string> > layers(8);
    int* indegree = new int[G.VerticesNum()];
    for (int i = 0; i < G.VerticesNum(); i++)
		indegree[i] = G.Indegree[i];
    int layer = 0;
    for (int i = 0; i < G.VerticesNum(); i++)
        if (indegree[i] == 0) 
            m1[mycourses[i].name] = mycourses[i];
    while (!s1.empty() || !m1.empty()) {              //如果队列中还有图的顶点
        map<string, course>::iterator iter;
        iter = m1.begin();
        while (iter != m1.end()) {
            s1.push(iter->second);
            layers[layer].push_back(iter->first);
            iter++;
        }
        m1.clear();
        while (!s1.empty()) {
            course V = s1.top();
            s1.pop();                     //一个顶点出队
            int no = V.no - 1;
            G.Mark[no] = VISITED;
            for (Edge e = G.FirstEdge(no); G.IsEdge(e); e = G.NextEdge(e)) {
                indegree[G.ToVertex(e)]--;  //所有与之相邻的顶点入度-1
                if (indegree[G.ToVertex(e)] == 0) {
                    m1[mycourses[G.ToVertex(e)].name] = mycourses[G.ToVertex(e)];
                }
            }
        }
        layer++;
    }
    for (int i = 0; i < G.VerticesNum(); i++)
        if (G.Mark[i] == UNVISITED) {
            cout << " 此图有环！";        //图有环
            return false;
        }
    cout << endl;
    for (int i = 0; i < layers.size(); i++) {
        for(int j=0;j<layers[i].size();j++)
			cout << layers[i][j] << " ";
        cout << endl<<endl;
    }
    return true;
}

bool TopsortbyStack(Graph& G) {     
    for (int i = 0; i < G.VerticesNum(); i++)
        G.Mark[i] = UNVISITED;
    stack<course> s1;
    map<string, course> m1;  // 用于暂存课程名和课程的对应关系
    vector<table> tables;
    int hours_count = 0;
    int term = 1;
    for (int i = 0; i < G.VerticesNum(); i++)
        if (G.Indegree[i] == 0) {
            m1[mycourses[i].name] = mycourses[i];
            hours_count += mycourses[i].hours;
        }
    while (!s1.empty() || !m1.empty()) {              //如果队列中还有图的顶点
        if (hours_count > 310) {
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
            while(hours_tmp>310){
                cout << "input the course you want to choose:";
                hours_tmp = 0;
                string select;
                getline(cin, select);
                if(select=="")
					continue;
                istringstream sin;
                string course_name;
                sin.clear();
                sin.str(select);
                course_names.clear();
                while (getline(sin, course_name, ' ')) {
                    if (!m1.count(course_name)) {
						cout<<"the course you input is not in the list! Please input again"<<endl;
                        hours_tmp = 315;
						break;
					}
                    course_names.push_back(course_name);
                    hours_tmp += m1[course_name].hours;
                }
                map<string, course>::iterator iter;
                iter = m1.begin();
                while (iter != m1.end()) {
                    if (find(course_names.begin(), course_names.end(), iter->first) == course_names.end()) {  
                        if (8 - G.path[iter->second.no - 1] == term) {
                            cout<<iter->first<<" has to be chosen this term or you can't graduate on time"<<endl;
                            hours_tmp = 315;
                        }
					}
                    iter++;
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
        table t1;
        t1.term = term;
        while(!s1.empty()){         
            course V = s1.top();
            s1.pop();                     //一个顶点出队
            t1.set_table(V);
            //Visit(G, V);
            int no = V.no - 1;
            G.Mark[no] = VISITED;
            for (Edge e = G.FirstEdge(no); G.IsEdge(e); e = G.NextEdge(e)) {
                G.Indegree[G.ToVertex(e)]--;  //所有与之相邻的顶点入度-1
                if (G.Indegree[G.ToVertex(e)] == 0 && mycourses[G.ToVertex(e)].sort != "选修课") {
                    m1[mycourses[G.ToVertex(e)].name] = mycourses[G.ToVertex(e)];
                    //if(mycourses[G.ToVertex(e)].sort != "选修课")
                    hours_count += mycourses[G.ToVertex(e)].hours;
                }
            }
        }
        t1.show_table();
        tables.push_back(t1);
        term++;
        cout<< endl;
    }
    //for (int i = 0; i < G.VerticesNum(); i++)
    //    if (G.Mark[i] == UNVISITED) {
    //        cout << " 此图有环！";        //图有环
    //        return false;
    //    }
    return true;
}

int main()
{
    write_in();
    read_in(mycourses);
    for(int i=0;i<mycourses.size();i++){
        cout<<mycourses[i].no<<" "<<mycourses[i].name<<" "<<mycourses[i].credits<<" "<<mycourses[i].hours<<" "<<mycourses[i].sort<<" ";
        for(int j=0;j<mycourses[i].prerequisites.size();j++){
            cout<<mycourses[i].prerequisites[j]<<" ";
        }
        cout<<endl;
    }
    Graphl aGraphl(mycourses.size());
    graph_set(aGraphl, mycourses);
    for (int i = 0; i < aGraphl.VerticesNum(); i++) {
        calpath(aGraphl, i, 0);
        aGraphl.path[i] = maxn;
        maxn = -1;
	}
    for (int i = 0; i < aGraphl.VerticesNum(); i++) {
        //cout<<aGraphl.Outdegree[i]<<" "<<mycourses[i].name<<endl;
		cout<<mycourses[i].name<<" "<<aGraphl.path[i]<<endl;
	}
    draw_graph(aGraphl);
    TopsortbyStack(aGraphl);
    return 0;
}
