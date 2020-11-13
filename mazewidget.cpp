#include "mazewidget.h"

MazeWidget::MazeWidget(QWidget *parent) : QWidget(parent) {
     this->setMinimumWidth(MIN_WIDTH);
};

MazeWidget::MazeWidget(int n, int step){
    this->setMinimumWidth(MIN_WIDTH);
    this->maze = new Maze(n);
    this->step = step;
    Maze::initWall(wall, maze->n);
}

bool MazeWidget::empty() {
    return maze == nullptr;
}

void MazeWidget::setMaze(const MazeWidget *m) {
    this->maze = m->maze;
}

void MazeWidget::setStep(const int s) {
    step = s;
}

/**
  *Overload of paintEvent to draw maze.
  */
void MazeWidget::paintEvent(QPaintEvent *event) {
    int n = maze->n;
    std::cout << "step = " << step << " ";
    if (step == 0) {
        Maze::initWall(wall, n);
    } else if (step > 1) {
        int m = n * n - step;
        wall[maze->process[m][0]][maze->process[m][1]] = 0;
        std::cout << maze->process[m][0] << "," << maze->process[m][1] << std::endl;
    }
    double w = this->width() + WIDTH_ADJUSTER - 2 * MARGIN;
    double c = w / (2 * n);    // width of a cell
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    double x, y;
    for (int i = 0; i <= 2 *n; i++) {
        y = MARGIN + i / 2 * w / (2 * n);
        for (int j = 0; j <= 2 * n; j++) {
            x = MARGIN + j / 2 * w / (2 * n);
            if ((i + j) % 2 == 1 && (step? wall[i][j] : maze->wall[i][j])) {
                if (i % 2 == 0)    // horizontal
                    painter.drawLine(x, y, x + c, y);
                else    // vertical
                    painter.drawLine(x, y, x, y + c);
            }
        }
    }
}
