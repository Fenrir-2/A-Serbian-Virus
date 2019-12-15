#ifndef CLIPBOARDWINDOW_H
#define CLIPBOARDWINDOW_H

#include <QDialog>

namespace Ui {
  class ClipboardWindow;
}

class ClipboardWindow : public QDialog
{
  Q_OBJECT

public:
  explicit ClipboardWindow(QWidget *parent = nullptr);
  ~ClipboardWindow();

private:
  Ui::ClipboardWindow *ui;
};

#endif // CLIPBOARDWINDOW_H
