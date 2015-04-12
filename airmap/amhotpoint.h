#ifndef AMHOTPOINT_H
#define AMHOTPOINT_H

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
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    bool m_pressed=false;
    QPoint m_pressedPoint, m_startPos;
};

#endif // AMHOTPOINT_H
