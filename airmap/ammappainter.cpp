#include <QJsonDocument>
#include <QGraphicsDropShadowEffect>
#include <QJsonObject>
#include <QMouseEvent>
#include <QJsonArray>
#include <QLabel>
#include <QFile>
#include <QPainter>
#include <QTimeLine>
#include <QTimer>

#include "amsearcherbase.h"
#include "ammapitemdetail.h"
#include "amlocationmanagerbase.h"

#include "ammappainter.h"

#include <QDebug>

AMMapPainter::AMMapPainter(QWidget *parent) :
    QWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
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
    //Initial the map item icon.
    m_iconList.append(QIcon("://resource/icons/DIn.png"));
    m_iconList.append(QIcon("://resource/icons/EAn.png"));
    m_iconList.append(QIcon("://resource/icons/ELn.png"));
    m_iconList.append(QIcon("://resource/icons/ESn.png"));
    m_iconList.append(QIcon("://resource/icons/Cn.png"));
    m_iconList.append(QIcon("://resource/icons/SCn.png"));
    m_iconList.append(QIcon("://resource/icons/WTn.png"));
    m_iconList.append(QIcon("://resource/icons/Wn.png"));
    m_iconList.append(QIcon("://resource/icons/Qn.png"));
    m_iconList.append(QIcon("://resource/icons/Sn.png"));
    m_iconList.append(QIcon("://resource/icons/Bn.png"));
    //Initial the map item detail.
    m_itemDetail=new AMMapItemDetail(this);
    m_indicator=new QLabel(this);
    m_indicatorLeftIcon=QPixmap("://resource/indicator.png");
    m_indicatorRightIcon=QPixmap("://resource/indicator2.png");
    m_indicator->setPixmap(m_indicatorLeftIcon);
    m_indicator->resize(m_indicatorLeftIcon.size());
    QGraphicsDropShadowEffect *shadowEffect=
            new QGraphicsDropShadowEffect(m_itemDetail);
    shadowEffect->setBlurRadius(10);
    shadowEffect->setXOffset(0);
    shadowEffect->setYOffset(0);
    m_itemDetail->setGraphicsEffect(shadowEffect);
    m_itemDetail->hide();
    m_indicator->hide();

    connect(m_itemDetail, SIGNAL(requireHideDetail()),
            this, SLOT(hideItemDetail()));
    connect(m_itemDetail, SIGNAL(requireSearchPath(int,int,int)),
            this, SIGNAL(requireSearchPath(int,int,int)));

    m_delay=new QTimer(this);
    m_delay->setSingleShot(true);
    m_delay->setInterval(800);

    int minimalBorderSize=45, maximumBorderSize=60;
    m_breathTimeLine=new QTimeLine(350, this);
    connect(m_delay, SIGNAL(timeout()),
            m_breathTimeLine, SLOT(start()));
    m_breathTimeLine->setUpdateInterval(20);
    m_breathTimeLine->setEasingCurve(QEasingCurve::InCubic);
    m_breathTimeLine->setFrameRange(minimalBorderSize, maximumBorderSize);
    connect(m_breathTimeLine, &QTimeLine::finished,
            [=]
            {
                if(m_tracking)
                {
                    if(m_breathTimeLine->startFrame()==minimalBorderSize)
                    {
                        m_breathTimeLine->setFrameRange(maximumBorderSize, minimalBorderSize);
                        m_breathTimeLine->start();
                    }
                    else
                    {
                        m_breathTimeLine->setFrameRange(minimalBorderSize, maximumBorderSize);
                        m_delay->start();
                    }
                }
            });
    connect(m_breathTimeLine, &QTimeLine::frameChanged,
            [=](const int &frame)
            {
                m_borderWidth=frame/10;
                update();
            });
}

void AMMapPainter::addMap(const QPixmap &pixmap,
                          const QString &mapInfoFilePath,
                          const QString &mapCaption)
{
    //Generate the map item.
    Map item;
    item.image=pixmap;
    item.caption=mapCaption;
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

Map AMMapPainter::map(const int &index) const
{
    return m_mapList.at(index);
}

void AMMapPainter::setCurrentIndex(int index)
{
    if(index>-1 && index<m_mapList.size())
    {
        //Save the index.
        m_floorIndex=index;
        updateImage();
    }
}

void AMMapPainter::onActionPressed(QPoint position)
{
    //Check if current map is available.
    if(m_floorIndex!=-1)
    {
        QList<MapItem> itemList=m_mapList.at(m_floorIndex).items;
        for(QList<MapItem>::iterator i=itemList.begin();
            i!=itemList.end();
            ++i)
        {
            if((*i).zoomGeometry.contains(position))
            {
                //If item invalid, break;
                if((*i).type==-1)
                {
                    break;
                }
                showItemDetail(*i);
                break;
            }
        }
    }
}

void AMMapPainter::drawRoute()
{
    m_drawRoute=true;
    update();
}

void AMMapPainter::clearRoute()
{
    m_drawRoute=false;
    update();
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
                           QPainter::TextAntialiasing, true);
    //Paint the pixmap.
    painter.drawPixmap(0,0,m_currentImage.width(),m_currentImage.height(),
                       m_currentImage);

    if(m_floorIndex!=-1)
    {
        //----Debug---
        painter.setPen(QColor(255,0,0));

        QList<MapItem> itemList=m_mapList.at(m_floorIndex).items;
        for(QList<MapItem>::iterator i=itemList.begin();
            i!=itemList.end();
            ++i)
        {
//            if((*i).type==-1)
//            {
//                continue;
//            }
            QSize scaledSize=(*i).zoomGeometry.size().toSize();
            int iconSize=((qreal)qMin(scaledSize.width(), scaledSize.height()))*0.8;
            QRect currentRect=(*i).zoomGeometry.toRect();

            //----Debug----
            painter.drawRect(currentRect);

            //----Debug-----
            //After debug, enable the upper.
            if((*i).type==-1)
            {
                continue;
            }

            painter.drawPixmap(QRect(currentRect.x()+((currentRect.width()-iconSize)>>1),
                                     currentRect.y()+((currentRect.height()-iconSize)>>1),
                                     iconSize,
                                     iconSize),
                               m_iconList.at((*i).type).pixmap(iconSize, iconSize));
        }

        if(m_drawRoute)
        {
            painter.setPen(QColor(255,0,0));
            painter.setBrush(QColor(255,0,0));
            //Get route points from searcher.
            QJsonObject currentPath=m_searcher->path();
            QJsonArray pointsArray=currentPath.value("Path").toArray();
            for(QJsonArray::iterator i=pointsArray.begin();
                i!=pointsArray.end();
                ++i)
            {
                QJsonArray point=(*i).toArray();
                if(point.at(0).toInt()==m_floorIndex)
                {
                    painter.drawEllipse(QPoint(((qreal)point.at(1).toInt())*m_zoom,
                                               ((qreal)point.at(2).toInt())*m_zoom),
                                        5,
                                        5);
                }
            }
        }
    }

    //Check if enabled tracking.
    if(m_tracking && m_locationManager)
    {
            //Check if the floor is the current floor.
            if((int)m_currentFloor==m_floorIndex)
            {
                painter.setPen(Qt::NoPen);
                QPointF trackPointCenter=QPointF(m_currentX * (qreal)width(),
                                                 m_currentY * (qreal)height());
                painter.setBrush(QColor(255,255,255));
                painter.drawEllipse(trackPointCenter,
                                    m_trackPointSize,
                                    m_trackPointSize);
                painter.setBrush(QColor(79,132,251));
                //Draw the circle to the point.
                painter.drawEllipse(trackPointCenter,
                                    m_trackPointSize-m_borderWidth,
                                    m_trackPointSize-m_borderWidth);
            }
    }
}

void AMMapPainter::setTrackingData(double a, double b, double c)
{
    m_currentX=a;
    m_currentY=b;
    m_currentFloor=c;
    update();
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
            mapItem.zoomGeometry=QRectF(mapItem.geometry.topLeft()*m_zoom,
                                        mapItem.geometry.size()*m_zoom);
            mapItem.type=m_typeTextToIndex.value(mapItemArray.at(4).toString(),
                                                 -1);
            mapItem.id=mapItemArray.at(5).toInt();
            //Insert the item to map.
            map.items.append(mapItem);
        }
    }
}

inline void AMMapPainter::updateImage()
{
    //Scale the current image.
    m_currentImage=m_mapList.at(m_floorIndex).image;
    m_currentImage=m_currentImage.scaled(m_currentImage.size()*m_zoom,
                                         Qt::KeepAspectRatio,
                                         Qt::FastTransformation);
    //Resize the widget.
    resize(m_currentImage.size());
    //Update the painter to update the image.
    update();
}

AMLocationManagerBase *AMMapPainter::locationManager() const
{
    return m_locationManager;
}

void AMMapPainter::setLocationManager(AMLocationManagerBase *locationManager)
{
    m_locationManager = locationManager;
}

QString AMMapPainter::itemName(int type)
{
    return m_mapItemTypeName[type];
}

bool AMMapPainter::tracking() const
{
    return m_tracking;
}

void AMMapPainter::setTracking(bool tracking)
{
    m_tracking = tracking;
    if(m_tracking) //If enabled tracking.
    {
        m_locationManager->getCurrentPos(m_currentX, m_currentY, m_currentFloor);
        m_locationManager->startTracking();
        connect(m_locationManager, &AMLocationManagerBase::pointGet,
                this, &AMMapPainter::setTrackingData);
        m_breathTimeLine->start();
    }
    else
    {
        disconnect(m_locationManager, &AMLocationManagerBase::pointGet,
                   this, &AMMapPainter::setTrackingData);
        m_breathTimeLine->stop();
        update();
    }
}

AMSearcherBase *AMMapPainter::searcher() const
{
    return m_searcher;
}

void AMMapPainter::setSearcher(AMSearcherBase *searcher)
{
    m_searcher = searcher;
    connect(m_searcher, SIGNAL(searchSuccess()),
            this, SLOT(drawRoute()));
}

void AMMapPainter::hideItemDetail()
{
    //Get the focus.
    setFocus();
    //Hide the details.
    m_itemDetail->hide();
    m_indicator->hide();
}

void AMMapPainter::showItemDetail(const MapItem &item)
{
    //Set the data to detail.
    m_itemDetail->setTitle(m_mapList.at(m_floorIndex).caption + " " +
                           m_mapItemTypeName[item.type] + " " +
                           QString::number(item.id));
    m_itemDetail->setItemInformation(item.type,
                                     item.id,
                                     m_floorIndex);
    m_indicator->setPixmap(m_indicatorLeftIcon);
    //Set the position.
    QRect itemRect=item.zoomGeometry.toRect();
    m_itemDetail->resize(qMin((parentWidget()->width()>>2)*3,
                              200),
                         m_itemDetail->sizeHint().height());
    int halfContentHeight=(m_itemDetail->height()-m_indicator->height())>>1;
    QPoint preferPos=QPoint(itemRect.right()+m_indicator->width(),
                            itemRect.center().y()-(m_itemDetail->height()>>1)),
           indicatorPos=QPoint(preferPos.x()-m_indicator->width(),
                               preferPos.y()+halfContentHeight);
    //Check if the rect is out of the border.
    if(preferPos.x()+m_itemDetail->width() > width())
    {
        //Move the item detail widget to the left.
        preferPos.setX(itemRect.x()-m_itemDetail->width()-m_indicator->width());
        m_indicator->setPixmap(m_indicatorRightIcon);
        indicatorPos.setX(preferPos.x()+m_itemDetail->width());
    }
    //Check the top rect is out of the border.
    if(preferPos.y()<5)
    {
        preferPos.setY(5);
    }
    if(preferPos.y()+m_itemDetail->height()>height()-5)
    {
        preferPos.setY(height()-m_itemDetail->height()-5);
    }
    emit requireMoveCenterTo(QRect(preferPos, m_itemDetail->size()));
    m_itemDetail->move(preferPos);
    m_indicator->move(indicatorPos);
    m_itemDetail->show();
    m_indicator->show();
}

qreal AMMapPainter::zoom() const
{
    return m_zoom;
}

void AMMapPainter::setZoom(const qreal &zoom)
{
    //Hide the item detail first.
    hideItemDetail();
    //Set zoom.
    m_zoom = zoom;
    //Update all the zoom geometry.
    for(int i=0; i<m_mapList.size(); i++)
    {
        Map map=m_mapList.at(i);
        QList<MapItem> itemList=m_mapList.at(i).items,
                       zoomItemList;
        for(int j=0; j<itemList.size(); j++)
        {
            MapItem zoomItem=itemList.at(j);
            zoomItem.zoomGeometry=QRectF(zoomItem.geometry.topLeft()*m_zoom,
                                         zoomItem.geometry.size()*m_zoom);
            zoomItemList.append(zoomItem);
        }
        map.items=zoomItemList;
        m_mapList.replace(i, map);
    }
    updateImage();
}

