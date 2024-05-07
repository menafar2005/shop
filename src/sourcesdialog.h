#ifndef SOURCESDIALOG_H
#define SOURCESDIALOG_H

#include <QDialog>

namespace Ui {
class sourcesdialog;
}

class sourcesdialog : public QDialog
{
    Q_OBJECT

public:
    explicit sourcesdialog(QWidget *parent = nullptr);
    ~sourcesdialog();

private:
    Ui::sourcesdialog *ui;
};

#endif // SOURCESDIALOG_H
