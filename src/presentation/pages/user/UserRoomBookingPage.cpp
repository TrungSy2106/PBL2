#include "User.h"
#include "ui_User.h"
#include "Account.h"
#include "Booking.h"
#include "Room.h"
#include "Tenant.h"

void User::managerooms(){
    QAction *searchAction = new QAction(QIcon(":/new/prefix1/Resources/loupe.png"), "Search", this);
    ui->LineEditSearchRoom->addAction(searchAction, QLineEdit::LeadingPosition);
    Room::searchByStatus(0, this);
    // ui->totalroom->setText(QString::number(Room::total));
    ui->table1->horizontalHeader()->setStyleSheet("QHeaderView::section { border: none; }");
    ui->table1->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->table1->horizontalHeaderItem(ui->table1->columnCount() - 1)->setTextAlignment(Qt::AlignCenter);
    ui->table1->setColumnWidth(0, 150);
    ui->table1->setColumnWidth(1, 150);
    ui->table1->setColumnWidth(2, 200);
    ui->table1->setColumnWidth(3, 150);
    ui->table1->setColumnWidth(4, 150);
    // ui->table1->setColumnWidth(5, 150);
    // ui->table1->setColumnWidth(6, 150);
    ui->table1->verticalHeader()->hide();

    //sx
    QRect headerRect = ui->table1->visualRect(ui->table1->model()->index(0, 0));
    QPushButton* sortButton = new QPushButton(ui->table1);
    sortButton->setText("");
    sortButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
    sortButton->setFixedSize(16, 16);
    sortButton->setToolTip("Sort by Room ID");
    sortButton->move(headerRect.right() - 90, headerRect.top() + 3);
    sortButton->setCheckable(true);
    connect(sortButton, &QPushButton::toggled, this, [this, sortButton](bool checked) {
        if (checked) {
            sortButton->setIcon(QIcon(":/new/prefix1/Resources/sxgiam.png"));
            Room::Descending();
            ui->table1->clearContents();
            ui->table1->setRowCount(0);
            Room::searchByStatus(0, this);
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
        } else {
            sortButton->setIcon(QIcon(":/new/prefix1/Resources/sxtang.png"));
            Room::Ascending();
            ui->table1->clearContents();
            ui->table1->setRowCount(0);
            Room::searchByStatus(0, this);
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
        }
    });
}

void User::displayRooms(const Room& room) {
    string tenantName = "N/A";
    Tenant* tenant = Tenant::tenantList.searchID(room.getTenantID());
    if (tenant != nullptr) {
        tenantName = tenant->getFullName();
    }
    int row = ui->table1->rowCount();
    ui->table1->insertRow(row);

    ui->table1->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(room.getID())));
    ui->table1->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(room.getRoomTypeID())));
    ui->table1->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(room.getRoomType()->getName())));
    ui->table1->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(room.getRoomType()->getDescription())));
    ui->table1->setItem(row, 4, new QTableWidgetItem(QString::number(room.getRoomType()->getPrice(), 'f', 2)));

    QWidget* buttonWidget = new QWidget();
    QPushButton* editButton = new QPushButton();
    editButton->setIcon(QIcon(":/new/prefix1/Resources/booking2.png"));
    editButton->setToolTip("Book");
    connect(editButton, &QPushButton::clicked, this, [this, row]() {
        onEditButtonClicked(row);
    });

    QHBoxLayout* layout = new QHBoxLayout(buttonWidget);
    layout->addWidget(editButton);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    editButton->setFixedSize(20, 20);

    buttonWidget->setLayout(layout);

    ui->table1->setCellWidget(row, 5, buttonWidget);
}

void User::onEditButtonClicked(int row){
    Booking b(ui->table1->item(row, 0)->text().toStdString(), this);
    b.exec();
    ui->table1->clearContents();
    ui->table1->setRowCount(0);
    Room::searchByStatus(0, this);
}

void User::on_roombtn_clicked()
{
    ui->stackedWidget_7->setCurrentIndex(1);
}

void User::on_pushButton_3_clicked()
{
    ui->stackedWidget_7->setCurrentIndex(1);
}

void User::searchroom()
{
    string search = ui->LineEditSearchRoom->text().toStdString();
    string check = ui->CBSR->currentText().toStdString();
    if (search.empty()) {
        ui->table1->clearContents();
        ui->table1->setRowCount(0);
        Room::searchByStatus(0, this);
    }
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
}

void User::on_Refbtn_clicked()
{
    ui->table1->clearContents();
    ui->table1->setRowCount(0);
    Room::searchByStatus(0, this);
    ui->LineEditSearchRoom->clear();
    ui->CBSR->setCurrentIndex(0);
}
