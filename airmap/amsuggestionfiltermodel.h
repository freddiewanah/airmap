#ifndef AMSUGGESTIONFILTERMODEL_H
#define AMSUGGESTIONFILTERMODEL_H

#include <QSortFilterProxyModel>

class AMSuggestionFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit AMSuggestionFilterModel(QObject *parent = 0);
    ~AMSuggestionFilterModel();

signals:

public slots:

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
};

#endif // AMSUGGESTIONFILTERMODEL_H
