#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "aboutdialog.h"
#include "editdialog.h"
#include "createdialog.h"
#include "sourcedialog.h"
#include "csvview.h"

#include <QPixmap>
#include <QFileDialog>
#include <QMessageBox>
#include <QFontDatabase>

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

/*  this line below typically visualize how should the csv-database one line look like.
    name;type;subtype;radius;weight;moons;population;rotation;temperature;image
    whatever deviation met will result in program complete collapse (now it's prevented)    */

void MainWindow::on_openMenuBar_triggered()
{
    //stage 1 - open file dialog and get the name, full path. (step 1.1)
    clearLabels();
    ui->objectsList->clear();
    QString openFileFilter = "Text File (*.txt) ;; CSV File (*.csv) ;; All File (*.*)";
    QString openFilePath = QFileDialog::getOpenFileName(this,"Open a file","/",openFileFilter);

    //stage 2 - opening file. (step 1.2)
    QFile file(openFilePath);
    //check if file was actually opened
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {   QMessageBox::information(this,"Open uncomplete","open::The file wasn't chosen!!\n(Code ER:1)");
        openFilePath=NULL;
        return;
    }
    else
    {
        QFileInfo ThisFile(openFilePath);
        //check file format if it isn't txt - full function stop. (step 1.2.ER)
        if (ThisFile.suffix()!="txt" && ThisFile.suffix()!="csv")
        {   QMessageBox::information(this,"Open uncomplete","open::The file has wrong type!\n(Code ER:2)");
            openFilePath=NULL;
            return;
        }
        QTextStream in(&file);
        //stage 3 - reading file. (step 1.3)
        do
        {
            QString fileLine = in.readLine();
            if (fileLine.count(";") < 9) {
                openFilePath=NULL;
                file.close();
                return;
            }
            QStringList lineList = fileLine.split(";");
            //single try to prevent program work with wrong csv file (step 1.3.ER)
            if (lineList.length()<10 || lineList.length()%10!=0)
                {
                QMessageBox::information(this,"Parsing unfinished","open::Parsing error, lacking required ';'!\n(Code ER:3)");
                file.close();
                clearLabels();
                openFilePath=NULL;
                fileLine=NULL;
                lineList.clear();
                wideList.clear();
                return;
                }
            //check if file has empty fields - throws a warning (step 1.3.ER2)
            if (lineList.contains(" ") || lineList.contains(""))
                QMessageBox::information(this,"Parsing unfinished","open::Some parameters are not specified!\n(Code WR:4)");
            wideList.append(fileLine);
            ui->objectsList->addItem(lineList[1]+" ("+lineList[2]+") named "+lineList[0]);
        } while (!in.atEnd());
        //close file (it isn't required cause it is closed in ~destructor()
        file.close();
        //set default (starting index)
        wideIndex = 0;

        //stage 4 - setting up the labels. (step 1.4)
        setLabels();
        //somekind of crutch - to prevent out of range
        if (wideList.length()!=1)
        {ui->nextObjectButton->setEnabled(1);
        ui->prevObjectButton->setEnabled(1);}
    }
}

void MainWindow::on_exitMenuBar_triggered()
{ QCoreApplication::exit(); }

void MainWindow::on_closeMenuBar_triggered()
{
    if (wideList.isEmpty())
        QMessageBox::information(this,"Warning","close::The list is empty or the file wasn't opened.\nNo need to close anything!\n(Code WR:5)");
    clearLabels();
    ui->nextObjectButton->setEnabled(0);
    ui->prevObjectButton->setEnabled(0);
}

void MainWindow::on_nextObjectButton_clicked()
{
    //stage 1 - increment index (step 2.1)
    wideIndex++;
    //stage 2 - check if index is bigger than maxindex - then index=0 so there is no out of range (step 2.2)
    if (wideIndex==wideList.length())
        wideIndex=0;
    //stage 3 - set fields (step 2.3)
    setLabels();
    //change combobox's current index - current chosen object
    ui->objectsList->setCurrentIndex(wideIndex);
}

void MainWindow::on_prevObjectButton_clicked()
{
    //stage 1 - decrement index (step 3.1)
    wideIndex--;
    //stage 2 - check if index is lesser than minindex - then index=maxindex so there is no out of range (step 3.2)
    if (wideIndex<0)
        wideIndex=wideList.length()-1;
    //stage 3 set fields (step 3.3)
    setLabels();
    //change combobox's current index - current chosen object
    ui->objectsList->setCurrentIndex(wideIndex);
}

void MainWindow::on_objectsList_currentIndexChanged(int index)
{
    //stage 1 - change selected object by the index in combobox (step 4.1)
    wideIndex = index;
    //stage 2 - set labels if wideindex is within range ">0"
    if (0<wideIndex && wideIndex<(wideList.length()))
        setLabels();
}

void MainWindow::setLabels()
{
    //index is universal, so it is changed depending on button and list funcs.
    //this func. is mere sets the labels of the line(one string) with this index
    QString thisString = wideList[wideIndex]; //chosing this object out of all
    QStringList thisList = thisString.split(";"); //split this object by parameters

    //setting up the texts in labels
    ui->nameObject->setText(thisList[0]);
    ui->typeObject->setText(thisList[1]);
    ui->subTypeObject->setText(thisList[2]);
    ui->radiusObject->setText(thisList[3]);
    ui->weightObject->setText(thisList[4]);
    ui->moonsObject->setText(thisList[5]);
    ui->populationObject->setText(thisList[6]);
    ui->rotationObject->setText(thisList[7]);
    ui->temperatureObject->setText(thisList[8]);

    //setting up the image in pixmap - check whether the file exists
    if (QFile::exists(thisList[9]))
    {   QPixmap image(thisList[9]);
        ui->imageObject->setPixmap(image);    }
    else //if not the code below sets default picture
    {
        QPixmap image(":/images/volume1/iconmark.png");
        ui->imageObject->setPixmap(image);
    }
}

void MainWindow::clearLabels()
{
    //extra tool - required for closing and opening new databases
    //clear all lists and labels
    wideList.clear();
    ui->objectsList->clear();
    ui->objectsList->addItem("Planet named Earth");

    //setting up default names
    ui->nameObject->setText("Earth");
    ui->typeObject->setText("Planet");
    ui->subTypeObject->setText("Exoplanet");
    ui->radiusObject->setText("6371 km");
    ui->weightObject->setText("5.972e24 kg");
    ui->moonsObject->setText("1 (Moon)");
    ui->populationObject->setText("7 500 000 000");
    ui->rotationObject->setText("23:56:04");
    ui->temperatureObject->setText("14 celsius");

    //setting up default images
    QPixmap image(":/images/volume1/planetDefault.png");
    ui->imageObject->setPixmap(image);
}

void MainWindow::on_showAboutMenuBar_triggered()
{
    //simple open new dialog (about dialog)
    AboutDialog aboutdialog;
    //so has forced focus while mainwindow is disabled
    aboutdialog.setModal(true);
    //execution of dialog
    aboutdialog.exec();
}

void MainWindow::on_openEditMenuBar_triggered()
{
    //pretty much the same. BUT it closes current opened csv-base
    clearLabels();
    ui->nextObjectButton->setEnabled(0);
    ui->prevObjectButton->setEnabled(0);
    EditDialog editdialog;
    editdialog.setModal(true);
    editdialog.exec();
}

void MainWindow::on_openCreateMenuBar_triggered()
{
    //exactly the same as one before
    clearLabels();
    ui->nextObjectButton->setEnabled(0);
    ui->prevObjectButton->setEnabled(0);
    CreateDialog createdialog;
    createdialog.setModal(true);
    createdialog.exec();
}

void MainWindow::on_showSourcesMenuBar_triggered()
{
    SourceDialog sourcedialog;
    sourcedialog.setModal(true);
    sourcedialog.exec();
}

void MainWindow::on_openCSVMenuBar_triggered()
{
    QString string = wideList.join("\n");
    CsvView csvview(this,string);
    csvview.setModal(true);
    csvview.exec();
}

