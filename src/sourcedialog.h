#ifndef SOURCEDIALOG_H
#define SOURCEDIALOG_H

#include <QDialog>

namespace Ui {
class SourceDialog;
}

class SourceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SourceDialog(QWidget *parent = nullptr);
    ~SourceDialog();

private slots:
    // func. Close dialog window, proceed to MainWindow (ViewWindow)
    void on_closeButton_clicked();

private:
    Ui::SourceDialog *ui;
};

#endif // SOURCEDIALOG_H
