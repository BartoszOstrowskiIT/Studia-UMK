#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>
#include <QMouseEvent>

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
	
	int szer;
    int wys;
    int poczX;
    int poczY;

    int clickX;
    int clickY;
    int releaseX;
    int releaseY;
	
	void czysc();
    void rysujOdcinek(int red, int green, int blue);
	
private slots:
    void on_cleanButton_clicked();
    void on_exitButton_clicked();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);
};
#endif // MAINWINDOW_H
