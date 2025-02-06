#include "admin.h"
#include "ui_admin.h"
#include "Service.h"
#include "ServiceUsage.h"
#include "AddService.h"
#include "Editservice.h"
#include <QMessageBox>

using namespace std;

void Admin::manageservices(){
    QAction *searchAction = new QAction(QIcon(":/new/prefix1/Resources/loupe.png"), "Search", this);
    ui->LineEditSearchSer->addAction(searchAction, QLineEdit::LeadingPosition);
    Service::showAllServices(this);
    ui->totalservice->setText(QString::number(Service::total));
    ui->SerTable->horizontalHeader()->setStyleSheet("QHeaderView::section { border: none; }");
    ui->SerTable->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->SerTable->horizontalHeaderItem(ui->SerTable->columnCount() - 1)->setTextAlignment(Qt::AlignCenter);
    ui->SerTable->setColumnWidth(0, 200);
    ui->SerTable->setColumnWidth(1, 200);
    ui->SerTable->setColumnWidth(2, 200);
    ui->SerTable->setColumnWidth(3, 150);
    ui->SerTable->setColumnWidth(4, 150);
    ui->SerTable->verticalHeader()->hide();
    ui->SerTable->setShowGrid(false);

    //sx id
    QRect headerSer = ui->SerTable->visualRect(ui->SerTable->model()->index(0, 0));
    QPushButton* sortidserviceButton = new QPushButton(ui->SerTable);
    sortidserviceButton->setText("");
    sortidserviceButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
    sortidserviceButton->setFixedSize(16, 16);
    sortidserviceButton->setToolTip("Sort by Room ID");
    sortidserviceButton->move(headerSer.right() - 155, headerSer.top() + 3);
    sortidserviceButton->setCheckable(true);
    connect(sortidserviceButton, &QPushButton::toggled, this, [this, sortidserviceButton](bool checked) {
        if (checked) {
            sortidserviceButton->setIcon(QIcon(":/new/prefix1/Resources/sxgiam.png"));
            Service::sortID(false);
            ui->SerTable->clearContents();
            ui->SerTable->setRowCount(0);
            Service::showAllServices(this);
            if (ui->CBSS->currentIndex() == 1 && !ui->LineEditSearchSer->text().isEmpty()){
                sortidserviceButton->setIcon(QIcon(":/new/prefix1/Resources/sxgiam.png"));
                Service::sortID(false);
                ui->SerTable->clearContents();
                ui->SerTable->setRowCount(0);
                Service::searchByID(ui->LineEditSearchSer->text().toStdString(), this);
            }
            if (ui->CBSS->currentIndex() == 2 && !ui->LineEditSearchSer->text().isEmpty()){
                sortidserviceButton->setIcon(QIcon(":/new/prefix1/Resources/sxgiam.png"));
                Service::sortID(false);
                ui->SerTable->clearContents();
                ui->SerTable->setRowCount(0);
                Service::searchByName(ui->LineEditSearchSer->text().toStdString(), this);
            }
        } else {
            sortidserviceButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
            Service::sortID(true);
            ui->SerTable->clearContents();
            ui->SerTable->setRowCount(0);
            Service::showAllServices(this);
            if (ui->CBSS->currentIndex() == 1 && !ui->LineEditSearchSer->text().isEmpty()){
                sortidserviceButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
                Service::sortID(true);
                ui->SerTable->clearContents();
                ui->SerTable->setRowCount(0);
                Service::searchByID(ui->LineEditSearchSer->text().toStdString(), this);
            }
            if (ui->CBSS->currentIndex() == 2 && !ui->LineEditSearchSer->text().isEmpty()){
                sortidserviceButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
                Service::sortID(true);
                ui->SerTable->clearContents();
                ui->SerTable->setRowCount(0);
                Service::searchByName(ui->LineEditSearchSer->text().toStdString(), this);
            }
        }
    });
}

void Admin::manageserviceusages(){
    QAction *searchAction = new QAction(QIcon(":/new/prefix1/Resources/loupe.png"), "Search", this);
    ui->LineEditSearchSerUsage->addAction(searchAction, QLineEdit::LeadingPosition);
    ServiceUsage::showAllServiceUsages(this);
    ui->totalserviceUsage->setText(QString::number(ServiceUsage::total));
    ui->SerUsageTable->horizontalHeader()->setStyleSheet("QHeaderView::section { border: none; }");
    ui->SerUsageTable->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    // ui->SerUsageTable->horizontalHeaderItem(ui->SerUsageTable->columnCount() - 1)->setTextAlignment(Qt::AlignCenter);
    ui->SerUsageTable->setColumnWidth(0, 200);
    ui->SerUsageTable->setColumnWidth(1, 200);
    ui->SerUsageTable->setColumnWidth(2, 200);
    ui->SerUsageTable->setColumnWidth(3, 200);
    ui->SerUsageTable->setColumnWidth(4, 200);
    ui->SerUsageTable->setColumnWidth(5, 200);
    ui->SerUsageTable->verticalHeader()->hide();
    ui->SerUsageTable->setShowGrid(false);
    // QRect headerRect = ui->SerUsageTable->visualRect(ui->SerUsageTable->model()->index(0, 0));

    //sx
    QRect headerSerUsage = ui->SerUsageTable->visualRect(ui->SerUsageTable->model()->index(0, 0));
    QPushButton* sortidserviceusageButton = new QPushButton(ui->SerUsageTable);
    sortidserviceusageButton->setText("");
    sortidserviceusageButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
    sortidserviceusageButton->setFixedSize(16, 16);
    sortidserviceusageButton->setToolTip("Sort by ID");
    sortidserviceusageButton->move(headerSerUsage.right() - 135, headerSerUsage.top() + 3);
    sortidserviceusageButton->setCheckable(true);
    connect(sortidserviceusageButton, &QPushButton::toggled, this, [this, sortidserviceusageButton](bool checked) {
        if (checked) {
            sortidserviceusageButton->setIcon(QIcon(":/new/prefix1/Resources/sxgiam.png"));
            ServiceUsage::sortID(false);
            ui->SerUsageTable->clearContents();
            ui->SerUsageTable->setRowCount(0);
            ServiceUsage::showAllServiceUsages(this);
            if (ui->CBSSUsage->currentIndex() == 1 && !ui->LineEditSearchSerUsage->text().isEmpty()){
                sortidserviceusageButton->setIcon(QIcon(":/new/prefix1/Resources/sxgiam.png"));
                ServiceUsage::sortID(false);
                ui->SerUsageTable->clearContents();
                ui->SerUsageTable->setRowCount(0);
                ServiceUsage::searchByID(ui->LineEditSearchSerUsage->text().toStdString(), this);
            }
            if (ui->CBSSUsage->currentIndex() == 2 && !ui->LineEditSearchSerUsage->text().isEmpty()){
                sortidserviceusageButton->setIcon(QIcon(":/new/prefix1/Resources/sxgiam.png"));
                ServiceUsage::sortID(false);
                ui->SerUsageTable->clearContents();
                ui->SerUsageTable->setRowCount(0);
                ServiceUsage::searchByRoomID(ui->LineEditSearchSerUsage->text().toStdString(), this);
            }
        } else {
            sortidserviceusageButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
            ServiceUsage::sortID(true);
            ui->SerUsageTable->clearContents();
            ui->SerUsageTable->setRowCount(0);
            ServiceUsage::showAllServiceUsages(this);
            if (ui->CBSSUsage->currentIndex() == 1 && !ui->LineEditSearchSerUsage->text().isEmpty()){
                sortidserviceusageButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
                ServiceUsage::sortID(true);
                ui->SerUsageTable->clearContents();
                ui->SerUsageTable->setRowCount(0);
                ServiceUsage::searchByID(ui->LineEditSearchSerUsage->text().toStdString(), this);
            }
            if (ui->CBSSUsage->currentIndex() == 2 && !ui->LineEditSearchSerUsage->text().isEmpty()){
                sortidserviceusageButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
                ServiceUsage::sortID(true);
                ui->SerUsageTable->clearContents();
                ui->SerUsageTable->setRowCount(0);
                ServiceUsage::searchByRoomID(ui->LineEditSearchSerUsage->text().toStdString(), this);
            }
        }
    });
}

void Admin::displayServices(const Service& s) {
    int row = ui->SerTable->rowCount();
    ui->SerTable->insertRow(row);

    ui->SerTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(s.getID())));
    ui->SerTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(s.getName())));
    ui->SerTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(s.getdes())));
    ui->SerTable->setItem(row, 3, new QTableWidgetItem(QString::number(s.getUnitPrice(), 'f', 0)));
    ui->SerTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(s.getis_mandatory()? "Cố định" : "Tự do")));
    QWidget* buttonWidget = new QWidget();

    QPushButton* edit_Ser_btn = new QPushButton();
    edit_Ser_btn->setIcon(QIcon(":/new/prefix1/Resources/edit.png"));
    edit_Ser_btn->setToolTip("Edit this room");
    connect(edit_Ser_btn, &QPushButton::clicked, this, [this, row]() {
        onedit_Ser_btnClicked(row);
    });

    QPushButton* delete_Ser_btn = new QPushButton();
    delete_Ser_btn->setIcon(QIcon(":/new/prefix1/Resources/delete.png"));
    delete_Ser_btn->setToolTip("Delete this room");
    connect(delete_Ser_btn, &QPushButton::clicked, this, [this, row]() {
        ondelete_Ser_btnClicked(row);
    });

    QHBoxLayout* layout = new QHBoxLayout(buttonWidget);
    layout->addWidget(edit_Ser_btn);
    layout->addWidget(delete_Ser_btn);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    edit_Ser_btn->setFixedSize(20, 20);
    delete_Ser_btn->setFixedSize(20, 20);

    buttonWidget->setLayout(layout);

    ui->SerTable->setCellWidget(row, 5, buttonWidget);
}

void Admin::displayServiceUsages(const ServiceUsage& su){
    int row = ui->SerUsageTable->rowCount();
    ui->SerUsageTable->insertRow(row);
    ui->SerUsageTable->setRowHeight(row, 35);
    ui->SerUsageTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(su.getID())));
    ui->SerUsageTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(su.getRoomID())));
    ui->SerUsageTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(su.getServiceID())));
    ui->SerUsageTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(su.getTenantID())));
    QTableWidgetItem *status = new QTableWidgetItem(QString::fromStdString(su.getStatus() ? "Active" : "Inactive"));
    QFont font = status->font();
    font.setBold(true);
    status->setFont(font);
    if (su.getStatus()) {
        status->setForeground(QColor("green"));
    }
    ui->SerUsageTable->setItem(row, 4, status);
}

void Admin::onedit_Ser_btnClicked(int row){
    string ID = ui->SerTable->item(row, 0)->text().toStdString();
    string name = ui->SerTable->item(row, 1)->text().toStdString();
    double price = ui->SerTable->item(row, 3)->text().toDouble();
    string des = ui->SerTable->item(row, 2)->text().toStdString();
    Editservice edit(ID, name, price, des, this);
    edit.exec();
    ui->CBSS->setCurrentIndex(0);
    ui->SerTable->clearContents();
    ui->SerTable->setRowCount(0);
    Service::showAllServices(this);
}

void Admin::ondelete_Ser_btnClicked(int row){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete", "Are you sure you want to delete this?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        string ID = ui->SerTable->item(row, 0)->text().toStdString();
        if(Service::isActive(ID)){
            QMessageBox::warning(this, "Delete", "This service is currently in use and cannot be deleted.");
            return;
        } else {
        Service::deleteService(ID);
        ui->CBSS->setCurrentIndex(0);
        ui->SerTable->clearContents();
        ui->SerTable->setRowCount(0);
        Service::showAllServices(this);
        ui->totalservice->setText(QString::number(Service::total));
        }
    }
}

void Admin::searchSer()
{
    string search = ui->LineEditSearchSer->text().toStdString();
    string check = ui->CBSS->currentText().toStdString();
    if (search.empty()) {
        ui->SerTable->clearContents();
        ui->SerTable->setRowCount(0);
        Service::showAllServices(this);
    }
    if (check == "Service ID"){
        ui->SerTable->clearContents();
        ui->SerTable->setRowCount(0);
        Service::searchByID(search, this);
    }
    if (check == "Service Name"){
        ui->SerTable->clearContents();
        ui->SerTable->setRowCount(0);
        Service::searchByName(search, this);
    }
}

void Admin::searchSerUsage(){
    string search = ui->LineEditSearchSerUsage->text().toStdString();
    string check = ui->CBSSUsage->currentText().toStdString();
    if (search.empty()){
        ui->SerUsageTable->clearContents();
        ui->SerUsageTable->setRowCount(0);
        ServiceUsage::showAllServiceUsages(this);
    }
    if (check == "Room ID"){
        ui->SerUsageTable->clearContents();
        ui->SerUsageTable->setRowCount(0);
        ServiceUsage::searchByRoomID(search, this);
    }
    if (check == "Service Usage ID"){
        ui->SerUsageTable->clearContents();
        ui->SerUsageTable->setRowCount(0);
        ServiceUsage::searchByID(search, this);
    }
}

void Admin::on_RefbtnSerusage_clicked()
{
    ui->SerUsageTable->clearContents();
    ui->SerUsageTable->setRowCount(0);
    ServiceUsage::showAllServiceUsages(this);
    ui->LineEditSearchSerUsage->clear();
    ui->CBSSUsage->setCurrentIndex(0);
}

void Admin::on_RefbtnSer_clicked()
{
    ui->SerTable->clearContents();
    ui->SerTable->setRowCount(0);
    Service::showAllServices(this);
    ui->LineEditSearchSer->clear();
    ui->CBSR->setCurrentIndex(0);
}

void Admin::on_Serbtn1_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void Admin::on_Serbtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void Admin::on_addSer_clicked()
{
    AddService add(this);
    add.exec();
    ui->SerTable->clearContents();
    ui->SerTable->setRowCount(0);
    Service::showAllServices(this);
    ui->totalservice->setText(QString::number(Service::total));
}

void Admin::on_SerUsage1btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void Admin::on_SerUsagebtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}
