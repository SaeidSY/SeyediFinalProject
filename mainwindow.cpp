#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

}

void MainWindow::handleAgree(){

}

void handleReset(){

}

void MainWindow::resetGame(){

}
