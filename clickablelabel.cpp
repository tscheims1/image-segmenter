#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget* parent)
    : QLabel(parent)
{
}
void ClickableLabel::setupPainter()
{
    if(pixmap !=nullptr)
    {
        painter->end();
        delete painter;
        delete pixmap;
    }
    pixmap = new QPixmap(width(),height());
    pixmap->fill(QColor("transparent"));
    painter = new QPainter(pixmap);
    painter->setOpacity(0.7);
    setPixmap(*pixmap);
}


ClickableLabel::~ClickableLabel()
{
    painter->end();
    delete pixmap;
    delete painter;
}

void ClickableLabel::mousePressEvent(QMouseEvent* event)
{
    qDebug() << "clicked"<<endl;
    emit clicked();
}
void ClickableLabel::mouseMoveEvent(QMouseEvent* event)
{
    if(isFirstNode)
    {
        path.moveTo(event->x(),event->y());
        isFirstNode = false;
    }
    else
    {
        path.lineTo(event->x(),event->y());
    }

    painter->drawPath(path);
    setPixmap(*pixmap);


}
void ClickableLabel::mouseReleaseEvent(QMouseEvent *event)
{

}
void ClickableLabel::mouseDoubleClickEvent( QMouseEvent * event)
{
    QBrush brush(QColor (255, 0, 0));
    painter->fillPath(path,brush);
    setPixmap(*pixmap);
    isFirstNode = true;
    path = QPainterPath();

}
