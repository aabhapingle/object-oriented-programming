#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"
using namespace std;
QImage image(600,600,QImage::Format_RGB888);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    start = true;   // initializing start equal to true
    accept=true;
    j = 0;
     T=8,B=4,R=2,L=1;
    //k = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event){
   /* if(start == true){
        int p = event->pos().x();
        int q = event->pos().y();

        a[j]=p;
        b[j]=q;

        if(j>0 && j%2==1){
            dda(a[j], b[j],a[j-1],b[j-1]);}

        if(event->button()==Qt::RightButton){
            // dda(a[j-1],b[j-1],a[0], b[0]);
            start = false;
        }
        else{
            if(j>0 && j%2==1){
                dda(a[j], b[j],a[j-1],b[j-1]);
            }
        }
        j++;

    }
    //start = false;*/
    if(start)
    {
    int p=event->pos().x();
    int q=event->pos().y();
    a[j]=p;
    b[j]=q;

    if(event->button()==Qt::RightButton)
    {

        start=false;
    }
    else{
        if(j%2!=0)
        {
            dda(a[j],b[j],a[j-1],b[j-1]);
        }
    }
    j++;

    }


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

    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->size();
    ui->label->show();
     }

// find code of a point
int MainWindow::code(float x1, float y1){
   /* int line_code[4]; // array to store the code

    // code TBRL format

    // set all values to zero
    for (int i=0;i<4 ;i++) {
        line_code[i] = 0;
    }

    if(x1 < x_low){
        line_code[3]=1;
    }
    if(x1 > x_high){
        line_code[2]=1;
    }
    if(y1 < y_low){
        line_code[1]=1;
    }
    if(y1 > y_high){
        line_code[0]=1;
    }
    return line_code; */


    int line_code=0;
    if (x1<x_low){ line_code|=L;} // assigning codes TOP,BOTTOM,RIGHT,LEFT .
    if (x1>x_high){ line_code|=R;}
    if (y1<y_low){ line_code|=T;}
    if (y1>y_high){ line_code|=B;}

    return line_code;


}

// clipping algorithm
void MainWindow::clip(float x1,float y1,float x2,float y2){
    int c1,c2;


    accept=false;
     c1 = code(x1, y1);
     c2 = code(x2, y2);

     while(1)
    {
         double m=double((y2-y1)/(x2-x1));
         if(c1==0 && c2==0)
         {
             accept=true;
             break;
         }
         else if( (c1 & c2) !=0)
         {
            break;
         }
         else
         {
             double x,y,x3,y3;
             int temp;
             if(c1==0)
             {
                 temp=c2; x3=x2; y3=y2;
             }
             else{ temp=c1 ; x3=x1; y3=y1; }
             if(temp & L){
                   x=x_low;
                   y=y3+m*(x_low-x3);
             }
             else if(temp & B){
                   y=y_high;
                   x=x3+(y_high-y3)/m;
             }
             else if(temp & R){
                   x=x_high;
                   y=y3+m*(x_high-x3);
             }
             else if(temp & T){
                   y=y_low;
                   x=x3+(y_low-y3)/m;
             }
             // here we replace original coordinates with new one
             if(temp==c1){
                 x1=x;
                 y1=y;
                 c1=code(x1,y1);
             }
             else{
                 x2=x;
                 y2=y;
                 c2=code(x2,y2);
             }
         }
     }
     if(accept==true)
     {
         dda(x1,y1,x2,y2);
     }

    // check if both are 0000

 /*   // count of 0s in the code
    int count1 = 0;
    int count2 = 0;

    // point 1
    for (int i=0; i<4 ;i++ ) {
        if(ptr1[i]==0){
            count1++;
        }
    }

    // point 2
    for (int i=0; i<4 ;i++ ) {
        if(ptr2[i]==0){
            count2++;
        }
    }

    // AND of the codes
    int ans = 0;
    for(int i =0; i<4; i++){
        if(ptr1[i]==1 && ptr2[i]==1){
            ans=1;
            break;
        }
    }

    // if both are 0000 then display the line
    if(count1==4 && count2==4){
        dda(x1,y1,x2,y2);
    }
    else if(ans==1){
        // the line is invisible
        // don't do anything for this line
    }
    else{
        // line could be partially visible or invisible
        // find intersections with window edges

        float m;  // slope of the line
        m = (y1-y2)/(x1-x2);

        // stop this for loop when bit 1 is encountered
        // then after we will have recursion

        // new coordinates formed after intersection with window
        float y_new;
        float x_new;

        // which point are we excluding afterwards?
        int which = 2;

        for (int i=3;i>=0 ; i--) {
            if(ptr1[i] == 1 || ptr2[i] == 1){

                // first find out which point
                if(ptr1[i] == 1){
                    which = 1;
                }

                if(i==3){
                    // means point is to the left of the window
                    y_new = y1 + m*(x_low - x1);
                    x_new = x_low;
                }
                else if(i==2){
                    // means point is to the right of the window
                    y_new = y1 + m*(x_high - x1);
                    x_new = x_high;
                }
                else if(i==1){
                    // means point is below the window
                    x_new = x1 + (y_low - y1)/m;
                    y_new = y_low;
                }
                else{
                    // means point is above the window
                    x_new = x1 + (y_high - y1)/m;
                    y_new = y_high;
                }

                break;
            }
        }
        if(which == 1){
            clip(x_new, y_new, x2, y2);
        }
        else{
            clip(x_new, y_new, x1, y1);
        }
    }*/
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->size();
    ui->label->show();
}

void MainWindow::on_pushButton_4_clicked()
{
  /*  // for clearing the screen
    image.fill(0);
    start = true;
    // ver = 0;
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();*/
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

void MainWindow::on_pushButton_3_clicked()
{
    // first clear the screen
    image.fill(0);
    start = true;
    // ver = 0;
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();

    // draw window

    dda(x_low, y_low, x_high, y_low);
    dda(x_low, y_low, x_low, y_high);
    dda(x_low, y_high, x_high, y_high);
    dda(x_high, y_high, x_high, y_low);


    // clipping the lines
    for(int k=0; k<j;k=k+2){
        clip(a[k],b[k],a[k+1],b[k+1]);
    }
}

void MainWindow::on_pushButton_clicked()
{
    // draw window

    dda(x_low, y_low, x_high, y_low);
    dda(x_low, y_low, x_low, y_high);
    dda(x_low, y_high, x_high, y_high);
    dda(x_high, y_high, x_high, y_low);
}
