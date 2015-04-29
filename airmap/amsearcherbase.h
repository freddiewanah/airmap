#ifndef AMSEARCHERBASE_H
#define AMSEARCHERBASE_H

#include <QJsonObject>

#include <QObject>

class AMMapPainter;
class AMLocationManagerBase;
class AMSearcherBase : public QObject
{
    Q_OBJECT
public:
    AMSearcherBase(QObject *parent = 0):QObject(parent){}
    virtual QJsonObject path()=0;
    virtual AMLocationManagerBase *locationManager()=0;
    virtual AMMapPainter *mapPainter()=0;

signals:
    void searchFailed();
    void searchSuccess();

public slots:
    virtual void clearSearchResult()=0;
    virtual void setMapPainter(AMMapPainter *mapPainter)=0;
    virtual void searchPath(const QJsonObject &target)=0;
    virtual void setLocationManager(AMLocationManagerBase *locationManager)=0;
};

#endif // AMSEARCHERBASE_H
