#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QLabel>
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QVector>
#include <QMainWindow>
#include <QWidget>
#include <QSpacerItem>
#include <QTextFormat>
#include <QFont>
#include <QString>
#include <cmath>
#include <QKeyEvent>
#include <QMessageBox>
#include "toolbar.h"
#include <QGuiApplication>

class Board : public QWidget
{
    Q_OBJECT

public:
    Board(QWidget* = nullptr);
    ~Board();
private:
    const int SCREENHEIGHT = QGuiApplication::primaryScreen()->geometry().height();
    const int COLORRGB = 255; // constant for rgb-conversion
    int board[4][4] = {}; // board automatically initalized with zeroes
    QGridLayout *grid;
    QVector<QLabel*> labels;
    void creatingBoard();
    void settingBoard();
    void generateAndAddNewNumber();
    void caseUp();
    void caseDown();
    void caseRight();
    void caseLeft();
    void movingElementsUp();
    void movingElementsDown();
    void movingElementsLeft();
    void movingElementsRight();
    bool canMoveUp();
    bool canMoveDown();
    bool canMoveLeft();
    bool canMoveRight();
    bool hasOptionsToMove();
    bool isEmpty();
    bool hasSpace();
    bool hasWon();
    QString calculatingColor(int);

signals:
    void hasMerged(int = 0);

protected:
    void keyPressEvent(QKeyEvent* );
};

#endif // BOARD_H
