#ifndef QLABELPAINTER_H
#define QLABELPAINTER_H
#include <QWidget>
#include <QLabel>

class QLabelPainter : public QLabel
{
Q_OBJECT
public:
     explicit QLabelPainter( const QString& text="", QWidget* parent=0 );
    ~QLabelPainter();
signals:
    void clicked();
protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // QLABELPAINTER_H
