#ifndef DRAWING_H
#define DRAWING_H

#include <QtWidgets>
#include <bits/stdc++.h>
#include "Graph.h"
#include "Graphl.h"
#include "course.h"

using namespace std;

struct coordinate {
    int x;
    int y;
};

class Drawing : public QMainWindow {
    Q_OBJECT
public:
    Drawing(const Graphl& aGraphl, const vector<course>& mycourses, const map<int, int> index, QWidget* parent = nullptr)
        : QMainWindow(parent), aGraphl(aGraphl), mycourses(mycourses), index(index){
        setupUI();
        setInitialWindowSize();
        setMouseTracking(true);
        // Set up zoom parameters
        scaleFactor = 1.0;
        zoomFactor = 1.1;
        isDragging = false;
    }
    vector<vector<string> > get_layers() {
		return layers;
	}

private slots:
    void search_course() {
        QString content = searchLineEdit->text();
        if (content.isEmpty()) {
            for (int i = 0; i < rects_highlight.size(); i++) {
                for (int j = 0; j < rects_highlight[i].size(); j++) {
                    rects_highlight[i][j] = 0;
                }
            }
            for (int i = 0; i < lines_highlight.size(); i++) {
                lines_highlight[i] = 0;
            }
            update();
            QMessageBox::warning(this, "error", "please input a course");
            return;
        }
        string search_content = content.toLocal8Bit().constData();
        for (int i = 0; i < layers.size(); i++) {
            for (int j = 0; j < layers[i].size(); j++) {
                if (search_content == layers[i][j]) {
                    coordinate center = coordinates[layers[i][j]];
                    for (int k = 0; k < lines.size(); k++) {
                        if ((lines[k].x1() == center.x && lines[k].y1() == center.y + 25) || (lines[k].x2() == center.x && lines[k].y2() == center.y - 25)) {
                            lines_highlight[k] = 1;
                            for (int m = 0; m < rects.size(); m++) {
                                for (int n = 0; n < rects[m].size(); n++) {
                                    if (rects[m][n].contains(lines[k].p1()) || rects[m][n].contains(lines[k].p2()))
                                        rects_highlight[m][n] = 1;
                                }
                            }
                        }
                        else
                            lines_highlight[k] = 2;
                    }
                    for (int m = 0; m < rects_highlight.size(); m++) {
                        for (int n = 0; n < rects_highlight[m].size(); n++) {
                            if (rects_highlight[m][n] != 1)
                                rects_highlight[m][n] = 2;
                        }
                    }
                    rects_highlight[i][j] = 1;
                    update();
                    return;
                }
            }
        }
        for (int i = 0; i < lines_highlight.size(); i++) {
            lines_highlight[i] = 0;
        }
        for (int i = 0; i < rects_highlight.size(); i++) {
            for (int j = 0; j < rects_highlight[i].size(); j++) {
                rects_highlight[i][j] = 0;
            }
        }
        searchLineEdit->clear();
        update();
        QMessageBox::warning(this, "error", "no such course");
    }

protected:
    void paintEvent(QPaintEvent* event) override {
        Q_UNUSED(event);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);

        // Apply scaling transformation
        painter.scale(scaleFactor, scaleFactor);

        // Apply translation transformation for panning
        painter.translate(panOffset);

        int arrowSize = 10;
        // Draw rectangles and arrows
        for (int i = 0; i < rects.size(); i++) {
            for (int j = 0; j < rects[i].size(); j++) {
               // if (i == rect_highlight.x && j==rect_highlight.y)
                if(rects_highlight[i][j]==1)
                    painter.setPen(QPen(Qt::red, 2));
                else if(rects_highlight[i][j]==0)
                    painter.setPen(QPen(Qt::black, 2));
                else {
                    QColor trb = Qt::black;
                    trb.setAlphaF(0.1);
                    painter.setPen(QPen(trb));
                }
                painter.drawRect(rects[i][j]);
                QRectF textRect = rects[i][j].adjusted(0, 0, 0, -arrowSize);
                painter.drawText(textRect, Qt::AlignCenter, QString::fromLocal8Bit(layers[i][j]));
            }
        }
        for (int i = 0; i < lines.size(); i++) {
            //if(i== line_highlight || lines_highlight[i] == 1)
            if (lines_highlight[i] == 1)
                painter.setPen(QPen(Qt::red, 2));
            else if (lines_highlight[i] == 0)
                painter.setPen(QPen(Qt::black, 2));
            else {
                QColor trb = Qt::black;
                trb.setAlphaF(0.1);
                painter.setPen(QPen(trb));
            }
            painter.drawLine(lines[i]);
           
        }
    }

    void wheelEvent(QWheelEvent* event) override {
        // Zoom in/out with the mouse wheel
        if (event->angleDelta().y() > 0) {
            // Zoom in
            scaleFactor *= zoomFactor;
        }
        else {
            // Zoom out
            scaleFactor /= zoomFactor;
        }

        // Redraw the widget
        update();
    }

    void mousePressEvent(QMouseEvent* event) override {
        // Start dragging when the left mouse button is pressed
        if (event->button() == Qt::LeftButton) {
            lastMousePos = event->pos();
            isDragging = true;
        }
    }

    void mouseMoveEvent(QMouseEvent* event) override {
        // Perform panning when dragging with the left mouse button
        if (isDragging) {
            QPoint delta = event->pos() - lastMousePos;
            panOffset += delta;
            lastMousePos = event->pos();
            // Redraw the widget
            update();
        }
        else {
            QPointF mousePos = event->pos();
            // 通过坐标映射进行反向变换，以获取实际坐标
            QPointF scenePos = QPointF(mousePos.x() / scaleFactor - panOffset.x(),
                mousePos.y() / scaleFactor - panOffset.y());

            // 遍历线段，检测鼠标是否位于某条线段上
            for (int i = 0; i < lines.size(); i++) {
                // 检测鼠标是否位于线段上
                if (isPointOnLine(scenePos, lines[i]) && !lines_highlight[i]) {
                    coordinate c1 = { lines[i].x1(),lines[i].y1() - 25 };
                    QString str, end;
                    for (auto& pair : coordinates) {
                        if (pair.second.x == c1.x && pair.second.y == c1.y) {
                            str = QString::fromLocal8Bit(pair.first);
                            break;
                        }
                    }
                    coordinate c2 = { lines[i].x2(),lines[i].y2() + 25 };
                    for (auto& pair : coordinates) {
                        if (pair.second.x == c2.x && pair.second.y == c2.y) {
                            end = QString::fromLocal8Bit(pair.first);
                            break;
                        }
                    }
                    QString coordinatesText = str + "->" + end;

                    // 在状态栏或其他地方显示坐标信息
                    statusBar()->showMessage(coordinatesText);
                    lines_highlight[i] = 1;
                    update();
                    return;
                }
            }
            // 如果鼠标不在任何线段上，清空坐标信息
            statusBar()->clearMessage();
            update();

            if (searchLineEdit->text().isEmpty()) {
                for (int i = 0; i < rects.size(); i++) {
                    for (int j = 0; j < rects[i].size(); j++) {
                        if (rects[i][j].contains(scenePos)) {
                            coordinate center = coordinates[layers[i][j]];
                            for (int k = 0; k < lines.size(); k++) {
                                if ((lines[k].x1() == center.x && lines[k].y1() == center.y + 25) || (lines[k].x2() == center.x && lines[k].y2() == center.y - 25)) {
                                    lines_highlight[k] = 1;
                                    for (int m = 0; m < rects.size(); m++) {
                                        for (int n = 0; n < rects[m].size(); n++) {
                                            if(rects[m][n].contains(lines[k].p1()) || rects[m][n].contains(lines[k].p2()))
												rects_highlight[m][n] = 1;
                                        }
                                    }
                                }
                                else
                                    lines_highlight[k] = 2;
                            }
                            for (int m = 0; m < rects_highlight.size(); m++) {
                                for (int n = 0; n < rects_highlight[m].size(); n++) {
                                    if (rects_highlight[m][n]!=1)
                                        rects_highlight[m][n] = 2;
                                }
                            }
                            rects_highlight[i][j] = 1;
                            update();
                            return;
                        }
                    }
                }
                for (int i = 0; i < rects_highlight.size(); i++) {
                    for (int j = 0; j < rects_highlight[i].size(); j++) {
                        rects_highlight[i][j] = 0;
                    }
                }
                for (int i = 0; i < lines_highlight.size(); i++) {
                    lines_highlight[i] = 0;
                }
            }
        }
    }

    void mouseReleaseEvent(QMouseEvent* event) override {
        // Stop dragging when the left mouse button is released
        if (event->button() == Qt::LeftButton) {
            isDragging = false;
        }
    }

private:
    void setupUI() {
        QWidget* widget = new QWidget(this);
        QHBoxLayout* layout = new QHBoxLayout(widget);
        widget->setGeometry(QRect(20, 20, 250, 80));
        QLabel* label = new QLabel("search for");
        searchLineEdit = new QLineEdit(widget);

        QStringList course_list;
        for (int i = 0; i < mycourses.size(); i++) {
            course_list << QString::fromLocal8Bit(mycourses[i].name);
        }
        QCompleter* completer = new QCompleter(course_list, this);
        searchLineEdit->setCompleter(completer);
        layout->addWidget(label);
        layout->addWidget(searchLineEdit);
        QShortcut* key = new QShortcut(QKeySequence(Qt::Key_Return), this);//创建一个快捷键"Key_Return"键  回车检索
        connect(key, &QShortcut::activated, this, &Drawing::search_course);//连接到指定槽函数

        layers = draw_graph(aGraphl);
        rects.resize(layers.size());
        int rectangleWidth = 110;
        int rectangleHeight = 50;
        int center = 500;

        // Draw rectangles and arrows
        for (int i = 0; i < layers.size(); i++) {
            for (int j = 0; j < layers[i].size(); j++) {
                int x, y;
                if (!layers[i].size() % 2) {
                    x = center - layers[i].size() / 2 * rectangleWidth - (layers[i].size() / 2 - 1) * 150 - 75 - 100*i + j * (rectangleWidth + 150);
                    y = 250 * i;
                }
				else{
                    x = center - layers[i].size() / 2 * 260 - 55 -75*i + j * (rectangleWidth + 150);
					y = 250 * i;
				}

                QRectF rectangle(x, y, rectangleWidth, rectangleHeight);
                rects[i].push_back(rectangle);
                coordinate c = { x + rectangleWidth / 2, y + rectangleHeight / 2 };
                coordinates[layers[i][j]] = c;
            }
        }
        for (int i = 0; i < aGraphl.VerticesNum(); i++) {
            for (Edge e = aGraphl.FirstEdge(i); aGraphl.IsEdge(e); e = aGraphl.NextEdge(e)) {
                int x1 = coordinates[mycourses[aGraphl.FromVertex(e)].name].x;
                int y1 = coordinates[mycourses[aGraphl.FromVertex(e)].name].y + rectangleHeight / 2;
                int x2 = coordinates[mycourses[aGraphl.ToVertex(e)].name].x;
                int y2 = coordinates[mycourses[aGraphl.ToVertex(e)].name].y - rectangleHeight / 2;
                QLineF line(x1, y1, x2, y2);
                lines.push_back(line);
            }
        }
        lines_highlight.resize(lines.size());
        rects_highlight.resize(rects.size());
        for (int i = 0; i < lines_highlight.size(); i++) {
            lines_highlight[i] = 0;
        }
        for (int i = 0; i < rects_highlight.size(); i++) {
            rects_highlight[i].resize(rects[i].size());
            for (int j = 0; j < rects_highlight[i].size(); j++) {
                rects_highlight[i][j] = 0;
            }
        }
    }
    void setInitialWindowSize() {
        resize(1000, 1500);       // Set initial window size
        setMinimumSize(500, 250); // Set minimum window size
    }

    vector<vector<string> > draw_graph(Graph& G) {
        for (int i = 0; i < G.VerticesNum(); i++)
            G.Mark[i] = UNVISITED;
        stack<course> s1;
        map<string, course> m1;
        vector<vector<string> > layers(8);
        int* indegree1 = new int[G.VerticesNum()];
        for (int i = 0; i < G.VerticesNum(); i++)
            indegree1[i] = G.Indegree[i];
        int layer = 0;
        for (int i = 0; i < G.VerticesNum(); i++)
            if (indegree1[i] == 0)
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
                int no;
                for (auto& pair : index) {
                    if (pair.second == V.no) {
                        no = pair.first;
                        break;
                    }
                }
                for (Edge e = G.FirstEdge(no); G.IsEdge(e); e = G.NextEdge(e)) {
                    indegree1[G.ToVertex(e)]--;  //所有与之相邻的顶点入度-1
                    if (indegree1[G.ToVertex(e)] == 0) {
                        m1[mycourses[G.ToVertex(e)].name] = mycourses[G.ToVertex(e)];
                    }
                }
            }
            layer++;
        }
        return layers;
    }

    bool isPointOnLine(const QPointF& point, const QLineF& line) {
        qreal distanceFromStart = QLineF(line.p1(), point).length();
        qreal distanceFromEnd = QLineF(line.p2(), point).length();
        qreal lineLength = line.length();
    
        // 使用一个很小的误差来处理浮点数精度问题
        qreal epsilon = 1e-2;

        return abs(distanceFromStart + distanceFromEnd - lineLength) < epsilon;
    }

    vector<vector<string>> layers;
    Graphl aGraphl;
    vector<course> mycourses;
    map<string, coordinate> coordinates;
    map<int, int> index;   //课程编号和图中序号的对应 前：图中序号 后：课程编号
    qreal scaleFactor;    // Scaling factor for zooming
    qreal zoomFactor;     // Zoom factor for each step
    bool isDragging;      // Flag to indicate whether dragging is in progress
    QPoint lastMousePos;  // Last recorded mouse position during dragging
    QPoint panOffset;     // Offset for panning
    int line_highlight;		// Index of the highlighted line for mouse
    QVector<QLineF> lines; // Vector of lines to draw
    QVector<QVector<QRectF> > rects; // Vector of rectangles to draw
    vector<vector<int> > rects_highlight; // 0: not highlight 1: highlight 2: 虚化
    vector<int> lines_highlight;
    QLineEdit* searchLineEdit;
};


#endif // DRAWING_H 