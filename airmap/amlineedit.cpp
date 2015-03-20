#include "amlineedit.h"

AMLineEdit::AMLineEdit(QWidget *parent) : QLineEdit(parent)
{

}

AMLineEdit::~AMLineEdit()
{

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

