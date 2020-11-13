#ifndef MAZEWIDGET_H
#define MAZEWIDGET_H

#include <QWidget>
#include <QPainter>
#include "maze.h"

const int MIN_WIDTH = 500;
const int MARGIN = 50;
const int WIDTH_ADJUSTER = 350;

class MazeWidget : public QWidget {
public:
    explicit MazeWidget(QWidget *parent = nullptr);
    MazeWidget(int n, int step = 0);
    bool empty();
    void setMaze(const MazeWidget *m);
    void setStep(const int s);
protected:
    void paintEvent(QPaintEvent *event);
    Maze *maze;
    int step;
    bool **wall;
};

#endif // MAZEWIDGET_H
