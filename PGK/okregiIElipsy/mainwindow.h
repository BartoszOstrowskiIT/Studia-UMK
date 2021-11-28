#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>
#include <QRadioButton>
#include <QMouseEvent>
#include <cmath>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
	
	QImage *img;
    QImage *img_dump;
	
	int szer;
    int wys;
    int poczX;
    int poczY;

    int clickX;
    int clickY;
    int releaseX;
    int releaseY;

    int red;
    int green;
    int blue;

    QSpinBox *spinBox_1;
    QSpinBox *spinBox_2;
    QSpinBox *spinBox_3;
    QSpinBox *spinBox_7;
    QSlider *slider_1;
    QSlider *slider_2;
    QSlider *slider_3;
    QSlider *slider_7;

    int figura;
    int v;

	void czysc();
    void zapisz();
    void wczytaj();
    void rysujOkrag();
    void rysujElipse();
    void rysujWielokat();
    void rysujOdcinek(int x1, int y1, int x2, int y2);
	
private slots:
    void on_cleanButton_clicked();
    void on_exitButton_clicked();
    void on_spinBox_1_valueChanged(int value);
    void on_spinBox_2_valueChanged(int value);
    void on_spinBox_3_valueChanged(int value);
    void on_spinBox_7_valueChanged(int value);
    void on_horizontalSlider_1_valueChanged(int value);
    void on_horizontalSlider_2_valueChanged(int value);
    void on_horizontalSlider_3_valueChanged(int value);
    void on_horizontalSlider_7_valueChanged(int value);
    void on_radioButton_1_toggled(bool checked);
    void on_radioButton_2_toggled(bool checked);
    void on_radioButton_3_toggled(bool checked);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);
};
#endif
