#include "createdialog.h"
#include "ui_createdialog.h"

#include "queue.h"

#include <QMessageBox>
#include <QFileDialog>

CreateDialog::CreateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateDialog)
{
    ui->setupUi(this);
}

CreateDialog::~CreateDialog()
{
    delete ui;
}

void CreateDialog::on_createNewDBButton_clicked()
{
    //check if textbrowser is empty - this is a sign that it WAS CLOSED or SAVED
    if (!ui->staticLabel2->toPlainText().isEmpty())
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"Action required","You have unsaved progress!\nDo you want to proceed and DELETE this database?",QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
           totalWipe();
        else return;
    }
}

void CreateDialog::on_saveDBButton_clicked()
{
    if (containContent.size()>0)
    {
        //stage 1 - open SaveFileDialog (step 5.1)
        QString saveFileFilter = "Text File (*.txt) ;; CSV File (*.csv) ;; All File (*.*)";
        QString saveFilePath = QFileDialog::getSaveFileName(this,"Save file","/",saveFileFilter);

        //stage 2 - choose file by the path (step 5.2)
        QFile file(saveFilePath);

        //check whether the file is avaiable
        if(!file.open(QFile::WriteOnly | QFile::Text))
        {
            QMessageBox::information(this,"Saving uncomplete","saveDB::The file wasn't chosen!\n(Code ER:1)");
            saveFilePath=NULL;
            return;
        }

        //stage 3 - writing the info into the file (step 5.3)
        QTextStream out(&file);
        for (size_t i = 0; i<locallength;i++)
        {
            QString thisLine = containContent.getSpecific(i);
            out << thisLine << "\n";
        }

        //stage 4 - closing the file and wipe all the information (step 5.4)
        file.close();
        totalWipe();
    }
    else QMessageBox::information(this,"Saving uncomplete","saveDB::Database is empty!\n(Code ER:6)");
}

void CreateDialog::on_addObjectButton_clicked()
{
    //stage 1 - check if fields are not empty - if so, set default param. (step 6.1)
    QString localLine;
    if(ui->nameField->text().isEmpty() || ui->typeList->currentText().isEmpty() || ui->subtypeList->currentText().isEmpty()
            || ui->radiusField->text().isEmpty() || ui->weightField->text().isEmpty() || ui->moonsField->text().isEmpty() ||
            ui->populationField->text().isEmpty() || ui->rotationField->text().isEmpty() || ui->temperatureField->text().isEmpty() ||
            ui->imageField->text().isEmpty())
    {
        QMessageBox::information(this,"Add object uncomplete","addObject::Some fields are empty!\n(Code WR:ADD)");
        if(ui->nameField->text().isEmpty())
            ui->nameField->setText("Unknown");
        if(ui->typeList->currentText().isEmpty())
            ui->typeList->setCurrentIndex(10);
        if(ui->subtypeList->currentText().isEmpty())
            ui->subtypeList->setCurrentText("Unknown");
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

    //stage 2 - create a line consisting of these parameters (step 6.2)
    localLine=localLine+ui->nameField->text()+";"+ui->typeList->currentText()+";"+ui->subtypeList->currentText()+
            ";"+ui->radiusField->text()+";"+ui->weightField->text()+";"+ui->moonsField->text()+";"+ui->populationField->text()+";"+
            ui->rotationField->text()+";"+ui->temperatureField->text()+";"+ui->imageField->text();

    //stage 3 - write lines into the queue container (step 6.3)
    containContent.push(localLine);
    //increasing total length;
    locallength++;
    //update textbrowser
    updateTextWhole(localLine);
    clearLabels();
}

void CreateDialog::on_clearFieldsButton_clicked()
{
    clearLabels();
}

void CreateDialog::on_applyButton_clicked()
{
    //so if we need to firstly save then close is calls the function to save database and closes the app.
    on_saveDBButton_clicked();
    this->close();
}

void CreateDialog::on_closeButton_clicked()
{
    //if there is no file inside the textbox -> so there is no database which is being edited.
    if (!ui->staticLabel2->toPlainText().isEmpty())
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"Action required","You have unsaved progress!\nDo you want to SAVE the progress?",QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
           on_saveDBButton_clicked();
           this->close();
           return;
        }
    }
    this->close();
}

void CreateDialog::clearLabels()
{
    ui->nameField->clear();
    ui->rotationField->clear();
    ui->populationField->clear();
    ui->temperatureField->clear();
    ui->tempSlider->setValue(0);
    ui->popSlider->setValue(0);
    ui->rotationField->clear();
    ui->imageField->clear();
    ui->subtypeList->clear();
    ui->typeList->setCurrentIndex(0);
    ui->radiusField->clear();
    ui->moonsField->clear();
    ui->weightField->clear();
}

void CreateDialog::on_typeList_currentIndexChanged(int index)
{
    //so to arrange the subtype list obiously if type changes so do the subtype this is VERY plain approach nevertheless it works perfectly
    QComboBox *sl = ui->subtypeList;

    if(index==0)
    {
        sl->clear();
    }
    if(index==1)
    {
        sl->clear();
        sl->addItem("Blue giant");
        sl->addItem("Red giant");
        sl->addItem("Orange giant");
        sl->addItem("Blue dwarf");
        sl->addItem("Red dwarf");
        sl->addItem("Yellow dwarf");
        sl->addItem("Brown dwarf");
        sl->addItem("White dwarf");
        sl->addItem("Neutron");
        sl->addItem("Blue supergiant");
        sl->addItem("Red supergiant");
        sl->addItem("Magenta dwarf");
        sl->addItem("Unlisted");
    }
    if(index==2)
    {
        sl->clear();
        sl->addItem("Exoplanet");
        sl->addItem("Rocky");
        sl->addItem("Greenhouse");
        sl->addItem("Gas giant");
        sl->addItem("Artificial");
        sl->addItem("Ocean world");
        sl->addItem("Lava world");
        sl->addItem("Rogue");
        sl->addItem("Unlisted");
    }
    if(index==3)
    {
        sl->clear();
        sl->addItem("Large (<200km");
        sl->addItem("Medium (<3km)");
        sl->addItem("Small (<100m)");
    }
    if(index==4)
    {
        sl->clear();
        sl->addItem("Great");
        sl->addItem("Sungrazing");
        sl->addItem("Unusual");
        sl->addItem("Centaurs");
        sl->addItem("Huge sized");
    }
    if(index==5)
    {
        sl->clear();
        sl->addItem("Elleptical");
        sl->addItem("Spiral");
        sl->addItem("Irregular");
        sl->addItem("Lenticular");
        sl->addItem("Barred spiral");
        sl->addItem("Peculiar");
        sl->addItem("Unlised");
    }
    if(index==6)
    {
        sl->clear();
        sl->addItem("Flux");
        sl->addItem("Diffuse");
        sl->addItem("Planetary");
        sl->addItem("Protoplanetary");
        sl->addItem("Supernova remnants");
        sl->addItem("Unlised");
    }
    if(index==7)
    {
        sl->clear();
        sl->addItem("Standard");
    }
    if(index==8)
    {
        sl->clear();
        sl->addItem("Dreadnought");
        sl->addItem("Cruiser");
        sl->addItem("Destroyer");
        sl->addItem("Frigate");
        sl->addItem("Corvette");
        sl->addItem("Fighter");
        sl->addItem("Bombarder");
        sl->addItem("Cruise ship");
        sl->addItem("Stealth");
        sl->addItem("Cargo ship");
        sl->addItem("Unknown");
    }
    if (index==9){
        sl->clear();
        sl->addItem("Stellar");
        sl->addItem("Intermediate");
        sl->addItem("Supermassive");
        sl->addItem("Miniature");
        sl->addItem("Unlisted");
    }
    if(index==10)
    {
        sl->clear();
        sl->addItem("Unknown subtype");
    }
}

void CreateDialog::on_chooseFileButton_clicked()
{
    ui->imageField->clear();
    QString openFileFilter = "PNG File (*.png) ;; Image File (*.jpeg *.jpg *.png *.bmp *.bwm5)";
    QString openFilePath = QFileDialog::getOpenFileName(this,"Select a file","/",openFileFilter);
    QFileInfo thisFile(openFilePath);
    if(!thisFile.exists())
    {
        QMessageBox::information(this,"Image was not found","chooseFile::File does not exist!\n(Code ER:IMAGE)");
        return;
    }
    ui->imageField->setText(openFilePath);
}

void CreateDialog::totalWipe()
{
    clearLabels();
    ui->staticLabel2->clear();
    locallength = 0;
    containContent.clearAll();
}

void CreateDialog::updateTextWhole(QString string)
{
    ui->staticLabel2->moveCursor(QTextCursor::End);
    ui->staticLabel2->insertPlainText(string+"\n");
    ui->staticLabel2->moveCursor(QTextCursor::End);
}

void CreateDialog::on_popSlider_valueChanged(int value)
{
    //we have slider on creationform which utterly arranges the value. it might be more quick and cozy
    QString translated = QString::number(value);
    if (translated != "0")
        translated = translated+"0";
    ui->populationField->setText(translated);
}

void CreateDialog::on_tempSlider_valueChanged(int value)
{
    //the same as before - only difference is that Temperature is limited within -273 .. 10000 great!
    ui->temperatureField->setText(QString::number(value)+"C");
}
