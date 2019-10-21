#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionHelp_triggered()
{
    HelpWindow* h = new HelpWindow(nullptr);
    h->show();
    h->setFocus();
}

void MainWindow::on_actionQuit_triggered()
{
    close();
}

