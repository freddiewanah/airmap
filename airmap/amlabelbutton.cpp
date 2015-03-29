#include <QMouseEvent>
#include <QPainter>
#include <QTimeLine>

#include "amlabelbutton.h"

AMLabelButton::AMLabelButton(QWidget *parent) :
    QWidget(parent)
{
    //Set contents margins.
    setContentsMargins(5,5,5,5);
    //Set palette.
    QPalette pal=palette();
    pal.setColor(QPalette::WindowText, QColor(0x00, 0x7a, 0xff));
    setPalette(pal);
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
    int preferWidth=(m_pixmap.isNull()?fontMetrics().width(m_text):m_pixmap.width())+5;
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

void AMLabelButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    //Initial the painter.
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing |
                           QPainter::TextAntialiasing |
                           QPainter::SmoothPixmapTransform,
                           true);
    //Set the opacity to the painter.
    painter.setOpacity(m_pressedOpacity);
    //Draw the text, draw the pixmap.
    if(m_pixmap.isNull())
    {
        painter.drawText(rect(),
                         Qt::AlignRight | Qt::AlignVCenter,
                         m_text);
    }
    else
    {
        painter.drawPixmap((width()-m_pixmap.width())>>1,
                           0,
                           m_pixmap);
    }
}

void AMLabelButton::mousePressEvent(QMouseEvent *event)
{
    //Set the pressed event.
    m_pressed=true;
    //Change the opacity.
    m_pressedOpacity=0.2;
    //Update the button.
    update();
    //Do the original pressed event.
    QWidget::mousePressEvent(event);
}

void AMLabelButton::mouseReleaseEvent(QMouseEvent *event)
{
    //Restore the opacity.
    m_pressedOpacity=1.0;
    //Update the button.
    update();
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
    QWidget::mouseReleaseEvent(event);
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
QString AMLabelButton::text() const
{
    return m_text;
}

void AMLabelButton::setText(const QString &text)
{
    m_text = text;
}

QPixmap AMLabelButton::pixmap() const
{
    return m_pixmap;
}

void AMLabelButton::setPixmap(const QPixmap &pixmap, const QSize &preferSize)
{
    if(preferSize.isNull())
    {
        m_pixmap=pixmap;
        return;
    }
    m_pixmap = pixmap.scaled(preferSize,
                             Qt::KeepAspectRatio,
                             Qt::SmoothTransformation);
}
