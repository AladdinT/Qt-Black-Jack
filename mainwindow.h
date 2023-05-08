#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <ctime>
#include <vector>
#include <QVBoxLayout>
#include <QPainter>
#include <QStandardItem>
#include <QFile>
#include "cards.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QLabel *label_array[6];
    QPixmap player1_appendCardPics(QString imgPath);
    QPixmap player2_appendCardPics(QString imgPath);
    void gameOver(void);



private slots:
    void on_pushButton_Logo_clicked();

    void on_pushButton_play_clicked();

    void on_pushButton_p1_draw_clicked();

    void on_pushButton_p2_draw_clicked();

    void on_pushButton_p1_pass_clicked();

    void on_pushButton_p2_pass_clicked();

    void on_pushButton_playAgain_clicked();

    void on_pushButton_help_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
