#include "admin.h"
#include "ui_admin.h"
#include "Tenant.h"
#include "Edittenant.h"

using namespace std;

void Admin::managetenants(){
    QAction *searchAction = new QAction(QIcon(":/new/prefix1/Resources/loupe.png"), "Search", this);
    ui->LineEditSearchTenant->addAction(searchAction, QLineEdit::LeadingPosition);
    Tenant::showAllTenants(this);
    ui->totaltenant->setText(QString::number(Tenant::total));
    ui->TenantTable->horizontalHeader()->setStyleSheet("QHeaderView::section { border: none; }");
    ui->TenantTable->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->TenantTable->horizontalHeaderItem(ui->TenantTable->columnCount() - 1)->setTextAlignment(Qt::AlignCenter);
    ui->TenantTable->setColumnWidth(0, 150);
    ui->TenantTable->setColumnWidth(1, 150);
    ui->TenantTable->setColumnWidth(2, 150);
    ui->TenantTable->setColumnWidth(3, 100);
    ui->TenantTable->setColumnWidth(4, 150);
    ui->TenantTable->setColumnWidth(5, 100);
    ui->TenantTable->verticalHeader()->hide();
    ui->TenantTable->setShowGrid(false);

    //sx id
    QRect headertenant = ui->TenantTable->visualRect(ui->TenantTable->model()->index(0, 0));
    QPushButton* sortIDTenantButton = new QPushButton(ui->TenantTable);
    sortIDTenantButton->setText("");
    sortIDTenantButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
    sortIDTenantButton->setFixedSize(16, 16);
    sortIDTenantButton->setToolTip("Sort by ID");
    sortIDTenantButton->move(headertenant.right() - 90, headertenant.top() + 3);
    sortIDTenantButton->setCheckable(true);
    connect(sortIDTenantButton, &QPushButton::toggled, this, [this, sortIDTenantButton](bool checked) {
        if (checked) {
            sortIDTenantButton->setIcon(QIcon(":/new/prefix1/Resources/sxgiam.png"));
            Tenant::sortID(false);
            ui->TenantTable->clearContents();
            ui->TenantTable->setRowCount(0);
            Tenant::showAllTenants(this);
            if (ui->CBST->currentIndex() == 3){
                sortIDTenantButton->setIcon(QIcon(":/new/prefix1/Resources/sxgiam.png"));
                Tenant::sortID(false);
                ui->TenantTable->clearContents();
                ui->TenantTable->setRowCount(0);
                Tenant::searchByGender(0, this);
            }
            if (ui->CBST->currentIndex() == 4){
                sortIDTenantButton->setIcon(QIcon(":/new/prefix1/Resources/sxgiam.png"));
                Tenant::sortID(false);
                ui->TenantTable->clearContents();
                ui->TenantTable->setRowCount(0);
                Tenant::searchByGender(1, this);
            }
            if (ui->CBST->currentIndex() == 1 && !ui->LineEditSearchTenant->text().isEmpty()){
                sortIDTenantButton->setIcon(QIcon(":/new/prefix1/Resources/sxgiam.png"));
                Tenant::sortID(false);
                ui->TenantTable->clearContents();
                ui->TenantTable->setRowCount(0);
                Tenant::searchByID(ui->LineEditSearchTenant->text().toStdString(), this);
            }
            if (ui->CBST->currentIndex() == 2 && !ui->LineEditSearchTenant->text().isEmpty()){
                sortIDTenantButton->setIcon(QIcon(":/new/prefix1/Resources/sxgiam.png"));
                Tenant::sortID(false);
                ui->TenantTable->clearContents();
                ui->TenantTable->setRowCount(0);
                Tenant::searchByName(ui->LineEditSearchTenant->text().toStdString(), this);
            }
        } else {
            sortIDTenantButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
            Tenant::sortID(true);
            ui->TenantTable->clearContents();
            ui->TenantTable->setRowCount(0);
            Tenant::showAllTenants(this);
            if (ui->CBST->currentIndex() == 3){
                sortIDTenantButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
                Tenant::sortID(true);
                ui->TenantTable->clearContents();
                ui->TenantTable->setRowCount(0);
                Tenant::searchByGender(0, this);
            }
            if (ui->CBST->currentIndex() == 4){
                sortIDTenantButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
                Tenant::sortID(true);
                ui->TenantTable->clearContents();
                ui->TenantTable->setRowCount(0);
                Tenant::searchByGender(1, this);
            }
            if (ui->CBST->currentIndex() == 1 && !ui->LineEditSearchTenant->text().isEmpty()){
                sortIDTenantButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
                Tenant::sortID(true);
                ui->TenantTable->clearContents();
                ui->TenantTable->setRowCount(0);
                Tenant::searchByID(ui->LineEditSearchTenant->text().toStdString(), this);
            }
            if (ui->CBST->currentIndex() == 2 && !ui->LineEditSearchTenant->text().isEmpty()){
                sortIDTenantButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
                Tenant::sortID(true);
                ui->TenantTable->clearContents();
                ui->TenantTable->setRowCount(0);
                Tenant::searchByName(ui->LineEditSearchTenant->text().toStdString(), this);
            }
        }
    });
    //sx ten
    QPushButton* sortNameTenantButton = new QPushButton(ui->TenantTable);
    sortNameTenantButton->setText("");
    sortNameTenantButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
    sortNameTenantButton->setFixedSize(16, 16);
    sortNameTenantButton->setToolTip("Sort by Name");
    sortNameTenantButton->move(headertenant.right() +35, headertenant.top() + 3);
    sortNameTenantButton->setCheckable(true);
    connect(sortNameTenantButton, &QPushButton::toggled, this, [this, sortNameTenantButton](bool checked) {
        if (checked) {
            sortNameTenantButton->setIcon(QIcon(":/new/prefix1/Resources/sxgiam.png"));
            Tenant::sortName(false);
            ui->TenantTable->clearContents();
            ui->TenantTable->setRowCount(0);
            Tenant::showAllTenants(this);
            if (ui->CBST->currentIndex() == 3){
                sortNameTenantButton->setIcon(QIcon(":/new/prefix1/Resources/sxgiam.png"));
                Tenant::sortName(false);
                ui->TenantTable->clearContents();
                ui->TenantTable->setRowCount(0);
                Tenant::searchByGender(0, this);
            }
            if (ui->CBST->currentIndex() == 4){
                sortNameTenantButton->setIcon(QIcon(":/new/prefix1/Resources/sxgiam.png"));
                Tenant::sortName(false);
                ui->TenantTable->clearContents();
                ui->TenantTable->setRowCount(0);
                Tenant::searchByGender(1, this);
            }
            if (ui->CBST->currentIndex() == 1 && !ui->LineEditSearchTenant->text().isEmpty()){
                sortNameTenantButton->setIcon(QIcon(":/new/prefix1/Resources/sxgiam.png"));
                Tenant::sortName(false);
                ui->TenantTable->clearContents();
                ui->TenantTable->setRowCount(0);
                Tenant::searchByID(ui->LineEditSearchTenant->text().toStdString(), this);
            }
            if (ui->CBST->currentIndex() == 2 && !ui->LineEditSearchTenant->text().isEmpty()){
                sortNameTenantButton->setIcon(QIcon(":/new/prefix1/Resources/sxgiam.png"));
                Tenant::sortName(false);
                ui->TenantTable->clearContents();
                ui->TenantTable->setRowCount(0);
                Tenant::searchByName(ui->LineEditSearchTenant->text().toStdString(), this);
            }
        } else {
            sortNameTenantButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
            Tenant::sortName(true);
            ui->TenantTable->clearContents();
            ui->TenantTable->setRowCount(0);
            Tenant::showAllTenants(this);
            if (ui->CBST->currentIndex() == 3){
                sortNameTenantButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
                Tenant::sortName(true);
                ui->TenantTable->clearContents();
                ui->TenantTable->setRowCount(0);
                Tenant::searchByGender(0, this);
            }
            if (ui->CBST->currentIndex() == 4){
                sortNameTenantButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
                Tenant::sortName(true);
                ui->TenantTable->clearContents();
                ui->TenantTable->setRowCount(0);
                Tenant::searchByGender(1, this);
            }
            if (ui->CBST->currentIndex() == 1 && !ui->LineEditSearchTenant->text().isEmpty()){
                sortNameTenantButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
                Tenant::sortName(true);
                ui->TenantTable->clearContents();
                ui->TenantTable->setRowCount(0);
                Tenant::searchByID(ui->LineEditSearchTenant->text().toStdString(), this);
            }
            if (ui->CBST->currentIndex() == 2 && !ui->LineEditSearchTenant->text().isEmpty()){
                sortNameTenantButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
                Tenant::sortName(true);
                ui->TenantTable->clearContents();
                ui->TenantTable->setRowCount(0);
                Tenant::searchByName(ui->LineEditSearchTenant->text().toStdString(), this);
            }
        }
    });
}

void Admin::displayTenants(const Tenant& t) {
    int row = ui->TenantTable->rowCount();
    ui->TenantTable->insertRow(row);

    ui->TenantTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(t.getID())));
    ui->TenantTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(t.getFullName())));
    ui->TenantTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(t.getPhone())));
    ui->TenantTable->setItem(row, 3, new QTableWidgetItem(QString::number(t.getAge())));
    ui->TenantTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(t.getCCCD())));
    ui->TenantTable->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(t.getGender() ? "Nu" : "Nam")));
    QWidget* buttonWidget = new QWidget();

    QPushButton* edit_tenant_btn = new QPushButton();
    edit_tenant_btn->setIcon(QIcon(":/new/prefix1/Resources/edit.png"));
    edit_tenant_btn->setToolTip("Edit");
    connect(edit_tenant_btn, &QPushButton::clicked, this, [this, row]() {
        onedit_tenant_btnClicked(row);
    });

    QHBoxLayout* layout = new QHBoxLayout(buttonWidget);
    layout->addWidget(edit_tenant_btn);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    edit_tenant_btn->setFixedSize(20, 20);

    buttonWidget->setLayout(layout);

    ui->TenantTable->setCellWidget(row, 6, buttonWidget);
}

void Admin::onedit_tenant_btnClicked(int row){
    string tenantID = ui->TenantTable->item(row, 0)->text().toStdString();
    string name = ui->TenantTable->item(row, 1)->text().toStdString();
    string phone = ui->TenantTable->item(row, 2)->text().toStdString();
    int age = ui->TenantTable->item(row, 3)->text().toInt();
    string cccd = ui->TenantTable->item(row, 4)->text().toStdString();
    string gender = ui->TenantTable->item(row, 5)->text().toStdString();
    Edittenant tenantedit(tenantID, name, phone, age, cccd, gender, this);
    tenantedit.exec();
    ui->CBST->setCurrentIndex(0);
    ui->TenantTable->clearContents();
    ui->TenantTable->setRowCount(0);
    Tenant::showAllTenants(this);
    ui->totaltenant->setText(QString::number(Tenant::total));
}

void Admin::searchtenant()
{
    string search = ui->LineEditSearchTenant->text().toStdString();
    string check = ui->CBST->currentText().toStdString();
    if (search.empty()) {
        ui->TenantTable->clearContents();
        ui->TenantTable->setRowCount(0);
        Tenant::showAllTenants(this);
    }
    if (check == "Tenant ID"){
        ui->TenantTable->clearContents();
        ui->TenantTable->setRowCount(0);
        Tenant::searchByID(search, this);
    }
    if (check == "Tên"){
        ui->TenantTable->clearContents();
        ui->TenantTable->setRowCount(0);
        Tenant::searchByName(search, this);
    }
}

void Admin::on_Tenantbtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void Admin::on_pushButton_17_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void Admin::on_RefTenantbtn_clicked()
{
    ui->TenantTable->clearContents();
    ui->TenantTable->setRowCount(0);
    Tenant::showAllTenants(this);
    ui->LineEditSearchTenant->clear();
    ui->CBST->setCurrentIndex(0);
    ui->LineEditSearchTenant->setEnabled(true);
    ui->LineEditSearchTenant->setStyleSheet("QLineEdit{padding-left:20px;border: 1px solid gray;border-radius: 10px;}");
}

void Admin::on_CBST_currentIndexChanged(int index)
{
    if (index == 0 || index == 3 || index == 4) {
        ui->LineEditSearchTenant->clear();
        ui->LineEditSearchTenant->setEnabled(false);
        ui->LineEditSearchTenant->setStyleSheet("QLineEdit { background-color: #d3d3d3; padding-left:20px; border: 1px solid gray; border-radius: 10px; }");
    } else {
        ui->LineEditSearchTenant->setEnabled(true);
        ui->LineEditSearchTenant->setStyleSheet("QLineEdit {padding-left:20px; border: 1px solid gray; border-radius: 10px;}");
    }
    string search = ui->LineEditSearchTenant->text().toStdString();
    string check = ui->CBST->currentText().toStdString();
    if (search.empty()) {
        ui->TenantTable->clearContents();
        ui->TenantTable->setRowCount(0);
        Tenant::showAllTenants(this);
    }
    if (check == "Tenant ID"){
        ui->TenantTable->clearContents();
        ui->TenantTable->setRowCount(0);
        Tenant::searchByID(search, this);
    }
    if (check == "Tên"){
        ui->TenantTable->clearContents();
        ui->TenantTable->setRowCount(0);
        Tenant::searchByName(search, this);
    }
    if (check == "Nam"){
        ui->TenantTable->clearContents();
        ui->TenantTable->setRowCount(0);
        ui->LineEditSearchTenant->clear();
        Tenant::searchByGender(0, this);
    }
    if (check == "Nữ"){
        ui->TenantTable->clearContents();
        ui->TenantTable->setRowCount(0);
        ui->LineEditSearchTenant->clear();
        Tenant::searchByGender(1, this);
    }
}
