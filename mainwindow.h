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
    void onControllerStarted();
    void onControllerStopped();

    void on_actionGenerate_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
