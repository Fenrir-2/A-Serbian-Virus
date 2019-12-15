#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <clipboard_hijacker.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(QApplication::clipboard(),SIGNAL(dataChanged()),this,&Clipboard_hijacker::clipboardChanged());

//connect(QApplication::clipboard(), SIGNAL(dataChanged()),this, SLOT(processClipboardChange()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

