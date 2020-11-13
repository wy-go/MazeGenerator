#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    this->setMinimumSize(MIN_SIZE);
    w = new QWidget(this);
    this->setCentralWidget(w);

    l = new QWidget(w);
    l->setMinimumHeight(L_MIN_HEI);
    vl = new QVBoxLayout(l);
    prompt = new QLabel(l);
    prompt->setText("Input an integer n to get an n × n maze!");
    prompt->setAlignment(Qt::AlignCenter);
    prompt->setFixedSize(PROMPT_SIZE);
    prompt->setFont(PF);
    mazePath = new MazeWidget();
    vl->addWidget(prompt);

    r = new QWidget(w);
    r->setMinimumWidth(R_MIN_WIDTH);
    vr = new QVBoxLayout(r);
    spacer = new QLabel(r);
    spacer->setFixedHeight(SPACER_HEI);
    create = new QPushButton(r);
    create->setText("create");
    creationProcess = new QPushButton(r);
    creationProcess->setText("creation     process");
    showPath = new QPushButton(r);
    showPath->setText("show           path");
    create->setFont(BF);
    creationProcess->setFont(BF);
    showPath->setFont(BF);
    le = new QLineEdit(r);
    le->setPlaceholderText("input a positive integer");
    vr->addWidget(spacer);
    vr->addWidget(create);
    vr->addWidget(creationProcess);
    vr->addWidget(showPath);
    vr->addWidget(le);

    QWidget *rr = new QWidget();
    rr->setFixedWidth(RR_WIDTH);

    h = new QHBoxLayout(w);
    h->addWidget(l);
    h->addWidget(r);
    h->addWidget(rr);
    h->setStretchFactor(l, 3);
    h->setStretchFactor(r, 1);
    h->setStretchFactor(rr, 1);

    connect(create, &QPushButton::clicked, this, &MainWindow::maze);
    connect(creationProcess, &QPushButton::clicked, this, &MainWindow::process);
    connect(showPath, &QPushButton::clicked, this, &MainWindow::path);
}

MainWindow::~MainWindow() {
    delete mazePath;
}

void MainWindow::maze() {
    int n = (le->text().trimmed()).toInt();
    std::cout << "Input: n = " << n << std::endl;
    if (n <= 0 || n > 200) {
        if (n <= 0)
            refreshLe("input a positive integer");
        else
            refreshLe("too large");
    } else {
        if (stepCount > 0 && stepCount <= n * n)
            timer->stop();
        this->n = n;
        prompt->setParent(nullptr);
        mazePath->setParent(nullptr);
        vl->removeWidget(prompt);
        vl->removeWidget(mazePath);
        prompt->setText(QString::number(n) + " × "+ QString::number(n));
        mazePath = new MazeWidget(n);
        vl->addWidget(prompt);
        vl->addWidget(mazePath);
    }
}

/**
 * Slot function connected with creationProcess.
 */
void MainWindow::process() {
    if (mazePath->empty()) {    // click button without creating a maze first
       std::cout << "empty" << std::endl;
       refreshLe("create a maze first");
    } else {
        if (stepCount > 0 && stepCount <= n * n) {    // last process unfinished
            mazePath->setStep(0);
            std::cout << "Process interrupted, step = 0" << std::endl;
            timer->stop();
        }
        stepCount = 0;
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(oneStep()));
        timer->start(REFRESH_CYCLE);
    }
}

/**
 * Slot function react to signal timeout().
 * Refresh widget to show building maze。
 */
void MainWindow::oneStep() {
    mazePath->setParent(nullptr);
    vl->removeWidget(mazePath);
    mazePath->setStep(stepCount++);
    vl->addWidget(mazePath);
    if (stepCount > n * n) {
        mazePath->setStep(0);
        std::cout << "Process finished, step = 0" << std::endl;
        timer->stop();
    }
}

void MainWindow::path() {
    if (mazePath->empty()) {
        std::cout << "empty" << std::endl;
        refreshLe("create a maze first");
    } else {
        if (stepCount > 0 && stepCount <= n * n) {
            mazePath->setStep(0);
            std::cout << "Process interrupted, step = 0" << std::endl;
            timer->stop();
        }
        PathWidget *pw = new PathWidget();
        pw->setMaze(mazePath);
        mazePath->setParent(nullptr);
        vl->removeWidget(mazePath);
        mazePath = pw;
        vl->addWidget(mazePath);
    }
}

void MainWindow::refreshLe(QString str) {
    le->setParent(nullptr);
    vr->removeWidget(le);
    le = new QLineEdit(r);
    le->setPlaceholderText(str);
    vr->addWidget(le);
}
