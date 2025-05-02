#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

#include "devicemanager.h"
#include "consolelogger.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addFridgeButton_clicked();
    void on_addDrillButton_clicked();
    void on_editButton_clicked();
    void on_deleteButton_clicked();
    void on_turnOnAllButton_clicked();

private:
    void updateDeviceList();
    void updateTotalPower();

    Ui::MainWindow *ui;
    std::shared_ptr<ILogger> logger;
    DeviceManager manager;
};

#endif // MAINWINDOW_H
