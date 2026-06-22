#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->radioBlack, SIGNAL(clicked()), this, SLOT(do_setFontColor()));
    connect(ui->radioBlue, SIGNAL(clicked()), this, SLOT(do_setFontColor()));
    connect(ui->radioRed, SIGNAL(clicked()), this, SLOT(do_setFontColor()));
}


Dialog::~Dialog()
{
    delete ui;
}

/*
 * 设置斜体
 */
void Dialog::on_chkBoxItalic_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked)
    {
        QFont plainFont = ui->plainTextEdit->font();
        plainFont.setItalic(true);
        ui->plainTextEdit->setFont(plainFont);
    }
    else if (arg1 == Qt::Unchecked)
    {
        QFont plainFont = ui->plainTextEdit->font();
        plainFont.setItalic(false);
        ui->plainTextEdit->setFont(plainFont);
    }
}

/*
 * 设置下划线
 */
void Dialog::on_chkBoxUnder_checkStateChanged(const Qt::CheckState &arg1)
{
     if (arg1 == Qt::Checked)
    {
        QFont plainFont = ui->plainTextEdit->font();
        plainFont.setUnderline(true);
        ui->plainTextEdit->setFont(plainFont);
    }
    else if (arg1 == Qt::Unchecked)
    {
        QFont plainFont = ui->plainTextEdit->font();
        plainFont.setUnderline(false);
        ui->plainTextEdit->setFont(plainFont);
    }

}


/*
 * 设置粗体
 */
void Dialog::on_chkBoxBold_checkStateChanged(const Qt::CheckState &arg1)
{
    if (arg1 == Qt::Checked)
    {
        QFont plainFont = ui->plainTextEdit->font();
        plainFont.setBold(true);
        ui->plainTextEdit->setFont(plainFont);
    }
    else if (arg1 == Qt::Unchecked)
    {
        QFont plainFont = ui->plainTextEdit->font();
        plainFont.setBold(false);
        ui->plainTextEdit->setFont(plainFont);
    }

}


void Dialog::on_btnClear_clicked()
{
    ui->plainTextEdit->clear();
}


void Dialog::on_btnOK_clicked()
{
    qInfo() << ui->plainTextEdit->toPlainText();
}


void Dialog::on_btnExit_clicked()
{
    exit(0);
}

void Dialog::do_setFontColor()
{
    QPalette plet = ui->plainTextEdit->palette();
    if (ui->radioBlue->isChecked())
    {
        plet.setColor(QPalette::Text, Qt::blue);
    }
    else if (ui->radioRed->isChecked())
    {
        plet.setColor(QPalette::Text, Qt::red);
    }
    else if (ui->radioBlack->isChecked())
    {
        plet.setColor(QPalette::Text, Qt::black);
    }
    else
        plet.setColor(QPalette::Text, Qt::black);

    ui->plainTextEdit->setPalette(plet);
}