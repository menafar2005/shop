#include "editdialog.h"
#include "ui_editdialog.h"
#include "queue.h"

#include <QFileDialog>
#include <QMessageBox>

#include <vector>

EditDialog::EditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDialog)
{
    ui->setupUi(this);
}

EditDialog::~EditDialog()
{
    delete ui;
}

/*  it was the most difficult part of the entire project so there might be some problems caused
    by not proper testing.  */

void EditDialog::cearAllLabels()
{
    ui->nameField->setText("");
    ui->typeField->setText("");
    ui->subField->setText("");
    ui->radiusField->setText("");
    ui->weightField->setText("");
    ui->moonsField->setText("");
    ui->populationField->setText("");
    ui->rotationField->setText("");
    ui->temperatureField->setText("");
    ui->imageField->setText("");
}

void EditDialog::totalWipe() {
    cearAllLabels();
    ui->mainbox->clear();
}

void EditDialog::loadLabels()
{
    QString thisString = mainContainer[localWideIndex];
    QStringList thisVector = thisString.split(";");

    ui->nameField->setText(thisVector[0]);
    ui->typeField->setText(thisVector[1]);
    ui->subField->setText(thisVector[2]);
    ui->radiusField->setText(thisVector[3]);
    ui->weightField->setText(thisVector[4]);
    ui->moonsField->setText(thisVector[5]);
    ui->populationField->setText(thisVector[6]);
    ui->rotationField->setText(thisVector[7]);
    ui->temperatureField->setText(thisVector[8]);
    ui->imageField->setText(thisVector[9]);
}

void EditDialog::on_openDBButton_clicked()
{
    QString openFileFilter = "Text File (*.txt) ;; CSV File (*.csv) ;; All File (*.*)";
    QString openFilePathNew = QFileDialog::getOpenFileName(this,"Open a file","/",openFileFilter);

    QFile file(openFilePathNew);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::information(this,"Open uncomplete","openDB::The file wasn't chosen!\n(Code ER:1)");
        openFilePathNew=NULL;
        file.close();
        return;
    }
    else
    {
        QFileInfo thisFile(openFilePathNew);
        if (thisFile.suffix()!="txt" && thisFile.suffix()!="csv")
        {
            QMessageBox::information(this,"Open uncomplete","openDB::The file has wrong type!\n(Code ER:2)");
            openFilePathNew=NULL;
            file.close();
            return;
        }
        QTextStream in(&file);
        totalWipe();
        do
        {
            QString fileLine = in.readLine();
            if (fileLine.count(";") < 9) {
                openFilePath=NULL;
                file.close();
                return;
            }
            QStringList lineList = fileLine.split(";");
            if (lineList.length()<10 || lineList.length()%10!=0)
                {
                totalWipe();
                fileLine=NULL;
                lineList.clear();
                mainContainer.clear();
                QMessageBox::information(this,"Parsing unfinished","openDB::Parsing error, lacking required ';'!\n(Code ER:2)");
                openFilePathNew=NULL;
                file.close();
                return;
                }
            if (lineList.contains(" ") || lineList.contains(""))
            {
                QMessageBox::information(this,"Parsing unfinished","openDB::Some parameters are not specified!\n(Code WR:4)");
            }
            mainContainer.push_back(fileLine);
            ui->mainbox->addItem(fileLine);
        } while (!in.atEnd());
        if (!openFilePathNew.isNull())
        {
            ui->saveChangesButton->setText("Change This Object");
            ui->openDBButton->setEnabled(0);
            ui->mergeButton->setEnabled(1);
            openFilePath = openFilePathNew;
        }
        //so the main idea of this editing mode is its ability to add new object to database. so in order to create new object
        //one must select "<add>" item of list and then save the labels - not very convenient yet there're worse ways
        ui->mainbox->addItem("<add>");
        localWideIndex = 0;
        loadLabels();
        file.close();
        ui->deleteObjectButton->setEnabled(1);
        ui->saveChangesButton->setEnabled(1);
    }
}

//to save changes OF THIS PARTICULAR OBJECT - might be changes or completely new object
void EditDialog::on_saveChangesButton_clicked()
{
    QString localline;
    if(ui->nameField->text().isEmpty() || ui->typeField->text().isEmpty() || ui->subField->text().isEmpty()
            || ui->radiusField->text().isEmpty() || ui->weightField->text().isEmpty() || ui->moonsField->text().isEmpty() ||
            ui->populationField->text().isEmpty() || ui->rotationField->text().isEmpty() || ui->temperatureField->text().isEmpty() ||
            ui->imageField->text().isEmpty())
    {
        QMessageBox::information(this,"Warning","saveChanges::Some fields are empty!\nCode WR:ADD");
        if(ui->nameField->text().isEmpty())
            ui->nameField->setText("Unknown");
        if(ui->typeField->text().isEmpty())
            ui->typeField->setText("Unknown");
        if(ui->subField->text().isEmpty())
            ui->subField->setText("Unknown");
        if(ui->radiusField->text().isEmpty())
            ui->radiusField->setText("Unknown");
        if(ui->weightField->text().isEmpty())
            ui->weightField->setText("Unknown");
        if(ui->moonsField->text().isEmpty())
            ui->moonsField->setText("Unknown");
        if(ui->populationField->text().isEmpty())
            ui->populationField->setText("Unknown");
        if(ui->rotationField->text().isEmpty())
            ui->rotationField->setText("Unknown");
        if(ui->temperatureField->text().isEmpty())
            ui->temperatureField->setText("Unknown");
        if(ui->imageField->text().isEmpty())
            ui->imageField->setText("none");
    }
    localline=localline+ui->nameField->text()+";"+ui->typeField->text()+";"+ui->subField->text()+
            ";"+ui->radiusField->text()+";"+ui->weightField->text()+";"+ui->moonsField->text()+";"+ui->populationField->text()+";"+
            ui->rotationField->text()+";"+ui->temperatureField->text()+";"+ui->imageField->text();
    if (localWideIndex<mainContainer.size())
    {
        mainContainer[localWideIndex]=localline;
        ui->mainbox->setItemText(localWideIndex,localline);
    }
    else
    {
        mainContainer.push_back(localline);
        ui->mainbox->setItemText(localWideIndex,localline);
        ui->mainbox->addItem("<add>");
        ui->deleteObjectButton->setEnabled(1);
    }
    QMessageBox::information(this,"Success","This object was successefully (re)loaded!");
}

void EditDialog::on_deleteObjectButton_clicked()
{
    mainContainer.erase(mainContainer.begin()+localWideIndex);
    ui->mainbox->removeItem(localWideIndex);
    QMessageBox::information(this,"Success","deleteObject::Object deleted!");
}

void EditDialog::on_mainbox_currentIndexChanged(int index)
{
    if (index == ui->mainbox->count()-1) {
        ui->deleteObjectButton->setEnabled(0);
        ui->saveChangesButton->setText("Add object");
    }
    else {
        ui->deleteObjectButton->setEnabled(1);
        ui->saveChangesButton->setText("Change This Object");
    }
    if(mainContainer.size()==0)
        ui->deleteObjectButton->setEnabled(0);
    if(index<mainContainer.size())
    {
        localWideIndex = index;
        ui->deleteObjectButton->setEnabled(1);
    }
    else
    {
        if (index==mainContainer.size())
        {
            localWideIndex = index;
            cearAllLabels();
            return;
        }
        cearAllLabels();
        ui->deleteObjectButton->setEnabled(0);
        return;
    }
    loadLabels();
}

void EditDialog::on_saveDBButton_clicked()
{
    QFile localFile(openFilePath);
    if(!localFile.open(QFile::WriteOnly|QFile::Truncate))
    {
        QMessageBox::warning(this,"Warning","SaveAs::The file wasn't chosen!\n(Code ER:1)");
        openFilePath=NULL;
        return;
    }
    QTextStream out(&localFile);
    for (size_t i = 0; i<mainContainer.size();i++)
    {
        QString ThisLine = mainContainer[i];
        out << ThisLine << "\n";
    }
    localFile.close();
    QMessageBox::information(this,"Success","Database saved!");
    this->close();
}

void EditDialog::on_mergeButton_clicked()
{
    QString secondOpenFileFilter = "Text File (*.txt) ;; CSV File (*.csv) ;; All File (*.*)";
    QString secondOpenFilePath = QFileDialog::getOpenFileName(this,"Open a file","/",secondOpenFileFilter);
    QFile file(secondOpenFilePath);
    ui->mainbox->setCurrentIndex(0);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::information(this,"Open uncomplete","merge::The file wasn't chosen!\n(Code ER:1)");
        secondOpenFilePath=NULL;
        file.close();
        return;
    }
    QFileInfo thisFile(secondOpenFilePath);
    if (thisFile.suffix()!="txt" && thisFile.suffix()!="csv")
    {   QMessageBox::information(this,"Open uncomplete","merge::The file has wrong type!\n(Code ER:2)");
        secondOpenFilePath=NULL;
        file.close();
        return;   }
    QTextStream in(&file);
    int i=0;
    while(!in.atEnd())
    {
        QString fileLine = in.readLine();
        QStringList lineList = fileLine.split(";");

        if (lineList.length()<10 || lineList.length()%10!=0)
            {
            fileLine=NULL;
            lineList.clear();
            mainContainer.clear();
            QMessageBox::information(this,"Parsing unfinished","merge::Parsing error, lacking required ';'!!\n(Code ER:2)");
            secondOpenFilePath=NULL;
            file.close();
            return;
            }
        if (lineList.contains(" ") || lineList.contains(""))
            QMessageBox::information(this,"Parsing unfinished","merge::Some parameters are not specified!\n(Code WR:4)");
        if(i == 0)
        {
            ui->mainbox->removeItem(mainContainer.size());
            i=1;
        }
        mainContainer.push_back(fileLine);
        ui->mainbox->addItem(fileLine);

    }
    file.close();
    localWideIndex=0;
    ui->saveChangesButton->setEnabled(1);
    ui->deleteObjectButton->setEnabled(1);
}

void EditDialog::on_openImageButton_clicked()
{
    ui->imageField->clear();
    QString openFileFilter = "PNG File (*.png) ;; Image File (*.jpeg *.jpg *.png *.bmp *.bwm5)";
    QString openFilePath = QFileDialog::getOpenFileName(this,"Select a file","/",openFileFilter);
    QFileInfo thisFile(openFilePath);
    if(!thisFile.exists())
    {
        QMessageBox::information(this,"Image was not found","openImage::File does not exist!\n(Code ER:IMAGE)");
        return;
    }
    ui->imageField->setText(openFilePath);
}
