#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	
	szer = ui->rysujFrame->width();
    wys = ui->rysujFrame->height();
    poczX = ui->rysujFrame->x();
    poczY = ui->rysujFrame->y();

    img = new QImage(szer,wys,QImage::Format_RGB32);
    img_dump = new QImage(szer,wys,QImage::Format_RGB32);

    spinBox_1 = ui->spinBox_1;
    spinBox_2 = ui->spinBox_2;
    spinBox_3 = ui->spinBox_3;
    spinBox_7 = ui->spinBox_7;
    slider_1 = ui->horizontalSlider_1;
    slider_2 = ui->horizontalSlider_2;
    slider_3 = ui->horizontalSlider_3;
    slider_7 = ui->horizontalSlider_7;

    red = 0;
    green = 0;
    blue = 0;
    v = 3;

    czysc();
    update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exitButton_clicked()
{
    qApp->quit();
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(poczX,poczY,*img);
}

void MainWindow::on_cleanButton_clicked()
{
    czysc();
    update();
}

void MainWindow::on_spinBox_1_valueChanged(int value)
{
    red = value;
    slider_1->setValue(value);
}

void MainWindow::on_spinBox_2_valueChanged(int value)
{
    green = value;
    slider_2->setValue(value);
}

void MainWindow::on_spinBox_3_valueChanged(int value)
{
    blue = value;
    slider_3->setValue(value);
}

void MainWindow::on_horizontalSlider_1_valueChanged(int value)
{
    red = value;
    spinBox_1->setValue(value);
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    green = value;
    spinBox_2->setValue(value);
}

void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    blue = value;
    spinBox_3->setValue(value);
}

void MainWindow::on_radioButton_1_toggled(bool checked)
{
    if (checked) { figura = 1; }
}

void MainWindow::on_radioButton_2_toggled(bool checked)
{
    if (checked) { figura = 2; }
}

void MainWindow::on_radioButton_3_toggled(bool checked)
{
    if (checked) { figura = 3; }
}

void MainWindow::on_spinBox_7_valueChanged(int value)
{
    v = value;
    slider_7->setValue(value);
}

void MainWindow::on_horizontalSlider_7_valueChanged(int value)
{
    v = value;
    spinBox_7->setValue(value);
}

void MainWindow::czysc()
{
    unsigned char *ptr;
    ptr = img->bits();

    int i,j;
    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j] = 255;
            ptr[szer*4*i + 4*j + 1] = 255;
            ptr[szer*4*i + 4*j + 2] = 255;
        }
    }
}

void MainWindow::zapisz()
{
    unsigned char *ptr;
    ptr = img->bits();
    unsigned char *ptr2;
    ptr2 = img_dump->bits();

    int i,j;
    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            ptr2[szer*4*i + 4*j] = ptr[szer*4*i + 4*j];
            ptr2[szer*4*i + 4*j + 1] = ptr[szer*4*i + 4*j + 1];
            ptr2[szer*4*i + 4*j + 2] = ptr[szer*4*i + 4*j + 2];
        }
    }
}

void MainWindow::wczytaj()
{
    unsigned char *ptr;
    ptr = img->bits();
    unsigned char *ptr2;
    ptr2 = img_dump->bits();

    int i,j;
    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j] = ptr2[szer*4*i + 4*j];
            ptr[szer*4*i + 4*j + 1] = ptr2[szer*4*i + 4*j + 1];
            ptr[szer*4*i + 4*j + 2] = ptr2[szer*4*i + 4*j + 2];
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    clickX = event->x();
    clickY = event->y();
    clickX = clickX - poczX;
    clickY = clickY - poczY;
    zapisz();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    releaseX = event->x();
    releaseY = event->y();
    releaseX = releaseX - poczX;
    releaseY = releaseY - poczY;

    if ((clickX>=0)&&(clickY>=0)&&(clickX<szer)&&(clickY<wys)&&(releaseX>=0)&&(releaseY>=0)&&(releaseX<szer)&&(releaseY<wys))
    {
        wczytaj();
        if (figura == 1) { rysujOkrag(); }
        if (figura == 2) { rysujElipse(); }
        if (figura == 3) { rysujWielokat(); }
    }
    update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    releaseX = event->x();
    releaseY = event->y();
    releaseX = releaseX - poczX;
    releaseY = releaseY - poczY;

    if ((clickX>=0)&&(clickY>=0)&&(clickX<szer)&&(clickY<wys)&&(releaseX>=0)&&(releaseY>=0)&&(releaseX<szer)&&(releaseY<wys))
    {
        if (figura == 1) { rysujOkrag(); }
        if (figura == 2) { rysujElipse(); }
        if (figura == 3) { rysujWielokat(); }
    }
    update();
    zapisz();
}

void MainWindow::rysujOkrag()
{
    unsigned char *ptr;
    ptr = img->bits();

    int i;
    double r;
    int y;

    r = abs(sqrt(pow(releaseX - clickX, 2) + pow(releaseY - clickY, 2)));

    for (i = 0; i <= (int)floor(r/sqrt(2) + 0.5); i++)
    {
        y = (int)floor(sqrt(pow(r, 2) - pow(i, 2)) + 0.5);

        if ((i+clickX>=0)&&((y-2*y)+clickY>=0)&&(i+clickX<szer)&&((y-2*y)+clickY<wys))
        {
            ptr[szer*4*((y-2*y)+clickY) + 4*(i+clickX)] = blue;
            ptr[szer*4*((y-2*y)+clickY) + 4*(i+clickX) + 1] = green;
            ptr[szer*4*((y-2*y)+clickY) + 4*(i+clickX) + 2] = red;
        }//1
        if (((i-2*i)+clickY>=0)&&(y+clickX>=0)&&((i-2*i)+clickY<szer)&&(y+clickX<wys))
        {
            ptr[szer*4*((i-2*i)+clickY) + 4*(y+clickX)] = blue;
            ptr[szer*4*((i-2*i)+clickY) + 4*(y+clickX) + 1] = green;
            ptr[szer*4*((i-2*i)+clickY) + 4*(y+clickX) + 2] = red;
        }//2
        if ((i+clickY>=0)&&(y+clickX>=0)&&(i+clickY<szer)&&(y+clickX<wys))
        {
            ptr[szer*4*(i+clickY) + 4*(y+clickX)] = blue;
            ptr[szer*4*(i+clickY) + 4*(y+clickX) + 1] = green;
            ptr[szer*4*(i+clickY) + 4*(y+clickX) + 2] = red;
        }//3
        if ((i+clickX>=0)&&(y+clickY>=0)&&(i+clickX<szer)&&(y+clickY<wys))
        {
            ptr[szer*4*(y+clickY) + 4*(i+clickX)] = blue;
            ptr[szer*4*(y+clickY) + 4*(i+clickX) + 1] = green;
            ptr[szer*4*(y+clickY) + 4*(i+clickX) + 2] = red;
        }//4
        if (((i-2*i)+clickX>=0)&&(y+clickY>=0)&&((i-2*i)+clickX<szer)&&(y+clickY<wys))
        {
            ptr[szer*4*(y+clickY) + 4*((i-2*i)+clickX)] = blue;
            ptr[szer*4*(y+clickY) + 4*((i-2*i)+clickX) + 1] = green;
            ptr[szer*4*(y+clickY) + 4*((i-2*i)+clickX) + 2] = red;
        }//5
        if ((i+clickY>=0)&&((y-2*y)+clickX>=0)&&(i+clickY<szer)&&((y-2*y)+clickX<wys))
        {
            ptr[szer*4*(i+clickY) + 4*((y-2*y)+clickX)] = blue;
            ptr[szer*4*(i+clickY) + 4*((y-2*y)+clickX) + 1] = green;
            ptr[szer*4*(i+clickY) + 4*((y-2*y)+clickX) + 2] = red;
        }//6
        if (((i-2*i)+clickY>=0)&&((y-2*y)+clickX>=0)&&((i-2*i)+clickY<szer)&&((y-2*y)+clickX<wys))
        {
            ptr[szer*4*((i-2*i)+clickY) + 4*((y-2*y)+clickX)] = blue;
            ptr[szer*4*((i-2*i)+clickY) + 4*((y-2*y)+clickX) + 1] = green;
            ptr[szer*4*((i-2*i)+clickY) + 4*((y-2*y)+clickX) + 2] = red;
        }//7
        if (((i-2*i)+clickX>=0)&&((y-2*y)+clickY>=0)&&((i-2*i)+clickX<szer)&&((y-2*y)+clickY<wys))
        {
            ptr[szer*4*((y-2*y)+clickY) + 4*((i-2*i)+clickX)] = blue;
            ptr[szer*4*((y-2*y)+clickY) + 4*((i-2*i)+clickX) + 1] = green;
            ptr[szer*4*((y-2*y)+clickY) + 4*((i-2*i)+clickX) + 2] = red;
        }//8
    }
}

void MainWindow::rysujElipse()
{
    unsigned char *ptr;
    ptr = img->bits();

    int i;
    int a,b;
    int x,y;

    if (clickX > releaseX)
    {
        a = clickX - releaseX;
    }
    else
    {
        a = releaseX - clickX;
    }
    if (clickY > releaseY)
    {
        b = clickY - releaseY;
    }
    else
    {
        b = releaseY - clickY;
    }

    for (i = 0; i <= 1571; i++)
    {
        x = (int)floor(a * cos((double)i/1000) + 0.5);
        y = (int)floor(b * sin((double)i/1000) + 0.5);

        if ((x+clickX>=0)&&((y-2*y)+clickY>=0)&&(x+clickX<szer)&&((y-2*y)+clickY<wys))
        {
            ptr[szer*4*((y-2*y)+clickY) + 4*(x+clickX)] = blue;
            ptr[szer*4*((y-2*y)+clickY) + 4*(x+clickX) + 1] = green;
            ptr[szer*4*((y-2*y)+clickY) + 4*(x+clickX) + 2] = red;
        }//1
        if ((x+clickX>=0)&&(y+clickY>=0)&&(x+clickX<szer)&&(y+clickY<wys))
        {
            ptr[szer*4*(y+clickY) + 4*(x+clickX)] = blue;
            ptr[szer*4*(y+clickY) + 4*(x+clickX) + 1] = green;
            ptr[szer*4*(y+clickY) + 4*(x+clickX) + 2] = red;
        }//2
        if (((x-2*x)+clickX>=0)&&(y+clickY>=0)&&((x-2*x)+clickX<szer)&&(y+clickY<wys))
        {
            ptr[szer*4*(y+clickY) + 4*((x-2*x)+clickX)] = blue;
            ptr[szer*4*(y+clickY) + 4*((x-2*x)+clickX) + 1] = green;
            ptr[szer*4*(y+clickY) + 4*((x-2*x)+clickX) + 2] = red;
        }//3
        if (((x-2*x)+clickX>=0)&&((y-2*y)+clickY>=0)&&((x-2*x)+clickX<szer)&&((y-2*y)+clickY<wys))
        {
            ptr[szer*4*((y-2*y)+clickY) + 4*((x-2*x)+clickX)] = blue;
            ptr[szer*4*((y-2*y)+clickY) + 4*((x-2*x)+clickX) + 1] = green;
            ptr[szer*4*((y-2*y)+clickY) + 4*((x-2*x)+clickX) + 2] = red;
        }//4
    }
}

void MainWindow::rysujWielokat()
{
    int i;
    int a,b;
    int x1,y1,x2,y2;

    if (clickX > releaseX)
    {
        a = clickX - releaseX;
    }
    else
    {
        a = releaseX - clickX;
    }
    if (clickY > releaseY)
    {
        b = clickY - releaseY;
    }
    else
    {
        b = releaseY - clickY;
    }

    for (i = 0; i < 6283; i+=(int)floor((2*M_PI/v)*1000 + 0.5))
    {
        x1 = (int)floor(a * cos((double)i/1000) + 0.5);
        y1 = (int)floor(b * sin((double)i/1000) + 0.5);
        x2 = (int)floor(a * cos((double)(i+floor((2*M_PI/v)*1000 + 0.5))/1000) + 0.5);
        y2 = (int)floor(b * sin((double)(i+floor((2*M_PI/v)*1000 + 0.5))/1000) + 0.5);
        rysujOdcinek(x1+clickX, y1+clickY, x2+clickX, y2+clickY);
    }
}

void MainWindow::rysujOdcinek(int x1, int y1, int x2, int y2)
{
    unsigned char *ptr;
    ptr = img->bits();

    double m;
    int x,y;
    int i;

    if ((x1 != x2) && (y1 != y2))
    {
        m = (double)(y2 - y1)/(double)(x2 - x1);
        if (m >= -1 && m < 1)
        {
            if (x1 < x2)
            {
                for (i = x1; i <= x2; i++)
                {
                    y = (int)floor((m * (i - x1)) + y1 + 0.5);
                    if ((i>=0)&&(y>=0)&&(i<szer)&&(y<wys))
                    {
                        ptr[szer*4*y + 4*i] = blue;
                        ptr[szer*4*y + 4*i + 1] = green;
                        ptr[szer*4*y + 4*i + 2] = red;
                    }
                }
            }
            else
            {
                for (i = x2; i <= x1; i++)
                {
                    y = (int)floor((m * (i - x2)) + y2 + 0.5);
                    if ((i>=0)&&(y>=0)&&(i<szer)&&(y<wys))
                    {
                        ptr[szer*4*y + 4*i] = blue;
                        ptr[szer*4*y + 4*i + 1] = green;
                        ptr[szer*4*y + 4*i + 2] = red;
                    }
                }
            }
        }
        else
        {
            if (y1 < y2)
            {
                for (i = y1; i <= y2; i++)
                {
                    x = (int)floor(((i - y1) / m) + x1 + 0.5);
                    if ((x>=0)&&(i>=0)&&(x<szer)&&(i<wys))
                    {
                        ptr[szer*4*i + 4*x] = blue;
                        ptr[szer*4*i + 4*x + 1] = green;
                        ptr[szer*4*i + 4*x + 2] = red;
                    }
                }
            }
            else
            {
                for (i = y2; i <= y1; i++)
                {
                    x = (int)floor(((i - y2) / m) + x2 + 0.5);
                    if ((x>=0)&&(i>=0)&&(x<szer)&&(i<wys))
                    {
                        ptr[szer*4*i + 4*x] = blue;
                        ptr[szer*4*i + 4*x + 1] = green;
                        ptr[szer*4*i + 4*x + 2] = red;
                    }
                }
            }
        }
    }
    else
    {
        if (x1 == x2)
        {
            if (y1 < y2)
            {
                for (i = y1; i <= y2; i++)
                {
                    if ((x1>=0)&&(i>=0)&&(x1<szer)&&(i<wys))
                    {
                        ptr[szer*4*i + 4*x1] = blue;
                        ptr[szer*4*i + 4*x1 + 1] = green;
                        ptr[szer*4*i + 4*x1 + 2] = red;
                    }
                }
            }
            else
            {
                for (i = y2; i <= y1; i++)
                {
                    if ((x1>=0)&&(i>=0)&&(x1<szer)&&(i<wys))
                    {
                        ptr[szer*4*i + 4*x1] = blue;
                        ptr[szer*4*i + 4*x1 + 1] = green;
                        ptr[szer*4*i + 4*x1 + 2] = red;
                    }
                }
            }
        }
        else
        {
            if (x1 < x2)
            {
                for (i = x1; i <= x2; i++)
                {
                    if ((i>=0)&&(y1>=0)&&(i<szer)&&(y1<wys))
                    {
                        ptr[szer*4*y1 + 4*i] = blue;
                        ptr[szer*4*y1 + 4*i + 1] = green;
                        ptr[szer*4*y1 + 4*i + 2] = red;
                    }
                }
            }
            else
            {
                for (i = x2; i <= x1; i++)
                {
                    if ((i>=0)&&(y1>=0)&&(i<szer)&&(y1<wys))
                    {
                        ptr[szer*4*y1 + 4*i] = blue;
                        ptr[szer*4*y1 + 4*i + 1] = green;
                        ptr[szer*4*y1 + 4*i + 2] = red;
                    }
                }
            }
        }
    }
    if ((x1>=0)&&(y1>=0)&&(x1<szer)&&(y1<wys))
    {
        ptr[szer*4*y1 + 4*x1] = blue;
        ptr[szer*4*y1 + 4*x1 + 1] = green;
        ptr[szer*4*y1 + 4*x1 + 2] = red;
    }
}
