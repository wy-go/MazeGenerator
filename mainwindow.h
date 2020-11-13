#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTimer>
#include "mazewidget.h"
#include "pathwidget.h"

const QSize MIN_SIZE(900, 600);
const QSize PROMPT_SIZE(515, 50);
const QFont PF("Papyrus", 23);
const QFont BF("Marker Felt", 20);
const int L_MIN_HEI = 450, R_MIN_WIDTH = 180;
const int SPACER_HEI = 20, RR_WIDTH = 40;
const int REFRESH_CYCLE= 20;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QWidget *w, *l, *r;
    QVBoxLayout *vl, *vr;
    QHBoxLayout *h;
    QLabel *prompt, *spacer;
    QLineEdit *le;
    QPushButton *create, *creationProcess, *showPath;
    QTimer *timer;
    MazeWidget *mazePath;
    int n, stepCount;
    void refreshLe(QString str);
public slots:
    void maze();
    void path();
    void process();
    void oneStep();
};

#endif // MAINWINDOW_H
