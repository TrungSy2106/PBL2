#include "User.h"
#include "ui_User.h"
#include "Account.h"
#include "Payment.h"
#include "Paybill.h"

void User::managepayments(){
    Payment::searchByTenantID(Account::currentTenantID, this);
    ui->PaymentTable->setColumnWidth(6, 70);
    ui->PaymentTable->setColumnWidth(7, 70);
    ui->PaymentTable->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->PaymentTable->horizontalHeader()->setStyleSheet("QHeaderView::section { border: none; }");
    ui->PaymentTable->horizontalHeaderItem(ui->PaymentTable->columnCount() - 1)->setTextAlignment(Qt::AlignCenter);
    ui->PaymentTable->verticalHeader()->hide();
    ui->PaymentTable->setShowGrid(false);
}

void User::displayPayments(const Payment& p){
    int row = ui->PaymentTable->rowCount();
    ui->PaymentTable->insertRow(row);
    ui->PaymentTable->setRowHeight(row, 40);

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
        status->setForeground(QColor(0, 255, 0));
    } else {
        status->setForeground(QColor(255, 165, 0));
    }
    ui->PaymentTable->setItem(row, 9, status);
    ui->PaymentTable->setItem(row, 10, new QTableWidgetItem(QString::number(p.getdepositAmount(), 'f', 2)));
    ui->PaymentTable->setItem(row, 11, new QTableWidgetItem(QString::number(p.getRemainingAmount(), 'f', 2)));
    if (p.getRemainingAmount() != 0){
        QWidget* buttonWidget = new QWidget();

        QPushButton* pay_btn = new QPushButton();
        // terminate_btn->setIcon(QIcon(":/new/prefix1/Resources/rejectcontract.png"));
        pay_btn->setText("Pay");
        connect(pay_btn, &QPushButton::clicked, this, [this, row]() {
            onpay_btnbtnClicked(row);
        });

        QHBoxLayout* layout = new QHBoxLayout(buttonWidget);
        layout->addWidget(pay_btn);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);
        pay_btn->setFixedSize(70, 23);

        buttonWidget->setLayout(layout);

        ui->PaymentTable->setCellWidget(row, 12, buttonWidget);
    }
}

void User::on_Paymentbtn_clicked()
{
    ui->stackedWidget_7->setCurrentIndex(3);
}

void User::on_Paymentbtn1_clicked()
{
    ui->stackedWidget_7->setCurrentIndex(3);
}

void User::onpay_btnbtnClicked(int row){
    Paybill pay(ui->PaymentTable->item(row, 0)->text().toStdString(), this);
    pay.exec();
    ui->PaymentTable->clearContents();
    ui->PaymentTable->setRowCount(0);
    Payment::searchByTenantID(Account::currentTenantID, this);
}

void User::on_searchPayment_clicked()
{
    int month = ui->CBSP->currentText().toInt();
    int year = ui->LineEditSearchPayment->text().toInt();
    ui->PaymentTable->clearContents();
    ui->PaymentTable->setRowCount(0);
    Payment::searchByMonth(month, year, this);
}

void User::on_RefPaymentbtn_clicked()
{
    ui->LineEditSearchPayment->clear();
    ui->CBSP->setCurrentIndex(0);
    ui->PaymentTable->clearContents();
    ui->PaymentTable->setRowCount(0);
    Payment::searchByTenantID(Account::currentTenantID, this);
}
