#ifndef AMSEARCHERBASE_H
#define AMSEARCHERBASE_H

#include <QJsonObject>

#include <QObject>

class AMLocationManagerBase;
class AMSearcherBase : public QObject
{
    Q_OBJECT
public:
    AMSearcherBase(QObject *parent = 0):QObject(parent){}
    virtual QJsonObject path()=0;
    virtual AMLocationManagerBase *locationManager()=0;

signals:
    void searchFailed();
    void searchSuccess();

public slots:
    virtual void searchPath(const QJsonObject &target)=0;
    virtual void setLocationManager(AMLocationManagerBase *locationManager)=0;

private:
    AMLocationManagerBase *m_locationManager=nullptr;
};

#endif // AMSEARCHERBASE_H
