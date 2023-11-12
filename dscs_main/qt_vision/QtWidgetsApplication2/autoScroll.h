#ifndef AUTOSCROLL_H
#define AUTOSCROLL_H

#include <QtWidgets>

class autoScroll : public QScrollArea
{
    Q_OBJECT

public:
    enum ScrollDirection { NoScroll, ScrollUp, ScrollDown };
    autoScroll(QWidget* parent = nullptr) : QScrollArea(parent)
    {
        setWidgetResizable(true);
        setMouseTracking(true);
        // Initialize the scrolling variables
        scrollSpeed = 2;
        scrollMargin = 20; // Adjust the margin as needed
        scrollDirection = NoScroll;
        scrollTimerId = 0;
    }

protected:
    void mouseMoveEvent(QMouseEvent* event) override
    {
        if (event->y() <= scrollMargin) {
            startScroll(ScrollUp);
        }
        else if (event->y() >= height() - scrollMargin) {
            startScroll(ScrollDown);
        }
        else {
            stopScroll();
        }
    }

    void timerEvent(QTimerEvent* event) override
    {
        if (scrollDirection == ScrollUp) {
            verticalScrollBar()->setValue(verticalScrollBar()->value() - scrollSpeed);
        }
        else if (scrollDirection == ScrollDown) {
            verticalScrollBar()->setValue(verticalScrollBar()->value() + scrollSpeed);
        }
    }

    void startScroll(ScrollDirection direction)
    {
        if (scrollDirection != direction) {
            stopScroll();
            scrollDirection = direction;
            scrollTimerId = startTimer(10); // Adjust the timer interval as needed
        }
    }

    void stopScroll()
    {
        if (scrollDirection != NoScroll) {
            killTimer(scrollTimerId);
            scrollDirection = NoScroll;
        }
    }

private:
    
    int scrollSpeed;
    int scrollMargin;
    int scrollTimerId;
    ScrollDirection scrollDirection;
};

#endif // AUTOSCROLL_H