//Write C++ program to generate snowflake using concept of fractals

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"
#include<QInputDialog>
#include<math.h>

QImage image(800, 800, QImage::Format_RGB888);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    start = true;
    j = 0;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    QRgb color = qRgb(233,196,106);
    if(start == true){
        int p = event->pos().x();
        int q = event->pos().y();

        a[j] = p;
        b[j] = q;

        if(event->button()==Qt::RightButton){
            dda(a[j-1], b[j-1], a[0],b[0], color);
            start = false;
        }
        else{
            if(j > 0){
                dda(a[j], b[j],a[j-1], b[j-1], color);
            }
        }
        j++;
    }
}

// dda function
void MainWindow ::dda(float x1, float y1, float x2, float y2, QRgb value){
    // all variables except i are float

    float length;

    // length
    if(abs(x2- x1) >= abs(y2- y1)) {
        length = abs(x2- x1);
    }
    else{
        length = abs(y2 - y1);
    }

    // raster unit
    float dx, dy;
    dx = ( x2 - x1 )/length;
    dy = ( y2 - y1 )/length;

    // iterations xi and yi;
    float xi = x1 + 0.5;
    float yi = y1 + 0.5;

    // main loop
    int i = 1;
    while(i <= length){
           image.setPixel(int(xi), int(yi), value);

                xi = xi + dx;
                yi = yi + dy;
                i++;
          }

    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->size();
    ui->label->show();
     }


// draw polygon
void MainWindow::on_pushButton_clicked()
{
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->size();
    ui->label->show();
}

// clear button
void MainWindow::on_pushButton_2_clicked()
{
    for(int i=0;i<=j;i++){
           a[i]=0;
           b[i]=0;
       }
       j=0;
       QImage* newImage=new QImage(800,800,QImage::Format_RGB888);
       image=*newImage;
       ui->label->setPixmap((QPixmap::fromImage(image)));
       start=true;

}
// perform fractal operations
void MainWindow::frac(float x1, float y1, float x2, float y2, int i){
    float ang = 60*3.14159/180;   // angle in radians

    float x3 = (2*x1 + x2)/3;   // divide in ratio 2:1
    float y3 = (2*y1 + y2)/3;

    float x4 = (x1 + 2*x2)/3;   // divide in ratio 1:2
    float y4 = (y1 + 2*y2)/3;

    float x5 = x3 + (x4-x3)*cos(ang) + (y4-y3)*sin(ang);    // rotate about (x3,y3) by 60 deg anticlockwise
    float y5 = y3 - (x4-x3)*sin(ang) + (y4-y3)*cos(ang);

    if(i > 0){
        frac(x1, y1, x3, y3, i-1); // call the function for all the segments
        frac(x3, y3, x5, y5, i-1);
        frac(x5, y5, x4, y4, i-1);
        frac(x4, y4, x2, y2, i-1);
    }
    else{
        QRgb col = qRgb(69,123,157);
        dda(x1, y1, x3, y3, col);
        dda(x3, y3, x5, y5, col);
        dda(x5, y5, x4, y4, col);
        dda(x4, y4, x2, y2, col);

    }

}

void MainWindow::on_pushButton_3_clicked()
{
    //    QRgb color = qRgb(231,111,81);  // red

    int it = QInputDialog::getDouble(this, "Iterations","Enter number of iterations:");

    QImage* newImage=new QImage(800,800,QImage::Format_RGB888);
    image=*newImage;
    ui->label->setPixmap((QPixmap::fromImage(image)));

    for (int k=0; k<j-2; k++) {
        frac(a[k], b[k], a[k+1],b[k+1],it);
    }
    frac(a[j-2], b[j-2], a[0],b[0],it);
}
