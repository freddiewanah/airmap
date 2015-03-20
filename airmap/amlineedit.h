#ifndef AMLINEEDIT_H
#define AMLINEEDIT_H

#include <QLineEdit>

class AMLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit AMLineEdit(QWidget *parent = 0);
    ~AMLineEdit();

signals:
    void focusIn();
    void focusOut();

public slots:

protected:
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
};

#endif // AMLINEEDIT_H
