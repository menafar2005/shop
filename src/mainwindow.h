#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    //funcs. For menu bar's buttons
    void on_openMenuBar_triggered();
    void on_exitMenuBar_triggered();
    void on_closeMenuBar_triggered();

    //funcs. To manipulate view
    void on_nextObjectButton_clicked();
    void on_prevObjectButton_clicked();
    void on_objectsList_currentIndexChanged(int index);

    //funcs. To open other forms, dialogs
    void on_showAboutMenuBar_triggered();
    void on_showSourcesMenuBar_triggered();
    void on_openEditMenuBar_triggered();
    void on_openCreateMenuBar_triggered();
    void on_openCSVMenuBar_triggered();

private:
    Ui::MainWindow *ui;

    //vars. Universal vars to track showing objects of all avaiable
    int wideIndex = 0;
    QStringList wideList;

    //funcs. To clear and set values in fields
    void setLabels();
    void clearLabels();
};
#endif // MAINWINDOW_H
