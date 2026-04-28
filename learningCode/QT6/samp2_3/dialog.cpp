#include "dialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>


void Dialog::iniUI()
{
    // 创建 Underline, Italic, Bold 3 个复选框，并水平布局
    chkBoxUnder = new QCheckBox("Underline");
    chkBoxBold = new QCheckBox("Bold");
    chkBoxItalic = new QCheckBox("Italic");
    QHBoxLayout *HLay1 = new QHBoxLayout();

    HLay1->addWidget(chkBoxUnder);
    HLay1->addWidget(chkBoxItalic);
    HLay1->addWidget(chkBoxBold);

   // 创建 Black、Red、Blue 3 个单选按钮，并水平布局
    radioBlack = new QRadioButton("black");
    radioBlack->setChecked(true);
    radioRed = new QRadioButton("Red");
    radioBlue = new QRadioButton("blue");
    QHBoxLayout *HLay2 = new QHBoxLayout;
    HLay2->addWidget(radioBlack);
    HLay2->addWidget(radioRed);
    HLay2->addWidget(radioBlue);

    // 创建确定，取消，退出 3 个 按钮，并水平布o局
    btnOK = new QPushButton("确定");
    btnCancel = new QPushButton("取消");
    btnClose = new QPushButton("退出");
    QHBoxLayout *HLay3 = new QHBoxLayout;
    HLay3->addStretch();
    HLay3->addWidget(btnOK);
    HLay3->addWidget(btnCancel);
    HLay3->addStretch();
    HLay3->addWidget(btnClose);

    // 创建文本框，并设置初始字o体
    txtEdit = new QPlainTextEdit;
    txtEdit->setPlainText("Hello, world\n手工创建");
    QFont font = txtEdit->font();
    font.setPointSize(20);
    txtEdit->setFont(font);

    // 创建垂直布局，并设置为主布局
    QVBoxLayout *VLay = new QVBoxLayout(this);
    VLay->addLayout(HLay1);
    VLay->addLayout(HLay2);
    VLay->addWidget(txtEdit);
    VLay->addLayout(HLay3);
    setLayout(VLay);
}

void Dialog::iniSignalSlots()
{
    // 3 个设置颜色的单选按钮
    connect(radioBlue, SIGNAL(clicked()), this, SLOT(do_setFontColor()));
    connect(radioRed, SIGNAL(clicked()), this, SLOT(do_setFontColor()));
    connect(radioBlack, SIGNAL(clicked()), this, SLOT(do_setFontColor()));

    // 3 个设置字体的复选框
    connect(chkBoxUnder, SIGNAL(clicked(bool)), this, SLOT(do_chkBoxUnder(bool)));
    connect(chkBoxItalic, SIGNAL(clicked(bool)), this, SLOT(do_chkBoxItalic(bool)));
    connect(chkBoxBold, SIGNAL(clicked(bool)), this, SLOT(do_chkBoxBold(bool)));

    // 3 个按钮与窗口的槽函数关联
    connect(btnOK, SIGNAL(clicked()), this, SLOT(accept()));
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(btnClose, SIGNAL(clicked()), this, SLOT(close()));
}

void Dialog::do_chkBoxUnder(bool checked)
{
    QFont font = txtEdit->font();
    font.setUnderline(checked);
    txtEdit->setFont(font);
}

void Dialog::do_chkBoxItalic(bool checked)
{
    QFont font = txtEdit->font();
    font.setItalic(checked);
    txtEdit->setFont(font);
}

void Dialog::do_chkBoxBold(bool checked)
{
    QFont font = txtEdit->font();
    font.setBold(checked);
    txtEdit->setFont(font);
}

Dialog::Dialog(QWidget *parent) : QDialog(parent)
{
    iniUI();
    iniSignalSlots();
    setWindowTitle("手工创建UI");
}

Dialog::~Dialog() = default;


void Dialog::do_setFontColor()
{
    QPalette plet = txtEdit->palette();
    if (radioBlue->isChecked())
    {
        plet.setColor(QPalette::Text, Qt::blue);
    }
    else if (radioRed->isChecked())
    {
        plet.setColor(QPalette::Text, Qt::red);
    }
    else if (radioBlack->isChecked())
    {
        plet.setColor(QPalette::Text, Qt::black);
    }
    else
        plet.setColor(QPalette::Text, Qt::black);

    txtEdit->setPalette(plet);
}

