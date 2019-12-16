#include "addtargetwindow.h"
#include "ui_addtargetwindow.h"

AddTargetWindow::AddTargetWindow(QWidget *parent, QTableWidget* table) :
  QDialog(parent),
  ui(new Ui::addTargetWindow)
{
  ui->setupUi(this);
  this->ui->nameLineEdit->setFocus();
  this->ui->nameLineEdit->keyboardGrabber();
  this->table = table;
}

void AddTargetWindow::accept(){

  this->table->insertRow(this->table->rowCount());

  this->table->setItem(this->table->rowCount()-1, 0, new QTableWidgetItem(this->ui->nameLineEdit->text()));
  this->table->setItem(this->table->rowCount()-1, 1, new QTableWidgetItem(this->ui->ipLineEdit->text()));
  this->table->setItem(this->table->rowCount()-1, 2, new QTableWidgetItem("Disconnected"));

  this->close();
}

AddTargetWindow::~AddTargetWindow()
{
  delete ui;
}
