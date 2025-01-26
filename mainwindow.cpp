#include "mainwindow.h"
#include "./ui_mainwindow.h"

bool gameStarted;
int currentPlayer = 1;
int board[25] {0};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gameStarted = false;

    //etesale names be enableGame
    connect(ui->lineEditName1 , &QLineEdit::textChanged , this , &MainWindow::enableGame);
    connect(ui->lineEditName2 , &QLineEdit::textChanged , this , &MainWindow::enableGame);

    //etesale dokme haye bazi -> handleButtonClick
    for (int i = 1 ; i < 26 ; i++){
        QPushButton *button = findChild<QPushButton*>(QString("btn%1").arg(i));
        if(button){
            connect(button, &QPushButton::clicked , this , &MainWindow::handleButtonClick);
        }
    }

    //etesale Agree va Reset
    connect(ui->btnAgree , &QPushButton::clicked , this , &MainWindow::handleAgree);
    connect(ui->btnReset , &QPushButton::clicked , this , &MainWindow::handleReset);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::enableGame(){
    bool bothNamesEntered = !ui->lineEditName1->text().isEmpty() && !ui->lineEditName2->text().isEmpty();
    for (int i = 0 ; i<=25 ; i++){
        QPushButton* button = findChild<QPushButton*>(QString("btn%1").arg(i));
        if (button){
            button->setEnabled(bothNamesEntered);
        }
        if (bothNamesEntered){
            resetGame();
        }
    }

}

void MainWindow::handleButtonClick(){
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button){
        if (!gameStarted){
            ui->lineEditName1->setEnabled(false);
            ui->lineEditName2->setEnabled(false);
            gameStarted = true;
        }
    }
    int buttonNumber = button->text().toInt();
    if (currentPlayer == 1){
        button -> setStyleSheet("border: 3px solid red;");
        board[buttonNumber-1] = 1;
    }
    else{
        button -> setStyleSheet("border: 3px solid blue;");
        board[buttonNumber-1] = 2;
    }
    button->setEnabled(false);
    checkForWin();
    currentPlayer = (currentPlayer == 1 ) ? 2 : 1 ;

}

void MainWindow::handleAgree(){

}

void handleReset(){

}

void MainWindow::resetGame(){

}

void MainWindow::checkForWin(){
    //check winner in radif
    for (int row = 0 ; row<5 ; row++){
        if (board[row*5] != 0 && board[row*5] == board[row*5 + 1] && board[row*5] == board[row*5+2] && board[row*5] == board[row*5 + 3] && board[row*5] == board[row*5 + 4]){
            declareWinner(board[row*5]);
            return;
        }
    }

    //check winner in sotoon
    for (int col = 0 ; col <5 ; col++){
        if (board[col] != 0 && board[col] == board[col + 5] && board[col] == board[col + 10] && board[col] == board[col + 15] && board[col] == board[col + 20]){
            declareWinner(board[col]);
            return;
        }
    }

    //check winner ghotr asli
    if (board[0]!=0 && board[0] == board[6] && board[0] == board[12]&& board[0] == board[18] && board[0] == board[24]){
        declareWinner(board[0]);
        return;
    }

    //check winner ghotr faree
    if (board[4]!=0 && board[4] == board[8] && board[4] == board[12] && board[4] == board[16] && board[4] == board[20]){
        declareWinner(board[4]);
        return;
    }

    //check equal
    bool isDraw = true;
        for (int i = 0 ; i < 25 ; i++){
            if (board[i] == 0){
                isDraw = false;
                break;
            }
        }
        if (isDraw){
            declareWinner(0);
        }
}

void MainWindow::declareWinner(int n){

}
