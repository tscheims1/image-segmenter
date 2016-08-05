#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H
#include <QLabel>
#include <QApplication>
#include <QWidget>
#include <QDebug>
#include <QMouseEvent>
#include <QPainterPath>
#include <QPainter>
class ClickableLabel : public QLabel
{
Q_OBJECT
public:
    explicit ClickableLabel(QWidget* parent=0 );
    void setupPainter();
    ~ClickableLabel();
signals:
    void clicked();
protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent( QMouseEvent * event );
    void mouseDoubleClickEvent( QMouseEvent * event);
    QPainterPath path;
    QPainter *painter;
    QPixmap *pixmap;
private:
    bool isFirstNode = true;
};

#endif // CLICKABLELABEL_H