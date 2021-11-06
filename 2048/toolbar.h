#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QApplication>
#include <QVBoxLayout>
#include <QGuiApplication>
#include <QObject>
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QVector>
#include <QMainWindow>
#include <QSpacerItem>
#include <QTextFormat>
#include <QFont>
#include <QString>
#include <QKeyEvent>
#include <QMessageBox>

class ToolBar : public QWidget
{
    Q_OBJECT

public:
    ToolBar(int = 0, QWidget* = nullptr);
    ~ToolBar();
    QHBoxLayout* settingScore(int val = 0);
    QVBoxLayout *mainLayout;
    QLabel* score;
    void updateScore(int = 0);
private:
    const int SCREENHEIGHT = QGuiApplication::primaryScreen()->geometry().height();
    const int SCREENLWIDTH= QGuiApplication::primaryScreen()->geometry().width();

signals:
        void newGame();
};


#endif // TOOLBAR_H
