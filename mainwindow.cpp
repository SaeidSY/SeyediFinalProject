#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->lineEditName1 , &QLineEdit::textChanged , this , &MainWindow::enableGame);
    connect(ui->lineEditName2 , &QLineEdit::textChanged , this , &MainWindow::enableGame);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::enableGame(){

}
