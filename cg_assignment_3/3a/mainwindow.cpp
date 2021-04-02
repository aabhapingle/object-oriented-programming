#include "mainwindow.h"
#include "ui_mainwindow.h"
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
    float xc=0; float yc=0; float r=0;
    xc  = ui-> lineEdit   ->text().toFloat();
    yc  = ui-> lineEdit_2 ->text().toFloat();
    r   = ui-> lineEdit_3 ->text().toFloat();

    // input validation

    if(xc > 500 || xc <= 0){
        QMessageBox::about(this, "x coord","Please enter x coordinates between 0 to 500");
    }
    if(yc > 500 || yc <= 0){
        QMessageBox::about(this, "y coord","Please enter y coordinates between 0 to 500");
    }
    if(r > 300 || r <= 0){
        QMessageBox::about(this, "radius","Please enter radius between 0 to 300");

    }

    else if(xc < 500 && xc > 0 && yc < 500 && yc > 0 && r < 300 && r>0){
        // call bresenham circle for bigger circle
        bres_circle(xc, yc, r);

        // call bresenham circle for smaller circle
        bres_circle(xc, yc , r/2);

        // call dda
        dda(xc - r*0.866, yc + r*0.5, xc, yc-r);
        dda(xc - r*0.886, yc + r*0.5, xc + r*0.886, yc + r*0.5);
        dda(xc + r*0.886, yc + r*0.5, xc, yc - r);

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
