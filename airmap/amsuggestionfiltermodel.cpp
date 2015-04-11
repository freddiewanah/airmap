#include "amglobal.h"

#include "amsuggestionfiltermodel.h"

#include <QDebug>

using namespace AMStd;

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
    return (sourceModel()->index(source_row, 0, source_parent).data(ItemSearchSuggestionRole).toString().indexOf(filterRegExp())>=0) ||
            QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
}

