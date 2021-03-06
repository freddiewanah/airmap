#include <QJsonArray>
#include <QDebug>

#include "ammappainter.h"

#include "amsearcher.h"

AMSearcher::AMSearcher(QObject *parent) :
    AMSearcherBase(parent)
{
}

QJsonObject AMSearcher::path()
{
    return m_pathResult;
}

AMLocationManagerBase *AMSearcher::locationManager()
{
    return m_locationManager;
}

void AMSearcher::searchPath(const QJsonObject &target)
{
    //Clear the previous path result;
    clearSearchResult();

    m_mapIndex=target.value("FromZ").toInt();
    const Map &currentMap=m_mapPainter->map(m_mapIndex);
    QSize mapSize=currentMap.image.size();
    int startX=((qreal)mapSize.width())*target.value("FromX").toDouble(),
        startY=((qreal)mapSize.height())*target.value("FromY").toDouble(),
        endX=-1, endY=-1;
    loadMap(currentMap,
            startX,
            startY,
            endX,
            endY,
            target.value("DestinationType").toInt(),
            target.value("DestinationIndex").toInt());

    //Check if we can't find the end point.
    if(endX==-1 || endY==-1)
    {
        qDebug()<<"Error! We cannot find the point!";
        return;
    }
    m_end = m_dot[endX][endY];
    m_dot[endX][endY].status = Destiation;
    m_dot[startX][startY].toFrom = 0;
    m_start = m_dot[startX][startY];

    m_start.toDest = abs(m_start.x - m_end.x) + abs(m_start.y - m_end.y);
    m_start.total = m_start.toFrom + m_start.toDest;

    m_q=priority_queue<Dot>();
    m_q.push(m_start);

    while (!m_q.empty())
    {
        m_now = m_q.top();
        m_q.pop();

        if (m_now.status==Walked)
        {
            continue;
        }

        if(aStarSearch(m_now, 10, 0, 4))
        {
            break;
        }
        else
        {
            if (aStarSearch(m_now, 14, 4, 8))
            {
                break;
            }
        }
        m_dot[m_now.x][m_now.y].status=Walked;
    }
}

void AMSearcher::setLocationManager(AMLocationManagerBase *locationManager)
{
    m_locationManager = locationManager;
}

void AMSearcher::loadMap(const Map &map,
                         const int &startX,
                         const int &startY,
                         int &endX,
                         int &endY,
                         const int &type,
                         const int &index)
{
    //Clear cache.
    for (int i = 0; i < 2000; i++)
    {
        for (int j = 0; j < 2000; j++)
        {
            m_dot[i][j].x = i;
            m_dot[i][j].y = j;
            m_dot[i][j].total = 10000000;
            m_dot[i][j].toFrom = 10000000;
            m_dot[i][j].toDest = 0;
            m_dot[i][j].status = Normal;
            m_dot[i][j].Fx = -1;
            m_dot[i][j].Fy = -1;
        }
    }
    //Genereate the start pos.
    QPoint startPos=QPoint(startX, startY);
    //Set map data.
    QList<MapItem> items=map.items;
    for(QList<MapItem>::iterator i=items.begin();
        i!=items.end();
        ++i)
    {
        if((*i).type==type && (*i).id==index)
        {
            //Save the endX and end Y.
            QPoint destinationPoint=(*i).geometry.center().toPoint();
            endX=destinationPoint.x();
            endY=destinationPoint.y();
        }
        else if((*i).geometry.contains(startPos))
        {
            continue;
        }
        else
        {
            //Set the point disabled.
            int hS=(int)((*i).geometry.x())-m_borderWidth,
                hE=hS+((int)((*i).geometry.width()))+(m_borderWidth<<1),
                vS=(int)((*i).geometry.y())-m_borderWidth,
                vE=vS+((int)((*i).geometry.height()))+(m_borderWidth<<1);
            if(hS<0)
            {
                hS=0;
            }
            if(hE>1999)
            {
                hE=1999;
            }
            if(vS<0)
            {
                vS=0;
            }
            if(vE>1999)
            {
                vE=1999;
            }
            for(int h=hS; h<hE; h++)
            {
                for(int v=vS; v<vE; v++)
                {
                    //Treat invaild point as walked point.
                    m_dot[h][v].status=Walked;
                }
            }
        }
    }
}

bool AMSearcher::aStarCanbe(int x, int y)
{
    if (x >= 0 && x < 2000 && y >= 0 && y < 2000 && m_dot[x][y].status != 1)
    {
        return true;
    }
    return false;
}

void AMSearcher::aStarRecall(Dot now)
{
    QJsonArray dots, tempDotData;
    tempDotData.append(m_mapIndex);
    tempDotData.append(now.x);
    tempDotData.append(now.y);
    dots.append(tempDotData);
    while (now.Fx >= 0)
    {
        now = m_dot[now.Fx][now.Fy];
        QJsonArray dotData;
        dotData.append(m_mapIndex);
        dotData.append(now.x);
        dotData.append(now.y);
        dots.append(dotData);
    }

    m_pathResult.insert("Path", dots);
}

bool AMSearcher::aStarSearch(Dot now, int value, int startarr, int endarr)
{
    int x = now.x, y = now.y;
    bool flag = false;
    for (int i = startarr; i < endarr; i++)
    {
        if (aStarCanbe(x + m_arr[2 * i], y + m_arr[2 * i + 1]))
        {
            Dot &current = m_dot[x + m_arr[2 * i]][y + m_arr[2 * i + 1]];
            if (current.status == Walked)
            {
                continue;
            }
            if (current.status == Destiation)
            {
                current.toFrom = now.toFrom + value;
                current.Fx = now.x;
                current.Fy = now.y;
                aStarRecall(current);
                emit searchSuccess();
                flag = true;
                break;
            }
            if (current.toFrom > now.toFrom + value)
            {
                current.toFrom = now.toFrom + value;
                current.toDest = abs(current.x - m_end.x)
                        + abs(current.y - m_end.y);
                current.total = current.toFrom + current.toDest;
                current.Fx = now.x;
                current.Fy = now.y;
                m_q.push(current);
            }
        }
    }
    return flag;
}

AMMapPainter *AMSearcher::mapPainter()
{
    return m_mapPainter;
}

void AMSearcher::clearSearchResult()
{
    //Clear the path result.
    m_pathResult=QJsonObject();
}

void AMSearcher::setMapPainter(AMMapPainter *mapPainter)
{
    m_mapPainter=mapPainter;
}
