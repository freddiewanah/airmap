#ifndef AMHOTPOINT_H
#define AMHOTPOINT_H

#include <QWidget>

class QDial;
class QLabel;
class QTimeLine;
class AMTextButton;
class QPropertyAnimation;
class AMHotPoint : public QWidget
{
    Q_OBJECT
public:
    explicit AMHotPoint(QWidget *parent = 0);

signals:
    void requireChangeZoom(qreal zoom);
    void requireChangeMap(int mapIndex);
    void requireCheckPosition();

public slots:
    void setZoom(int zoomSize);
    void onActionShowItems();
    void onActionHideItems();
    void foldHotPoint();

protected:
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void onActionExpand(const QVariant &value);
    void onActionFold(const QVariant &value);
    void onActionClicked();

private:
    void moveToSide();
    bool m_pressed=false, m_moved=false;
    QPoint m_pressedPoint, m_startPos;
    QDial *m_slider;
    QLabel *m_indicator;
    AMTextButton *m_floor[3];
    QTimeLine *m_stickAnime;
    QPropertyAnimation *m_expandAnime, *m_foldAnime;
    QRect m_expandGeometry=QRect();
};

#endif // AMHOTPOINT_H
