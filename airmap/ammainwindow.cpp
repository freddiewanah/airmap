#include <QBoxLayout>
#include <QLineEdit>
#include <QResizeEvent>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QPropertyAnimation>

#include "ammappainter.h"
#include "amlabelbutton.h"
#include "amlineedit.h"
#include "amlocationmanagerbase.h"
#include "amsearchsuggetions.h"
#include "amsearcherbase.h"

#include "ammainwindow.h"

#include <QDebug>

AMMainWindow::AMMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //Initial the graphics scene for the map painting.
    m_mapScene=new QGraphicsScene(this);
    m_mapView=new QGraphicsView(m_mapScene, this);
    m_mapView->setFrameShape(QFrame::NoFrame);
    //Initial the map painter.
    m_mapPainter=new AMMapPainter;
    m_mapPainter->addMap(QPixmap("://resource/maps/square_0_2d_F2s.png"),
                         "://resource/maps/square_0_2d_F2s.json");
    //Initial the map graphics proxy widget.
    m_mapItem=new QGraphicsProxyWidget(0, Qt::Widget);
    m_mapItem->setWidget(m_mapPainter);
    m_mapScene->addItem(m_mapItem);

    //Initial the search bar.
    m_searchBox=new QWidget(this);
    m_searchBox->setFixedHeight(45);
    m_searchBox->setAutoFillBackground(true);
    QPalette pal=m_searchBox->palette();
    pal.setColor(QPalette::Window, QColor(128,128,128));
    m_searchBox->setPalette(pal);
    //Initial the search bar layout.
    QBoxLayout *searchBoxLayout=new QBoxLayout(QBoxLayout::LeftToRight,
                                               m_searchBox);
    searchBoxLayout->setContentsMargins(5,0,5,0);
    searchBoxLayout->setSpacing(0);
    m_searchBox->setLayout(searchBoxLayout);
    m_addPoint=new AMLabelButton(this);
    m_addPoint->setPixmap(QPixmap("://resource/add.png"), QSize(16, 16));
    m_addPoint->setFixedHeight(16);
    m_addPoint->hideButton();
    searchBoxLayout->addWidget(m_addPoint);
    m_searchBoxText=new AMLineEdit(this);
    m_searchBoxText->setPlaceHolderLabelText("搜索或输入地点");
    m_searchBoxText->setFixedHeight(30);
    connect(m_searchBoxText, &AMLineEdit::textChanged,
            this, &AMMainWindow::filterChanged);
    connect(m_searchBoxText, &AMLineEdit::returnPressed,
            this, &AMMainWindow::startSearch);
    m_searchBoxText->setFrame(false);
    pal=m_searchBoxText->palette();
    pal.setColor(QPalette::Text, QColor(0,0,0));
    pal.setColor(QPalette::Highlight, QColor(255,255,255,70));
    pal.setColor(QPalette::HighlightedText, QColor(255,255,255));
    pal.setColor(QPalette::Base, QColor(255,255,255,128));
    m_searchBoxText->setPalette(pal);
    searchBoxLayout->addWidget(m_searchBoxText);
    m_cancelSearch=new AMLabelButton(this);
    m_cancelSearch->setText("取消");
    m_cancelSearch->hideButton();
    connect(m_searchBoxText, &AMLineEdit::focusIn,
            this, &AMMainWindow::onActionSearchFocusIn);
    connect(m_searchBoxText, &AMLineEdit::focusOut,
            this, &AMMainWindow::onActionSearchFocusOut);
    connect(m_cancelSearch, &AMLabelButton::clicked,
            this, &AMMainWindow::onActionCancelSearch);
    searchBoxLayout->addWidget(m_cancelSearch);
    m_stopNavigate=new AMLabelButton(this);
    m_stopNavigate->setText("结束");
    m_stopNavigate->hideButton();
    searchBoxLayout->addWidget(m_stopNavigate);

    //Initial the search suggestion widget.
    m_searchSuggestion=new AMSearchSuggetions(this);
    m_searchSuggestion->setGeometry(0,-10,0,10);
    //When search suggestion has a selected item, the item will be the
    //item you want to search.
    connect(m_searchSuggestion, &AMSearchSuggetions::requireSearch,
            this, &AMMainWindow::onActionSearch);
    m_showSuggestion=new QPropertyAnimation(m_searchSuggestion,
                                            "geometry",
                                            this);
    m_showSuggestion->setEasingCurve(QEasingCurve::OutCubic);
    m_hideSuggestion=new QPropertyAnimation(m_searchSuggestion,
                                            "geometry",
                                            this);
    m_hideSuggestion->setEasingCurve(QEasingCurve::OutCubic);
    m_hideSuggestion->setEndValue(QRect(0,-10,width(),10));

    //Set the map view.
//    ;

    m_searchSuggestion->raise();
    m_searchBox->raise();
}

AMMainWindow::~AMMainWindow()
{

}

AMLocationManagerBase *AMMainWindow::locationManager()
{
    return m_locationManager;
}

void AMMainWindow::setLocationManager(AMLocationManagerBase *locationManager)
{
    //Save the location manager.
    m_locationManager = locationManager;
    if(m_locationManager==nullptr)
    {
        return;
    }
    //Give the location manager to searcher.
    if(m_searcher!=nullptr)
    {
        m_searcher->setLocationManager(m_locationManager);
    }
}

void AMMainWindow::resizeEvent(QResizeEvent *event)
{
    //Do the original resize event, to resize the main window.
    QMainWindow::resizeEvent(event);
    //Resize the search box.
    m_searchBox->resize(width(), m_searchBoxHeight);
    m_mapView->setGeometry(0,
                           m_searchBox->height(),
                           width(),
                           height()-m_searchBox->height());
    //Check search widget position.
    if(m_searchSuggestion->y()>0)
    {
        QSize suggestionSize=QSize(width(), height()-m_searchBoxHeight+5);
        m_searchSuggestion->resize(suggestionSize);
        //Check if search suggestion animation is running.
        if(m_showSuggestion->state()==QAbstractAnimation::Running)
        {
            m_showSuggestion->setEndValue(QRect(QPoint(0, m_searchBoxHeight-5),
                                                suggestionSize));
        }
    }
}

void AMMainWindow::startSearch()
{
    //Hide the suggestions and buttons.
    hideSearchHelperWidgets();
    //Show the stop button.
    m_stopNavigate->showButton();
    //Ask searcher to search.
    qDebug()<<m_searchBoxText->text();
    //Ensure the loacation manager and searcher exist.
    if(m_locationManager==nullptr || m_searcher==nullptr)
    {
        return;
    }
}

void AMMainWindow::filterChanged(const QString &text)
{
    m_searchSuggestion->searchText(text);
}

void AMMainWindow::onActionSearch(const QModelIndex &current)
{
    //Check if the current is a vaild item.
    if(current.isValid())
    {
        //Set the search text to the current item.
        m_searchBoxText->setText(current.data(Qt::DisplayRole).toString());
        //Start to search the item.
        startSearch();
    }
    ;
}

void AMMainWindow::onActionCancelSearch()
{
    m_mapView->setFocus(Qt::MouseFocusReason);
    m_searchBoxText->clear();
    //Hide the search suggestions.
    onActionSearchFocusOut();
}

void AMMainWindow::onActionSearchFocusIn()
{
    //Check if the cancel button has been shown or not.
    //If the button is showed, ignore the show animation request.
    if(m_cancelSearch->width()>0)
    {
        return;
    }
    //Show cancel button.
    m_cancelSearch->showButton();
    //Show add button.
    m_addPoint->showButton();
    //Reset the search suggestion.
    m_searchSuggestion->scrollToTop();
    m_searchSuggestion->selectionModel()->clearSelection();
    //Show search suggestion.
    m_hideSuggestion->stop();
    m_showSuggestion->setStartValue(QRect(m_searchSuggestion->x(),
                                          m_searchSuggestion->y(),
                                          width(),
                                          m_searchSuggestion->height()));
    m_showSuggestion->setEndValue(QRect(0,
                                        m_searchBoxHeight-5,
                                        width(),
                                        height()-m_searchBoxHeight+5));
    m_showSuggestion->start();
}

void AMMainWindow::onActionSearchFocusOut()
{
    //Check if the focus is on the search suggestion.
    if(m_searchSuggestion->hasFocus())
    {
        return;
    }
    //Hide search suggestion and other widgets.
    hideSearchHelperWidgets();
}

inline void AMMainWindow::hideSearchHelperWidgets()
{
    //Hide search button
    m_cancelSearch->hideButton();
    //Hide add button.
    m_addPoint->hideButton();
    //Hide search suggestion.
    m_showSuggestion->stop();
    m_hideSuggestion->setStartValue(QRect(m_searchSuggestion->x(),
                                          m_searchSuggestion->y(),
                                          width(),
                                          m_searchSuggestion->height()));
    m_hideSuggestion->setEndValue(QRect(0,-10,width(),10));
    m_hideSuggestion->start();
}

AMSearcherBase *AMMainWindow::searcher()
{
    return m_searcher;
}

void AMMainWindow::setSearcher(AMSearcherBase *searcher)
{
    m_searcher = searcher;
    if(m_searcher==nullptr)
    {
        return;
    }
    //Check if the location manager has been set before.
    //Give the location manager to the search if it's possible.
    if(m_locationManager!=nullptr)
    {
        m_searcher->setLocationManager(m_locationManager);
    }
}
