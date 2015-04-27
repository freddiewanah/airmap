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
    //Clear the path result;
    m_pathResult=QJsonObject();

    int currentMapIndex=target.value("FromZ").toInt();
    const Map &currentMap=m_mapPainter->map(currentMapIndex);
    QSize mapSize=currentMap.image.size();
    int startX=((qreal)mapSize.width())*target.value("FromX").toDouble(),
        startY=((qreal)mapSize.height())*target.value("FromY").toDouble(),
        endX=-1, endY=-1;
    loadMap(currentMap,
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
    m_dot[endX][endY].status = 2;
    m_dot[startX][startY].g = 0;
    m_start = m_dot[startX][startY];

    m_start.h = abs(m_start.x - m_end.x) + abs(m_start.y - m_end.y);
    m_start.f = m_start.g + m_start.h;

    while(!m_q.empty())
    {
        m_q.pop();
    }
    m_q.push(m_start);

    while (!m_q.empty())
    {
        m_now = m_q.top();
        m_q.pop();

        if (m_now.status == 1)
        {
            continue;
        }

        if(Search(m_now, 10, 0, 4))
        {
            break;
        }
        else
        {
            if (Search(m_now, 14, 4, 8))
            {
                break;
            }
        }
        m_dot[m_now.x][m_now.y].status = 1;
    }
}

void AMSearcher::setLocationManager(AMLocationManagerBase *locationManager)
{
    m_locationManager = locationManager;
}

void AMSearcher::loadMap(const Map &map, int &endX, int &endY, const int &type, const int &index)
{
    qDebug()<<"type="<<type<<"index="<<index;
    //Clear cache.
    for (int i = 0; i < 2000; i++)
    {
        for (int j = 0; j < 2000; j++)
        {
            m_dot[i][j].x = i;
            m_dot[i][j].y = j;
            m_dot[i][j].f = 10000;
            m_dot[i][j].g = 10000;
            m_dot[i][j].h = 0;
            m_dot[i][j].status = 0;
            m_dot[i][j].Fx = -1;
            m_dot[i][j].Fy = -1;
        }
    }

    //Set map data.
    QList<MapItem> items=map.items;
    for(QList<MapItem>::iterator i=items.begin();
        i!=items.end();
        ++i)
    {
        if((*i).type==type && (*i).id==index)
        {
            QPoint destinationPoint=(*i).geometry.center().toPoint();
            endX=destinationPoint.x();
            endY=destinationPoint.y();
        }
        else
        {
            int hS=(int)((*i).geometry.x()),
                hE=hS+((int)((*i).geometry.width())),
                vS=(int)((*i).geometry.y()),
                vE=vS+((int)((*i).geometry.height()));
            for(int h=hS; h<hE; h++)
            {
                for(int v=vS; v<vE; v++)
                {
                    m_dot[h][v].status=1;
                }
            }
        }
    }
}

bool AMSearcher::canbe(int x, int y)
{
    if (x >= 0 && x < 2000 && y >= 0 && y < 2000 && m_dot[x][y].status != 1)
    {
        return true;
    }
    return false;
}

void AMSearcher::Recall(Dot now)
{
    QJsonArray dots, tempDotData;
    tempDotData.append(now.x);
    tempDotData.append(now.y);
    dots.append(tempDotData);
    while (now.Fx >= 0)
    {
        now = m_dot[now.Fx][now.Fy];
        QJsonArray dotData;
        dotData.append(now.x);
        dotData.append(now.y);
        dots.append(dotData);
    }

    m_pathResult.insert("Path", dots);
}

bool AMSearcher::Search(Dot now, int value, int startarr, int endarr)
{
    int x = now.x, y = now.y;
    bool flag = false;
    for (int i = startarr; i < endarr; i++)
    {
        if (canbe(x + m_arr[2 * i], y + m_arr[2 * i + 1]))
        {
            Dot *current = &m_dot[x + m_arr[2 * i]][y + m_arr[2 * i + 1]];
            if ((*current).status == 2)
            {
                (*current).g = now.g + value;
                (*current).Fx = now.x;
                (*current).Fy = now.y;
                Recall((*current));
                emit searchSuccess();
                flag = true;
                break;
            }
            if ((*current).g > now.g + value)
            {
                (*current).g = now.g + value;
                (*current).h = abs((*current).x - m_end.x)
                        + abs((*current).y - m_end.y);
                (*current).f = (*current).g + (*current).h;
                (*current).Fx = now.x;
                (*current).Fy = now.y;
                m_q.push((*current));
            }
        }
    }
    return flag;
}

AMMapPainter *AMSearcher::mapPainter()
{
    return m_mapPainter;
}

void AMSearcher::setMapPainter(AMMapPainter *mapPainter)
{
    m_mapPainter=mapPainter;
}
