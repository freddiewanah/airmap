#ifndef AMSEARCHER_H
#define AMSEARCHER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <queue>

#include "amglobal.h"

#include "amsearcherbase.h"

using namespace std;
using namespace AMStd;

class AMSearcher : public AMSearcherBase
{
    Q_OBJECT
public:
    explicit AMSearcher(QObject *parent = 0);
    QJsonObject path();

    AMLocationManagerBase *locationManager();
    AMMapPainter *mapPainter();

signals:

public slots:
    void clearSearchResult();
    void setMapPainter(AMMapPainter *mapPainter);
    void searchPath(const QJsonObject &target);
    void setLocationManager(AMLocationManagerBase *locationManager);

private:
    struct Dot
    {
        int x;
        int y;
        int z;
        int f;
        int g;
        int h;
        int status;
        int Fx;
        int Fy;
        friend bool operator < (Dot a, Dot b)
        {
            if (a.h == b.h)
                return a.f > b.f;
            return a.h > b.h;
        }
    };
    Dot m_dot[2009][2009];
    void loadMap(const Map &map, int &endX, int &endY, const int &type, const int &index);
    bool aStarCanbe(int x, int y);
    void aStarRecall(Dot m_now);
    bool aStarSearch(Dot m_now, int value, int startarr, int endarr);
    AMLocationManagerBase *m_locationManager=nullptr;
    AMMapPainter *m_mapPainter=nullptr;
    priority_queue<Dot> m_q;
    Dot m_start, m_end, m_now;

    QJsonObject m_pathResult;

    int m_arr[16] = { 0, 1, 1, 0, -1, 0, 0, -1, 1, 1, -1, -1, 1, -1, -1, 1 };
    int m_borderWidth=20;
};

#endif // AMSEARCHER_H
