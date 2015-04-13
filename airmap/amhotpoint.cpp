#include <QTimeLine>

#include <QMouseEvent>

#include "amhotpoint.h"

#include <QDebug>

AMHotPoint::AMHotPoint(QWidget *parent) :
    QWidget(parent)
{
    setAutoFillBackground(true);
    QPalette pal=palette();
    pal.setColor(QPalette::Window, QColor(0,0,0,200));
    setPalette(pal);

    m_stickAnime=new QTimeLine(200, this);
    m_stickAnime->setUpdateInterval(20);
    m_stickAnime->setEasingCurve(QEasingCurve::OutCubic);
    connect(m_stickAnime, &QTimeLine::frameChanged,
            [=](const int &frame)
            {
                move(frame, y());
    });
}

void AMHotPoint::leaveEvent(QEvent *event)
{
    if(m_pressed)
    {
        m_pressed=false;
        moveToSide();
    }
    QWidget::leaveEvent(event);
}

void AMHotPoint::mousePressEvent(QMouseEvent *event)
{
    //Set the pressed.
    m_moved=false;
    m_pressed=true;
    //Stop stick the anime.
    m_stickAnime->stop();
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
        //Set the moved flag.
        m_moved=true;
        QPoint preferPoint=m_startPos+mapTo(parentWidget(), event->pos())-m_pressedPoint;
        if(preferPoint.x()<0)
        {
            preferPoint.setX(0);
        }
        if(preferPoint.y()<45)
        {
            preferPoint.setY(45);
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
    //Reset the pressed flag.
    m_pressed=false;
    if(!m_moved)
    {
        //Means clicked.
        m_moved=false;
        onActionClicked();
        return;
    }
    //Move to side.
    moveToSide();
    //Release the event.
    QWidget::mouseReleaseEvent(event);
}

void AMHotPoint::onActionClicked()
{
    qDebug()<<"Expand!";
}

void AMHotPoint::moveToSide()
{
    m_stickAnime->stop();
    //Check release position.
    m_stickAnime->setFrameRange(x(),
                                ((pos().x()+(width()>>1))<(parentWidget()->width()>>1))?0:(parentWidget()->width()-width()));
    m_stickAnime->start();
}
