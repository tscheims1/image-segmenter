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
    connect(ui->clearButton, SIGNAL (released()), this, SLOT (clearMask()));

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
        loadImage(*imagesIt);
    }

}
void MainWindow::loadImage(QString fileName)
{
    QImage image(buildImagePath(fileName));
    ui->imageLabel->setGeometry(ui->imageLabel->geometry().x(),
                                ui->imageLabel->geometry().y(),
                                image.width(),image.height());
    ui->imageLabel->setPixmap(QPixmap::fromImage(image));

    ui->drawingLabel->setGeometry(ui->imageLabel->geometry().x(),
                                ui->imageLabel->geometry().y(),
                                image.width(),image.height());
    QString maskName = getMaskDir()+fileName;

    if(QFile(maskName).exists())
    {
        QPixmap pm(maskName);
        ui->drawingLabel->setupPainter(pm);
    }
    else
        ui->drawingLabel->setupPainter();


}
void MainWindow::nextImage()
{
    if(imagesIt != nullptr && imagesIt != images.constEnd())
    {
        imagesIt++;
        loadImage(*imagesIt);

    }
}
void MainWindow::prevImage()
{
    if(imagesIt != nullptr && imagesIt !=images.constBegin())
    {
        imagesIt--;
        loadImage(*imagesIt);
    }

}
void MainWindow::saveImage()
{
    QString maskDirName = getMaskDir();
    if(!QDir(maskDirName).exists())
        QDir().mkdir(maskDirName);

    if(ui->drawingLabel->savePixmap(maskDirName+(*imagesIt)))
    {
        QMessageBox msgBox;
        msgBox.setText("Image successfull saved");
        msgBox.exec();
    }
}
void MainWindow::clearMask()
{
    ui->drawingLabel->clearMask();
}
QString MainWindow::buildImagePath(QString fileName)
{
    return currentDir+"/"+fileName;
}
QString MainWindow::getMaskDir()
{
    return currentDir+"/masks/";
}

MainWindow::~MainWindow()
{
    delete ui;
}
