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
        m_categoryItem[i]=new QStandardItem(categoryCaption[i]);
        m_categoryItem[i]->setFlags(Qt::NoItemFlags);
        m_categoryItem[i]->setEnabled(false);
        m_categoryItem[i]->setEditable(false);
        m_categoryItem[i]->setSelectable(false);
        appendRow(m_categoryItem[i]);
    }

    QStandardItem *currentCategory, *categoryItem;
    currentCategory=m_categoryItem[RuKou];
    for(int i=3; i>=1; i--)
    {
        categoryItem=new QStandardItem("入口 "+QString::number(i));
        categoryItem->setIcon(QIcon("://resource/icons/DIn.png"));
        categoryItem->setEditable(false);
        categoryItem->setData("D" + QString::number(i));
        insertRow(currentCategory->row()+1, categoryItem);
    }

    currentCategory=m_categoryItem[ShangDian];
    for(int i=32; i>=1; i--)
    {
        categoryItem=new QStandardItem("F2 出发大厅 商店 "+QString::number(i));
        categoryItem->setIcon(QIcon("://resource/icons/Sn.png"));
        categoryItem->setEditable(false);
        categoryItem->setData("F2S" + QString::number(i));
        insertRow(currentCategory->row()+1, categoryItem);
    }
    for(int i=42; i>=1; i--)
    {
        categoryItem=new QStandardItem("F1 到达大厅 商店 "+QString::number(i));
        categoryItem->setIcon(QIcon("://resource/icons/Sn.png"));
        categoryItem->setEditable(false);
        categoryItem->setData("F1S" + QString::number(i));
        insertRow(currentCategory->row()+1, categoryItem);
    }

    currentCategory=m_categoryItem[ChuKou];
    for(int i=3; i>=1; i--)
    {
        categoryItem=new QStandardItem("出口 "+QString::number(i));
        categoryItem->setIcon(QIcon("://resource/icons/DOn.png"));
        categoryItem->setEditable(false);
        categoryItem->setData("D" + QString::number(i));
        insertRow(currentCategory->row()+1, categoryItem);
    }

    currentCategory=m_categoryItem[DengJiKou];
    for(int i=18; i>=1; i--)
    {
        categoryItem=new QStandardItem("登机口 "+QString::number(i));
        categoryItem->setIcon(QIcon("://resource/icons/EDn.png"));
        categoryItem->setEditable(false);
        categoryItem->setSelectable(true);
        categoryItem->setData("E" + QString::number(i));
        insertRow(currentCategory->row()+1, categoryItem);
    }

    currentCategory=m_categoryItem[Dianti];
    for(int i=8; i>=1; i--)
    {
        categoryItem=new QStandardItem("电梯 "+QString::number(i));
        categoryItem->setIcon(QIcon("://resource/icons/ELn.png"));
        categoryItem->setEditable(false);
        categoryItem->setSelectable(true);
        categoryItem->setData("EL" + QString::number(i));
        insertRow(currentCategory->row()+1, categoryItem);
    }

    currentCategory=m_categoryItem[Futi];
    for(int i=8; i>=1; i--)
    {
        categoryItem=new QStandardItem("扶梯 "+QString::number(i));
        categoryItem->setIcon(QIcon("://resource/icons/ESn.png"));
        categoryItem->setEditable(false);
        categoryItem->setSelectable(true);
        categoryItem->setData("ES" + QString::number(i));
        insertRow(currentCategory->row()+1, categoryItem);
    }

    currentCategory=m_categoryItem[ZhiJiGuiTai];
    for(int i=6; i>=1; i--)
    {
        categoryItem=new QStandardItem("值机柜台 "+QString::number(i));
        categoryItem->setIcon(QIcon("://resource/icons/Cn.png"));
        categoryItem->setEditable(false);
        categoryItem->setData("C" + QString::number(i));
        insertRow(currentCategory->row()+1, categoryItem);
    }

    currentCategory=m_categoryItem[AnJianKou];
    for(int i=3; i>=1; i--)
    {
        categoryItem=new QStandardItem("安检口 "+QString::number(i));
        categoryItem->setIcon(QIcon("://resource/icons/SCn.png"));
        categoryItem->setEditable(false);
        categoryItem->setData("SC" + QString::number(i));
        insertRow(currentCategory->row()+1, categoryItem);
    }

    currentCategory=m_categoryItem[WeiShengJian];
    for(int i=8; i>=1; i--)
    {
        categoryItem=new QStandardItem("F2 出发大厅 卫生间 "+QString::number(i));
        categoryItem->setIcon(QIcon("://resource/icons/Wn.png"));
        categoryItem->setEditable(false);
        categoryItem->setData("F2W" + QString::number(i));
        insertRow(currentCategory->row()+1, categoryItem);
    }
    for(int i=8; i>=1; i--)
    {
        categoryItem=new QStandardItem("F1 到达大厅 卫生间 "+QString::number(i));
        categoryItem->setIcon(QIcon("://resource/icons/Wn.png"));
        categoryItem->setEditable(false);
        categoryItem->setData("F1W" + QString::number(i));
        insertRow(currentCategory->row()+1, categoryItem);
    }

    currentCategory=m_categoryItem[YinShuiChu];
    for(int i=10; i>=1; i--)
    {
        categoryItem=new QStandardItem("F2 出发大厅 饮水处 "+QString::number(i));
        categoryItem->setIcon(QIcon("://resource/icons/WTn.png"));
        categoryItem->setEditable(false);
        categoryItem->setData("F2WT" + QString::number(i));
        insertRow(currentCategory->row()+1, categoryItem);
    }
    for(int i=10; i>=1; i--)
    {
        categoryItem=new QStandardItem("F1 到达大厅 饮水处 "+QString::number(i));
        categoryItem->setIcon(QIcon("://resource/icons/WTn.png"));
        categoryItem->setEditable(false);
        categoryItem->setData("F1WT" + QString::number(i));
        insertRow(currentCategory->row()+1, categoryItem);
    }

    currentCategory=m_categoryItem[XunWenChu];
    for(int i=2; i>=1; i--)
    {
        categoryItem=new QStandardItem("询问处 "+QString::number(i));
        categoryItem->setIcon(QIcon("://resource/icons/Qn.png"));
        categoryItem->setEditable(false);
        categoryItem->setData("Q" + QString::number(i));
        insertRow(currentCategory->row()+1, categoryItem);
    }

    currentCategory=m_categoryItem[XingLiPan];
    for(int i=6; i>=1; i--)
    {
        categoryItem=new QStandardItem("行李盘 "+QString::number(i));
        categoryItem->setIcon(QIcon("://resource/icons/Bn.png"));
        categoryItem->setEditable(false);
        categoryItem->setData("B" + QString::number(i));
        insertRow(currentCategory->row()+1, categoryItem);
    }
}
