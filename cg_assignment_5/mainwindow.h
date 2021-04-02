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

    // for drawing the poly
    bool start;
    int j;
    float a[100];
    float b[100];


private slots:
    void dda(float, float,float,float,QRgb);
    void mousePressEvent(QMouseEvent *ev); // for drawing a ploygon

    void frac(float, float,float,float,int);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
