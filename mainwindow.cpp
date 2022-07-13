#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //where you define functionality of the application
    ui->setupUi(this); //sets up user interface
    this->setCentralWidget(ui->MaintextEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered() //When the New action is clicked
{
    currentFile.clear(); //Clear the Current File Name
    ui->MaintextEdit->setText(QString()); //Set the TextEdit to Empty
}


void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file"); //Opens a Dialog to open a file and stores the input name in fileName
    QFile file(fileName); //Object for reading and writing files
    currentFile = fileName;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)) //Try to open the file as read-only or as text, otherwise open a message box
    {
        QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString()); //warning cannot open file: "*more specific information on error*"
        return;
    }
    setWindowTitle(fileName); //sets the title of the window to the name of the open file
    QTextStream in(&file); //Creates a text stream
    QString text = in.readAll(); //get everything from the text stream
    ui->MaintextEdit->setText(text);
    file.close();
}


void MainWindow::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save As"); //Opens a Dialog to save the file and stores the input name in fileName
    QFile file(fileName); //Object for reading and writing files
    if(!file.open(QIODevice::WriteOnly | QFile::Text)) //Try to open the file as write-only or as text, otherwise open a message box
    {
        QMessageBox::warning(this, "Warning", "Cannot save file : " + file.errorString()); //warning cannot save file: "*more specific information on error*"
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->MaintextEdit->toPlainText(); //converts everything in widget to text and stores in text string
    out << text; //pushes text into output text stream
    file.close();
}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer; //Creates a printer object that allows interaction with printers on network
    printer.setPrinterName("Printer Name"); //can put printer name in here
    QPrintDialog pDialog(&printer, this); //is a printer dialog that allows the user to select the printer they want to use
    if(pDialog.exec() == QDialog::Rejected) //check if we were able to connect to a printer without any error
    {
        QMessageBox::warning(this, "Warning", "Cannot Access Printer");
        return;
    }
    ui->MaintextEdit->print(&printer);
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->MaintextEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->MaintextEdit->paste();
}


void MainWindow::on_actionCut_triggered()
{
    ui->MaintextEdit->cut();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->MaintextEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->MaintextEdit->redo();
}

