#include "clipboardwindow.h"
#include "ui_clipboardwindow.h"

ClipboardWindow::ClipboardWindow(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ClipboardWindow)
{
  ui->setupUi(this);
}

ClipboardWindow::~ClipboardWindow()
{
  delete ui;
}
