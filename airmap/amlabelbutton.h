#ifndef AMLABELBUTTON_H
#define AMLABELBUTTON_H

#include <QPixmap>

#include <QWidget>

class QTimeLine;
class AMLabelButton : public QWidget
{
    Q_OBJECT
public:
    explicit AMLabelButton(QWidget *parent = 0);
    ~AMLabelButton();

    QPixmap pixmap() const;
    void setPixmap(const QPixmap &pixmap, const QSize &preferSize=QSize());

    QString text() const;
    void setText(const QString &text);

signals:
    void clicked();

public slots:
    void showButton();
    void hideButton();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    inline void stopAnimes();
    inline void startAnime(QTimeLine *anime);
    QTimeLine *generateAnime();
    bool m_pressed=false;
    QTimeLine *m_expandAnime, *m_foldAnime;
    QPixmap m_pixmap;
    QString m_text;
    qreal m_pressedOpacity=1.0;
};

#endif // AMLABELBUTTON_H
