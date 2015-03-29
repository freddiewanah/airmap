#include <QHeaderView>

#include "amsuggestionmodel.h"
#include "amsuggestiondelegate.h"

#include "amsearchsuggetions.h"

AMSearchSuggetions::AMSearchSuggetions(QWidget *parent) :
    QTreeView(parent)
{
    //Set properties.
    setFrameStyle(QFrame::NoFrame);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    setIndentation(0);
    header()->setVisible(false);
    //Set palette.
    QPalette pal=palette();
    pal.setColor(QPalette::Base, QColor(0,0,0,100));
    setPalette(pal);
    //Set item view delegate
    setItemDelegate(new AMSuggestionDelegate(this));

    //Initial the models.
    m_suggestionModel=new AMSuggestionModel(this);
    setModel(m_suggestionModel);

    //Expand all.
    expandAll();
}
