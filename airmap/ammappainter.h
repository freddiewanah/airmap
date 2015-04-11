#ifndef AMMAPPAINTER_H
#define AMMAPPAINTER_H

#include <QList>
#include <QPixmap>
#include <QWidget>
#include <QRectF>
#include <QHash>

#include "amglobal.h"

namespace MapPainter
{
struct MapItem
{
    QRectF geometry;
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

signals:
    void requireSearchPath(int type, int id, int floor);

public slots:
    void setCurrentIndex(int index);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    inline void loadMapInfo(Map &map, const QString &filePath);
    QList<Map> m_mapList;
    QPixmap m_currentImage;
    int m_floorIndex=-1;
    QString m_mapItemTypeName[MapItemTypeCount];
    QHash<QString, int> m_typeTextToIndex;
};

#endif // AMMAPPAINTER_H
