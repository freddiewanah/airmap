#ifndef AMLOCATIONMANAGERBASE_H
#define AMLOCATIONMANAGERBASE_H

#include <QObject>

class AMLocationManagerBase : public QObject
{
    Q_OBJECT
public:
    AMLocationManagerBase(QObject *parent = 0):QObject(parent){}
    virtual bool getCurrentPos(double &a, double &b, double &c)=0;
    virtual void setUrl(const QString &url)=0;

signals:
    void pointGet(double a, double b, double c);

public slots:
    virtual void startTracking()=0;
    virtual void stopTracking()=0;

};

#endif // AMLOCATIONMANAGERBASE_H
