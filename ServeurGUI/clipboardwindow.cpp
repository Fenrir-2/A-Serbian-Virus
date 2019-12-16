#include "clipboardwindow.h"
#include "ui_clipboardwindow.h"

ClipboardWindow::ClipboardWindow(QWidget *parent, QString clip) :
  QDialog(parent),
  ui(new Ui::ClipboardWindow)
{
  ui->setupUi(this);
  this->ui->clipboardBrowser->setText(clip);
}

ClipboardWindow::~ClipboardWindow()
{
  delete ui;
}
