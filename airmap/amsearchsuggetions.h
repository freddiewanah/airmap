#ifndef AMSEARCHSUGGETIONS_H
#define AMSEARCHSUGGETIONS_H

#include <QTreeView>

class QPanGesture;
class QGestureEvent;
class AMSuggestionFilterModel;
class AMSuggestionModel;
class AMSearchSuggetions : public QTreeView
{
    Q_OBJECT
public:
    explicit AMSearchSuggetions(QWidget *parent = 0);

signals:

public slots:
    void searchText(const QString &text);

protected:
    bool event(QEvent *event);
    bool gestureEvent(QGestureEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    void panTriggered(QPanGesture *gesture);
    AMSuggestionModel *m_suggestionModel;
    AMSuggestionFilterModel *m_proxyModel;
    bool m_pressed=false;
};

#endif // AMSEARCHSUGGETIONS_H
