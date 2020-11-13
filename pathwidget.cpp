#include "pathwidget.h"

PathWidget::PathWidget(MazeWidget *parent) : MazeWidget(parent) {}

/**
 * Overload of paintEvent to draw maze and path,
 * with invoke of paintEvent of MazeWidget.
 */
void PathWidget::paintEvent(QPaintEvent *event) {
    int n = maze->n;
    MazeWidget::paintEvent(event);
    int w = (this->width() + WIDTH_ADJUSTER - 2 * MARGIN);    // width of maze
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QColor(Qt::red));    // draw path in red
    std::stack<int> p(maze->path);    // temporary copy of path stack
    int a = p.top(), b;
    p.pop();
    while (!p.empty()) {    // draw line ab repeatedly until stack is empty
       b = p.top();
       p.pop();
       int x1 = MARGIN + (a % n + 0.5) * w / (2 * n);
       int x2 = MARGIN + (b % n + 0.5) * w / (2 * n);
       int y1 = MARGIN + (a / n + 0.5) * w / (2 * n);
       int y2 = MARGIN + (b / n + 0.5) * w / (2 * n);
       painter.drawLine (x1, y1, x2, y2);
       a = b;
   }
}
