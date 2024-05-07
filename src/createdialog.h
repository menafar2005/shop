#ifndef CREATEDIALOG_H
#define CREATEDIALOG_H

#include <QDialog>
#include "queue.h"

namespace Ui {
class CreateDialog;
}

class CreateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateDialog(QWidget *parent = nullptr);
    ~CreateDialog();

private slots:

    //funcs. Create new database and save it
    void on_createNewDBButton_clicked();
    void on_saveDBButton_clicked();

    //funcs. Add new object to the database and clean all the fields after
    void on_addObjectButton_clicked();
    void on_clearFieldsButton_clicked();

    //funcs. Manage windows. Save database and close, or simply close create window
    void on_applyButton_clicked();
    void on_closeButton_clicked();

    //func. Manage typelist -> subtypelist proper correlation
    void on_typeList_currentIndexChanged(int index);

    //func. Open another file, simplyfied
    void on_chooseFileButton_clicked();

    //funcs. Manage sliders to change values in fields
    void on_tempSlider_valueChanged(int value);
    void on_popSlider_valueChanged(int value);

private:
    Ui::CreateDialog *ui;

    //func. Tools to clear fields and databases
    void clearLabels();
    void totalWipe();

    //func. Update textbrowser
    void updateTextWhole(QString string);

    //vars. Internal var, and object-container
    queue<QString> containContent;
    size_t locallength = 0;
};

#endif // CREATEDIALOG_H
