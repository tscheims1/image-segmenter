#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void loadImage(QString fileName);
    QString buildImagePath(QString fileName);
    QStringList images;
    QStringList::const_iterator imagesIt;
    QString currentDir;

private slots:
    void openDir();
    void nextImage();
    void prevImage();
    void saveImage();

};

#endif // MAINWINDOW_H
