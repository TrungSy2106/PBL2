QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

INCLUDEPATH += \
    $$PWD/src/core \
    $$PWD/src/domain \
    $$PWD/src/presentation/dialogs \
    $$PWD/src/presentation/statistics \
    $$PWD/src/presentation/windows

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/app/main.cpp \
    src/core/Date.cpp \
    src/core/LinkedList.cpp \
    src/domain/Account.cpp \
    src/domain/Contract.cpp \
    src/domain/Payment.cpp \
    src/domain/Reservation.cpp \
    src/domain/Room.cpp \
    src/domain/RoomType.cpp \
    src/domain/Service.cpp \
    src/domain/ServiceUsage.cpp \
    src/domain/Tenant.cpp \
    src/presentation/dialogs/AddService.cpp \
    src/presentation/dialogs/Addroom.cpp \
    src/presentation/dialogs/Addroomtype.cpp \
    src/presentation/dialogs/Adminaccount.cpp \
    src/presentation/dialogs/Booking.cpp \
    src/presentation/dialogs/Createpayment.cpp \
    src/presentation/dialogs/Editroom.cpp \
    src/presentation/dialogs/Editroomtype.cpp \
    src/presentation/dialogs/Editservice.cpp \
    src/presentation/dialogs/Edittenant.cpp \
    src/presentation/dialogs/Extend.cpp \
    src/presentation/dialogs/Paybill.cpp \
    src/presentation/statistics/PaymentStatistics.cpp \
    src/presentation/windows/Signin.cpp \
    src/presentation/windows/User.cpp \
    src/presentation/windows/admin.cpp

HEADERS += \
    src/core/Date.h \
    src/core/LinkedList.h \
    src/domain/Account.h \
    src/domain/Contract.h \
    src/domain/Payment.h \
    src/domain/Reservation.h \
    src/domain/Room.h \
    src/domain/RoomType.h \
    src/domain/Service.h \
    src/domain/ServiceUsage.h \
    src/domain/Tenant.h \
    src/presentation/dialogs/AddService.h \
    src/presentation/dialogs/Addroom.h \
    src/presentation/dialogs/Addroomtype.h \
    src/presentation/dialogs/Adminaccount.h \
    src/presentation/dialogs/Booking.h \
    src/presentation/dialogs/Createpayment.h \
    src/presentation/dialogs/Editroom.h \
    src/presentation/dialogs/Editroomtype.h \
    src/presentation/dialogs/Editservice.h \
    src/presentation/dialogs/Edittenant.h \
    src/presentation/dialogs/Extend.h \
    src/presentation/dialogs/Paybill.h \
    src/presentation/statistics/PaymentStatistics.h \
    src/presentation/windows/Signin.h \
    src/presentation/windows/User.h \
    src/presentation/windows/admin.h

FORMS += \
    src/presentation/dialogs/AddService.ui \
    src/presentation/dialogs/Addroom.ui \
    src/presentation/dialogs/Addroomtype.ui \
    src/presentation/dialogs/Adminaccount.ui \
    src/presentation/dialogs/Booking.ui \
    src/presentation/dialogs/Createpayment.ui \
    src/presentation/dialogs/Editroom.ui \
    src/presentation/dialogs/Editroomtype.ui \
    src/presentation/dialogs/Editservice.ui \
    src/presentation/dialogs/Edittenant.ui \
    src/presentation/dialogs/Extend.ui \
    src/presentation/dialogs/Paybill.ui \
    src/presentation/windows/Signin.ui \
    src/presentation/windows/User.ui \
    src/presentation/windows/admin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc

# Keep demo data in source control and copy it beside the build working
# directory so the application can run immediately after a fresh build.
DEMO_DATA_FILES = \
    $$PWD/data/Account.txt \
    $$PWD/data/Contract.txt \
    $$PWD/data/Payment.txt \
    $$PWD/data/Reservation.txt \
    $$PWD/data/Room.txt \
    $$PWD/data/RoomType.txt \
    $$PWD/data/Service.txt \
    $$PWD/data/ServiceUsage.txt \
    $$PWD/data/Tenant.txt

demo_data.files = $$DEMO_DATA_FILES
win32 {
    CONFIG(debug, debug|release) {
        demo_data.path = $$OUT_PWD/debug
    } else {
        demo_data.path = $$OUT_PWD/release
    }
} else {
    demo_data.path = $$OUT_PWD
}
COPIES += demo_data

OTHER_FILES += $$DEMO_DATA_FILES
