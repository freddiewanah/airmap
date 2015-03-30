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

void AMSearchSuggetions::mousePressEvent(QMouseEvent *event)
{
    //Set the flag.
    m_pressed=true;m_moved=false;
    //Save the position.
    m_pressedPoint=event->pos();
    m_pressedScrollBarValue=verticalScrollBar()->value();
    QTreeView::mousePressEvent(event);
}

void AMSearchSuggetions::mouseReleaseEvent(QMouseEvent *event)
{
    if(!m_moved)
    {
        QTreeView::mouseReleaseEvent(event);
    }
}

void AMSearchSuggetions::mouseMoveEvent(QMouseEvent *event)
{
    //Set moved flag.
    m_moved=true;
    //Move the scroll area.
    verticalScrollBar()->setValue(m_pressedScrollBarValue-(event->pos().y()-m_pressedPoint.y()));
//    QTreeView::mouseMoveEvent(event);
}
