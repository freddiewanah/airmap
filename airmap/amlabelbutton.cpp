#include <QMouseEvent>

#include "amlabelbutton.h"

AMLabelButton::AMLabelButton(QWidget *parent) :
    QLabel(parent)
{

}

AMLabelButton::~AMLabelButton()
{

}

void AMLabelButton::mousePressEvent(QMouseEvent *event)
{
    //Set the pressed event.
    m_pressed=true;
    //Do the original pressed event.
    QLabel::mousePressEvent(event);
}

void AMLabelButton::mouseReleaseEvent(QMouseEvent *event)
{
    //Checked the pressed event flag has been set.
    if(m_pressed)
    {
        //Release the pressed flag.
        m_pressed=false;
        if(event->button()==Qt::LeftButton)
        {
            //Emit the clicked signal.
            emit clicked();
        }
    }
    //Do the label release event.
    QLabel::mouseReleaseEvent(event);
}

