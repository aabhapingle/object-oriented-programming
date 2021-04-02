#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QLineEdit>
#include<QWidget>

#include <QApplication>
#include <cstdlib>
#include <cmath>
#include <QLabel>
#include <iostream>
using namespace std;


QImage image(500, 500, QImage::Format_RGB888);

// global

// store x coordinates of the lines
int xx[25];

// y coords
int yy[25];

// number of points
int n = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    float x1, x2, y1, y2;
    x1 = ui->lineEdit->text().toFloat();
    y1 = ui->lineEdit_2->text().toFloat();
    x2 = ui->lineEdit_3->text().toFloat();
    y2 = ui->lineEdit_4->text().toFloat();

    xx[n] = x2;
    yy[n] = y2;

    n++;

    // dda called
    dda(x1, y1, x2, y2);
}

void MainWindow::on_pushButton_2_clicked()
{
    float x1, y1, x2, y2;
    x1 = ui->lineEdit->text().toFloat();
    y1 = ui->lineEdit_2->text().toFloat();
    x2 = ui->lineEdit_3->text().toFloat();
    xx[n] = x2;

    y2 = ui->lineEdit_4->text().toFloat();
    yy[n] = y2;

    n++;

    // bres called
    bres(x1, y1, x2, y2);
}


// dda function
void MainWindow ::dda(float x1, float y1, float x2, float y2){
    // all variables except i are float

    float length;

    // length
    if(abs(x2- x1)>= abs(y2- y1)) {
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

    // colour
    QRgb value;
    value = qRgb(0, 255, 0);

    // main loop
    int i = 1;
    while(i <= length){
           image.setPixel(int(xi), int(yi), value);

                xi = xi + dx;
                yi = yi + dy;
                i++;
          }

    ui->label_6->setPixmap(QPixmap::fromImage(image));
    ui->label_6->size();
    ui->label_6->show();
     }

// sign function
int MainWindow:: sign(int c1, int c2){
    if (c1-c2 > 0){
        return 1;
    }
    else if(abs(c1-c2) == 0){
        return 0;
    }
    else {
        return -1;
    }
}

// bresenham function
void MainWindow ::bres(int x1,int y1, int x2, int y2){
    // iterators

    // i am changing everything to float
    float xi = x1;
    float yi = y1;

    float dx = abs(x2 - x1);
    float dy = abs(y2 - y1);

    int s1 = sign(x2, x1);
    int s2 = sign(y2, y1);

    int interchange = 0;

    // interchange dx and dy depending on the slope of the line
    if(dy > dx){
        float temp = dx;
         dx = dy;
         dy = temp;
         interchange = 1;
         }
         else{
          interchange = 0;
         }

     // intialize the error term
     float e = 2*dy - dx;

     // colour
     QRgb value;
     value = qRgb(255, 0, 0);

     //main loop
             for(int i = 1;i < dx ; i++){
                 image.setPixel(xi, yi, value);

                 // while loop
                 while(e > 0){
                     if (interchange == 1){
                         xi = xi + s1;
                     }
                     else {
                         yi = yi + s2;
                     }
                     e = e - 2*dx;
                 }

                 // if-else condition
                 if(interchange == 1){
                     yi = yi + s2;
                 }
                 else {
                     xi = xi + s1;
                 }
                 e = e + 2*dy;
             }

             ui->label_6->setPixmap(QPixmap::fromImage(image));
             ui->label_6->size();
             ui->label_6->show();
}

void MainWindow::scan(int xx[25], int yy[25], int n){
    int i, k, inter_x[50],temp,y,ymax = 0,ymin = 500;
    float m[25],dx,dy;

    for(i=0; i<n; i++){

        // finding ymax from the array
        if(yy[i] >= ymax){ymax = yy[i];};

        // finding ymin from the array
        if(yy[i] <= ymin){ymin = yy[i];};

        //difference between the consecutive elements in the array
        dx = xx[i+1] - xx[i];
        dy = yy[i+1] - yy[i];

        // line parallel to y axis, inverse of slope 0
        if(dx==0)m[i] = 0;

        // line parallel to x axis, inverse of slope 1
        if(dy==0)m[i] = 1;

        // inverse of slope of a normal line
        if(dx!=0 && dy!=0)m[i]=(float)dx/dy;
    }

    int cnt;

    for(y = ymax; y >= ymin; y--){
        cnt = 0;
        for(i=0; i<n; i++){
            if((yy[i] > y && yy[i+1] <= y) || (yy[i] <= y && yy[i+1]>y))
            {
                // this is just the slope formula for finding x intersection
                inter_x[cnt] = (xx[i]+(m[i]*(y - yy[i])));
                cnt++;
            }
        }

        // bubble sort for x intersections array
        for(k=0; k < cnt-1; k++){
            for(i=0; i< cnt-1; i++){
                if(inter_x[i] > inter_x[i+1]){
                    // swap the elements
                    temp = inter_x[i];
                    inter_x[i] = inter_x[i+1];
                    inter_x[i+1] = temp;
                }
            }
        }
        for(i = 0; i < cnt-1; i += 2){
            dda(inter_x[i],y,inter_x[i+1]+1,y);
        }
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    // calling scan line function

    scan(xx,yy,n);/*
    ui->label_6->setPixmap(QPixmap::fromImage(image));
    ui->label_6->size();
    ui->label_6->show();*/
}

void MainWindow::on_pushButton_4_clicked()
{
    // for refreshing the screen

    image.fill(0);
    ui->label_6->setPixmap(QPixmap::fromImage(image));
    ui->label_6->show();
}
