#include "amsuggestionmodel.h"

AMSuggestionModel::AMSuggestionModel(QObject *parent) :
    QStandardItemModel(parent)
{
    //Add the category rows.
    QString categoryCaption[MapItemTypeCount];
    categoryCaption[ChuRuKou]="出入口";
    categoryCaption[DengJiKou]="登机口";
    categoryCaption[DianTi]="电梯";
    categoryCaption[FuTi]="扶梯";
    categoryCaption[ZhiJiGuiTai]="值机柜台";
    categoryCaption[AnJianKou]="安检口";
    categoryCaption[YinShuiChu]="饮水处";
    categoryCaption[WeiShengJian]="卫生间";
    categoryCaption[XunWenChu]="询问处";
    categoryCaption[ShangDian]="商店";
    categoryCaption[XingLiPan]="行李盘";

    for(int i=0; i<MapItemTypeCount; i++)
    {
        m_categoryItem[i]=new QStandardItem(categoryCaption[i]);
        m_categoryItem[i]->setFlags(Qt::NoItemFlags);
        m_categoryItem[i]->setEnabled(false);
        m_categoryItem[i]->setEditable(false);
        m_categoryItem[i]->setSelectable(false);
        appendRow(m_categoryItem[i]);
    }

    QStandardItem *currentCategory, *categoryItem;
    currentCategory=m_categoryItem[ChuRuKou];
    for(int i=3; i>=1; i--)
    {
        categoryItem=new QStandardItem("B1 出入口 "+QString::number(i));
        categoryItem->setIcon(QIcon("://resource/icons/DIn.png"));
        categoryItem->setEditable(false);
        categoryItem->setData("D" + QString::number(i), ItemSearchSuggestionRole);
        categoryItem->setData(ChuRuKou, ItemTypeRole);
        categoryItem->setData(i, ItemIndexRole);
        categoryItem->setData(0, ItemFloorRole);
        insertRow(currentCategory->row()+1, categoryItem);
    }
    for(int i=3; i>=1; i--)
    {
        categoryItem=new QStandardItem("F1 出入口 "+QString::number(i));
        categoryItem->setIcon(QIcon("://resource/icons/DIn.png"));
        categoryItem->setEditable(false);
        categoryItem->setData("D" + QString::number(i), ItemSearchSuggestionRole);
        categoryItem->setData(ChuRuKou, ItemTypeRole);
        categoryItem->setData(i, ItemIndexRole);
        categoryItem->setData(1, ItemFloorRole);
        insertRow(currentCategory->row()+1, categoryItem);
    }
    for(int i=3; i>=1; i--)
    {
        categoryItem=new QStandardItem("F2 出入口 "+QString::number(i));
        categoryItem->setIcon(QIcon("://resource/icons/DIn.png"));
        categoryItem->setEditable(false);
        categoryItem->setData("D" + QString::number(i), ItemSearchSuggestionRole);
        categoryItem->setData(ChuRuKou, ItemTypeRole);
        categoryItem->setData(i, ItemIndexRole);
        categoryItem->setData(2, ItemFloorRole);
        insertRow(currentCategory->row()+1, categoryItem);
    }

    currentCategory=m_categoryItem[ShangDian];
    for(int i=32; i>=1; i--)
    {
        categoryItem=new QStandardItem("F2 出发大厅 商店 "+QString::number(i));
        categoryItem->setIcon(QIcon("://resource/icons/Sn.png"));
        categoryItem->setEditable(false);
        categoryItem->setData("f2F2S" + QString::number(i), ItemSearchSuggestionRole);
        categoryItem->setData(ShangDian, ItemTypeRole);
        categoryItem->setData(i, ItemIndexRole);
        categoryItem->setData(2, ItemFloorRole);
        insertRow(currentCategory->row()+1, categoryItem);
    }
    for(int i=42; i>=1; i--)
    {
        categoryItem=new QStandardItem("F1 到达大厅 商店 "+QString::number(i));
        categoryItem->setIcon(QIcon("://resource/icons/Sn.png"));
        categoryItem->setEditable(false);
        categoryItem->setData("f1F1S" + QString::number(i), ItemSearchSuggestionRole);
        categoryItem->setData(ShangDian, ItemTypeRole);
        categoryItem->setData(i, ItemIndexRole);
        categoryItem->setData(1, ItemFloorRole);
        insertRow(currentCategory->row()+1, categoryItem);
    }

    currentCategory=m_categoryItem[DengJiKou];
    for(int i=18; i>=1; i--)
    {
        categoryItem=new QStandardItem("登机口 "+QString::number(i));
        categoryItem->setIcon(QIcon("://resource/icons/EDn.png"));
        categoryItem->setEditable(false);
        categoryItem->setSelectable(true);
        categoryItem->setData("E" + QString::number(i), ItemSearchSuggestionRole);
        categoryItem->setData(DengJiKou, ItemTypeRole);
        categoryItem->setData(i, ItemIndexRole);
        categoryItem->setData(2, ItemFloorRole);
        insertRow(currentCategory->row()+1, categoryItem);
    }

    currentCategory=m_categoryItem[DianTi];
    for(int i=8; i>=1; i--)
    {
        categoryItem=new QStandardItem("电梯 "+QString::number(i));
        categoryItem->setIcon(QIcon("://resource/icons/ELn.png"));
        categoryItem->setEditable(false);
        categoryItem->setSelectable(true);
        categoryItem->setData("EL" + QString::number(i), ItemSearchSuggestionRole);
        categoryItem->setData(DianTi, ItemTypeRole);
        categoryItem->setData(i, ItemIndexRole);
        categoryItem->setData(1, ItemFloorRole);
        insertRow(currentCategory->row()+1, categoryItem);
    }

    currentCategory=m_categoryItem[FuTi];
    for(int i=8; i>=1; i--)
    {
        categoryItem=new QStandardItem("扶梯 "+QString::number(i));
        categoryItem->setIcon(QIcon("://resource/icons/ESn.png"));
        categoryItem->setEditable(false);
        categoryItem->setSelectable(true);
        categoryItem->setData("ES" + QString::number(i), ItemSearchSuggestionRole);
        categoryItem->setData(FuTi, ItemTypeRole);
        categoryItem->setData(i, ItemIndexRole);
        categoryItem->setData(1, ItemFloorRole);
        insertRow(currentCategory->row()+1, categoryItem);
    }

    currentCategory=m_categoryItem[ZhiJiGuiTai];
    for(int i=6; i>=1; i--)
    {
        categoryItem=new QStandardItem("值机柜台 "+QString::number(i));
        categoryItem->setIcon(QIcon("://resource/icons/Cn.png"));
        categoryItem->setEditable(false);
        categoryItem->setData("C" + QString::number(i), ItemSearchSuggestionRole);
        categoryItem->setData(ZhiJiGuiTai, ItemTypeRole);
        categoryItem->setData(i, ItemIndexRole);
        categoryItem->setData(2, ItemFloorRole);
        insertRow(currentCategory->row()+1, categoryItem);
    }

    currentCategory=m_categoryItem[AnJianKou];
    for(int i=3; i>=1; i--)
    {
        categoryItem=new QStandardItem("安检口 "+QString::number(i));
        categoryItem->setIcon(QIcon("://resource/icons/SCn.png"));
        categoryItem->setEditable(false);
        categoryItem->setData("SC" + QString::number(i), ItemSearchSuggestionRole);
        categoryItem->setData(AnJianKou, ItemTypeRole);
        categoryItem->setData(i, ItemIndexRole);
        categoryItem->setData(2, ItemFloorRole);
        insertRow(currentCategory->row()+1, categoryItem);
    }

    currentCategory=m_categoryItem[WeiShengJian];
    for(int i=8; i>=1; i--)
    {
        categoryItem=new QStandardItem("F2 出发大厅 卫生间 "+QString::number(i));
        categoryItem->setIcon(QIcon("://resource/icons/Wn.png"));
        categoryItem->setEditable(false);
        categoryItem->setData("f2F2W" + QString::number(i), ItemSearchSuggestionRole);
        categoryItem->setData(WeiShengJian, ItemTypeRole);
        categoryItem->setData(i, ItemIndexRole);
        categoryItem->setData(2, ItemFloorRole);
        insertRow(currentCategory->row()+1, categoryItem);
    }
    for(int i=8; i>=1; i--)
    {
        categoryItem=new QStandardItem("F1 到达大厅 卫生间 "+QString::number(i));
        categoryItem->setIcon(QIcon("://resource/icons/Wn.png"));
        categoryItem->setEditable(false);
        categoryItem->setData("f1F1W" + QString::number(i), ItemSearchSuggestionRole);
        categoryItem->setData(WeiShengJian, ItemTypeRole);
        categoryItem->setData(i, ItemIndexRole);
        categoryItem->setData(1, ItemFloorRole);
        insertRow(currentCategory->row()+1, categoryItem);
    }

    currentCategory=m_categoryItem[YinShuiChu];
    for(int i=10; i>=1; i--)
    {
        categoryItem=new QStandardItem("F2 出发大厅 饮水处 "+QString::number(i));
        categoryItem->setIcon(QIcon("://resource/icons/WTn.png"));
        categoryItem->setEditable(false);
        categoryItem->setData("f2F2WT" + QString::number(i), ItemSearchSuggestionRole);
        categoryItem->setData(YinShuiChu, ItemTypeRole);
        categoryItem->setData(i, ItemIndexRole);
        categoryItem->setData(2, ItemFloorRole);
        insertRow(currentCategory->row()+1, categoryItem);
    }
    for(int i=10; i>=1; i--)
    {
        categoryItem=new QStandardItem("F1 到达大厅 饮水处 "+QString::number(i));
        categoryItem->setIcon(QIcon("://resource/icons/WTn.png"));
        categoryItem->setEditable(false);
        categoryItem->setData("f1F1WT" + QString::number(i), ItemSearchSuggestionRole);
        categoryItem->setData(YinShuiChu, ItemTypeRole);
        categoryItem->setData(i, ItemIndexRole);
        categoryItem->setData(1, ItemFloorRole);
        insertRow(currentCategory->row()+1, categoryItem);
    }

    currentCategory=m_categoryItem[XunWenChu];
    for(int i=2; i>=1; i--)
    {
        categoryItem=new QStandardItem("询问处 "+QString::number(i));
        categoryItem->setIcon(QIcon("://resource/icons/Qn.png"));
        categoryItem->setEditable(false);
        categoryItem->setData("Q" + QString::number(i), ItemSearchSuggestionRole);
        categoryItem->setData(XunWenChu, ItemTypeRole);
        categoryItem->setData(i, ItemIndexRole);
        categoryItem->setData(2, ItemFloorRole);
        insertRow(currentCategory->row()+1, categoryItem);
    }

    currentCategory=m_categoryItem[XingLiPan];
    for(int i=6; i>=1; i--)
    {
        categoryItem=new QStandardItem("行李盘 "+QString::number(i));
        categoryItem->setIcon(QIcon("://resource/icons/Bn.png"));
        categoryItem->setEditable(false);
        categoryItem->setData("B" + QString::number(i), ItemSearchSuggestionRole);
        categoryItem->setData(XingLiPan, ItemTypeRole);
        categoryItem->setData(i, ItemIndexRole);
        categoryItem->setData(1, ItemFloorRole);
        insertRow(currentCategory->row()+1, categoryItem);
    }
}

QModelIndex AMSuggestionModel::findPlace(const QString &keyword)
{
    QModelIndexList matchedIndexes=match(index(0,0),
                                         Qt::DisplayRole,
                                         keyword,
                                         -1,
                                         Qt::MatchFixedString);
    if(!matchedIndexes.isEmpty())
    {
        return matchedIndexes.first();
    }
    matchedIndexes=match(index(0,0),
                         Qt::DisplayRole,
                         keyword,
                         1,
                         Qt::MatchContains);
    return matchedIndexes.isEmpty()?QModelIndex():matchedIndexes.first();
}
