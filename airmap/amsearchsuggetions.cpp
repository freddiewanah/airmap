#include <QHeaderView>
#include <QScrollBar>
#include <QMouseEvent>
#include <QGestureEvent>
#include <QPanGesture>

#include "amsuggestionmodel.h"
#include "amsuggestionfiltermodel.h"
#include "amsuggestiondelegate.h"

#include "amsearchsuggetions.h"

#include <QDebug>

AMSearchSuggetions::AMSearchSuggetions(QWidget *parent) :
    QTreeView(parent)
{
#ifdef Q_OS_ANDROID
    verticalScrollBar()->setStyleSheet("QScrollBar:vertical {"
                                       "   border: 0px solid grey;"
                                       "   background: rgba(0, 0, 0, 0);"
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
#endif
    //Set properties.
    setFrameShape(QFrame::NoFrame);
    setFrameShadow(QFrame::Plain);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    setIndentation(0);
    header()->setVisible(false);
    //Set palette.
    QPalette pal=palette();
    pal.setColor(QPalette::Base, QColor(0,0,0,100));
    setPalette(pal);
    //Set item view delegate
    setItemDelegate(new AMSuggestionDelegate(this));

    //Initial the models.
    m_proxyModel=new AMSuggestionFilterModel(this);
    m_suggestionModel=new AMSuggestionModel(this);
    m_proxyModel->setSourceModel(m_suggestionModel);
    setModel(m_proxyModel);

    //Expand all.
    expandAll();
}

void AMSearchSuggetions::searchText(const QString &text)
{
    m_proxyModel->setFilterFixedString(text);
}

bool AMSearchSuggetions::event(QEvent *event)
{
    if (event->type()==QEvent::Gesture)
    {
        return gestureEvent(static_cast<QGestureEvent*>(event));
    }
    return QTreeView::event(event);
}

bool AMSearchSuggetions::gestureEvent(QGestureEvent *event)
{
    if(QGesture *pan=event->gesture(Qt::PanGesture))
    {
        panTriggered(static_cast<QPanGesture *>(pan));
    }
    return true;
}

void AMSearchSuggetions::mousePressEvent(QMouseEvent *event)
{
    //Set the flag.
    m_pressed=true;
    //Do mouse pressed event.
    QTreeView::mousePressEvent(event);
}

void AMSearchSuggetions::mouseReleaseEvent(QMouseEvent *event)
{
    QTreeView::mouseReleaseEvent(event);
}

void AMSearchSuggetions::mouseMoveEvent(QMouseEvent *event)
{
    QTreeView::mouseMoveEvent(event);
}

void AMSearchSuggetions::panTriggered(QPanGesture *gesture)
{
    qDebug()<<"Triggered.";
}
