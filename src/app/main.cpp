#include "admin.h"
#include "Signin.h"
#include "RoomType.h"
#include "Room.h"
#include "Tenant.h"
#include "Service.h"
#include "ServiceUsage.h"
#include "Reservation.h"
#include "Payment.h"
#include "Contract.h"

#include <QApplication>
#include <QColor>
#include <QPalette>

int main(int argc, char *argv[]) {
    RoomType::load("RoomType.txt");
    Room::load("Room.txt");
    Tenant::load("Tenant.txt");
    Service::load("Service.txt");
    ServiceUsage::load("ServiceUsage.txt");
    Reservation::load("Reservation.txt");
    Account::load("Account.txt");
    Payment::load("Payment.txt");
    Contract::load("Contract.txt");

    QApplication a(argc, argv);

    // Keep widgets readable when the operating system uses a dark theme.
    // Individual windows still retain their own explicitly styled dark areas.
    QPalette palette = a.palette();
    palette.setColor(QPalette::Window, QColor(243, 243, 243));
    palette.setColor(QPalette::WindowText, QColor(35, 35, 35));
    palette.setColor(QPalette::Base, Qt::white);
    palette.setColor(QPalette::AlternateBase, QColor(247, 247, 247));
    palette.setColor(QPalette::Text, QColor(35, 35, 35));
    palette.setColor(QPalette::Button, QColor(243, 243, 243));
    palette.setColor(QPalette::ButtonText, QColor(35, 35, 35));
    palette.setColor(QPalette::ToolTipBase, Qt::white);
    palette.setColor(QPalette::ToolTipText, QColor(35, 35, 35));
    palette.setColor(QPalette::Highlight, QColor(63, 211, 145));
    palette.setColor(QPalette::HighlightedText, Qt::white);
    a.setPalette(palette);

    // Tables use a white body inside dark pages, so their text color must be
    // explicit instead of inheriting white text from the surrounding frame.
    a.setStyleSheet(R"(
        QTableView, QTableWidget, QTreeView, QTreeWidget, QListView, QListWidget {
            color: #232323;
            background-color: #ffffff;
            alternate-background-color: #f7f7f7;
            selection-color: #ffffff;
            selection-background-color: #3fd391;
        }
    )");

    Signin w;
    w.show();
    return a.exec();
}
