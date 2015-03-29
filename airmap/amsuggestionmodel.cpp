#include "amsuggestionmodel.h"

AMSuggestionModel::AMSuggestionModel(QObject *parent) :
    QStandardItemModel(parent)
{
    //Add the category rows.
    QString categoryCaption[CategoriesCount];
    categoryCaption[RuKou]="入口";
    categoryCaption[ChuKou]="出口";
    categoryCaption[DengJiKou]="登机口";
    categoryCaption[Dianti]="电梯";
    categoryCaption[Futi]="扶梯";
    categoryCaption[ZhiJiGuiTai]="值机柜台";
    categoryCaption[AnJianKou]="安检口";
    categoryCaption[YinShuiChu]="饮水处";
    categoryCaption[WeiShengJian]="卫生间";
    categoryCaption[XunWenChu]="询问处";
    categoryCaption[ShangDian]="商店";
    categoryCaption[XingLiPan]="行李盘";

    for(int i=0; i<CategoriesCount; i++)
    {
        QStandardItem *categoryItem=new QStandardItem(categoryCaption[i]);
        categoryItem->setFlags(Qt::NoItemFlags);
        categoryItem->setSelectable(false);
        appendRow(categoryItem);
    }

    QStandardItem *currentCategory;
    currentCategory=item(RuKou, 0);
    for(int i=1; i<=3; i++)
    {
        QStandardItem *ruKouItem=new QStandardItem("入口 "+QString::number(i));
        ruKouItem->setIcon(QIcon("://resource/icons/DIn.png"));
        ruKouItem->setEditable(false);
        currentCategory->appendRow(ruKouItem);
    }

    currentCategory=item(ChuKou, 0);
    for(int i=1; i<=3; i++)
    {
        QStandardItem *chuKouItem=new QStandardItem("出口 "+QString::number(i));
        chuKouItem->setIcon(QIcon("://resource/icons/DOn.png"));
        chuKouItem->setEditable(false);
        currentCategory->appendRow(chuKouItem);
    }

    currentCategory=item(DengJiKou, 0);
    for(int i=1; i<=18; i++)
    {
        QStandardItem *dengJiKouItem=new QStandardItem("登机口 "+QString::number(i));
        dengJiKouItem->setIcon(QIcon("://resource/icons/EDn.png"));
        dengJiKouItem->setEditable(false);
        dengJiKouItem->setSelectable(true);
        currentCategory->appendRow(dengJiKouItem);
    }

    currentCategory=item(ZhiJiGuiTai, 0);
    for(int i=1; i<=6; i++)
    {
        QStandardItem *zhiJiGuiTaiItem=new QStandardItem("值机柜台 "+QString::number(i));
        zhiJiGuiTaiItem->setIcon(QIcon("://resource/icons/Cn.png"));
        zhiJiGuiTaiItem->setEditable(false);
        currentCategory->appendRow(zhiJiGuiTaiItem);
    }

    currentCategory=item(AnJianKou, 0);
    for(int i=1; i<=3; i++)
    {
        QStandardItem *anJianKouItem=new QStandardItem("安检口 "+QString::number(i));
        anJianKouItem->setIcon(QIcon("://resource/icons/SCn.png"));
        anJianKouItem->setEditable(false);
        currentCategory->appendRow(anJianKouItem);
    }

    currentCategory=item(WeiShengJian, 0);
    for(int i=1; i<=8; i++)
    {
        QStandardItem *weiShengJianItem=new QStandardItem("卫生间 "+QString::number(i));
        weiShengJianItem->setIcon(QIcon("://resource/icons/Wn.png"));
        weiShengJianItem->setEditable(false);
        currentCategory->appendRow(weiShengJianItem);
    }

    currentCategory=item(YinShuiChu, 0);
    for(int i=1; i<=10; i++)
    {
        QStandardItem *yinShuiChuItem=new QStandardItem("饮水处 "+QString::number(i));
        yinShuiChuItem->setIcon(QIcon("://resource/icons/WTn.png"));
        yinShuiChuItem->setEditable(false);
        currentCategory->appendRow(yinShuiChuItem);
    }

    currentCategory=item(XunWenChu, 0);
    for(int i=1; i<=2; i++)
    {
        QStandardItem *xunWenChuItem=new QStandardItem("询问处 "+QString::number(i));
        xunWenChuItem->setIcon(QIcon("://resource/icons/Qn.png"));
        xunWenChuItem->setEditable(false);
        currentCategory->appendRow(xunWenChuItem);
    }

    currentCategory=item(XingLiPan, 0);
    for(int i=1; i<=2; i++)
    {
        QStandardItem *xingLiPanItem=new QStandardItem("询问处 "+QString::number(i));
        xingLiPanItem->setIcon(QIcon("://resource/icons/Bn.png"));
        xingLiPanItem->setEditable(false);
        currentCategory->appendRow(xingLiPanItem);
    }
}
