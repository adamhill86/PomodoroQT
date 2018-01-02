#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    time = 25 * 60; // 25 minutes in seconds
    isBreakTime = false;
    qtimer = new QTimer(this);
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*!
 * \brief MainWindow::clicked
 * This function is called when the Start button is clicked.
 * It sets the text label to Work hard and starts the countdown timer
 */
void MainWindow::clicked() {
    updateTimeString();
    ui->pomodoroLabel->setText("Work hard!");
    connect(qtimer, SIGNAL(timeout()), this, SLOT(updateTimer()));
    qtimer->start(1000);
    ui->pushButton->setEnabled(false);
    ui->pushButton->setVisible(false);
}

/*!
 * \brief MainWindow::updateTimer
 * This function is called every second while the timer is running.
 * It decrements \a time until it hits 0.
 * Once that happens, a system beep sound effect is played and it is
 * determined whether or not a user is on break.
 * It then resets the timer accordingly (25 minutes for work, 5 minutes for break).
 */
void MainWindow::updateTimer() {
    time--;
    if (time == 0 && !isBreakTime)
    {
        QApplication::beep();
        isBreakTime = true;
        ui->pomodoroLabel->setText("Break time");
        time = 5 * 60; // 5 minute break (in seconds)
    } else if (time == 0 && isBreakTime)
    {
        QApplication::beep();
        isBreakTime = false;
        time = 25 * 60; // 25 minute work time in seconds
        ui->pomodoroLabel->setText("Work hard!");
    }
    updateTimeString();
}

/*!
 * \brief MainWindow::updateTimeString
 * This function formats the time remaining appropriately for the label.
 * The \a time variable represents the time remaining in seconds,
 * but this function converts that to the standard clock format: 12:34
 */
void MainWindow::updateTimeString() {
    int minutes = time / 60;
    int seconds = time % 60;
    QString minutesString = QString::number(minutes);
    QString secondsString;

    if (seconds >= 10)
    {
        secondsString = QString::number(seconds);
    } else if (seconds > 0)
    {
        secondsString = "0" + QString::number(seconds);
    } else
    {
        secondsString = "00";
    }

    ui->timer->setText(minutesString + ":" + secondsString);
}
