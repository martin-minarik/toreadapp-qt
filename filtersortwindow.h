#ifndef FILTERSORTWINDOW_H
#define FILTERSORTWINDOW_H

#include <QDialog>

namespace Ui {
class FilterSortWindow;
}

class FilterSortWindow : public QDialog
{
    Q_OBJECT

public:
    explicit FilterSortWindow(QWidget *parent = nullptr);
    ~FilterSortWindow();

private:
    Ui::FilterSortWindow *ui;
};

#endif // FILTERSORTWINDOW_H
