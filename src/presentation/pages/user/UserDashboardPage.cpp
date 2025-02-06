#include "User.h"
#include "ui_User.h"
#include "Account.h"
#include "Room.h"

void User::showlist(){
    LinkedList<Room>::Node* current = Room::roomList.begin();
    while (current != nullptr) {
        if (current->data.getTenantID() == Account::currentTenantID) {
            QListWidgetItem *newItem = new QListWidgetItem;
            newItem->setText(QString::fromStdString(current->data.getID()));
            QFont f;

            f.setPointSize(11);
            newItem->setFont(f);
            ui->listWidget->addItem(newItem);
            ui->listWidget_2->addItem(newItem);
        }
        current = current->next;
    }
}

void User::showmyroom(){
    LinkedList<Room>::Node* current = Room::roomList.begin();
    while (current != nullptr) {
        if (current->data.getTenantID() == Account::currentTenantID) {
            QListWidgetItem *newItem = new QListWidgetItem;
            newItem->setText(QString::fromStdString(current->data.getID()));
            QFont f;

            f.setPointSize(11);
            newItem->setFont(f);
            ui->listWidget_2->addItem(newItem);
        }
        current = current->next;
    }
}

void User::on_listWidget_2_clicked(){
    LinkedList<Room>::Node* current = Room::roomList.begin();
    while (current){
        if (ui->listWidget_2->currentItem()->text() == current->data.getID()){
            ui->roomID->setText(QString::fromStdString(current->data.getID()));
            ui->RTID->setText(QString::fromStdString(current->data.getRoomTypeID()));
            ui->RT->setText(QString::fromStdString(current->data.getRoomType()->getName()));
            ui->Price->setText(QString::number(current->data.getPrice(), 'f', 0));
            ui->Desc->setText(QString::fromStdString(current->data.getRoomType()->getDescription()));
            ui->stackedWidget_2->setCurrentIndex(1);
            return;
        }
        current = current->next;
    }
}

void User::on_backbtn_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}
