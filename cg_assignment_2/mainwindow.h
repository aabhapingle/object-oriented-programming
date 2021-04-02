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
    bool start,accept;
    int T,B,R,L;

    // j is for keeping track of the number of points

    int j;

    // a contains x coordinates
    // b contains y coordinates
    // c contains codes of lines

    float a[20], b[20];

    // coords of window
    int x_low = 100;
    int y_low = 100;

    int x_high = 350;
    int y_high = 350;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

private:
    // for mouse click capture
    void mousePressEvent(QMouseEvent *ev);

    // line drawing
    void dda(float, float, float, float);

    // find code of a line
    int code(float, float);

    // clipping
    void clip(float, float, float, float);


    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
