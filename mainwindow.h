#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void enableGame();
    void handleButtonClick();
    void handleAgree();
    void handleReset();
    void resetGame();
    void checkForWin();
    void declareWinner(int);
    void disableAllButtons();
    void syncScoreBoard();
    void setScoreBoardEnabled(bool);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
