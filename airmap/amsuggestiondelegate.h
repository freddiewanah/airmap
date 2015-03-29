#ifndef AMSUGGESTIONDELEGATE_H
#define AMSUGGESTIONDELEGATE_H

#include <QStyledItemDelegate>

class AMSuggestionDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit AMSuggestionDelegate(QObject *parent = 0);
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

signals:

public slots:

protected:

};

#endif // AMSUGGESTIONDELEGATE_H
