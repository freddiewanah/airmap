#include <QJsonDocument>
#include <QJsonObject>
#include <QMouseEvent>
#include <QJsonArray>
#include <QFile>
#include <QPainter>

#include "ammappainter.h"

#include <QDebug>

AMMapPainter::AMMapPainter(QWidget *parent) :
    QWidget(parent)
{
    //Initial the text to index.
    m_typeTextToIndex.insert("ChuRuKou", ChuRuKou);
    m_typeTextToIndex.insert("DengJiKou", DengJiKou);
    m_typeTextToIndex.insert("DianTi", DianTi);
    m_typeTextToIndex.insert("FuTi", FuTi);
    m_typeTextToIndex.insert("ZhiJiGuiTai", ZhiJiGuiTai);
    m_typeTextToIndex.insert("AnJianKou", AnJianKou);
    m_typeTextToIndex.insert("YinShuiChu", YinShuiChu);
    m_typeTextToIndex.insert("WeiShengJian", WeiShengJian);
    m_typeTextToIndex.insert("XunWenChu", XunWenChu);
    m_typeTextToIndex.insert("ShangDian", ShangDian);
    m_typeTextToIndex.insert("XingLiPan", XingLiPan);
    //Initial the map item type name.
    m_mapItemTypeName[ShangDian]="商店";
    m_mapItemTypeName[WeiShengJian]="卫生间";
    m_mapItemTypeName[ChuRuKou]="出入口";
    m_mapItemTypeName[DengJiKou]="登机口";
    m_mapItemTypeName[DianTi]="电梯";
    m_mapItemTypeName[FuTi]="扶梯";
    m_mapItemTypeName[ZhiJiGuiTai]="值机柜台";
    m_mapItemTypeName[AnJianKou]="安检口";
    m_mapItemTypeName[YinShuiChu]="饮水处";
    m_mapItemTypeName[XunWenChu]="询问处";
    m_mapItemTypeName[XingLiPan]="行李盘";
}

void AMMapPainter::addMap(const QPixmap &pixmap, const QString &mapInfoFilePath)
{
    //Generate the map item.
    Map item;
    item.image=pixmap;
    //Load map information.
    loadMapInfo(item, mapInfoFilePath);
    //Add to map list.
    m_mapList.append(item);
    //Check if the current index is -1, means there's no available map image
    //here.
    if(m_floorIndex==-1)
    {
        setCurrentIndex(0);
    }
}

void AMMapPainter::setCurrentIndex(int index)
{
    if(index>-1 && index<m_mapList.size())
    {
        //Save the index.
        m_floorIndex=index;
        //Set the current pixmap.
        m_currentImage=m_mapList.at(m_floorIndex).image;
        //Resize the widget.
        resize(m_currentImage.size());
        //Update the painter to update the image.
        update();
    }
}

void AMMapPainter::paintEvent(QPaintEvent *event)
{
    //Ignore the event.
    Q_UNUSED(event)
    //Check is the current image null.
    if(m_currentImage.isNull())
    {
        return;
    }
    QPainter painter(this);
    //Set rendering hints.
    painter.setRenderHints(QPainter::Antialiasing |
                           QPainter::TextAntialiasing |
                           QPainter::SmoothPixmapTransform, true);
    //Paint the pixmap.
    painter.drawPixmap(0,0,m_currentImage.width(),m_currentImage.height(),
                       m_currentImage);

    //Debug
    if(m_floorIndex!=-1)
    {
        QList<MapItem> itemList=m_mapList.at(m_floorIndex).items;
        for(QList<MapItem>::iterator i=itemList.begin();
            i!=itemList.end();
            ++i)
        {
            painter.drawRect((*i).geometry);
        }
    }
}

void AMMapPainter::mousePressEvent(QMouseEvent *event)
{
    //Check if current map is available.
    if(m_floorIndex!=-1)
    {
        QList<MapItem> itemList=m_mapList.at(m_floorIndex).items;
        for(QList<MapItem>::iterator i=itemList.begin();
            i!=itemList.end();
            ++i)
        {
            if((*i).geometry.contains(event->pos()))
            {
                emit requireSearchPath((*i).type, (*i).id, m_floorIndex);
                break;
            }
        }
    }
    //Do original event.
    QWidget::mouseReleaseEvent(event);
}

void AMMapPainter::loadMapInfo(Map &map, const QString &filePath)
{
    //Load and open the file.
    QFile mapFile(filePath);
    if(mapFile.open(QIODevice::ReadOnly))
    {
        //Load the information.
        QJsonObject rootObj=QJsonDocument::fromJson(mapFile.readAll()).object();
        mapFile.close();
        if(rootObj.isEmpty())
        {
            return;
        }
        map.mapName=rootObj.value("MapName").toString();
        qreal xOffset=rootObj.value("X_offset").toDouble(),
              yOffset=rootObj.value("Y_offset").toDouble();
        QJsonArray mapItems=rootObj.value("MapItems").toArray();
        for(QJsonArray::iterator currentItem=mapItems.begin();
            currentItem!=mapItems.end();
            ++currentItem)
        {
            //Get the map item information array, translate it to the item.
            QJsonArray mapItemArray=(*currentItem).toArray();
            MapItem mapItem;
            mapItem.geometry=QRectF(mapItemArray.at(0).toDouble()+xOffset,
                                    mapItemArray.at(1).toDouble()+yOffset,
                                    mapItemArray.at(2).toDouble(),
                                    mapItemArray.at(3).toDouble());
            mapItem.type=m_typeTextToIndex.value(mapItemArray.at(4).toString());
            mapItem.id=mapItemArray.at(5).toInt();
            //Insert the item to map.
            map.items.append(mapItem);
        }
    }
}
