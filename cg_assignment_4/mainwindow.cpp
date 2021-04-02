#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"
#include<QInputDialog>
#include<math.h>

QImage image(600, 600, QImage::Format_RGB888);

// QColor color;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    start = true;
    j = 0;

    // scaling
    ui->label_2->setText(" ");
    ui->label_3->setText(" ");
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

// operator overloading for '+'

// draw a polygon
void MainWindow::on_pushButton_clicked()
{
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->size();
    ui->label->show();
}

// clear button
void MainWindow::on_pushButton_5_clicked()
{
    for(int i=0;i<=j;i++){
           a[i]=0;
           b[i]=0;
       }
       j=0;
       QImage* newImage=new QImage(600,600,QImage::Format_RGB888);
       image=*newImage;
       ui->label->setPixmap((QPixmap::fromImage(image)));
       start=true;
}

// scaling
void MainWindow::on_pushButton_4_clicked()
{
    QRgb s_color = qRgb(231,111,81);  // red

    sx = QInputDialog::getDouble(this, "Scaling","Enter x scaling factor");
    ui->label_2->setText(QString::number(sx));

    sy = QInputDialog::getDouble(this, "Scaling","Enter y scaling factor");
    ui->label_3->setText(QString::number(sy));

    QImage* newImage=new QImage(600,600,QImage::Format_RGB888);
    image=*newImage;
    ui->label->setPixmap((QPixmap::fromImage(image)));

    // perform scaling

    // float s_arr_x[j-1], s_arr_y[j-1];

    for(int s=0; s < j-1; s++){
        a[s] = a[s]*sx;
        b[s] = b[s]*sy;

        if(s > 0){
            dda(a[s], b[s], a[s-1], b[s-1], s_color);
        }
    }
    dda(a[0], b[0], a[j-2], b[j-2], s_color);
}

// translation
void MainWindow::on_pushButton_2_clicked()
{
    QRgb t_color = qRgb(42,157,143); // dark blue

    tx = QInputDialog::getDouble(this, "Translation","Enter x translation factor");
    ui->label_2->setText(QString::number(tx));

    ty = QInputDialog::getDouble(this, "Translation","Enter y translation factor");
    ui->label_3->setText(QString::number(ty));

    QImage* newImage=new QImage(600,600,QImage::Format_RGB888);
    image=*newImage;
    ui->label->setPixmap((QPixmap::fromImage(image)));

    ui->label_3->setText(QString::number(j));

    // perform operation

    for(int t=0; t<j-1;t++){
        a[t] = a[t]+tx;
        b[t] = b[t]+ty;

        if(t > 0){
            dda(a[t], b[t], a[t-1], b[t-1], t_color);
        }

    }
    // last edge of the polygon
    dda(a[0], b[0], a[j-2], b[j-2], t_color);
}

// rotation
void MainWindow::on_pushButton_3_clicked()
{
    QRgb r_color = qRgb(168,218,220);  // light blue

    ra = QInputDialog::getDouble(this, "Rotation","Enter Rotation angle in degree");
    ui->label_2->setText(QString::number(ra));

    QImage* newImage=new QImage(600,600,QImage::Format_RGB888);
    image=*newImage;
    ui->label->setPixmap((QPixmap::fromImage(image)));

    // perform operation

    // take input in degree (data type is double)
    ra = ra* (0.01745);

    // float r_arr_x[j-1], r_arr_y[j-1];

    for(int r=0; r<j-1;r++){
        a[r] = a[r]*cos(ra) - b[r]*sin(ra);
        b[r] = a[r]*sin(ra) + b[r]*cos(ra);

        if(r > 0){
            dda(a[r], b[r], a[r-1], b[r-1], r_color);
        }

    }
    // last edge of the polygon
    dda(a[0], b[0], a[j-2], b[j-2], r_color);

}
