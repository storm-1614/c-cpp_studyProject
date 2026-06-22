#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <QRadioButton>
#include <QWidget>
#include <QPushButton>
#include <QPlainTextEdit>

class Dialog : public QDialog
{
    Q_OBJECT

  private:
    QCheckBox *chkBoxUnder;
    QCheckBox *chkBoxItalic;
    QCheckBox *chkBoxBold;
    QRadioButton *radioBlack;
    QRadioButton *radioRed;
    QRadioButton *radioBlue;
    QPushButton *btnOK;
    QPushButton *btnCancel;
    QPushButton *btnClose;
    QPlainTextEdit *txtEdit;
    void iniUI();
    void iniSignalSlots()
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

  private slots:
    void do_chkBoxUnder(bool checked);
    void do_chkBoxItalic(bool checked);
    void do_chkBoxBold(bool checked);
    void do_setFontColor();

  public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog() override;
};
#endif // DIALOG_H
