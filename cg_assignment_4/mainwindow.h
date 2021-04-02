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
    float a[20];
    float b[20];

    // scaling
    double sx = 0;   // x scaling factor
    double sy = 0;   // y scaling factor

    // translation
    double tx = 0;
    double ty = 0;

    // rotation
    double ra = 0;

private slots:
    void dda(float, float,float,float,QRgb);
    void mousePressEvent(QMouseEvent *ev); // for drawing a ploygon

    // void operator+(float arr[]);

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
