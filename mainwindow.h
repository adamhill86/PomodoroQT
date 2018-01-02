#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int time;
    bool isBreakTime;
    QTimer *qtimer;

    void updateTimeString();

private slots:
    void clicked();
    void updateTimer();
};

#endif // MAINWINDOW_H
