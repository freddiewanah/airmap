#include <QMouseEvent>
#include <QScrollBar>

#include "amtouchsrollarea.h"

#include <QDebug>

AMTouchSrollArea::AMTouchSrollArea(QWidget *parent) :
    QScrollArea(parent)
{
    verticalScrollBar()->setStyleSheet("QScrollBar:vertical {"
                                       "   border: 0px solid grey;"
                                       "   background: rgba(64,64,64,255);"
                                       "   width: 8px;"
                                       "}"
                                       "QScrollBar::handle:vertical {"
                                       "   background: rgba(100, 100, 100);"
                                       "   min-height: 10px;"
                                       "   border-radius: 4px;"
                                       "}"
                                       "QScrollBar::add-line:vertical {"
                                       "   border: 0px solid grey;"
                                       "   background: rgba(0, 0, 0, 100);"
                                       "   height: 0px;"
                                       "   subcontrol-position: down;"
                                       "   subcontrol-origin: margin;"
                                       "}"
                                       "QScrollBar::sub-line:vertical {"
                                       "   border: 0px solid grey;"
                                       "   background: rgba(0, 0, 0, 100);"
                                       "   height: 0px;"
                                       "   subcontrol-position: up;"
                                       "   subcontrol-origin: margin;"
                                       "}");
    horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal {"
                                         "   border: 0px solid grey;"
                                         "   background: rgba(64,64,64,255);"
                                         "   height: 8px;"
                                         "}"
                                         "QScrollBar::handle:horizontal {"
                                         "   background: rgba(100, 100, 100);"
                                         "   min-height: 10px;"
                                         "   border-radius: 4px;"
                                         "}"
                                         "QScrollBar::add-line:horizontal {"
                                         "   border: 0px solid grey;"
                                         "   background: rgba(0, 0, 0, 100);"
                                         "   width: 0px;"
                                         "   subcontrol-position: down;"
                                         "   subcontrol-origin: margin;"
                                         "}"
                                         "QScrollBar::sub-line:horizontal {"
                                         "   border: 0px solid grey;"
                                         "   background: rgba(0, 0, 0, 100);"
                                         "   width: 0px;"
                                         "   subcontrol-position: up;"
                                         "   subcontrol-origin: margin;"
                                         "}");
}

void AMTouchSrollArea::mousePressEvent(QMouseEvent *event)
{
    m_pressed=true;
    m_moved=false;
    //Save the position.
    m_pressedPoint=event->pos();
    m_hValue=horizontalScrollBar()->value();
    m_vValue=verticalScrollBar()->value();
    QScrollArea::mousePressEvent(event);
}

void AMTouchSrollArea::mouseMoveEvent(QMouseEvent *event)
{
    //Check the pressed flag.
    if(m_pressed)
    {
        //Set moved flag.
        m_moved=true;
        //Move the content.
        QPoint preferPoint=event->pos()-m_pressedPoint;
        horizontalScrollBar()->setValue(m_hValue-preferPoint.x());
        verticalScrollBar()->setValue(m_vValue-preferPoint.y());
    }
    QScrollArea::mouseMoveEvent(event);
}

void AMTouchSrollArea::mouseReleaseEvent(QMouseEvent *event)
{
    //Release the flag.
    m_pressed=false;
    //Check moved or not.
    if(!m_moved)
    {
        //Emit touch event.
        emit touch(m_pressedPoint-widget()->pos());
    }
    QScrollArea::mouseReleaseEvent(event);
}
