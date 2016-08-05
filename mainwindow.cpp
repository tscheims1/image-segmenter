#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    connect(ui->openDirButton, SIGNAL (released()), this, SLOT (openDir()));
    connect(ui->prevImageButton, SIGNAL (released()), this, SLOT (prevImage()));
    connect(ui->nextImageButton, SIGNAL (released()), this, SLOT (nextImage()));
    connect(ui->saveButton, SIGNAL (released()), this, SLOT (saveImage()));

}
void MainWindow::openDir()
{
    currentDir = QFileDialog::getExistingDirectory(this, tr("Open Image Directory"),
                                                 "/home",
                                                 QFileDialog::DontResolveSymlinks);
    QDir recoredDir(currentDir);
    QStringList filters;
    filters << "*.jpg" << "*.png";
    recoredDir.setNameFilters(filters);
    images = recoredDir.entryList(QDir::NoDotAndDotDot | QDir::Filter::Files);
    if(!images.isEmpty())
    {
        imagesIt = images.constBegin();
        loadImage(buildImagePath(*imagesIt));
    }

}
void MainWindow::loadImage(QString fileName)
{
    QImage image(fileName);
    ui->imageLabel->setGeometry(ui->imageLabel->geometry().x(),
                                ui->imageLabel->geometry().y(),
                                image.width(),image.height());
    ui->imageLabel->setPixmap(QPixmap::fromImage(image));

    ui->drawingLabel->setGeometry(ui->imageLabel->geometry().x(),
                                ui->imageLabel->geometry().y(),
                                image.width(),image.height());

    ui->drawingLabel->setupPainter();
}
void MainWindow::nextImage()
{
    if(imagesIt != images.constEnd())
    {
        imagesIt++;
        loadImage(buildImagePath(*imagesIt));

    }
}
void MainWindow::prevImage()
{
    if(imagesIt !=images.constBegin())
    {
        imagesIt--;
        loadImage(buildImagePath(*imagesIt));
    }

}
void MainWindow::saveImage()
{
    if(ui->drawingLabel->savePixmap(currentDir+"/"+"mask_"+(*imagesIt)))
    {
        QMessageBox msgBox;
        msgBox.setText("Image successfull saved");
        msgBox.exec();
    }
}

QString MainWindow::buildImagePath(QString fileName)
{
    return currentDir+"/"+fileName;
}

MainWindow::~MainWindow()
{
    delete ui;
}
