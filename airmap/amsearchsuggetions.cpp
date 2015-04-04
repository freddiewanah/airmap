#include <QHeaderView>
#include <QScrollBar>
#include <QMouseEvent>
#include <QGestureEvent>
#include <QPanGesture>
#include <QTimeLine>

#include "amsuggestionmodel.h"
#include "amsuggestionfiltermodel.h"
#include "amsuggestiondelegate.h"

#include "amsearchsuggetions.h"

#include <QDebug>

AMSearchSuggetions::AMSearchSuggetions(QWidget *parent) :
    QTreeView(parent)
{
    verticalScrollBar()->setStyleSheet("QScrollBar:vertical {"
                                       "   border: 0px solid grey;"
                                       "   background: rgba(128,128,128,255);"
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
    //Set properties.
    setFrameShape(QFrame::NoFrame);
    setFrameShadow(QFrame::Plain);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    setIndentation(0);
    header()->setVisible(false);
    //Set palette.
    QPalette pal=palette();
    pal.setColor(QPalette::Base, QColor(100,100,100, 240));
    pal.setColor(QPalette::WindowText, QColor(0,0,0));
    pal.setColor(QPalette::Text, QColor(0,0,0));
    setPalette(pal);
    //Set item view delegate
    setItemDelegate(new AMSuggestionDelegate(this));

    //Initial the timeline.
    m_scrollTimeLine=new QTimeLine(500, this);
    m_scrollTimeLine->setUpdateInterval(2);
    connect(m_scrollTimeLine, &QTimeLine::frameChanged,
            verticalScrollBar(), &QScrollBar::setValue);

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
    //Get the pressed index.
    m_pressedIndex=indexAt(event->pos());
    setCurrentIndex(m_pressedIndex);
}

void AMSearchSuggetions::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    //If user just click/touch the item, emit the search signal.
    if(!m_moved)
    {
        //Check the index is available or not.
        QStandardItem *currentItem=m_suggestionModel->itemFromIndex(m_proxyModel->mapToSource(m_pressedIndex));
        if(currentItem->isSelectable())
        {
            emit requireSearch(m_pressedIndex);
        }
    }
    //Clear the flag.
    m_pressed=false;
    m_moved=false;
}

void AMSearchSuggetions::mouseMoveEvent(QMouseEvent *event)
{
    //Set moved flag.
    m_moved=true;
    //Clear the selection if mouse pressed.
    if(m_pressed)
    {
        //Clear the selection.
        clearSelection();
        //Move the scroll area.
        verticalScrollBar()->setValue(m_pressedScrollBarValue-(event->pos().y()-m_pressedPoint.y()));
    }
}
