#ifndef AMMAINWINDOW_H
#define AMMAINWINDOW_H

#include <QMainWindow>

class AMLineEdit;
class AMLabelButton;
class AMLocationManagerBase;
class AMSearcherBase;
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

private:
    AMLocationManagerBase *m_locationManager=nullptr;
    AMSearcherBase *m_searcher=nullptr;
    AMLineEdit *m_searchBoxText;
    AMLabelButton *m_addPoint, *m_cancelSearch, *m_stopNavigate;
    QWidget *m_searchBox;

    //Some consts.
    const int m_searchBoxHeight=50;
};

#endif // AMMAINWINDOW_H
