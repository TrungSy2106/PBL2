#include "User.h"
#include "ui_User.h"
#include "Service.h"
#include "ServiceUsage.h"

#include <QMessageBox>

void User::manageservices(){
    QAction *searchAction = new QAction(QIcon(":/new/prefix1/Resources/loupe.png"), "Search", this);
    ui->LineEditSearchSer->addAction(searchAction, QLineEdit::LeadingPosition);
    ui->SerTable->horizontalHeader()->setStyleSheet("QHeaderView::section { border: none; }");
    ui->SerTable->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->SerTable->horizontalHeaderItem(ui->SerTable->columnCount() - 1)->setTextAlignment(Qt::AlignCenter);
    // ui->SerTable->setColumnWidth(0, 200);
    // ui->SerTable->setColumnWidth(1, 200);
    ui->SerTable->setColumnWidth(2, 200);
    // ui->SerTable->setColumnWidth(3, 200);
    // ui->SerTable->setColumnWidth(4, 200);
    ui->SerTable->verticalHeader()->hide();
    ui->SerTable->setShowGrid(false);
}

void User::displayServices(const Service& s) {
    int row = ui->SerTable->rowCount();
    ui->SerTable->insertRow(row);

    ui->SerTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(s.getID())));
    ui->SerTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(s.getName())));
    ui->SerTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(s.getdes())));
    ui->SerTable->setItem(row, 3, new QTableWidgetItem(QString::number(s.getUnitPrice(), 'f', 0)));
    ui->SerTable->setItem(row, 4, new QTableWidgetItem(s.getis_mandatory()? "Cố định" : "Tự do"));
        LinkedList<ServiceUsage>::Node* current = ServiceUsage::usageList.begin();
        while (current) {
            if (ui->listWidget->currentItem()->text() == current->data.getRoomID() && ui->SerTable->item(row, 0)->text() == current->data.getServiceID()){
                ui->SerTable->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(current->data.getStatus()? "Active" : "Inactive")));
                break;
            }
            ui->SerTable->setItem(row, 5, new QTableWidgetItem(QString::fromStdString("Inactive")));
            current = current->next;
        }
        if (ui->SerTable->item(row, 5)->text() == "Inactive"){
            QWidget* buttonWidget = new QWidget();
            QPushButton* edit_Ser_btn = new QPushButton();
            // edit_Ser_btn->setIcon(QIcon(":/new/prefix1/Resources/edit.png"));
            edit_Ser_btn->setText("Register");
            connect(edit_Ser_btn, &QPushButton::clicked, this, [this, row]() {
                onedit_Ser_btnClicked(row);
            });
            QHBoxLayout* layout = new QHBoxLayout(buttonWidget);
            layout->addWidget(edit_Ser_btn);
            layout->setContentsMargins(0, 0, 0, 0);
            layout->setSpacing(0);
            edit_Ser_btn->setFixedSize(70, 23);
            buttonWidget->setLayout(layout);
            ui->SerTable->setCellWidget(row, 6, buttonWidget);
        }

        if (ui->SerTable->item(row, 5)->text() == "Active" && ui->SerTable->item(row, 4)->text() == "Tự do"){
            QWidget* buttonWidget = new QWidget();
            QPushButton* delete_Ser_btn = new QPushButton();
            // delete_Ser_btn->setIcon(QIcon(":/new/prefix1/Resources/delete.png"));
            delete_Ser_btn->setText("Unregister");
            connect(delete_Ser_btn, &QPushButton::clicked, this, [this, row]() {
                ondelete_Ser_btnClicked(row);
            });

            QHBoxLayout* layout = new QHBoxLayout(buttonWidget);
            layout->addWidget(delete_Ser_btn);
            layout->setContentsMargins(0, 0, 0, 0);
            layout->setSpacing(0);
            delete_Ser_btn->setFixedSize(70, 23);

            buttonWidget->setLayout(layout);

            ui->SerTable->setCellWidget(row, 6, buttonWidget);
        }
}

void User::on_listWidget_clicked(){
    ui->SerTable->clearContents();
    ui->SerTable->setRowCount(0);
    Service::showAllServices(this);
}

void User::on_Serbtn1_clicked()
{
    ui->stackedWidget_7->setCurrentIndex(2);
}

void User::on_Serbtn_clicked()
{
    ui->stackedWidget_7->setCurrentIndex(2);
}

void User::onedit_Ser_btnClicked(int i){
    ServiceUsage::addServiceUsage(ui->listWidget->currentItem()->text().toStdString(), ui->SerTable->item(i, 0)->text().toStdString());
    QMessageBox::information(this, "Đăng ký", "Đăng ký thành công!");
    on_listWidget_clicked();
}

void User::ondelete_Ser_btnClicked(int i){
    ServiceUsage::stopService(ui->listWidget->currentItem()->text().toStdString(), ui->SerTable->item(i, 0)->text().toStdString());
    QMessageBox::information(this, "Hủy", "Hủy dịch vụ thành công!");
    on_listWidget_clicked();
}

void User::searchSer()
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
