#include "admin.h"
#include "ui_admin.h"
#include "Room.h"
#include "Reservation.h"
#include "Contract.h"
#include <QMessageBox>

using namespace std;

void Admin::managereservations(){
    QAction *searchAction = new QAction(QIcon(":/new/prefix1/Resources/loupe.png"), "Search", this);
    ui->LineEditSearchRe->addAction(searchAction, QLineEdit::LeadingPosition);
    Reservation::showAllReservations(this);
    ui->totalreservation->setText(QString::number(Reservation::total));
    ui->ReservationTable->horizontalHeader()->setStyleSheet("QHeaderView::section { border: none; }");
    ui->ReservationTable->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->ReservationTable->horizontalHeaderItem(ui->ReservationTable->columnCount() - 1)->setTextAlignment(Qt::AlignCenter);
    ui->ReservationTable->setColumnWidth(0, 130);
    ui->ReservationTable->setColumnWidth(1, 130);
    ui->ReservationTable->setColumnWidth(2, 130);
    ui->ReservationTable->setColumnWidth(3, 130);
    ui->ReservationTable->setColumnWidth(4, 130);
    ui->ReservationTable->setColumnWidth(5, 130);
    ui->ReservationTable->setColumnWidth(6, 130);
    ui->ReservationTable->verticalHeader()->hide();
    ui->ReservationTable->setShowGrid(false);
    // QRect headerRect = ui->ReservationTable->visualRect(ui->ReservationTable->model()->index(0, 0));
    //sx
    QRect headerReservation = ui->ReservationTable->visualRect(ui->ReservationTable->model()->index(0, 0));
    QPushButton* sortidREButton = new QPushButton(ui->ReservationTable);
    sortidREButton->setText("");
    sortidREButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
    sortidREButton->setFixedSize(16, 16);
    sortidREButton->setToolTip("Sort by ID");
    sortidREButton->move(headerReservation.right() - 35, headerReservation.top() + 3);
    sortidREButton->setCheckable(true);
    connect(sortidREButton, &QPushButton::toggled, this, [this, sortidREButton](bool checked) {
        if (checked) {
            sortidREButton->setIcon(QIcon(":/new/prefix1/Resources/sxgiam.png"));
            Reservation::sortID(false);
            ui->ReservationTable->clearContents();
            ui->ReservationTable->setRowCount(0);
            Reservation::showAllReservations(this);
            if (ui->CBSRe->currentIndex() == 1 && !ui->LineEditSearchRe->text().isEmpty()){
                sortidREButton->setIcon(QIcon(":/new/prefix1/Resources/sxgiam.png"));
                Reservation::sortID(false);
                ui->ReservationTable->clearContents();
                ui->ReservationTable->setRowCount(0);
                Reservation::searchByID(ui->LineEditSearchRe->text().toStdString(), this);
            }
            if (ui->CBSRe->currentIndex() == 2){
                sortidREButton->setIcon(QIcon(":/new/prefix1/Resources/sxgiam.png"));
                Reservation::sortID(false);
                ui->ReservationTable->clearContents();
                ui->ReservationTable->setRowCount(0);
                Reservation::searchByStatus(1, this);
            }
            if (ui->CBSRe->currentIndex() == 3){
                sortidREButton->setIcon(QIcon(":/new/prefix1/Resources/sxgiam.png"));
                Reservation::sortID(false);
                ui->ReservationTable->clearContents();
                ui->ReservationTable->setRowCount(0);
                Reservation::searchByStatus(0, this);
            }
            if (ui->CBSRe->currentIndex() == 4){
                sortidREButton->setIcon(QIcon(":/new/prefix1/Resources/sxgiam.png"));
                Reservation::sortID(false);
                ui->ReservationTable->clearContents();
                ui->ReservationTable->setRowCount(0);
                Reservation::searchByStatus(2, this);
            }
        } else {
            sortidREButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
            Reservation::sortID(true);
            ui->ReservationTable->clearContents();
            ui->ReservationTable->setRowCount(0);
            Reservation::showAllReservations(this);
            if (ui->CBSRe->currentIndex() == 1 && !ui->LineEditSearchRe->text().isEmpty()){
                sortidREButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
                Reservation::sortID(true);
                ui->ReservationTable->clearContents();
                ui->ReservationTable->setRowCount(0);
                Reservation::searchByID(ui->LineEditSearchRe->text().toStdString(), this);
            }
            if (ui->CBSRe->currentIndex() == 2){
                sortidREButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
                Reservation::sortID(true);
                ui->ReservationTable->clearContents();
                ui->ReservationTable->setRowCount(0);
                Reservation::searchByStatus(1, this);
            }
            if (ui->CBSRe->currentIndex() == 3){
                sortidREButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
                Reservation::sortID(true);
                ui->ReservationTable->clearContents();
                ui->ReservationTable->setRowCount(0);
                Reservation::searchByStatus(0, this);
            }
            if (ui->CBSRe->currentIndex() == 4){
                sortidREButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
                Reservation::sortID(true);
                ui->ReservationTable->clearContents();
                ui->ReservationTable->setRowCount(0);
                Reservation::searchByStatus(2, this);
            }
        }
    });
}

void Admin::displayReservations(const Reservation& re) {
    QString statusText;
    QColor textColor;

    switch (re.getStatus()) {
    case 0:
        statusText = "Waiting";
        textColor = QColor(255, 165, 0);
        break;
    case 1:
        statusText = "Accepted";
        textColor = QColor("green");
        break;
    case 2:
        statusText = "Rejected";
        textColor = QColor("red");
        break;
    default:
        statusText = "Unknown";
        textColor = QColor("gray");
        break;
    }

    int row = ui->ReservationTable->rowCount();
    ui->ReservationTable->insertRow(row);

    ui->ReservationTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(re.getID())));
    ui->ReservationTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(re.getRoomID())));
    ui->ReservationTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(re.getTenantID())));
    ui->ReservationTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(re.getStartDate().toString())));
    ui->ReservationTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(re.getEndDate().toString())));

    QTableWidgetItem* statusItem = new QTableWidgetItem(statusText);
    QFont font = statusItem->font();
    font.setBold(true);
    statusItem->setFont(font);
    statusItem->setForeground(textColor);
    ui->ReservationTable->setItem(row, 5, statusItem);

    if (re.getStatus() == 0) {
        QWidget* buttonWidget = new QWidget();

        QPushButton* acceptbtn = new QPushButton();
        acceptbtn->setIcon(QIcon(":/new/prefix1/Resources/accept.png"));
        acceptbtn->setToolTip("Accept");
        connect(acceptbtn, &QPushButton::clicked, this, [this, row]() {
            onacceptbtnClicked(row);
        });

        QPushButton* rejectbtn = new QPushButton();
        rejectbtn->setIcon(QIcon(":/new/prefix1/Resources/decline1.png"));
        rejectbtn->setToolTip("Reject");
        connect(rejectbtn, &QPushButton::clicked, this, [this, row]() {
            onrejectbtnClicked(row);
        });

        QHBoxLayout* layout = new QHBoxLayout(buttonWidget);
        layout->addWidget(acceptbtn);
        layout->addWidget(rejectbtn);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);
        acceptbtn->setFixedSize(20, 20);
        rejectbtn->setFixedSize(20, 20);

        buttonWidget->setLayout(layout);

        ui->ReservationTable->setCellWidget(row, 6, buttonWidget);
    }
}

void Admin::onacceptbtnClicked(int row){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Accept", "Are you sure you want to accept this?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
    string id = ui->ReservationTable->item(row, 0)->text().toStdString();
    Contract::confirmReservationandcreatContract(1, id);
    ui->ContractTable->clearContents();
    ui->ContractTable->setRowCount(0);
    Contract::showAllContracts(this);
    ui->table1->clearContents();
    ui->table1->setRowCount(0);
    Room::showAllRooms(this);
    string search = ui->LineEditSearchRe->text().toStdString();
    string check = ui->CBSRe->currentText().toStdString();
    if (search.empty()){
        ui->ReservationTable->clearContents();
        ui->ReservationTable->setRowCount(0);
        Reservation::showAllReservations(this);
    }
    if (check == "Reservation ID"){
        ui->ReservationTable->clearContents();
        ui->ReservationTable->setRowCount(0);
        Reservation::searchByID(search, this);
    }
    if (check == "Accepted"){
        ui->ReservationTable->clearContents();
        ui->ReservationTable->setRowCount(0);
        Reservation::searchByStatus(1, this);
    }
    if (check == "Waiting"){
        ui->ReservationTable->clearContents();
        ui->ReservationTable->setRowCount(0);
        Reservation::searchByStatus(0, this);
    }
    if (check == "Rejected"){
        ui->ReservationTable->clearContents();
        ui->ReservationTable->setRowCount(0);
        Reservation::searchByStatus(2, this);
    }
    }
}

void Admin::onrejectbtnClicked(int row){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Reject", "Are you sure you want to reject this?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
    string id = ui->ReservationTable->item(row, 0)->text().toStdString();
    Contract::confirmReservationandcreatContract(2, id);
    string search = ui->LineEditSearchRe->text().toStdString();
    string check = ui->CBSRe->currentText().toStdString();
    if (search.empty()){
        ui->ReservationTable->clearContents();
        ui->ReservationTable->setRowCount(0);
        Reservation::showAllReservations(this);
    }
    if (check == "Reservation ID"){
        ui->ReservationTable->clearContents();
        ui->ReservationTable->setRowCount(0);
        Reservation::searchByID(search, this);
    }
    if (check == "Accepted"){
        ui->ReservationTable->clearContents();
        ui->ReservationTable->setRowCount(0);
        Reservation::searchByStatus(1, this);
    }
    if (check == "Waiting"){
        ui->ReservationTable->clearContents();
        ui->ReservationTable->setRowCount(0);
        Reservation::searchByStatus(0, this);
    }
    if (check == "Rejected"){
        ui->ReservationTable->clearContents();
        ui->ReservationTable->setRowCount(0);
        Reservation::searchByStatus(2, this);
    }
    }
}

void Admin::searchRe(){
    string search = ui->LineEditSearchRe->text().toStdString();
    string check = ui->CBSRe->currentText().toStdString();
    if (search.empty()){
        ui->ReservationTable->clearContents();
        ui->ReservationTable->setRowCount(0);
        Reservation::showAllReservations(this);
    }
    if (check == "Reservation ID"){
        ui->ReservationTable->clearContents();
        ui->ReservationTable->setRowCount(0);
        Reservation::searchByID(search, this);
    }
}

void Admin::on_RefRebtn_clicked()
{
    ui->ReservationTable->clearContents();
    ui->ReservationTable->setRowCount(0);
    Reservation::showAllReservations(this);
    ui->LineEditSearchRe->clear();
    ui->CBSRe->setCurrentIndex(0);
    ui->LineEditSearchRe->setEnabled(true);
    ui->LineEditSearchRe->setStyleSheet("QLineEdit{padding-left:20px;border: 1px solid gray;border-radius: 10px;}");
}

void Admin::on_ReservationUsagebtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void Admin::on_Reservation1btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void Admin::on_CBSRe_currentIndexChanged(int index)
{
    if (index == 2 || index == 3 || index == 4) {
        ui->LineEditSearchRe->clear();
        ui->LineEditSearchRe->setEnabled(false);
        ui->LineEditSearchRe->setStyleSheet("QLineEdit { background-color: #d3d3d3; padding-left:20px; border: 1px solid gray; border-radius: 10px; }");
    } else {
        ui->LineEditSearchRe->setEnabled(true);
        ui->LineEditSearchRe->setStyleSheet("QLineEdit {padding-left:20px; border: 1px solid gray; border-radius: 10px;}");
    }
    string search = ui->LineEditSearchRe->text().toStdString();
    string check = ui->CBSRe->currentText().toStdString();
    if (search.empty()){
        ui->ReservationTable->clearContents();
        ui->ReservationTable->setRowCount(0);
        Reservation::showAllReservations(this);
    }
    if (check == "Reservation ID"){
        ui->ReservationTable->clearContents();
        ui->ReservationTable->setRowCount(0);
        Reservation::searchByID(search, this);
    }
    if (check == "Accepted"){
        ui->ReservationTable->clearContents();
        ui->ReservationTable->setRowCount(0);
        Reservation::searchByStatus(1, this);
    }
    if (check == "Waiting"){
        ui->ReservationTable->clearContents();
        ui->ReservationTable->setRowCount(0);
        Reservation::searchByStatus(0, this);
    }
    if (check == "Rejected"){
        ui->ReservationTable->clearContents();
        ui->ReservationTable->setRowCount(0);
        Reservation::searchByStatus(2, this);
    }
}

void Admin::onterminate_btnClicked(int row){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Xác nhận", "Bạn có chắc chắn muốn hủy hợp đồng này không?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
    string id = ui->ContractTable->item(row, 1)->text().toStdString();
    Contract::deleteContract(id);
    ui->ContractTable->clearContents();
    ui->ContractTable->setRowCount(0);
    Contract::showAllContracts(this);
    ui->table1->clearContents();
    ui->table1->setRowCount(0);
    Room::showAllRooms(this);
    }
}
