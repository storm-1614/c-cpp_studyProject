#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

  private slots:
    void on_btnClose_clicked();

    void on_btnSelect_clicked();

  private:
    Ui::MainWindow *ui;
    std::vector<QString> List = {"Sele", "Basic", "da"};
};
#endif // MAINWINDOW_H
