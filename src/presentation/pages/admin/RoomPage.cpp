#include "admin.h"
#include "ui_admin.h"
#include "Room.h"
#include "RoomType.h"
#include "Tenant.h"
#include "Service.h"
#include "Addroom.h"
#include "Addroomtype.h"
#include "Editroom.h"
#include "Editroomtype.h"
#include <QMessageBox>

using namespace std;

void Admin::managerooms(){
    QAction *searchAction = new QAction(QIcon(":/new/prefix1/Resources/loupe.png"), "Search", this);
    ui->LineEditSearchRoom->addAction(searchAction, QLineEdit::LeadingPosition);
    Room::showAllRooms(this);
    ui->totalroom->setText(QString::number(Room::total));
    ui->table1->horizontalHeader()->setStyleSheet("QHeaderView::section { border: none; }");
    ui->table1->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->table1->horizontalHeaderItem(ui->table1->columnCount() - 1)->setTextAlignment(Qt::AlignCenter);
    ui->table1->setColumnWidth(0, 150);
    ui->table1->setColumnWidth(1, 150);
    ui->table1->setColumnWidth(2, 150);
    ui->table1->setColumnWidth(3, 100);
    ui->table1->setColumnWidth(4, 200);
    ui->table1->setColumnWidth(5, 150);
    // ui->table1->setColumnWidth(6, 150);
    ui->table1->verticalHeader()->hide();

    //sx
    QRect headerRect = ui->table1->visualRect(ui->table1->model()->index(0, 0));
    QPushButton* sortButton = new QPushButton(ui->table1);
    sortButton->setText("");
    sortButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
    sortButton->setFixedSize(16, 16);
    sortButton->setToolTip("Sort by Room ID");
    sortButton->move(headerRect.right() - 85, headerRect.top() + 3);
    sortButton->setCheckable(true);
    connect(sortButton, &QPushButton::toggled, this, [this, sortButton](bool checked) {
        if (checked) {
            sortButton->setIcon(QIcon(":/new/prefix1/Resources/sxgiam.png"));
            Room::Descending();
            ui->table1->clearContents();
            ui->table1->setRowCount(0);
            Room::showAllRooms(this);
            if (ui->CBSR->currentIndex() == 4){
                sortButton->setIcon(QIcon(":/new/prefix1/Resources/sxgiam.png"));
                Room::Descending();
                ui->table1->clearContents();
                ui->table1->setRowCount(0);
                Room::searchByStatus(0, this);
            }
            if (ui->CBSR->currentIndex() == 5){
                sortButton->setIcon(QIcon(":/new/prefix1/Resources/sxgiam.png"));
                Room::Descending();
                ui->table1->clearContents();
                ui->table1->setRowCount(0);
                Room::searchByStatus(1, this);
            }
            if (ui->CBSR->currentIndex() == 6){
                sortButton->setIcon(QIcon(":/new/prefix1/Resources/sxgiam.png"));
                Room::Descending();
                ui->table1->clearContents();
                ui->table1->setRowCount(0);
                Room::searchByStatus(3, this);
            }
            if (ui->CBSR->currentIndex() == 7){
                sortButton->setIcon(QIcon(":/new/prefix1/Resources/sxgiam.png"));
                Room::Descending();
                ui->table1->clearContents();
                ui->table1->setRowCount(0);
                Room::searchByStatus(2, this);
            }
            if (ui->CBSR->currentIndex() == 1 && !ui->LineEditSearchRoom->text().isEmpty()){
                sortButton->setIcon(QIcon(":/new/prefix1/Resources/sxgiam.png"));
                Room::Descending();
                ui->table1->clearContents();
                ui->table1->setRowCount(0);
                Room::searchByID(ui->LineEditSearchRoom->text().toStdString(), this);
            }
            if (ui->CBSR->currentIndex() == 2 && !ui->LineEditSearchRoom->text().isEmpty()){
                sortButton->setIcon(QIcon(":/new/prefix1/Resources/sxgiam.png"));
                Room::Descending();
                ui->table1->clearContents();
                ui->table1->setRowCount(0);
                Room::searchByRoomType(ui->LineEditSearchRoom->text().toStdString(), this);
            }
            if (ui->CBSR->currentIndex() == 3 && !ui->LineEditSearchRoom->text().isEmpty()){
                sortButton->setIcon(QIcon(":/new/prefix1/Resources/sxgiam.png"));
                Room::Descending();
                ui->table1->clearContents();
                ui->table1->setRowCount(0);
                Room::searchByName(ui->LineEditSearchRoom->text().toStdString(), this);
            }
        } else {
            sortButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
            Room::Ascending();
            ui->table1->clearContents();
            ui->table1->setRowCount(0);
            Room::showAllRooms(this);
            if (ui->CBSR->currentIndex() == 4){
                sortButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
                Room::Ascending();
                ui->table1->clearContents();
                ui->table1->setRowCount(0);
                Room::searchByStatus(0, this);
            }
            if (ui->CBSR->currentIndex() == 5){
                sortButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
                Room::Ascending();
                ui->table1->clearContents();
                ui->table1->setRowCount(0);
                Room::searchByStatus(1, this);
            }
            if (ui->CBSR->currentIndex() == 6){
                sortButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
                Room::Ascending();
                ui->table1->clearContents();
                ui->table1->setRowCount(0);
                Room::searchByStatus(3, this);
            }
            if (ui->CBSR->currentIndex() == 7){
                sortButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
                Room::Ascending();
                ui->table1->clearContents();
                ui->table1->setRowCount(0);
                Room::searchByStatus(2, this);
            }
            if (ui->CBSR->currentIndex() == 1 && !ui->LineEditSearchRoom->text().isEmpty()){
                sortButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
                Room::Ascending();
                ui->table1->clearContents();
                ui->table1->setRowCount(0);
                Room::searchByID(ui->LineEditSearchRoom->text().toStdString(), this);
            }
            if (ui->CBSR->currentIndex() == 2 && !ui->LineEditSearchRoom->text().isEmpty()){
                sortButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
                Room::Ascending();
                ui->table1->clearContents();
                ui->table1->setRowCount(0);
                Room::searchByRoomType(ui->LineEditSearchRoom->text().toStdString(), this);
            }
            if (ui->CBSR->currentIndex() == 3 && !ui->LineEditSearchRoom->text().isEmpty()){
                sortButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
                Room::Ascending();
                ui->table1->clearContents();
                ui->table1->setRowCount(0);
                Room::searchByName(ui->LineEditSearchRoom->text().toStdString(), this);
            }
        }
    });
}

void Admin::manageroomtypes(){
    QAction *searchAction = new QAction(QIcon(":/new/prefix1/Resources/loupe.png"), "Search", this);
    ui->LineEditSearchRoomType->addAction(searchAction, QLineEdit::LeadingPosition);
    RoomType::showAllRoomTypes(this);
    ui->totalservice->setText(QString::number(Service::total));
    ui->RoomTypeTable->horizontalHeader()->setStyleSheet("QHeaderView::section { border: none; }");
    ui->RoomTypeTable->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->RoomTypeTable->horizontalHeaderItem(ui->RoomTypeTable->columnCount() - 1)->setTextAlignment(Qt::AlignCenter);
    ui->RoomTypeTable->setColumnWidth(0, 150);
    ui->RoomTypeTable->setColumnWidth(1, 200);
    ui->RoomTypeTable->setColumnWidth(2, 250);
    ui->RoomTypeTable->setColumnWidth(3, 200);
    ui->RoomTypeTable->setColumnWidth(4, 200);
    ui->RoomTypeTable->verticalHeader()->hide();
    ui->RoomTypeTable->setShowGrid(false);
}

void Admin::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Admin::on_roombtn_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}

void Admin::displayRooms(const Room& room) {
    string tenantName = "N/A";
    Tenant* tenant = Tenant::tenantList.searchID(room.getTenantID());
    if (tenant != nullptr) {
        tenantName = tenant->getFullName();
    }
    int row = ui->table1->rowCount();
    ui->table1->insertRow(row);

    ui->table1->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(room.getID())));
    ui->table1->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(room.getRoomType()->getID())));
    QString status;
    if (room.getStatus()==0) status = "Trống";
    else if (room.getStatus()==1) status = "Đang thuê";
    else if (room.getStatus()==3) status = "Đang bảo trì";
    else status = "Đã đặt";
    ui->table1->setItem(row, 2, new QTableWidgetItem(status));
    ui->table1->setItem(row, 3, new QTableWidgetItem(room.getTenantID().empty() ? "N/A" : QString::fromStdString(room.getTenantID())));
    ui->table1->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(tenantName)));
    ui->table1->setItem(row, 5, new QTableWidgetItem(QString::number(room.getRoomType()->getPrice(), 'f', 2)));

    if (room.getStatus() == 0 || room.getStatus() == 3){
    QWidget* buttonWidget = new QWidget();
    QPushButton* editButton = new QPushButton();
    editButton->setIcon(QIcon(":/new/prefix1/Resources/edit.png"));
    editButton->setToolTip("Edit this room");
    connect(editButton, &QPushButton::clicked, this, [this, row]() {
        onEditButtonClicked(row);
    });

    QPushButton* deleteButton = new QPushButton();
    deleteButton->setIcon(QIcon(":/new/prefix1/Resources/delete.png"));
    deleteButton->setToolTip("Delete this room");
    connect(deleteButton, &QPushButton::clicked, this, [this, row]() {
        onDeleteButtonClicked(row);
    });

    QHBoxLayout* layout = new QHBoxLayout(buttonWidget);
    layout->addWidget(editButton);
    layout->addWidget(deleteButton);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    editButton->setFixedSize(20, 20);
    deleteButton->setFixedSize(20, 20);

    buttonWidget->setLayout(layout);

    ui->table1->setCellWidget(row, 6, buttonWidget);
    }
}

void Admin::displayRoomTypes(const RoomType& rt) {
    ui->totalroomtype->setText(QString::number(RoomType::total));
    int row = ui->RoomTypeTable->rowCount();
    ui->RoomTypeTable->insertRow(row);

    ui->RoomTypeTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(rt.getID())));
    ui->RoomTypeTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(rt.getName())));
    ui->RoomTypeTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(rt.getDescription())));
    ui->RoomTypeTable->setItem(row, 3, new QTableWidgetItem(QString::number(rt.getPrice(), 'f', 0)));
    QWidget* buttonWidget = new QWidget();

    QPushButton* edit_RT_btn = new QPushButton();
    edit_RT_btn->setIcon(QIcon(":/new/prefix1/Resources/edit.png"));
    edit_RT_btn->setToolTip("Edit this room");
    connect(edit_RT_btn, &QPushButton::clicked, this, [this, row]() {
        onedit_RT_btnClicked(row);
    });

    QPushButton* delete_RT_btn = new QPushButton();
    delete_RT_btn->setIcon(QIcon(":/new/prefix1/Resources/delete.png"));
    delete_RT_btn->setToolTip("Delete this room");
    connect(delete_RT_btn, &QPushButton::clicked, this, [this, row]() {
        ondelete_RT_btnClicked(row);
    });

    QHBoxLayout* layout = new QHBoxLayout(buttonWidget);
    layout->addWidget(edit_RT_btn);
    layout->addWidget(delete_RT_btn);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    edit_RT_btn->setFixedSize(20, 20);
    delete_RT_btn->setFixedSize(20, 20);

    buttonWidget->setLayout(layout);

    ui->RoomTypeTable->setCellWidget(row, 4, buttonWidget);
}

void Admin::onEditButtonClicked(int row) {
    string roomID = ui->table1->item(row, 0)->text().toStdString();
    Editroom roomedit(roomID, this);
    roomedit.exec();
    ui->CBSR->setCurrentIndex(0);
    ui->table1->clearContents();
    ui->table1->setRowCount(0);
    Room::showAllRooms(this);
    ui->totalroom->setText(QString::number(Room::total));
}

void Admin::onedit_RT_btnClicked(int row){
    string id = ui->RoomTypeTable->item(row, 0)->text().toStdString();
    string name = ui->RoomTypeTable->item(row, 1)->text().toStdString();
    double price = ui->RoomTypeTable->item(row, 3)->text().toDouble();
    string des = ui->RoomTypeTable->item(row, 2)->text().toStdString();
    Editroomtype edit(id, name, des, price, this);
    edit.exec();
    ui->CBSRT->setCurrentIndex(0);
    ui->RoomTypeTable->clearContents();
    ui->RoomTypeTable->setRowCount(0);
    RoomType::showAllRoomTypes(this);
}

void Admin::onDeleteButtonClicked(int row) {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete", "Are you sure you want to delete this?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
    string roomID = ui->table1->item(row, 0)->text().toStdString();
    Room::deleteRoom(roomID);
    ui->CBSR->setCurrentIndex(0);
    ui->table1->clearContents();
    ui->table1->setRowCount(0);
    Room::showAllRooms(this);
    ui->totalroom->setText(QString::number(Room::total));
    }
}

void Admin::ondelete_RT_btnClicked(int row){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete", "Are you sure you want to delete this?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        string ID = ui->RoomTypeTable->item(row, 0)->text().toStdString();
        if (RoomType::isActive(ID)){
            QMessageBox::warning(this, "Delete", "Cannot delete, this room type is currently in use!");
            return;
        } else {
        RoomType::deleteRoomType(ID);
        ui->CBSRT->setCurrentIndex(0);
        ui->RoomTypeTable->clearContents();
        ui->RoomTypeTable->setRowCount(0);
        RoomType::showAllRoomTypes(this);
        ui->totalservice->setText(QString::number(Service::total));
        }
    }
}

void Admin::on_addroom_clicked()
{
    Addroom roomDialog(this);
    roomDialog.exec();
    ui->table1->clearContents();
    ui->table1->setRowCount(0);
    Room::showAllRooms(this);
    ui->totalroom->setText(QString::number(Room::total));
}

void Admin::searchroom()
{
    string search = ui->LineEditSearchRoom->text().toStdString();
    string check = ui->CBSR->currentText().toStdString();
    if (search.empty()) {
        ui->table1->clearContents();
        ui->table1->setRowCount(0);
        Room::showAllRooms(this);
    } else {
        if (check == "Room ID"){
            ui->table1->clearContents();
            ui->table1->setRowCount(0);
            Room::searchByID(search, this);
        }
        if (ui->CBSR->currentText() == "Room Type"){
            ui->table1->clearContents();
            ui->table1->setRowCount(0);
            Room::searchByRoomType(search, this);
        }
        if (ui->CBSR->currentText() == "Tên khách thuê"){
            ui->table1->clearContents();
            ui->table1->setRowCount(0);
            Room::searchByName(search, this);
        }
    }
}

void Admin::searchRoomType(){
    string search = ui->LineEditSearchRoomType->text().toStdString();
    if (search.empty()){
        ui->RoomTypeTable->clearContents();
        ui->RoomTypeTable->setRowCount(0);
        RoomType::showAllRoomTypes(this);
    }
    if (ui->CBSRT->currentIndex() == 1){
        ui->RoomTypeTable->clearContents();
        ui->RoomTypeTable->setRowCount(0);
        RoomType::searchByID(search, this);
    }
    if (ui->CBSRT->currentIndex() == 2){
        ui->RoomTypeTable->clearContents();
        ui->RoomTypeTable->setRowCount(0);
        RoomType::searchByName(search, this);
    }
}
// void Admin::on_searchRer_clicked()
// {
//     string search = ui->LineEditSearchRe->text().toStdString();
//     ui->ReservationTable->clearContents();
//     ui->ReservationTable->setRowCount(0);
//     Reservation::searchByID(search, this);
// }

void Admin::on_CBSR_currentIndexChanged(int index)
{
    if (index == 4 || index == 5 || index == 6 || index == 7) {
        ui->LineEditSearchRoom->clear();
        ui->LineEditSearchRoom->setEnabled(false);
        ui->LineEditSearchRoom->setStyleSheet("QLineEdit { background-color: #d3d3d3; padding-left:20px; border: 1px solid gray; border-radius: 10px; }");
    } else {
        ui->LineEditSearchRoom->setEnabled(true);
        ui->LineEditSearchRoom->setStyleSheet("QLineEdit {padding-left:20px; border: 1px solid gray; border-radius: 10px;}");
    }
    string search = ui->LineEditSearchRoom->text().toStdString();
    string check = ui->CBSR->currentText().toStdString();
    if (search.empty()) {
        ui->table1->clearContents();
        ui->table1->setRowCount(0);
        Room::showAllRooms(this);
    } else {
        if (check == "Room ID"){
            ui->table1->clearContents();
            ui->table1->setRowCount(0);
            Room::searchByID(search, this);
        }
        if (ui->CBSR->currentText() == "Room Type"){
            ui->table1->clearContents();
            ui->table1->setRowCount(0);
            Room::searchByRoomType(search, this);
        }
        if (ui->CBSR->currentText() == "Tên khách thuê"){
            ui->table1->clearContents();
            ui->table1->setRowCount(0);
            Room::searchByName(search, this);
        }
    }
    if (ui->CBSR->currentIndex() == 4){

        ui->table1->clearContents();
        ui->table1->setRowCount(0);
        ui->LineEditSearchRoom->clear();
        Room::searchByStatus(0, this);
    }
    if (ui->CBSR->currentIndex() == 5){

        ui->table1->clearContents();
        ui->table1->setRowCount(0);
        ui->LineEditSearchRoom->clear();
        Room::searchByStatus(1, this);
    }
    if (ui->CBSR->currentIndex() == 6){

        ui->table1->clearContents();
        ui->table1->setRowCount(0);
        ui->LineEditSearchRoom->clear();
        Room::searchByStatus(3, this);
    }
    if (ui->CBSR->currentIndex() ==  7){
        ui->table1->clearContents();
        ui->table1->setRowCount(0);
        ui->LineEditSearchRoom->clear();
        Room::searchByStatus(2, this);
    }
}

void Admin::on_Refbtn_clicked()
{
    ui->table1->clearContents();
    ui->table1->setRowCount(0);
    Room::showAllRooms(this);
    ui->LineEditSearchRoom->clear();
    ui->CBSR->setCurrentIndex(0);
}

void Admin::on_RefRTbtn_clicked()
{
    ui->RoomTypeTable->clearContents();
    ui->RoomTypeTable->setRowCount(0);
    RoomType::showAllRoomTypes(this);
    ui->LineEditSearchRoomType->clear();
    ui->CBSRT->setCurrentIndex(0);
}

void Admin::on_RoomTypebtn1_clicked()
{
    ui->stackedWidget->setCurrentIndex(10);
}

void Admin::on_RoomTypebtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(10);
}

void Admin::on_addroomtype_clicked()
{
    Addroomtype a(this);
    a.exec();
    ui->RoomTypeTable->clearContents();
    ui->RoomTypeTable->setRowCount(0);
    RoomType::showAllRoomTypes(this);
}
