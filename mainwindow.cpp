#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "refrigerator.h"
#include "drill.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QFont>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , logger(std::make_shared<ConsoleLogger>())
    , manager(logger)
{
    ui->setupUi(this);

    ui->deviceListWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->deleteButton->setEnabled(false);
    ui->editButton->setEnabled(false);

    connect(ui->deviceListWidget, &QListWidget::itemSelectionChanged, [this]() {
        bool hasSelection = ui->deviceListWidget->currentRow() >= 0;
        ui->deleteButton->setEnabled(hasSelection);
        ui->editButton->setEnabled(hasSelection);
    });

    updateDeviceList();
}

MainWindow::~MainWindow() {
    delete ui;
}

// Добавление холодильника
void MainWindow::on_addFridgeButton_clicked() {
    bool ok;
    QString brand = QInputDialog::getText(this, "Добавить холодильник", "Бренд:",
                                          QLineEdit::Normal, "Samsung", &ok);
    if (!ok || brand.isEmpty()) return;

    int power = QInputDialog::getInt(this, "Добавить холодильник", "Мощность (Вт):",
                                     150, 50, 1000, 10, &ok);
    if (!ok) return;

    int capacity = QInputDialog::getInt(this, "Добавить холодильник", "Объем (л):",
                                        300, 100, 1000, 10, &ok);
    if (!ok) return;

    manager.AddDevice(std::make_unique<Refrigerator>("Холодильник", power, brand.toStdString(), capacity));
    updateDeviceList();
}

// Добавление дрели
void MainWindow::on_addDrillButton_clicked() {
    bool ok;
    int power = QInputDialog::getInt(this, "Добавить дрель", "Мощность (Вт):",
                                     800, 100, 2000, 10, &ok);
    if (!ok) return;

    int voltage = QInputDialog::getInt(this, "Добавить дрель", "Напряжение (В):",
                                       220, 12, 380, 1, &ok);
    if (!ok) return;

    int rpm = QInputDialog::getInt(this, "Добавить дрель", "Обороты (RPM):",
                                   3000, 1000, 10000, 100, &ok);
    if (!ok) return;

    manager.AddDevice(std::make_unique<Drill>("Дрель", power, voltage, rpm));
    updateDeviceList();
}

// Редактирование устройства
void MainWindow::on_editButton_clicked() {
    int index = ui->deviceListWidget->currentRow();
    auto& devices = manager.GetDevices();

    if (index < 0 || index >= static_cast<int>(devices.size()) || !devices[index]) return;

    auto& device = devices[index];
    bool updated = false;

    if (auto* fridge = dynamic_cast<Refrigerator*>(device.get())) {
        bool ok;
        QString brand = QInputDialog::getText(this, "Редактировать холодильник", "Бренд:",
                                              QLineEdit::Normal, QString::fromStdString(fridge->GetBrand()), &ok);
        if (!ok) return;

        int power = QInputDialog::getInt(this, "Редактировать холодильник", "Мощность (Вт):",
                                         fridge->GetBasePower(), 50, 1000, 10, &ok);
        if (!ok) return;

        int capacity = QInputDialog::getInt(this, "Редактировать холодильник", "Объем (л):",
                                            fridge->GetCapacity(), 100, 1000, 10, &ok);
        if (!ok) return;

        fridge->UpdateParameters(power, brand.toStdString(), capacity);
        updated = true;

    } else if (auto* drill = dynamic_cast<Drill*>(device.get())) {
        bool ok;
        int power = QInputDialog::getInt(this, "Редактировать дрель", "Мощность (Вт):",
                                         drill->GetBasePower(), 100, 2000, 10, &ok);
        if (!ok) return;

        int voltage = QInputDialog::getInt(this, "Редактировать дрель", "Напряжение (В):",
                                           drill->GetVoltage(), 12, 380, 1, &ok);
        if (!ok) return;

        int rpm = QInputDialog::getInt(this, "Редактировать дрель", "Обороты (RPM):",
                                       drill->GetRPM(), 1000, 10000, 100, &ok);
        if (!ok) return;

        drill->UpdateParameters(power, voltage, rpm);
        updated = true;
    }

    if (updated) {
        QMessageBox::information(this, "Успех", "Параметры устройства обновлены!");
        updateDeviceList();
    }
}

// Удаление устройства
void MainWindow::on_deleteButton_clicked() {
    int index = ui->deviceListWidget->currentRow();
    if (index < 0) return;

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Подтверждение");
    msgBox.setText("Вы уверены, что хотите удалить это устройство?");
    QPushButton* okButton = msgBox.addButton("ОК", QMessageBox::AcceptRole);
    msgBox.addButton("Отмена", QMessageBox::RejectRole);
    msgBox.exec();

    if (msgBox.clickedButton() == okButton) {
        manager.RemoveDevice(index);
        updateDeviceList();
        ui->deviceListWidget->clearSelection();
    }
}

// Включение всех устройств
void MainWindow::on_turnOnAllButton_clicked() {
    if (manager.GetDevices().empty()) {
        QMessageBox::information(this, "Информация", "Нет устройств для включения");
        return;
    }

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Подтверждение");
    msgBox.setText("Включить все устройства?");
    QPushButton* okButton = msgBox.addButton("ОК", QMessageBox::AcceptRole);
    msgBox.addButton("Отмена", QMessageBox::RejectRole);
    msgBox.exec();

    if (msgBox.clickedButton() == okButton) {
        manager.TurnOnAll();
        updateDeviceList();
    }
}

// Обновление списка устройств
void MainWindow::updateDeviceList() {
    ui->deviceListWidget->clear();
    const auto& devices = manager.GetDevices();

    for (const auto& device : devices) {
        auto* item = new QListWidgetItem(QString::fromStdString(device->GetInfo()), ui->deviceListWidget);
        item->setFont(QFont("Arial", 10));

        // Фиолетовый текст для включенных устройств (#8A2BE2)
        if (device->IsOn()) {
            item->setForeground(QColor(138, 43, 226)); // Насыщенный фиолетовый
            item->setFont(QFont("Arial", 10, QFont::Bold));
        }

        // Цвет фона по типу устройства
        if (dynamic_cast<Refrigerator*>(device.get())) {
            item->setBackground(QColor(240, 248, 255)); // Светло-голубой
        } else {
            item->setBackground(QColor(255, 240, 245)); // Светло-розовый
        }
    }

    updateTotalPower();
}

// Обновление общей мощности (исправленная версия)
void MainWindow::updateTotalPower() {
    int total = manager.GetTotalPower();
    int count = manager.GetDevices().size();

    QString textColor = total > 2000 ? "#e74c3c" : "#1e3a8a";

    ui->totalPowerLabel->setText(
        QString("Устройств: <b>%1</b> | Общая мощность: <b>%2 Вт</b>")
            .arg(count).arg(total)
        );

    ui->totalPowerLabel->setStyleSheet(QString(
                                           "QLabel {"
                                           "  color: %1;"
                                           "  font: bold 14px;"
                                           "  padding: 8px;"
                                           "  border-radius: 6px;"
                                           "  background: #e6f7ff;" // Фиксированный голубой фон
                                           "  border: 1px solid #cfe7ff;" // Граница из UI
                                           "}"
                                           ).arg(textColor));
}
