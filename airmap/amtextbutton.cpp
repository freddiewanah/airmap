#include "amtextbutton.h"

AMTextButton::AMTextButton(QWidget *parent) :
    QLabel(parent)
{
    setAutoFillBackground(true);
    setSizePolicy(QSizePolicy::Expanding,
                  QSizePolicy::Expanding);
    //Set properties.
    QPalette pal=palette();
    pal.setColor(QPalette::Window, QColor(0,0,0,0));
    setPalette(pal);
}

void AMTextButton::mousePressEvent(QMouseEvent *event)
{
    QPalette pal=palette();
    pal.setColor(QPalette::Window, QColor(0x00, 0x7a, 0xff, 200));
    setPalette(pal);
    QLabel::mousePressEvent(event);
}

void AMTextButton::mouseMoveEvent(QMouseEvent *event)
{
    QLabel::mouseMoveEvent(event);
}

void AMTextButton::mouseReleaseEvent(QMouseEvent *event)
{
    //Change the background.
    QPalette pal=palette();
    pal.setColor(QPalette::Window, QColor(0x00, 0x7a, 0xff, 0));
    setPalette(pal);
    //Emit clicked signal.
    emit clicked();
    QLabel::mouseReleaseEvent(event);
}
