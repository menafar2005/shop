#ifndef CSVVIEW_H
#define CSVVIEW_H

#include <QDialog>

namespace Ui {
class CsvView;
}

class CsvView : public QDialog
{
    Q_OBJECT

public:
    // QString list stores which csv-formated text to show
    explicit CsvView(QWidget *parent = nullptr, QString list = "");
    ~CsvView();

private slots:
    // func. Close dialog window, proceed to MainWindow (ViewWindow)
    void on_closeButton_clicked();

private:
    Ui::CsvView *ui;
};

#endif // CSVVIEW_H
