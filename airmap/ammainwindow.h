#ifndef AMMAINWINDOW_H
#define AMMAINWINDOW_H

#include <QModelIndex>

#include <QMainWindow>

class QPropertyAnimation;
class AMTouchSrollArea;
class AMHotPoint;
class AMLineEdit;
class AMMapPainter;
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
    void startSearch(const int &type, const int &index, const int &floor);

private slots:
    void checkSearchText();
    void searchPathTo(const QJsonObject &details);
    void filterChanged(const QString &text);
    void onActionSuggetionRequireSearch(const QModelIndex &current);
    void onActionMapRequireSearch(const int &floor,
                                  const int &type,
                                  const int &index);
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

    AMTouchSrollArea *m_mapView;
    AMMapPainter *m_mapPainter;
    QWidget *m_searchBox;
    AMHotPoint *m_hotPoint;

    //Some consts.
    const int m_searchBoxHeight=50;
};

#endif // AMMAINWINDOW_H
