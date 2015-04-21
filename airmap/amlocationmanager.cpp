#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QEventLoop>
#include <QTimer>

#include "amlocationmanager.h"

AMLocationManager::AMLocationManager(QObject *parent) :
    AMLocationManagerBase(parent)
{
    m_timeout=new QTimer(this);
    m_timeout->setInterval(1000);
    m_tracking=new QTimer(this);
    m_tracking->setInterval(100);
    m_networkManager=new QNetworkAccessManager(this);
}

bool AMLocationManager::getCurrentPos(double &a, double &b, double &c)
{
    //----Debug-----
    a=0.5;
    b=0.5;
    c=1;
    return true;
    //Get information.
    QByteArray rawData=getPositionInfo();
    if(rawData.isEmpty())
    {
        return false;
    }
    QJsonArray positionData=QJsonDocument::fromJson(rawData).array();
    if(positionData.size()<3)
    {
        return false;
    }
    a=positionData.at(0).toDouble();
    b=positionData.at(1).toDouble();
    c=positionData.at(2).toDouble();
    return true;
}

void AMLocationManager::setUrl(const QString &url)
{
    m_url=url;
}

void AMLocationManager::startTracking()
{
    //Check if tracking timer is running.
    if(m_tracking->isActive())
    {
        return;
    }
    m_tracking->start();
}

void AMLocationManager::stopTracking()
{
    m_tracking->stop();
}

void AMLocationManager::onActionUpdatePosition()
{
    double a,b,c;
    if(getCurrentPos(a,b,c))
    {
        emit positionUpdate(a,b,c);
    }
}

QByteArray AMLocationManager::getPositionInfo()
{
    //Stop the timer.
    m_timeout->stop();
    //Clear the data first.
    m_networkManager->clearAccessCache();
    //Generate the request.
    QNetworkRequest currentRequest;
    //Set the url.
    currentRequest.setUrl(m_url);
    //Generate the reply and quit handler.
    QNetworkReply *currentReply=nullptr;
    //Wait for response, using the event loop, generate the loop.
    QEventLoop stuckWaitingLoop;
    connect(m_networkManager, SIGNAL(finished(QNetworkReply*)),
                              &stuckWaitingLoop, SLOT(quit()));
    connect(m_timeout, SIGNAL(timeout()),
                              &stuckWaitingLoop, SLOT(quit()));
    //Get the data.
    currentReply=m_networkManager->get(currentRequest);
    //Start counting.
    m_timeout->start();
    //Start loop.
    stuckWaitingLoop.exec();
    //Check if there's reply.
    if(currentReply==nullptr)
    {
        return QByteArray();
    }
    return currentReply->readAll();
}
