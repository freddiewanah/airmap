#ifndef AMLOCATIONMANAGER_H
#define AMLOCATIONMANAGER_H

#include "amlocationmanagerbase.h"

class QTimer;
class QNetworkAccessManager;
class AMLocationManager : public AMLocationManagerBase
{
    Q_OBJECT
public:
    explicit AMLocationManager(QObject *parent = 0);
    bool getCurrentPos(double &a, double &b, double &c);
    void setUrl(const QString &url);

signals:
    void positionUpdate(double a, double b, double c);

public slots:
    void startTracking();
    void stopTracking();

private slots:
    void onActionUpdatePosition();

private:
    QByteArray getPositionInfo();
    QNetworkAccessManager *m_networkManager;
    QString m_url;
    QTimer *m_timeout, *m_tracking;
};

#endif // AMLOCATIONMANAGER_H
