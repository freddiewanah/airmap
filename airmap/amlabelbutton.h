#ifndef AMLABELBUTTON_H
#define AMLABELBUTTON_H

#include <QLabel>

class QTimeLine;
class AMLabelButton : public QLabel
{
    Q_OBJECT
public:
    explicit AMLabelButton(QWidget *parent = 0);
    ~AMLabelButton();

signals:
    void clicked();

public slots:
    void showButton();
    void hideButton();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    inline void startAnime(QTimeLine *anime);
    QTimeLine *generateAnime();
    bool m_pressed=false;
    QTimeLine *m_expandAnime, *m_foldAnime;
};

#endif // AMLABELBUTTON_H
