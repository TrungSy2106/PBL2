#include "User.h"
#include "ui_User.h"
#include "Account.h"
#include "Contract.h"
#include "Tenant.h"

#include <QMessageBox>

void User::on_TTCNbtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void User::on_editprofilebtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void User::on_Changepassbtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void User::on_Changepass_clicked()
{
    if (ui->newpass->text() == ui->newpass2->text()){
        if (!Account::changePassword(ui->currentpass->text().toStdString(), ui->newpass->text().toStdString())){
            ui->error1->setText("Mật khẩu không đúng");
        } else {
            ui->error1->setText("");
            ui->error2->setText("");
            QMessageBox::information(this, "Success", "Password changed successfully!", QMessageBox::Ok);
            ui->currentpass->clear();
            ui->newpass->clear();
            ui->newpass2->clear();
        }
    } else { ui->error2->setText("Mật khẩu không khớp");}

}

void User::showprofile(){
    Tenant *tenant = Tenant::tenantList.searchID(Account::currentTenantID);
    ui->name->setText(QString::fromStdString(tenant->getFullName()));
    ui->sdt->setText(QString::fromStdString(tenant->getPhone()));
    ui->age->setText(QString::number(tenant->getBirthyear()));
    ui->cccd->setText(QString::fromStdString(tenant->getCCCD()));
    ui->gender->setText(QString::fromStdString(tenant->getGender()? "Nữ" : "Nam"));

    ui->upname->setText(QString::fromStdString(tenant->getFullName()));
    ui->upsdt->setText(QString::fromStdString(tenant->getPhone()));
    ui->upage->setText(QString::number(tenant->getBirthyear()));
    ui->upcccd->setText(QString::fromStdString(tenant->getCCCD()));
    if (tenant->getGender()){
    ui->checkBox_2->setChecked(true);
    } else { ui->checkBox->setChecked(true); }
}

void User::on_updateprofile_clicked()
{
    bool c, gender;
    string firstName, lastName;
    QString name = ui->upname->text();
    string sdt = ui->upsdt->text().toStdString();
    int age = ui->upage->text().toInt(&c);
    string cccd = ui->upcccd->text().toStdString();
    time_t now = time(0);
    tm* ltm = localtime(&now);
    int currentYear = 1900 + ltm->tm_year;
     if (ui->checkBox->isChecked()){
        gender = 0;
    } else { gender = 1; }
    int lastSpaceIndex = name.lastIndexOf(' ');
    if (lastSpaceIndex == -1) {
        QMessageBox::warning(this, "Cảnh báo", "Vui lòng nhập đầy đủ họ và tên.");
        return;
    } else {
        lastName = name.left(lastSpaceIndex).toStdString();
        firstName = name.mid(lastSpaceIndex + 1).toStdString();
    }
    if (ui->upname->text()=="" || ui->upage->text()=="" || ui->upcccd->text()=="" || ui->upsdt->text()=="") {
        QMessageBox::warning(this, "Warning", "Vui lòng nhập đầy đủ thông tin!");
    } else {
    if (!c || age<=0 || age > currentYear){
        QMessageBox::warning(this, "Warning", "Nhập tuổi không hợp lệ!");
    } else {
        Tenant::updateTenant(Account::currentTenantID, lastName, firstName, sdt, cccd, age, gender);
        ui->stackedWidget->setCurrentIndex(0);
        QMessageBox::information(this, "Success", "Update successfully!", QMessageBox::Ok);
        showprofile();
        ui->ContractTable->clearContents();
        ui->ContractTable->setRowCount(0);
        Contract::searchByTenantID(Account::currentTenantID, 0, this);
    }
    }
}

void User::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
