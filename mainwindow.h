#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <controller.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Controller &mController;

    void updateInterfaceMode();

public:
    explicit MainWindow(Controller &c, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnGenerate_clicked();
    void onControllerStarted();
    void onControllerStopped();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
