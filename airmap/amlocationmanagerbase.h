#ifndef AMLOCATIONMANAGERBASE_H
#define AMLOCATIONMANAGERBASE_H

#include <QObject>

class AMLocationManagerBase : public QObject
{
    Q_OBJECT
public:
    AMLocationManagerBase(QObject *parent = 0):QObject(parent){}
    virtual void getCurrentPos(int &a, int &b, int &c)=0;

signals:
    void pointGet(int a, int b, int c);

public slots:
    virtual void startTracking()=0;
    virtual void stopTracking()=0;

};

#endif // AMLOCATIONMANAGERBASE_H
