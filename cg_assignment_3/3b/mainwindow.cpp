#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<cmath>
#include<QMessageBox>

QImage image(800, 800, QImage::Format_RGB888);

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
    float x=0; float y=0; float l=0; float b=0;

    // x and y are the coordinates of the centre of the circle

    x = ui->lineEdit->text().toFloat();

    y = ui->lineEdit_2->text().toFloat();

    // length and breadth of the outer rectangle

    l = ui->lineEdit_3->text().toFloat();
    b = ui->lineEdit_4->text().toFloat();

    // input validation

    if(x > 500){
        QMessageBox::about(this, "x coord","Please enter x coordinates between 0 to 500");
    }
    if(y > 500){
        QMessageBox::about(this, "y coord","Please enter y coordinates between 0 to 500");
    }
    if(l<=b){
        QMessageBox::about(this, "length-breadth","Length of the rectangle should be more than breadth ");

    }
    else if(x>0 && x<500 && y>0 && y<500 && l>b){
        // draw the circle

        bres_circle(x, y, (b*l/2)*(pow((l*l + b*b),-0.5)));

        // draw the rectangle

        dda(x-l/2, y+b/2, x+l/2, y+b/2); // AB
        dda(x+l/2, y+b/2, x+l/2, y-b/2); // BC
        dda(x+l/2, y-b/2, x-l/2, y-b/2); // CD
        dda(x-l/2, y-b/2, x-l/2, y+b/2); // DA

        // draw the rhombus

        dda(x, y+b/2, x+l/2, y);
        dda(x+l/2, y, x, y-b/2);
        dda(x, y-b/2, x-l/2, y);
        dda(x-l/2, y, x, y+b/2);
    }

}

// draw pixels in all the eight octants

void MainWindow::eight(float xi, float yi, float xc, float yc){

    QRgb value;
    value = qRgb(0, 255, 0);

    // function for coloring values in all quadrants
    image.setPixel(xc + int(xi), yc + int(yi), value);
    image.setPixel(xc + int(xi), yc - int(yi), value);
    image.setPixel(xc - int(xi), yc + int(yi), value);
    image.setPixel(xc - int(xi), yc - int(yi), value);

    image.setPixel(xc + int(yi), yc + int(xi), value);
    image.setPixel(xc + int(yi), yc - int(xi), value);
    image.setPixel(xc - int(yi), yc + int(xi), value);
    image.setPixel(xc - int(yi), yc - int(xi), value);


}

// draw a circle with the given coordinates

void MainWindow::bres_circle(float x, float y, float r){
    // iteratives
    float xi = 0;
    float yi = r;

    // initial decision parameter
    float s = 3 - 2*r;

    eight(xi, yi, x, y);

    // main loop
    while(xi <= yi){
        xi = xi + 1;
        if(s < 0){
            s = s + 4*xi + 6;
        }
        else{
            yi = yi - 1;
            s = s + 4*(xi - yi) + 10;
        }
        eight(xi, yi, x, y);
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->size();
    ui->label->show();

}

// dda function to draw a line

void MainWindow ::dda(float x1, float y1, float x2, float y2){
    // all variables except i are float only

    float length;

    // length
    if(abs(x2- x1)>= abs(y2- y1)) {
        length = (abs(x2- x1));
    }
    else{
        length = (abs(y2 - y1));
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
    value = qRgb(255, 255, 0);

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


void MainWindow::on_pushButton_2_clicked()
{
    // first clear the screen
    image.fill(0);

    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}
