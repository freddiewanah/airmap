#include "amglobal.h"

AMGlobal *AMGlobal::m_instance=nullptr;

AMGlobal *AMGlobal::instance()
{
    return m_instance==nullptr?m_instance=new AMGlobal:m_instance;
}

AMGlobal::AMGlobal(QObject *parent) :
    QObject(parent)
{
}
