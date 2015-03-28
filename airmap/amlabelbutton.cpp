#include <QMouseEvent>
#include <QTimeLine>

#include "amlabelbutton.h"

AMLabelButton::AMLabelButton(QWidget *parent) :
    QLabel(parent)
{
    //Set contents margins.
    setContentsMargins(5,5,5,5);
    setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    //Generate animation timelines.
    m_expandAnime=generateAnime();
    m_foldAnime=generateAnime();
    m_foldAnime->setEndFrame(0);
    //Set fixed width first.
    setFixedWidth(0);
}

AMLabelButton::~AMLabelButton()
{

}

void AMLabelButton::showButton()
{
    //Check if the button has been shown.
    int preferWidth=sizeHint().width()+5;
    if(width()==preferWidth)
    {
        return;
    }
    //Set the end frame.
    m_expandAnime->setEndFrame(preferWidth);
    //Start animation.
    startAnime(m_expandAnime);
}

void AMLabelButton::hideButton()
{
    //Check the button's width first.
    if(width()==0)
    {
        return;
    }
    //Start animation.
    startAnime(m_foldAnime);
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

void AMLabelButton::stopAnimes()
{
    m_expandAnime->stop();
    m_foldAnime->stop();
}

inline void AMLabelButton::startAnime(QTimeLine *anime)
{
    //Stop all animations.
    stopAnimes();
    //Set the start frame.
    anime->setStartFrame(width());
    //Start anime.
    anime->start();
}

QTimeLine *AMLabelButton::generateAnime()
{
    //Timeline animation generate factory.
    QTimeLine *timeLine=new QTimeLine(200, this);
    //Configure the animation timeline.
    timeLine->setEasingCurve(QEasingCurve::OutCubic);
    timeLine->setUpdateInterval(15);
    //Link the time line to width change function.
    connect(timeLine, &QTimeLine::frameChanged,
            this, &AMLabelButton::setFixedWidth);
    return timeLine;
}

