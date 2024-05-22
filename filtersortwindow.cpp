#include "filtersortwindow.h"
#include "ui_filtersortwindow.h"

FilterSortWindow::FilterSortWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterSortWindow)
{
    ui->setupUi(this);
}

FilterSortWindow::~FilterSortWindow()
{
    delete ui;
}
