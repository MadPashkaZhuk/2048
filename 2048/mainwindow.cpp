#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

    ui->setupUi(this);
    this->setWindowTitle("2048");
    this->setWindowIcon(QIcon("C:\\Users\\paska\\OneDrive\\Documents\\untitled1\\2048.ico"));
    board = new Board;
    bar = new ToolBar;

    mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(board);
    board->setFocusPolicy(Qt::StrongFocus);
    mainLayout->addWidget(bar);
    ui->centralwidget->setLayout(mainLayout);
    //ui->centralwidget->setFocusPolicy(Qt::StrongFocus);
    connect(bar, &ToolBar::newGame, this, &MainWindow::newGameSlot);
    connect(board, &Board::hasMerged, this, &MainWindow::hasMergedSlot);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::newGameSlot() {
     board->setFocusPolicy(Qt::NoFocus);
     Board* newBoard = new Board;
     newBoard->setFocusPolicy(Qt::StrongFocus);
     board = newBoard;
     mainLayout->replaceWidget(mainLayout->itemAt(0)->widget(),board);
     board->setFocusPolicy(Qt::StrongFocus);
     ui->centralwidget->setLayout(mainLayout);
     bar->updateScore(scoreValue = 0);
     connect(board, &Board::hasMerged, this, &MainWindow::hasMergedSlot);
}

void MainWindow::hasMergedSlot(int num) {
    scoreValue += num;
    bar->updateScore(scoreValue);
}
