#ifndef AMMAPPAINTER_H
#define AMMAPPAINTER_H

#include <QList>
#include <QPixmap>
#include <QWidget>
#include <QRectF>
#include <QHash>

namespace MapPainter
{
enum MapItemType
{
    ChuRuKou,
    //ChuKou,
    DengJiKou,
    DianTi,
    FuTi,
    ZhiJiGuiTai,
    AnJianKou,
    YinShuiChu,
    WeiShengJian,
    XunWenChu,
    ShangDian,
    XingLiPan,
    MapItemTypeCount
};
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

class AMMapPainter : public QWidget
{
    Q_OBJECT
public:
    explicit AMMapPainter(QWidget *parent = 0);
    void addMap(const QPixmap &pixmap,
                const QString &mapInfoFilePath);

signals:

public slots:
    void setCurrentIndex(int index);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    inline void loadMapInfo(Map &map, const QString &filePath);
    QList<Map> m_mapList;
    QPixmap m_currentImage;
    int m_index=-1;
    QString m_mapItemTypeName[MapItemTypeCount];
    QHash<QString, int> m_typeTextToIndex;
};

#endif // AMMAPPAINTER_H
