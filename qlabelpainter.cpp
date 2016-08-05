#include "qlabelpainter.h"

QLabelPainter::QLabelPainter(const QString& text, QWidget* parent)
    : QLabel(parent)
{
    setText(text);
}

QLabelPainter::~QLabelPainter()
{
}

void QLabelPainter::mousePressEvent(QMouseEvent* event)
{
    emit clicked();
}
