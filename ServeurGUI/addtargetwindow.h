#ifndef ADDTARGETWINDOW_H
#define ADDTARGETWINDOW_H

#include <QDialog>
#include <QTableWidget>

namespace Ui {
  class addTargetWindow;
}

class AddTargetWindow : public QDialog
{
  Q_OBJECT

public:
  explicit AddTargetWindow(QWidget *parent = nullptr, QTableWidget *table = nullptr);
  ~AddTargetWindow();

private slots:
  void accept();

private:
  Ui::addTargetWindow *ui;
  QTableWidget* table;
};

#endif // ADDTARGETWINDOW_H
