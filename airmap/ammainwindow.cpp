#include <QBoxLayout>
#include <QLineEdit>
#include <QResizeEvent>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPropertyAnimation>

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
    //Initial the search bar.
    m_searchBox=new QWidget(this);
    m_searchBox->setFixedHeight(45);
    m_searchBox->setAutoFillBackground(true);
    QPalette pal=m_searchBox->palette();
    pal.setColor(QPalette::Window, QColor(0,0,0,127));
    m_searchBox->setPalette(pal);
    //Initial the search bar layout.
    QBoxLayout *searchBoxLayout=new QBoxLayout(QBoxLayout::LeftToRight,
                                               m_searchBox);
    searchBoxLayout->setContentsMargins(5,0,5,0);
    searchBoxLayout->setSpacing(0);
    m_searchBox->setLayout(searchBoxLayout);
    m_searchBoxText=new AMLineEdit(this);
    m_searchBoxText->setPlaceHolderLabelText("搜索或输入地点");
    m_searchBoxText->setFixedHeight(30);
    connect(m_searchBoxText, &AMLineEdit::returnPressed,
            this, &AMMainWindow::startSearch);
    m_searchBoxText->setFrame(false);
    pal=m_searchBoxText->palette();
    pal.setColor(QPalette::Base, QColor(255,255,255,40));
    pal.setColor(QPalette::Text, QColor(255,255,255,240));
    pal.setColor(QPalette::Highlight, QColor(255,255,255,70));
    pal.setColor(QPalette::HighlightedText, QColor(255,255,255));
    m_searchBoxText->setPalette(pal);
    searchBoxLayout->addWidget(m_searchBoxText);
    m_addPoint=new AMLabelButton(this);
    m_addPoint->setText("+");
    m_addPoint->hideButton();
    searchBoxLayout->addWidget(m_addPoint);
    m_cancelSearch=new AMLabelButton(this);
    m_cancelSearch->setText(tr("Cancel"));
    m_cancelSearch->hideButton();
    connect(m_searchBoxText, &AMLineEdit::focusIn,
            this, &AMMainWindow::onActionSearchFocusIn);
    connect(m_searchBoxText, &AMLineEdit::focusOut,
            this, &AMMainWindow::onActionSearchFocusOut);
    connect(m_cancelSearch, &AMLabelButton::clicked,
            this, &AMMainWindow::onActionCancelSearch);
    searchBoxLayout->addWidget(m_cancelSearch);
    m_stopNavigate=new AMLabelButton(this);
    m_stopNavigate->setText(tr("End"));
    m_stopNavigate->hideButton();
    searchBoxLayout->addWidget(m_stopNavigate);

    //Initial the search suggestion widget.
    m_searchSuggestion=new AMSearchSuggetions(this);
    m_searchSuggestion->setGeometry(0,-10,0,10);
    m_showSuggestion=new QPropertyAnimation(m_searchSuggestion,
                                            "geometry",
                                            this);
    m_showSuggestion->setEasingCurve(QEasingCurve::OutCubic);
    m_hideSuggestion=new QPropertyAnimation(m_searchSuggestion,
                                            "geometry",
                                            this);
    m_hideSuggestion->setEasingCurve(QEasingCurve::OutCubic);
    m_hideSuggestion->setEndValue(QRect(0,-10,width(),10));

    //Initial the graphics scene for the map painting.
    m_mapScene=new QGraphicsScene(this);
    m_mapView=new QGraphicsView(m_mapScene, this);
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
        QSize suggestionSize=QSize(width(), height()-m_searchBoxHeight);
        m_searchSuggestion->resize(suggestionSize);
        //Check if search suggestion animation is running.
        if(m_showSuggestion->state()==QAbstractAnimation::Running)
        {
            m_showSuggestion->setEndValue(QRect(QPoint(0, m_searchBoxHeight),
                                                suggestionSize));
        }
    }
}

void AMMainWindow::startSearch()
{
    //Ensure the loacation manager and searcher exist.
    if(m_locationManager==nullptr || m_searcher==nullptr)
    {
        return;
    }
    //Ask searcher to search.
    qDebug()<<m_searchBoxText->text();
}

void AMMainWindow::onActionCancelSearch()
{
    m_searchBoxText->clear();
    m_mapView->setFocus(Qt::MouseFocusReason);
}

void AMMainWindow::onActionSearchFocusIn()
{
    //Show cancel button.
    m_cancelSearch->showButton();
    //Show add button.
    m_addPoint->showButton();
    //Show search suggestion.
    m_hideSuggestion->stop();
    m_showSuggestion->setStartValue(m_searchSuggestion->geometry());
    m_showSuggestion->setEndValue(QRect(0,
                                        m_searchBoxHeight,
                                        width(),
                                        height()-m_searchBoxHeight));
    m_showSuggestion->start();
}

void AMMainWindow::onActionSearchFocusOut()
{
    //Hide search button
    m_cancelSearch->hideButton();
    //Hide add button.
    m_addPoint->hideButton();
    //Hide search suggestion.
    m_showSuggestion->stop();
    m_hideSuggestion->setStartValue(m_searchSuggestion->geometry());
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
