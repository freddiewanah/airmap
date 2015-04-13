#ifndef AMHOTPOINT_H
#define AMHOTPOINT_H

#include <QTimeLine>

#include <QWidget>

class AMHotPoint : public QWidget
{
    Q_OBJECT
public:
    explicit AMHotPoint(QWidget *parent = 0);

signals:
    void requireCheckPosition();

public slots:

protected:
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void onActionClicked();

private:
    void moveToSide();
    bool m_pressed=false, m_moved=false;
    QPoint m_pressedPoint, m_startPos;
    QTimeLine *m_stickAnime;
};

#endif // AMHOTPOINT_H
