#include <QMouseEvent>

#include "amhotpoint.h"

AMHotPoint::AMHotPoint(QWidget *parent) :
    QWidget(parent)
{
    setAutoFillBackground(true);
    QPalette pal=palette();
    pal.setColor(QPalette::Window, QColor(0,0,0,200));
    setPalette(pal);
}

void AMHotPoint::mousePressEvent(QMouseEvent *event)
{
    //Set the pressed.
    m_pressed=true;
    //Save the point.
    m_pressedPoint=mapTo(parentWidget(), event->pos());
    m_startPos=pos();
    //Do the original pressed event.
    QWidget::mousePressEvent(event);
}

void AMHotPoint::mouseMoveEvent(QMouseEvent *event)
{
    if(m_pressed)
    {
        QPoint preferPoint=m_startPos+mapTo(parentWidget(), event->pos())-m_pressedPoint;
        if(preferPoint.x()<0)
        {
            preferPoint.setX(0);
        }
        if(preferPoint.y()<0)
        {
            preferPoint.setY(0);
        }
        if(preferPoint.x()+width()>parentWidget()->width())
        {
            preferPoint.setX(parentWidget()->width()-width());
        }
        if(preferPoint.y()+height()>parentWidget()->height())
        {
            preferPoint.setY(parentWidget()->height()-height());
        }
        move(preferPoint);
    }
    QWidget::mouseMoveEvent(event);
}

void AMHotPoint::mouseReleaseEvent(QMouseEvent *event)
{
    m_pressed=false;
    //Ask to check the current position.
    emit requireCheckPosition();
    //Release the event.
    QWidget::mouseReleaseEvent(event);
}
