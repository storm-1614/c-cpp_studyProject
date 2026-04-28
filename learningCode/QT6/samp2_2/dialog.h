#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui
{
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

  public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog() override;

  private slots:
    void on_chkBoxItalic_stateChanged(int arg1);

    void on_chkBoxUnder_checkStateChanged(const Qt::CheckState &arg1);

    void on_chkBoxBold_checkStateChanged(const Qt::CheckState &arg1);

    void on_radioBlue_clicked();

    void on_radioRed_clicked();

    void on_radioBlack_clicked();

    void on_btnClear_clicked();

    void on_btnOK_clicked();

    void on_btnExit_clicked();

  private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
