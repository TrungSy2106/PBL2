#include "admin.h"
#include "ui_admin.h"
#include "Room.h"
#include "Account.h"
#include "Adminaccount.h"

using namespace std;

void Admin::manageaccounts(){
    Account::showAllAccount(this);
    ui->totalroom->setText(QString::number(Room::total));
    ui->AccountTable->horizontalHeader()->setStyleSheet("QHeaderView::section { border: none; }");
    ui->AccountTable->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    // ui->AccountTable->horizontalHeaderItem(ui->AccountTable->columnCount() - 1)->setTextAlignment(Qt::AlignCenter);
    ui->AccountTable->setColumnWidth(0, 250);
    ui->AccountTable->setColumnWidth(1, 250);
    ui->AccountTable->setColumnWidth(2, 250);
    ui->AccountTable->setColumnWidth(3, 250);
    ui->AccountTable->setColumnWidth(4, 250);
    ui->AccountTable->verticalHeader()->hide();
}

void Admin::displayAccounts(const Account& a){
    ui->totalaccount->setText(QString::number(Account::total));
    int row = ui->AccountTable->rowCount();
    ui->AccountTable->insertRow(row);

    ui->AccountTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(a.getID())));
    ui->AccountTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(a.getusername())));
    ui->AccountTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(a.getpassword())));
    ui->AccountTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(a.gettenantID())));
    ui->AccountTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(a.getrole() == 0 ? "Tenant" : "Admin")));
}

void Admin::on_Accountbtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
}

void Admin::on_Accountbtn1_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
}

void Admin::changeAdmincode(){
    Adminaccount A(true, this);
    A.exec();
}

void Admin::changePassword(){
    Adminaccount A(false, this);
    A.exec();
}

void Admin::on_Accbtn_2_clicked()
{
    ui->Accbtn->click();
}
