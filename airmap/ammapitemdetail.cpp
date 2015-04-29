#include <QBoxLayout>
#include <QFrame>
#include <QGridLayout>
#include <QPushButton>

#include <QLabel>

#include "ammapitemdetail.h"

AMMapItemDetail::AMMapItemDetail(QWidget *parent) :
    QWidget(parent)
{
    setAutoFillBackground(true);

    //Set the layout.
    m_mainLayout=new QBoxLayout(QBoxLayout::TopToBottom,
                                this);
    setLayout(m_mainLayout);

    //Initial the title.
    m_title=new QLabel(this);
    m_title->setAlignment(Qt::AlignHCenter);
    m_mainLayout->addWidget(m_title);

    //Add the line.
    QFrame *seperateLine=new QFrame(this);
    seperateLine->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    seperateLine->setFixedHeight(3);
    m_mainLayout->addWidget(seperateLine);

    //Add button matrix layout.
    QGridLayout *buttonMatrix=new QGridLayout(m_mainLayout->widget());
    m_mainLayout->addLayout(buttonMatrix);

    //Add search button.
    QPushButton *getRoute=generateButton("获取路线");
    buttonMatrix->addWidget(getRoute, 0, 0, 1, 1);
    connect(getRoute, SIGNAL(clicked()), this, SLOT(sendSearchRequest()));
    QPushButton *addTransfer=generateButton("添加中转点");
    buttonMatrix->addWidget(addTransfer, 0, 1, 1, 1);
    connect(addTransfer, SIGNAL(clicked()), this, SLOT(sendAddTransferRequest()));
}

void AMMapItemDetail::setItemInformation(int type, int id, int floor)
{
    //Save the data.
    m_type=type;
    m_id=id;
    m_floor=floor;
}

void AMMapItemDetail::setTitle(const QString &title)
{
    m_title->setText(title);
}

void AMMapItemDetail::hideContent()
{
    m_mainLayout->widget()->hide();
}

void AMMapItemDetail::sendSearchRequest()
{
    emit requireSearchPath(m_type, m_id, m_floor);
    emit requireHideDetail();
}

void AMMapItemDetail::sendAddTransferRequest()
{
    emit requireAddTransfer(m_type, m_id, m_floor);
    emit requireHideDetail();
}

QPushButton *AMMapItemDetail::generateButton(const QString &text)
{
    QPushButton *button=new QPushButton(text, this);
    button->setMinimumHeight(20);
    return button;
}
