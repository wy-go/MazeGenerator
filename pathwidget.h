#ifndef PATHWIDGET_H
#define PATHWIDGET_H

#include "mazewidget.h"

class PathWidget : public MazeWidget {
public:
    explicit PathWidget(MazeWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // PATHWIDGET_H
