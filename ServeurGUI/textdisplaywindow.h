#ifndef CLIPBOARDWINDOW_H
#define CLIPBOARDWINDOW_H

#include <QDialog>

namespace Ui {
  class ClipboardWindow;
}

class TextDisplayWindows : public QDialog
{
  Q_OBJECT

public:
  explicit TextDisplayWindows(QWidget *parent = nullptr, QString = "");
  ~TextDisplayWindows();

private:
  Ui::ClipboardWindow *ui;
};

#endif // CLIPBOARDWINDOW_H
