#ifndef AMGLOBAL_H
#define AMGLOBAL_H

#include <QObject>

namespace AMStd
{
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
