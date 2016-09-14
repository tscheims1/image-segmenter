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
    void setupPainter(QPixmap pm);
    ~ClickableLabel();
    bool savePixmap(QString fileName);
    void clearMask();
signals:
    void clicked();
protected:
    void mouseMoveEvent(QMouseEvent* event);
    void mouseDoubleClickEvent( QMouseEvent * event);
    QPainterPath path;
    QPainter *painter = nullptr;
    QPixmap *pixmap = nullptr;
private:
    bool isFirstNode = true;
};

#endif // CLICKABLELABEL_H
