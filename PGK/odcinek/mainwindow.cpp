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
    slider_1 = ui->horizontalSlider_1;
    slider_2 = ui->horizontalSlider_2;
    slider_3 = ui->horizontalSlider_3;

    red = 0;
    green = 0;
    blue = 0;

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
        rysujOdcinek();
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
        rysujOdcinek();
    }
    update();
    zapisz();
}

void MainWindow::rysujOdcinek()
{
    unsigned char *ptr;
    ptr = img->bits();

    double m;
    double x,y;
    int i;

    if ((clickX != releaseX) && (clickY != releaseY))
    {
        m = (double)(releaseY - clickY)/(double)(releaseX - clickX);
        if (m >= -1 && m < 1)
        {
            if (clickX < releaseX)
            {
                for (i = clickX; i <= releaseX; i++)
                {
                    y = (m * (i - clickX)) + clickY;
                    ptr[szer*4*(int)floor(y + 0.5) + 4*i] = blue;
                    ptr[szer*4*(int)floor(y + 0.5) + 4*i + 1] = green;
                    ptr[szer*4*(int)floor(y + 0.5) + 4*i + 2] = red;
                }
            }
            else
            {
                for (i = releaseX; i <= clickX; i++)
                {
                    y = (m * (i - releaseX)) + releaseY;
                    ptr[szer*4*(int)floor(y + 0.5) + 4*i] = blue;
                    ptr[szer*4*(int)floor(y + 0.5) + 4*i + 1] = green;
                    ptr[szer*4*(int)floor(y + 0.5) + 4*i + 2] = red;
                }
            }
        }
        else
        {
            if (clickY < releaseY)
            {
                for (i = clickY; i <= releaseY; i++)
                {
                    x = ((i - clickY) / m) + clickX;
                    ptr[szer*4*i + 4*(int)floor(x + 0.5)] = blue;
                    ptr[szer*4*i + 4*(int)floor(x + 0.5) + 1] = green;
                    ptr[szer*4*i + 4*(int)floor(x + 0.5) + 2] = red;
                }
            }
            else
            {
                for (i = releaseY; i <= clickY; i++)
                {
                    x = ((i - releaseY) / m) + releaseX;
                    ptr[szer*4*i + 4*(int)floor(x + 0.5)] = blue;
                    ptr[szer*4*i + 4*(int)floor(x + 0.5) + 1] = green;
                    ptr[szer*4*i + 4*(int)floor(x + 0.5) + 2] = red;
                }
            }
        }
    }
    else
    {
        if (clickX == releaseX)
        {
            if (clickY < releaseY)
            {
                for (i = clickY; i <= releaseY; i++)
                {
                    ptr[szer*4*i + 4*clickX] = blue;
                    ptr[szer*4*i + 4*clickX + 1] = green;
                    ptr[szer*4*i + 4*clickX + 2] = red;
                }
            }
            else
            {
                for (i = releaseY; i <= clickY; i++)
                {
                    ptr[szer*4*i + 4*clickX] = blue;
                    ptr[szer*4*i + 4*clickX + 1] = green;
                    ptr[szer*4*i + 4*clickX + 2] = red;
                }
            }
        }
        else
        {
            if (clickX < releaseX)
            {
                for (i = clickX; i <= releaseX; i++)
                {
                    ptr[szer*4*clickY + 4*i] = blue;
                    ptr[szer*4*clickY + 4*i + 1] = green;
                    ptr[szer*4*clickY + 4*i + 2] = red;
                }
            }
            else
            {
                for (i = releaseX; i <= clickX; i++)
                {
                    ptr[szer*4*clickY + 4*i] = blue;
                    ptr[szer*4*clickY + 4*i + 1] = green;
                    ptr[szer*4*clickY + 4*i + 2] = red;
                }
            }
        }
    }

    ptr[szer*4*clickY + 4*clickX] = blue;
    ptr[szer*4*clickY + 4*clickX + 1] = green;
    ptr[szer*4*clickY + 4*clickX + 2] = red;
}
