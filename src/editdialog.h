#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>

namespace Ui {
class EditDialog;
}

class EditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditDialog(QWidget *parent = nullptr);
    ~EditDialog();

private slots:
    //funcs. To manipulate files. Open new, save at the same dir, open another and merge
    void on_openDBButton_clicked();
    void on_saveDBButton_clicked();
    void on_mergeButton_clicked();

    //funcs. To manipulate objects. Save or add object, delete object
    void on_saveChangesButton_clicked();
    void on_deleteObjectButton_clicked();

    //func. Crucial navigator. List at the top
    void on_mainbox_currentIndexChanged(int index);

    //func. To load new image
    void on_openImageButton_clicked();

private:
    Ui::EditDialog *ui;

    //func. Extra tools to clear and set values in fields
    void cearAllLabels();
    void totalWipe();
    void loadLabels();

    //vars. Inner vars to work with editing
    std::vector<QString> mainContainer;
    size_t localWideIndex = 0;
    QString openFilePath;
};

#endif // EDITDIALOG_H
