#include <QLabel>

#include "amlineedit.h"

AMLineEdit::AMLineEdit(QWidget *parent) : QLineEdit(parent)
{
    //Set properties.
    setTextMargins(5,5,5,5);
    //Initial the place holder label.
    m_placeHolder=new QLabel(this);
    QPalette pal=m_placeHolder->palette();
    pal.setColor(QPalette::WindowText, QColor(0,0,0,120));
    pal.setColor(QPalette::Text, QColor(0,0,0,120));
    m_placeHolder->setPalette(pal);
    m_placeHolder->setAlignment(Qt::AlignCenter);
    m_placeHolder->setAttribute(Qt::WA_TransparentForMouseEvents);
    connect(this, &AMLineEdit::textChanged,
            [=](const QString &text)
            {
                m_placeHolder->setVisible(text.isEmpty());
            });
}

AMLineEdit::~AMLineEdit()
{

}

void AMLineEdit::setPlaceHolderLabelText(const QString &text)
{
    m_placeHolder->setText(text);
}

void AMLineEdit::focusInEvent(QFocusEvent *event)
{
    emit focusIn();
    QLineEdit::focusInEvent(event);
}

void AMLineEdit::focusOutEvent(QFocusEvent *event)
{
    emit focusOut();
    QLineEdit::focusOutEvent(event);
}

void AMLineEdit::resizeEvent(QResizeEvent *event)
{
    //Resize.
    QLineEdit::resizeEvent(event);
    //Resize the place holder label.
    m_placeHolder->resize(size());
}

