#include "amsuggestionfiltermodel.h"

#include <QDebug>

AMSuggestionFilterModel::AMSuggestionFilterModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{

}

AMSuggestionFilterModel::~AMSuggestionFilterModel()
{

}

bool AMSuggestionFilterModel::filterAcceptsRow(int source_row,
                                               const QModelIndex &source_parent) const
{
    return (sourceModel()->index(source_row, 0, source_parent).data(Qt::UserRole+1).toString().indexOf(filterRegExp())>=0) ||
            QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
}

