#include "sourcedialog.h"
#include "ui_sourcedialog.h"

SourceDialog::SourceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SourceDialog)
{
    ui->setupUi(this);
}

SourceDialog::~SourceDialog()
{
    delete ui;
}

void SourceDialog::on_closeButton_clicked()
{
    this->close();
}

