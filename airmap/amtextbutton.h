#ifndef AMTEXTBUTTON_H
#define AMTEXTBUTTON_H

#include <QLabel>

class AMTextButton : public QLabel
{
    Q_OBJECT
public:
    explicit AMTextButton(QWidget *parent = 0);

signals:
    void clicked();

public slots:

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // AMTEXTBUTTON_H
