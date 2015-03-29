#ifndef AMSEARCHSUGGETIONS_H
#define AMSEARCHSUGGETIONS_H

#include <QTreeView>

class AMSuggestionModel;
class AMSearchSuggetions : public QTreeView
{
    Q_OBJECT
public:
    explicit AMSearchSuggetions(QWidget *parent = 0);

signals:

public slots:

private:
    AMSuggestionModel *m_suggestionModel;
};

#endif // AMSEARCHSUGGETIONS_H
