#include "admin.h"
#include "ui_admin.h"
#include "PaymentStatistics.h"
#include <QMessageBox>

using namespace std;

void Admin::managesta(){
    ui->stackedWidgetSta->setCurrentIndex(0);
    drawchartMonths(2024);
    ui->MonthTable->horizontalHeader()->setStyleSheet("QHeaderView::section { border: none; }");
    ui->MonthTable->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    // ui->MonthTable->horizontalHeaderItem(ui->AccountTable->columnCount() - 1)->setTextAlignment(Qt::AlignCenter);
    ui->MonthTable->verticalHeader()->hide();
    ui->MonthTable->setShowGrid(false);
    ui->YearTable->horizontalHeader()->setStyleSheet("QHeaderView::section { border: none; }");
    ui->YearTable->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    // ui->YearTable->horizontalHeaderItem(ui->AccountTable->columnCount() - 1)->setTextAlignment(Qt::AlignCenter);
    ui->YearTable->verticalHeader()->hide();
    ui->YearTable->setShowGrid(false);
}

void Admin::drawchartMonths(int year){
    QLayout *layout = ui->widgetchart->layout();
    if (layout) {
        QLayoutItem *item = layout->itemAt(0);
        if (item && item->widget()) {
            delete item->widget();
        }
        delete layout;
    }

    layout = new QVBoxLayout(ui->widgetchart);

    QChart *chart = new QChart();
    PaymentStatistics::showMonthlyComparison(year, chart, this);
    QChartView *chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);


    layout->addWidget(chartview);
    ui->widgetchart->setLayout(layout);
}

void Admin::drawchartYears(int start, int end) {
    QLayout *layout = ui->widgetchart->layout();
    if (layout) {
        QLayoutItem *item = layout->itemAt(0);
        if (item && item->widget()) {
            delete item->widget();
        }
        delete layout;
    }

    layout = new QVBoxLayout(ui->widgetchart);

    QChart *chart = new QChart();
    PaymentStatistics::showYearlyComparison(start, end, chart, this);
    QChartView *chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);

    layout->addWidget(chartview);
    ui->widgetchart->setLayout(layout);
}

void Admin::on_Statisticsbtn1_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

void Admin::on_Statisticsbtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

void Admin::on_TKbtn_clicked()
{
    if(ui->comboBoxTK->currentIndex() == 0){
        bool c;
        int year = ui->TK3year->text().toInt(&c);
        if (!c || ui->TK3year->text().isEmpty()){
            QMessageBox::warning(this, "Warning", "Năm không hợp lệ");
            return;
        }
        ui->MonthTable->clearContents();
        ui->MonthTable->setRowCount(0);
        ui->stackedWidgetSta->setCurrentIndex(0);
        drawchartMonths(year);
    }
    if(ui->comboBoxTK->currentIndex() == 1){
        bool c, d;
        int start = ui->TK2year1->text().toInt(&c);
        int end = ui->TK2year2->text().toInt(&d);
        if (!c || ui->TK2year1->text().isEmpty() || !d || ui->TK2year2->text().isEmpty()){
            QMessageBox::warning(this, "Warning", "Năm không hợp lệ");
            return;
        }
        ui->YearTable->clearContents();
        ui->YearTable->setRowCount(0);
        ui->stackedWidgetSta->setCurrentIndex(1);
        if (end - start > 15){
        QMessageBox::warning(this, "Warning", "Giới hạn các năm cách nhau không quá 15 năm");
            return;
        }
        drawchartYears(start, end);
    }
}

void Admin::on_comboBoxTK_currentIndexChanged(int index)
{
    if (index == 0){
        ui->stackedWidget_2->setCurrentIndex(1);
    }
    if (index == 1){
        ui->stackedWidget_2->setCurrentIndex(0);
    }
}

void Admin::displayMonthlyComparison(int month, double tb, double tc, double t){
    int row = ui->MonthTable->rowCount();
    ui->MonthTable->insertRow(row);

    ui->MonthTable->setItem(row, 0, new QTableWidgetItem(QString::number(month)));
    ui->MonthTable->setItem(row, 1, new QTableWidgetItem(QString::number(tb, 'f', 2)));
    ui->MonthTable->setItem(row, 2, new QTableWidgetItem(QString::number(tc, 'f', 2)));
    ui->MonthTable->setItem(row, 3, new QTableWidgetItem(QString::number(t, 'f', 2)));
}

void Admin::displayYearlyComparison(int year, double tb, double tc, double t){
    int row = ui->YearTable->rowCount();
    ui->YearTable->insertRow(row);

    ui->YearTable->setItem(row, 0, new QTableWidgetItem(QString::number(year)));
    ui->YearTable->setItem(row, 1, new QTableWidgetItem(QString::number(tb, 'f', 2)));
    ui->YearTable->setItem(row, 2, new QTableWidgetItem(QString::number(tc, 'f', 2)));
    ui->YearTable->setItem(row, 3, new QTableWidgetItem(QString::number(t, 'f', 2)));
}
