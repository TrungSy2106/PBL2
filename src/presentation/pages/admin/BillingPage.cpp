#include "admin.h"
#include "ui_admin.h"
#include "Room.h"
#include "Tenant.h"
#include "Contract.h"
#include "Payment.h"
#include "Createpayment.h"
#include "Extend.h"

using namespace std;

void Admin::managepayments(){
    Payment::showAllPayments(this);
    ui->PaymentTable->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->PaymentTable->horizontalHeader()->setStyleSheet("QHeaderView::section { border: none; }");
    ui->PaymentTable->horizontalHeaderItem(ui->PaymentTable->columnCount() - 1)->setTextAlignment(Qt::AlignCenter);
    ui->PaymentTable->verticalHeader()->hide();
    ui->PaymentTable->setShowGrid(false);
}

void Admin::managecontracts(){
    Contract::showAllContracts(this);
    ui->ContractTable->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->ContractTable->horizontalHeader()->setStyleSheet("QHeaderView::section { border: none; }");
    ui->ContractTable->horizontalHeaderItem(ui->ContractTable->columnCount() - 1)->setTextAlignment(Qt::AlignCenter);
    ui->ContractTable->setColumnWidth(5, 50);
    ui->ContractTable->setColumnWidth(11, 50);
    ui->ContractTable->verticalHeader()->hide();
    ui->ContractTable->setShowGrid(false);
    //sx contract
    QRect headerContract = ui->ContractTable->visualRect(ui->ContractTable->model()->index(0, 0));
    QPushButton* sortidContractButton = new QPushButton(ui->ContractTable);
    sortidContractButton->setText("");
    sortidContractButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
    sortidContractButton->setFixedSize(16, 16);
    sortidContractButton->setToolTip("Sort by ID");
    sortidContractButton->move(headerContract.right() - 30, headerContract.top() + 3);
    sortidContractButton->setCheckable(true);
    connect(sortidContractButton, &QPushButton::toggled, this, [this, sortidContractButton](bool checked) {
        if (checked) {
            sortidContractButton->setIcon(QIcon(":/new/prefix1/Resources/sxgiam.png"));
            Contract::sortID(false);
            ui->ContractTable->clearContents();
            ui->ContractTable->setRowCount(0);
            Contract::showAllContracts(this);
        } else {
            sortidContractButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
            Contract::sortID(true);
            ui->ContractTable->clearContents();
            ui->ContractTable->setRowCount(0);
            Contract::showAllContracts(this);
        }
    });
}

void Admin::displayPayments(const Payment& p){
    ui->totalpayment->setText(QString::number(Payment::total));
    int row = ui->PaymentTable->rowCount();
    ui->PaymentTable->insertRow(row);

    ui->PaymentTable->setRowHeight(row, 35);
    ui->PaymentTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(p.getID())));
    ui->PaymentTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(p.getRoomID())));
    ui->PaymentTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(p.getTenantID())));
    ui->PaymentTable->setItem(row, 3, new QTableWidgetItem(QString::number(p.getRentAmount(), 'f', 2)));
    ui->PaymentTable->setItem(row, 4, new QTableWidgetItem(QString::number(p.getServiceAmount(), 'f', 2)));
    ui->PaymentTable->setItem(row, 5, new QTableWidgetItem(QString::number(p.getTotalAmount(), 'f', 2)));
    ui->PaymentTable->setItem(row, 6, new QTableWidgetItem(QString::number(p.getBillMonth())));
    ui->PaymentTable->setItem(row, 7, new QTableWidgetItem(QString::number(p.getBillYear())));
    ui->PaymentTable->setItem(row, 8, new QTableWidgetItem(QString::fromStdString(p.getpayDate().toString())));
    QTableWidgetItem *status = new QTableWidgetItem(QString::fromStdString(p.getStatus() ? "Paid" : "Pending"));
    QFont font = status->font();
    font.setBold(true);
    status->setFont(font);
    if (p.getStatus()) {
        status->setForeground(QColor("green"));
    } else {
        status->setForeground(QColor(255, 165, 0));
    }
    ui->PaymentTable->setItem(row, 9, status);
    ui->PaymentTable->setItem(row, 10, new QTableWidgetItem(QString::number(p.getdepositAmount(), 'f', 2)));
    ui->PaymentTable->setItem(row, 11, new QTableWidgetItem(QString::number(p.getRemainingAmount(), 'f', 2)));
}

void Admin::displayContracts(const Contract& c){
    ui->totalcontract->setText(QString::number(Contract::total));
    int row = ui->ContractTable->rowCount();
    ui->ContractTable->insertRow(row);
    Tenant* t = Tenant::tenantList.searchID(c.getTenantID());
    Room* r = Room::roomList.searchID(c.getRoomID());
    ui->ContractTable->setRowHeight(row, 35);
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
    // ui->ContractTable->setItem(row, 11, new QTableWidgetItem(QString::fromStdString(c.getStatus() == 1 ? "Active" : "Expired")));
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

void Admin::on_Paymentbtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void Admin::on_Paymentbtn1_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void Admin::on_Contractbtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}

void Admin::on_Contractbtn1_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}


// void Admin::on_CBSRe_currentIndexChanged(int index)
// {
    // if (index == 0 || index == 2 || index == 3 || index == 4) {
        //         ui->LineEditSearchRe->setEnabled(false);
        //         ui->LineEditSearchRe->setStyleSheet("QLineEdit { background-color: #d3d3d3; padding-left:20px; border: 1px solid gray; border-radius: 10px; }");
        //     } else {
        //         ui->LineEditSearchRe->setEnabled(true);
        //         ui->LineEditSearchRe->setStyleSheet("QLineEdit {padding-left:20px; border: 1px solid gray; border-radius: 10px;}");
        //     }
        //     QString check = ui->CBSRe->currentText();
        //     if (check == "Phòng đang trống"){

        //         ui->table1->clearContents();
        //         ui->table1->setRowCount(0);
        //         ui->LineEditSearchRoom->clear();
        //         Room::searchByStatus(0, this);
        //     }
        //     if (check == "Phòng đã có người thuê"){

        //         ui->table1->clearContents();
        //         ui->table1->setRowCount(0);
        //         ui->LineEditSearchRoom->clear();
        //         Room::searchByStatus(1, this);
        //     }
        //     if (check == "Phòng đang bảo trì"){

        //         ui->table1->clearContents();
        //         ui->table1->setRowCount(0);
        //         ui->LineEditSearchRoom->clear();
        //         Room::searchByStatus(3, this);
        //     }
        //     if (check == "Phòng đã đặt"){
        //         ui->table1->clearContents();
        //         ui->table1->setRowCount(0);
        //         ui->LineEditSearchRoom->clear();
        //         Room::searchByStatus(2, this);
        //     }
// }

void Admin::on_searchPayment_clicked()
{
    int month = ui->CBSP->currentText().toInt();
    int year = ui->LineEditSearchPayment->text().toInt();
    ui->PaymentTable->clearContents();
    ui->PaymentTable->setRowCount(0);
    Payment::searchByMonth(month, year, this);
}

void Admin::on_RefPaymentbtn_clicked()
{
    ui->PaymentTable->clearContents();
    ui->PaymentTable->setRowCount(0);
    Payment::showAllPayments(this);
    ui->LineEditSearchPayment->clear();
    ui->CBSR->setCurrentIndex(0);
}

void Admin::on_CreatePaymentbtn_clicked()
{
    Createpayment payment(this);
    payment.exec();
    ui->PaymentTable->clearContents();
    ui->PaymentTable->setRowCount(0);
    Payment::showAllPayments(this);
}

void Admin::onExtendButtonClicked(int row){
    string id = ui->ContractTable->item(row, 1)->text().toStdString();
    string idt = ui->ContractTable->item(row, 3)->text().toStdString();
    Extend e(id, idt, this);
    e.exec();
    ui->ContractTable->clearContents();
    ui->ContractTable->setRowCount(0);
    Contract::showAllContracts(this);
}
