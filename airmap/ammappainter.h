#ifndef AMMAPPAINTER_H
#define AMMAPPAINTER_H

#include <QPixmap>
#include <QWidget>
#include <QRectF>
#include <QHash>
#include <QIcon>

#include "amglobal.h"

using namespace AMStd;

class QLabel;
class QTimeLine;
class AMMapItemDetail;
class AMSearcherBase;
class AMLocationManagerBase;
class AMMapPainter : public QWidget
{
    Q_OBJECT
public:
    explicit AMMapPainter(QWidget *parent = 0);
    void addMap(const QPixmap &pixmap,
                const QString &mapInfoFilePath,
                const QString &mapCaption);
    Map map(const int &index) const;
    qreal zoom() const;

    AMSearcherBase *searcher() const;
    void setSearcher(AMSearcherBase *searcher);

    bool tracking() const;

    AMLocationManagerBase *locationManager() const;
    void setLocationManager(AMLocationManagerBase *locationManager);

    //Debug
    QString itemName(int type);

signals:
    void requireSearchPath(int type, int id, int floor);

public slots:
    void setTracking(bool tracking);

    void hideItemDetail();
    void showItemDetail(const MapItem &item);
    void setZoom(const qreal &zoom);
    void setCurrentIndex(int index);
    void onActionPressed(QPoint position);
    void drawRoute();
    void clearRoute();

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void setTrackingData(double a, double b, double c);

private:
    inline void loadMapInfo(Map &map, const QString &filePath);
    inline void updateImage();
    QList<Map> m_mapList;
    QList<QIcon> m_iconList;
    QPixmap m_currentImage;
    int m_floorIndex=-1, m_borderWidth=2;
    qreal m_trackPointSize=13.0;
    QString m_mapItemTypeName[MapItemTypeCount];
    QHash<QString, int> m_typeTextToIndex;
    double m_currentX, m_currentY, m_currentFloor;

    bool m_drawRoute=false, m_tracking=false;
    AMSearcherBase *m_searcher=nullptr;
    AMLocationManagerBase *m_locationManager=nullptr;
    qreal m_zoom=1.0;

    AMMapItemDetail *m_itemDetail;
    QLabel *m_indicator;
    QPixmap m_indicatorLeftIcon, m_indicatorRightIcon;

    QTimeLine *m_breathTimeLine;
    QTimer *m_delay;
};

#endif // AMMAPPAINTER_H
