#ifndef AMSUGGESTIONMODEL_H
#define AMSUGGESTIONMODEL_H

#include <QStandardItemModel>

class AMSuggestionModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit AMSuggestionModel(QObject *parent = 0);

signals:

public slots:

private:
    enum Categories
    {
        RuKou,
        ChuKou,
        DengJiKou,
        Dianti,
        Futi,
        ZhiJiGuiTai,
        AnJianKou,
        YinShuiChu,
        WeiShengJian,
        XunWenChu,
        ShangDian,
        XingLiPan,
        CategoriesCount
    };
};

#endif // AMSUGGESTIONMODEL_H
