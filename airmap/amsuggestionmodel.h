#ifndef AMSUGGESTIONMODEL_H
#define AMSUGGESTIONMODEL_H

#include <QStandardItemModel>

#include "amglobal.h"

using namespace AMStd;

class AMSuggestionModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit AMSuggestionModel(QObject *parent = 0);
    QModelIndex findPlace(const QString &keyword);

signals:

public slots:

private:
    QStandardItem *m_categoryItem[MapItemTypeCount];
};

#endif // AMSUGGESTIONMODEL_H
