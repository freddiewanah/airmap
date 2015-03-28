#ifndef AMLINEEDIT_H
#define AMLINEEDIT_H

#include <QLineEdit>

class QLabel;
class AMLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit AMLineEdit(QWidget *parent = 0);
    ~AMLineEdit();
    void setPlaceHolderLabelText(const QString &text);

signals:
    void focusIn();
    void focusOut();

public slots:

protected:
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    QLabel *m_placeHolder;
};

#endif // AMLINEEDIT_H
