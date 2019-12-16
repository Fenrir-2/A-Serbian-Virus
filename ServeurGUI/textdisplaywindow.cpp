#include "textdisplaywindow.h"
#include "ui_clipboardwindow.h"

TextDisplayWindows::TextDisplayWindows(QWidget *parent, QString clip) :
  QDialog(parent),
  ui(new Ui::ClipboardWindow)
{
  ui->setupUi(this);
  this->ui->clipboardBrowser->setText(clip);
}

TextDisplayWindows::~TextDisplayWindows()
{
  delete ui;
}
