#include "User.h"
#include "ui_User.h"
#include "Account.h"
#include "Contract.h"
#include "Extend.h"
#include "Payment.h"
#include "Room.h"
#include "Tenant.h"

#include <QMessageBox>

void User::managecontracts(){
    Contract::searchByTenantID(Account::currentTenantID, 0, this);
    ui->ContractTable->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->ContractTable->horizontalHeader()->setStyleSheet("QHeaderView::section { border: none; }");
    ui->ContractTable->horizontalHeaderItem(ui->ContractTable->columnCount() - 1)->setTextAlignment(Qt::AlignCenter);
    ui->ContractTable->setColumnWidth(5, 50);
    ui->ContractTable->setColumnWidth(11, 50);
    ui->ContractTable->verticalHeader()->hide();
    ui->ContractTable->setShowGrid(false);
}

void User::displayContracts(const Contract& c){
    int row = ui->ContractTable->rowCount();
    ui->ContractTable->insertRow(row);
    Tenant* t = Tenant::tenantList.searchID(c.getTenantID());
    Room* r = Room::roomList.searchID(c.getRoomID());
    ui->ContractTable->setRowHeight(row, 50);
    ui->ContractTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(c.getID())));
    ui->ContractTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(c.getRoomID())));
    ui->ContractTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(r->getRoomType()->getName())));
    ui->ContractTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(c.getTenantID())));
    ui->ContractTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(t->getFullName())));
    ui->ContractTable->setItem(row, 5, new QTableWidgetItem(QString::number(t->getAge())));
    ui->ContractTable->setItem(row, 6, new QTableWidgetItem(QString::fromStdString(t->getCCCD())));
    ui->ContractTable->setItem(row, 7, new QTableWidgetItem(QString::fromStdString(t->getPhone())));
    ui->ContractTable->setItem(row, 8, new QTableWidgetItem(QString::fromStdString(c.getStartDate().toString())));
    ui->ContractTable->setItem(row, 9, new QTableWidgetItem(QString::fromStdString(c.getEndDate().toString())));
    ui->ContractTable->setItem(row, 10, new QTableWidgetItem((QString("%1 VND/1 month").arg(QString::number(c.getrentprice(), 'f', 2)))));
    QTableWidgetItem *status = new QTableWidgetItem(QString::fromStdString(c.getStatus() == 1 ? "Active" : "Expired"));
    QFont font = status->font();
    if (c.getStatus() == 1) {
        status->setForeground(QColor("green"));
        font.setBold(true);
        status->setFont(font);
    } else {
        status->setForeground(QColor("red"));
        status->setFont(font);
    }
    ui->ContractTable->setItem(row, 11, status);
    if (c.getStatus() == 1){
        QWidget* buttonWidget = new QWidget();

        QPushButton* terminate_btn = new QPushButton();
        terminate_btn->setIcon(QIcon(":/new/prefix1/Resources/rejectcontract.png"));
        terminate_btn->setToolTip("Hủy thuê");
        connect(terminate_btn, &QPushButton::clicked, this, [this, row]() {
            onterminate_btnClicked(row);
        });

        QPushButton* extendButton = new QPushButton();
        extendButton->setIcon(QIcon(":/new/prefix1/Resources/extend.png"));
        extendButton->setToolTip("Gia hạn");
        connect(extendButton, &QPushButton::clicked, this, [this, row]() {
            onExtendButtonClicked(row);
        });

        QHBoxLayout* layout = new QHBoxLayout(buttonWidget);
        layout->addWidget(extendButton);
        layout->addWidget(terminate_btn);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);
        terminate_btn->setIconSize(QSize(20, 20));
        extendButton->setIconSize(QSize(30, 30));

        buttonWidget->setLayout(layout);

        ui->ContractTable->setCellWidget(row, 12, buttonWidget);
    }
}

void User::on_Contractbtn_clicked()
{
    ui->stackedWidget_7->setCurrentIndex(4);
}

void User::on_Contractbtn1_clicked()
{
    ui->stackedWidget_7->setCurrentIndex(4);
}

void User::onterminate_btnClicked(int row){
    if (Payment::checkUnpaidPaymentForRoom(Account::currentTenantID, ui->ContractTable->item(row, 1)->text().toStdString())) {
        QMessageBox::information(this, "Thông báo", "Bạn cần thanh toán trước khi hủy hợp đồng");
        return;
    }
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Xác nhận", "Bạn có chắc chắn muốn hủy hợp đồng này không?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        Contract::deleteContract(ui->ContractTable->item(row, 1)->text().toStdString());
        ui->ContractTable->clearContents();
        ui->ContractTable->setRowCount(0);
        Contract::searchByTenantID(Account::currentTenantID, 0, this);
        ui->table1->clearContents();
        ui->table1->setRowCount(0);
        Room::searchByStatus(0, this);
        ui->listWidget->clear();
        ui->listWidget_2->clear();
        showlist();
        showmyroom();
    }
}

void User::onExtendButtonClicked(int row){
    string id = ui->ContractTable->item(row, 1)->text().toStdString();
    Extend e(id, Account::currentTenantID, this);
    e.exec();
    ui->ContractTable->clearContents();
    ui->ContractTable->setRowCount(0);
    Contract::searchByTenantID(Account::currentTenantID, 0, this);
}
