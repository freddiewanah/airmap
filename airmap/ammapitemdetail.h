#ifndef AMMAPITEMDETAIL_H
#define AMMAPITEMDETAIL_H

#include <QWidget>

class QLabel;
class QBoxLayout;
class QPushButton;
class AMMapItemDetail : public QWidget
{
    Q_OBJECT
public:
    explicit AMMapItemDetail(QWidget *parent = 0);

signals:
    void requireSearchPath(int type, int id, int floor);
    void requireAddTransfer(int type, int id, int floor);
    void requireHideDetail();

public slots:
    void setItemInformation(int type, int id, int floor);
    void setTitle(const QString &title);
    void hideContent();

private slots:
    void sendSearchRequest();
    void sendAddTransferRequest();

private:
    QPushButton *generateButton(const QString &text);
    int m_type;
    int m_id;
    int m_floor;
    QLabel *m_title;
    QBoxLayout *m_mainLayout;
};

#endif // AMMAPITEMDETAIL_H
