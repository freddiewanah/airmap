#ifndef AMTOUCHSROLLAREA_H
#define AMTOUCHSROLLAREA_H

#include <QScrollArea>

class QTimeLine;
class AMTouchSrollArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit AMTouchSrollArea(QWidget *parent = 0);

signals:
    void touch(QPoint point);
    void pressed();

public slots:
    void setMapPainter(QWidget *widget);
    void animeMoveTo(int x, int y);
    void onActionMovePoint(QRect point);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    bool m_pressed=false, m_moved=false;
    QPoint m_pressedPoint;
    QTimeLine *m_movingHAnime, *m_movingVAnime;
    int m_hValue, m_vValue;
};

#endif // AMTOUCHSROLLAREA_H
