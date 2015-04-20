#ifndef AMMAPPAINTER_H
#define AMMAPPAINTER_H

#include <QList>
#include <QPixmap>
#include <QWidget>
#include <QRectF>
#include <QHash>
#include <QIcon>

#include "amglobal.h"

namespace MapPainter
{
struct MapItem
{
    QRectF geometry;
    QRectF zoomGeometry;
    int type;
    int id;
};
struct Map
{
    QPixmap image;
    QString mapName;
    QList<MapItem> items;
};
}

using namespace MapPainter;
using namespace AMStd;

class AMMapPainter : public QWidget
{
    Q_OBJECT
public:
    explicit AMMapPainter(QWidget *parent = 0);
    void addMap(const QPixmap &pixmap,
                const QString &mapInfoFilePath);
    qreal zoom() const;

signals:
    void requireSearchPath(int type, int id, int floor);

public slots:
    void setZoom(const qreal &zoom);
    void setCurrentIndex(int index);
    void onActionPressed(QPoint position);

protected:
    void paintEvent(QPaintEvent *event);

private:
    inline void loadMapInfo(Map &map, const QString &filePath);
    inline void updateImage();
    QList<Map> m_mapList;
    QList<QIcon> m_iconList;
    QPixmap m_currentImage;
    int m_floorIndex=-1;
    QString m_mapItemTypeName[MapItemTypeCount];
    QHash<QString, int> m_typeTextToIndex;

    qreal m_zoom=1.0;
};

#endif // AMMAPPAINTER_H
