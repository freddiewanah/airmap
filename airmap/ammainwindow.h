#ifndef AMMAINWINDOW_H
#define AMMAINWINDOW_H

#include <QMainWindow>

class QGraphicsView;
class QGraphicsScene;
class QPropertyAnimation;
class AMLineEdit;
class AMLabelButton;
class AMLocationManagerBase;
class AMSearcherBase;
class AMSearchSuggetions;
class AMMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit AMMainWindow(QWidget *parent = 0);
    ~AMMainWindow();

    AMLocationManagerBase *locationManager();
    AMSearcherBase *searcher();

signals:

public slots:
    void setLocationManager(AMLocationManagerBase *locationManager);
    void setSearcher(AMSearcherBase *searcher);

protected:
    void resizeEvent(QResizeEvent *event);

protected:
    void startSearch();

private slots:
    void currentSuggestionChanged(const QModelIndex &current,
                                  const QModelIndex &previous);
    void onActionCancelSearch();
    void onActionSearchFocusIn();
    void onActionSearchFocusOut();

private:
    inline void hideSearchHelperWidgets();
    AMLocationManagerBase *m_locationManager=nullptr;
    AMSearcherBase *m_searcher=nullptr;
    AMLineEdit *m_searchBoxText;
    AMLabelButton *m_addPoint, *m_cancelSearch, *m_stopNavigate;
    AMSearchSuggetions *m_searchSuggestion;

    QPropertyAnimation *m_showSuggestion, *m_hideSuggestion;

    QGraphicsView *m_mapView;
    QGraphicsScene *m_mapScene;
    QWidget *m_searchBox;

    //Some consts.
    const int m_searchBoxHeight=50;
};

#endif // AMMAINWINDOW_H
