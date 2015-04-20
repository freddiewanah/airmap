#include <QTimeLine>
#include <QPropertyAnimation>
#include <QBoxLayout>
#include <QDial>
#include <QSignalMapper>
#include <QMouseEvent>

#include "amtextbutton.h"

#include "amhotpoint.h"

#include <QDebug>

AMHotPoint::AMHotPoint(QWidget *parent) :
    QWidget(parent)
{
    setAutoFillBackground(true);
    QPalette pal=palette();
    pal.setColor(QPalette::Window, QColor(0,0,0,0));
    setPalette(pal);
    //Initial the layout.
    QBoxLayout *mainLayout=new QBoxLayout(QBoxLayout::TopToBottom,
                                          this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    //Initial the indicator.
    m_indicator=new QLabel(this);
    m_indicator->setScaledContents(true);
    m_indicator->setPixmap(QPixmap("://resource/point.png"));
    m_indicator->setFixedSize(50, 50);

    QSignalMapper *changeMap=new QSignalMapper(this);
    connect(changeMap, SIGNAL(mapped(int)), this, SIGNAL(requireChangeMap(int)));
    //Initial the buttons.
    for(int i=0; i<3; i++)
    {
        m_floor[i]=new AMTextButton(this);
        m_floor[i]->setMinimumHeight(50);
        m_floor[i]->setAlignment(Qt::AlignCenter);
        connect(m_floor[i], SIGNAL(clicked()), changeMap, SLOT(map()));
        connect(m_floor[i], SIGNAL(clicked()), this, SLOT(foldHotPoint()));
        changeMap->setMapping(m_floor[i], i);
        QPalette pal=m_floor[i]->palette();
        pal.setColor(QPalette::WindowText, QColor(255,255,255));
        m_floor[i]->setPalette(pal);
        mainLayout->addWidget(m_floor[i]);
    }
    m_floor[0]->setText("B1");
    m_floor[1]->setText("F1");
    m_floor[2]->setText("F2");
    m_slider=new QDial(this);
    m_slider->setRange(25,200);
    m_slider->setValue(100);
    connect(m_slider, &QDial::valueChanged,
            [=](const int &zoom)
            {
                emit requireChangeZoom(((qreal)zoom)/100.0);
            });
    mainLayout->addWidget(m_slider);

    m_stickAnime=new QTimeLine(200, this);
    m_stickAnime->setUpdateInterval(20);
    m_stickAnime->setEasingCurve(QEasingCurve::OutCubic);
    connect(m_stickAnime, &QTimeLine::frameChanged,
            [=](const int &frame)
            {
                move(frame, y());
            });

    m_expandAnime=new QPropertyAnimation(this, "geometry", this);
    m_expandAnime->setDuration(200);
    m_expandAnime->setEasingCurve(QEasingCurve::OutCubic);
    connect(m_expandAnime, SIGNAL(valueChanged(QVariant)),
            this, SLOT(onActionExpand(QVariant)));
    connect(m_expandAnime, SIGNAL(finished()),
            this, SLOT(onActionShowItems()));

    m_foldAnime=new QPropertyAnimation(this, "geometry", this);
    m_foldAnime->setDuration(200);
    m_foldAnime->setEasingCurve(QEasingCurve::OutCubic);
    connect(m_foldAnime, SIGNAL(valueChanged(QVariant)),
            this, SLOT(onActionFold(QVariant)));
    connect(m_foldAnime, &QPropertyAnimation::finished,
            [=]
            {
                m_indicator->show();
                m_expandGeometry=QRect();
            });

    onActionHideItems();
}

void AMHotPoint::onActionShowItems()
{
    //Show the items.
    m_floor[0]->show();
    m_floor[1]->show();
    m_floor[2]->show();
    m_slider->show();
}

void AMHotPoint::onActionHideItems()
{
    //Hide the items.
    m_floor[0]->hide();
    m_floor[1]->hide();
    m_floor[2]->hide();
    m_slider->hide();
}

void AMHotPoint::foldHotPoint()
{
    if(m_expandGeometry.isNull())
    {
        return;
    }
    //Configure the hot point.
    m_foldAnime->setStartValue(geometry());
    QRect preferGeometry=QRect((m_expandGeometry.x()==0)?0:(parentWidget()->width()-50),
                               m_expandGeometry.y(),
                               50,
                               50);
    if(preferGeometry.bottom()>parentWidget()->height())
    {
        preferGeometry.moveTop(parentWidget()->height()-preferGeometry.height());
    }
    if(preferGeometry.right()>parentWidget()->width())
    {
        preferGeometry.moveLeft(parentWidget()->width()-preferGeometry.width());
    }
    m_foldAnime->setEndValue(preferGeometry);
    m_foldAnime->start();
    //Hide the widget first.
    onActionHideItems();
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

void AMHotPoint::onActionExpand(const QVariant &value)
{
    Q_UNUSED(value)
    //Ignore the value.
    QPalette pal=palette();
    pal.setColor(QPalette::Window, QColor(0,0,0,m_expandAnime->currentTime()));
    setPalette(pal);
}

void AMHotPoint::onActionFold(const QVariant &value)
{
    Q_UNUSED(value)
    //Ignore the value.
    QPalette pal=palette();
    pal.setColor(QPalette::Window, QColor(0,0,0,200-m_foldAnime->currentTime()));
    setPalette(pal);
}

void AMHotPoint::onActionClicked()
{
    if(m_indicator->isVisible())
    {
        //Hide the indicator.
        m_indicator->hide();
        //Save the expand animation.
        m_expandGeometry=geometry();
        //Expand the animation, check the position first.
        m_expandAnime->setStartValue(geometry());
        QRect preferGeometry=QRect(geometry().x(),
                                   geometry().y(),
                                   80,
                                   m_floor[0]->height()*3+80);
        if(preferGeometry.bottom()>parentWidget()->height())
        {
            preferGeometry.moveTop(parentWidget()->height()-preferGeometry.height());
        }
        if(preferGeometry.right()>parentWidget()->width())
        {
            preferGeometry.moveLeft(parentWidget()->width()-preferGeometry.width());
        }
        m_expandAnime->setEndValue(preferGeometry);
        m_expandAnime->start();
    }
}

void AMHotPoint::moveToSide()
{
    m_stickAnime->stop();
    //Check release position.
    m_stickAnime->setFrameRange(x(),
                                ((pos().x()+(width()>>1))<(parentWidget()->width()>>1))?0:(parentWidget()->width()-width()));
    m_stickAnime->start();
}
