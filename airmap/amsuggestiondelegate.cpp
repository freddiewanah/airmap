#include <QPainter>

#include "amsuggestiondelegate.h"

#include <QDebug>

AMSuggestionDelegate::AMSuggestionDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QSize AMSuggestionDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(QStyledItemDelegate::sizeHint(option, index).width(),
                 index.data(Qt::DecorationRole).isNull()?52:48);
}

void AMSuggestionDelegate::paint(QPainter *painter,
                                 const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const
{
    if(index.data(Qt::DecorationRole).isNull())
    {
        //Draw background first.
        painter->fillRect(option.rect, QColor(255,255,255,100));
        QFont captionFont=option.font;
        captionFont.setPixelSize(11);
        painter->setFont(captionFont);
        painter->setPen(option.palette.color(QPalette::Disabled, QPalette::WindowText));
        //Means this is a title row. Draw it as a title.
        painter->drawText(option.rect.x()+16,
                          option.rect.y(),
                          option.rect.width(),
                          option.rect.height()-6,
                          Qt::AlignLeft | Qt::AlignBottom,
                          index.data(Qt::DisplayRole).toString());
        return;
    }
    //Draw the selected background if current item has been selected.
    if(option.state & QStyle::State_Selected)
    {
        painter->fillRect(option.rect, QColor(255,255,255,150));
    }
    //Draw the icon.
    painter->drawPixmap(option.rect.x()+16,
                        option.rect.y()+4,
                        40,
                        40,
                        index.data(Qt::DecorationRole).value<QIcon>().pixmap(40, 40));
    //Draw the text.
    QFont itemFont=option.font;
    itemFont.setPixelSize(15);
    painter->setFont(itemFont);
    painter->setPen(option.palette.color(QPalette::Normal, QPalette::WindowText));
    painter->drawText(option.rect.x()+66,
                      option.rect.y(),
                      option.rect.width(),
                      option.rect.height(),
                      Qt::AlignLeft | Qt::AlignVCenter,
                      index.data(Qt::DisplayRole).toString());
    painter->setPen(QColor(255,255,255,50));
    painter->drawLine(option.rect.x()+8,
                      option.rect.bottom(),
                      option.rect.right(),
                      option.rect.bottom());
}
