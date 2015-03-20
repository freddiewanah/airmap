#ifndef AMLABELBUTTON_H
#define AMLABELBUTTON_H

#include <QLabel>

class AMLabelButton : public QLabel
{
    Q_OBJECT
public:
    explicit AMLabelButton(QWidget *parent = 0);
    ~AMLabelButton();

signals:
    void clicked();

public slots:

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    bool m_pressed=false;
};

#endif // AMLABELBUTTON_H
