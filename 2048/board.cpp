#include "board.h"

Board::Board(QWidget* window) : QWidget(window) {
    this->setFixedSize(SCREENHEIGHT * 0.8, SCREENHEIGHT* 0.8);
    grid = new QGridLayout();
    generateAndAddNewNumber();
    creatingBoard();
    settingBoard();
    this->setLayout(grid);
}

Board::~Board() = default;

void Board::generateAndAddNewNumber(){ // calculating free space and adding 2 to this cell
    int newI, newJ, value;
    newI = rand() % 4;
    newJ = rand() % 4;
    while (board[newI][newJ] != NULL) {
        newI = rand() % 4;
        newJ = rand() % 4;
    }
    if(rand() % 100 < 90) // minimalizing the chance to get 4
        value = 2;
    else
        value = 4;
    board[newI][newJ] = value;
}

void Board::creatingBoard() { // creating 16 labels with specifications and adding them to QVector
    for (int i = 0, k = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++, k++) {
            QLabel *label = new QLabel();
            labels.push_back(label);
            labels[k]->setFixedSize( (SCREENHEIGHT * 0.8 / 4) - 10, // 10px - amount for cpacing
                                     (SCREENHEIGHT * 0.8 / 4) - 10);
            labels[k]->setAlignment(Qt::AlignCenter);
            QFont font("Arial", (SCREENHEIGHT * 0.8 / 4) / 4); // giving the number 1/4 of label's size
            labels[k]->setFont(font);
        }
    }
}

void Board::settingBoard() { // adding new cell with 2/4 every move and showing board
    generateAndAddNewNumber();
    for (int i = 0, k = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++, k++) {
            if(board[i][j] == 0)
                labels[k]->setText("");
            else
                labels[k]->setNum(board[i][j]);
            QString color = "QLabel { background-color : " + calculatingColor(board[i][j]) + ";}";
            labels[k]->setStyleSheet(color);
            grid->addWidget(labels[k],i, j, Qt::AlignCenter);
        }
    }
    if(hasWon()) {
        QMessageBox message;
        message.setFixedSize(500,500);
        message.information(this, ":)", "Nice! You won!!!");
    }
    else if(!hasOptionsToMove()) {
        QMessageBox message;
        message.setFixedSize(500,500);
        message.information(this, ":(", "YOU LOST!");
    }
}

bool Board::isEmpty() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if(board[i][j] != NULL)
                return false;
        }
    }
    return true;
}

bool Board::hasWon() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if(board[i][j] == 2048)
                return true;
        }
    }
    return false;
}

bool Board::hasOptionsToMove() {
    if(canMoveDown() || canMoveUp() || canMoveRight() || canMoveLeft() || isEmpty())
        return true;
    else
        return false;
}

QString Board::calculatingColor(int element){ // calculating color with specific RGB parameters(every power of two: - 50 alpha)
    int log, newB = COLORRGB, newG = COLORRGB, newR = COLORRGB;
    if(element == NULL)
        log = 0;
    else
        log = std::log2(element);
    if(log < 5) {
        newB -= 50*log;
    }
    else if (log < 10){
        newG -= 50*(log % 5);
        newB -= 50*5;
    }
    else {
        newR -= 50*(log % 5);
        newG -= 50*5;
        newB -= 50*5;
    }
    return "rgb("+ QString::number(newR) + ',' + QString::number(newG)
            + ','+ QString::number(newB) + ')';
}

void Board::movingElementsUp() {
    for (int j = 0; j < 4; j++) {
        for (int k = 0; k < 3; k++) {
            for (int i = 3; i >= 1; i--) {
                if (board[i][j] != NULL && board[i - 1][j] == NULL) {
                    board[i - 1][j] = board[i][j];
                    board[i][j] = NULL;
                }
            }
        }
    }
}

void Board::movingElementsDown() {
    for (int j = 0; j < 4; j++) {
        for (int k = 0; k < 3; k++) {
            for (int i = 0; i < 3; i++) {
                if (board[i][j] != NULL && board[i + 1][j] == NULL) {
                    board[i + 1][j] = board[i][j];
                    board[i][j] = NULL;
                }
            }
        }
    }
}

void Board::movingElementsLeft() {
    for (int i = 0; i < 4; i++) {
        for (int k = 0; k < 3; k++) {
            for (int j = 3; j >= 1; j--) {
                if (board[i][j] != NULL && board[i][j - 1] == NULL) {
                    board[i][j - 1] = board[i][j];
                    board[i][j] = NULL;
                }
            }
        }
    }
}

void Board::movingElementsRight() {
    for (int i = 0; i < 4; i++) {
        for (int k = 0; k < 3; k++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != NULL && board[i][j + 1] == NULL) {
                    board[i][j + 1] = board[i][j];
                    board[i][j] = NULL;
                }
            }
        }
    }
}

void Board::caseUp(){
    movingElementsUp();
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 3; i++) {
            if (board[i][j] == board[i + 1][j] && board[i][j] != NULL)
            {
                emit hasMerged(board[i][j] * 2);
                board[i][j] *= 2;
                board[i + 1][j] = NULL;
            }
        }
    }
    movingElementsUp();
}

void Board::caseDown(){
    movingElementsDown();
    for (int j = 0; j < 4; j++) {
        for (int i = 3; i > 0; i--) {
            if (board[i][j] == board[i - 1][j] && board[i][j] != NULL)
            {
                emit hasMerged(board[i][j] * 2);
                board[i][j] *= 2;
                board[i - 1][j] = NULL;
            }
        }
    }
    movingElementsDown();
}

void Board::caseRight(){
    movingElementsRight();
    for (int i = 0; i < 4; i++) {
        for (int j = 3; j > 0; j--) {
            if (board[i][j] == board[i][j - 1] && board[i][j] != NULL)
            {
                emit hasMerged(board[i][j] * 2);
                board[i][j] *= 2;
                board[i][j - 1] = NULL;
            }
        }
    }

    movingElementsRight();
}

void Board::caseLeft(){
    movingElementsLeft();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == board[i][j + 1] && board[i][j] != NULL)
            {
                emit hasMerged(board[i][j] * 2);
                board[i][j] *= 2;
                board[i][j + 1] = NULL;
            }
        }
    }
    movingElementsLeft();
}

bool Board::canMoveUp() {
    for (int j = 0; j < 4; j++) {
        for (int i = 3; i >= 1; i--) {
            if ((board[i][j] != NULL && board[i - 1][j] == NULL) || (( board[i][j] == board[i - 1][j]) && board[i][j] != NULL)) {
                return true;
            }
        }
    }
    return false;
}

bool Board::canMoveDown() {
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 3; i++) {
            if ((board[i][j] != NULL && board[i + 1][j] == NULL) || (( board[i][j] == board[i + 1][j]) && board[i][j] != NULL)) {
                return true;
            }
        }
    }
    return false;
}

bool Board::canMoveLeft() {
    for (int i = 0; i < 4; i++) {
        for (int j = 3; j >= 1; j--) {
            if ((board[i][j] != NULL && board[i][j - 1] == NULL) || (( board[i][j] == board[i][j - 1]) && board[i][j] != NULL)) {
                return true;
            }
        }
    }
    return false;
}

bool Board::canMoveRight() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if ((board[i][j] != NULL && board[i][j + 1] == NULL) || (( board[i][j] == board[i][j + 1]) && board[i][j] != NULL)) {
                return true;
            }
        }
    }
    return false;
}

void Board::keyPressEvent(QKeyEvent * event) {
    if(!hasWon()) {
        if(canMoveUp() &&(event->key() == Qt::Key_W || event->key() == Qt::Key_Up)) {
            caseUp();
            settingBoard();
        }
        if(canMoveRight() &&(event->key() == Qt::Key_D || event->key() == Qt::Key_Right)) {
            caseRight();
            settingBoard();
        }
        if(canMoveLeft() &&(event->key() == Qt::Key_A || event->key() == Qt::Key_Left)) {
            caseLeft();
            settingBoard();
        }
        if(canMoveDown() &&(event->key() == Qt::Key_S || event->key() == Qt::Key_Down)) {
            caseDown();
            settingBoard();
        }
    }
}
