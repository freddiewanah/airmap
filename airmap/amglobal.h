#ifndef AMGLOBAL_H
#define AMGLOBAL_H

#include <QList>
#include <QRectF>
#include <QPixmap>

#include <QObject>

namespace AMStd
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
    QString caption;
    QPixmap image;
    QString mapName;
    QList<MapItem> items;
};
enum MapItemType
{
    ChuRuKou,
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
enum SearchSuggetionRole
{
    ItemTypeRole = Qt::UserRole,
    ItemIndexRole,
    ItemFloorRole,
    ItemSearchSuggestionRole
};
}

class AMGlobal : public QObject
{
    Q_OBJECT
public:
    static AMGlobal *instance();

signals:

public slots:

private:
    static AMGlobal *m_instance;
    explicit AMGlobal(QObject *parent = 0);
};

#endif // AMGLOBAL_H
