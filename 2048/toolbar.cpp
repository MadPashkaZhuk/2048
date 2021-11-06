#include "toolbar.h"
#include <board.h>

ToolBar::ToolBar(int num, QWidget* window) : QWidget(window)
{
    this->setFixedSize(SCREENLWIDTH - SCREENHEIGHT, SCREENHEIGHT * 0.8);
    mainLayout = new QVBoxLayout(this);
    QHBoxLayout *boxForButtons = new QHBoxLayout(this);
    boxForButtons->setSpacing((SCREENLWIDTH - SCREENHEIGHT) * 0.1);
    QFont font("Arial", ((SCREENLWIDTH - SCREENHEIGHT) / 3) / 8);

    QPushButton *newGameButton = new QPushButton("New game", this);
    newGameButton->setStyleSheet("background:rgb(255,255,200);");
    newGameButton->setFont(font);
    newGameButton->setFixedSize((SCREENLWIDTH - SCREENHEIGHT) / 2.5, (SCREENLWIDTH - SCREENHEIGHT) / 3);
    boxForButtons->addWidget(newGameButton, 0, Qt::AlignTop | Qt::AlignTop);
    connect(newGameButton, &QPushButton::clicked, this, &ToolBar::newGame);

    QPushButton *quitButton = new QPushButton("Quit", this);
    quitButton->setStyleSheet("background:rgb(255,255,200);");
    quitButton->setFont(font);
    quitButton->setFixedSize((SCREENLWIDTH - SCREENHEIGHT) / 2.5, (SCREENLWIDTH - SCREENHEIGHT) / 3);
    boxForButtons->addWidget(quitButton, 0, Qt::AlignTop | Qt::AlignTop);
    connect(quitButton,  &QPushButton::clicked, this, &QApplication::quit);

    mainLayout->addLayout(settingScore(num));
    mainLayout->addLayout(boxForButtons);
    mainLayout->setSpacing(SCREENHEIGHT / 4 - 10);
}

ToolBar::~ToolBar() = default;

QHBoxLayout* ToolBar::settingScore(int scoreValue) {
    QFont font("Arial", ((SCREENLWIDTH - SCREENHEIGHT) / 3) / 8);
    score = new QLabel;
    QString scoreString = "Score: " + QString::number(scoreValue);
    score->setText(scoreString);
    score->setFixedSize((SCREENLWIDTH - SCREENHEIGHT) * 0.5, (SCREENLWIDTH - SCREENHEIGHT) / 3);
    score->setStyleSheet("background:rgb(255, 255, 255);");
    score->setFont(font);
    score->setAlignment(Qt::AlignCenter);
    QHBoxLayout *boxForScore = new QHBoxLayout(this);
    boxForScore->addWidget(score);
    mainLayout->addLayout(boxForScore);
    return boxForScore;
}

void ToolBar::updateScore(int newScore) {
    QString scoreString = "Score: " + QString::number(newScore);
    score->setText(scoreString);
}

