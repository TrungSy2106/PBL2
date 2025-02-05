#ifndef EXTEND_H
#define EXTEND_H

#include <QDialog>

namespace Ui {
class Extend;
}

class Extend : public QDialog
{
    Q_OBJECT

public:
    explicit Extend(const std::string idr, const std::string idt, QWidget *parent = nullptr);
    ~Extend();

private slots:
    void on_Extenbtn_clicked();

private:
    std::string idr;
    std::string idt;
    Ui::Extend *ui;
};

#endif // EXTEND_H
