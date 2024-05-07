#include "csvview.h"
#include "ui_csvview.h"

CsvView::CsvView(QWidget *parent,QString line):
    QDialog(parent),
    ui(new Ui::CsvView)
{
    ui->setupUi(this);
    ui->textBrowser->setPlainText(line);
}

CsvView::~CsvView()
{
    delete ui;
}

void CsvView::on_closeButton_clicked()
{
    this->close();
}
