#include "mainwindow.h"
#include "./ui_mainwindow.h"

bool gameStarted = false;
int currentPlayer = 1;
int board[25] {0};
int tempWin1 = 0 , tempWin2 = 0 , tempLose1 = 0 , tempLose2 = 0 , tempDraw1 = 0 , tempDraw2 = 0;
bool scoreBoardDisabled = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lblGameOver->setVisible(false);
    ui->lblWinnerTitle->setVisible(false);
    ui->gridLayoutWidget_4->setVisible(false);

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
    if (ui->rbtnYes->isChecked()){
        ui->lineEditWin1->setText(QString::number(ui->lineEditWin1->text().toInt() + tempWin1));
        ui->lineEditLose1 -> setText(QString::number(ui->lineEditLose1->text().toUInt() + tempLose1));
        ui->lineEditWin2 -> setText(QString::number(ui->lineEditWin2->text().toInt() + tempWin2));
        ui->lineEditLose2 -> setText(QString:: number(ui->lineEditLose2->text().toInt() + tempLose2));
        ui->lineEditDraw1 -> setText((QString::number(ui->lineEditDraw1->text().toInt() + tempDraw1)));
        ui->lineEditDraw2 -> setText(QString::number(ui->lineEditDraw2->text().toInt() + tempDraw2));

        resetGame();
    }
    else if(ui->rbtnNo->isChecked()){
        QApplication::quit();
    }
    tempDraw1 = 0;
    tempDraw2 = 0;
    tempLose1 = 0;
    tempLose2 = 0;
    tempWin1 = 0;
    tempWin2 = 0;
}

void MainWindow::handleReset(){
    tempDraw1 = 0;
    tempDraw2 = 0;
    tempLose1 = 0;
    tempLose2 = 0;
    tempWin1 = 0;
    tempWin2 = 0;

    resetGame();

}

void MainWindow::resetGame(){
    for (int i = 0 ; i<25 ; i++){
        board[i] = 0;
    }
    currentPlayer = 1;

    ui->lineEditName1->setEnabled(true);
    ui->lineEditName2->setEnabled(true);
    gameStarted = false;

    for (int i = 0 ; i<25 ; i++){
        QPushButton* button = findChild<QPushButton*>(QString("btn%1").arg(i));
        if (button){
            button->setStyleSheet("");
            button->setEnabled(!ui->lineEditName1->text().isEmpty() && !ui->lineEditName2->text().isEmpty());
        }
    }
    ui->lblGameOver->setVisible(false);
    ui->lblWinnerTitle->setVisible(false);
    ui->gridLayoutWidget_4->setVisible(false);

    ui->lineEditDraw1->setEnabled(true);
    ui->lineEditDraw2->setEnabled(true);
    ui->lineEditName1->setEnabled(true);
    ui->lineEditName2->setEnabled(true);
    ui->lineEditLose1->setEnabled(true);
    ui->lineEditLose2->setEnabled(true);

    scoreBoardDisabled = false;

    ui->rbtnYes->setChecked(true);
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

void MainWindow::declareWinner(int player){
    //temp save results
    if (player == 1){
        tempWin1 ++;
        tempLose2 ++;
        ui->lblWinnerTitle->setText("Winner = " + ui->lineEditName1 -> text());
    }
    else if (player == 2){
        tempWin2 ++;
        tempLose1 ++;
        ui->lblWinnerTitle->setText("Winner = " + ui->lineEditName2 -> text());
    }
    else{ //if player == 0
        tempDraw1++;
        tempDraw2++;
        ui->lblWinnerTitle ->setText("Draw!");
    }

    ui->lblGameOver -> setVisible(true);
    ui->lblWinnerTitle->setVisible(true);
    ui->gridLayoutWidget_4 ->setVisible(true);
    disableAllButtons();
}

void MainWindow::disableAllButtons(){

}


void MainWindow::syncScoreBoard() {
    // جلوگیری از حلقه بی‌نهایت با بلاک کردن سیگنال‌ها
    QSignalBlocker blocker1(ui->lineEditLose2);
    QSignalBlocker blocker2(ui->lineEditLose1);
    QSignalBlocker blocker3(ui->lineEditDraw2);

    ui->lineEditLose2->setText(ui->lineEditWin1->text());
    ui->lineEditLose1->setText(ui->lineEditWin2->text());
    ui->lineEditDraw2->setText(ui->lineEditDraw1->text());
}

