
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItem>
#include <string>
#include "filtersortwindow.h"
#include "cardwindow.h"
#include "toreadrecord.h"
#include <vector>
#include "globaldata.h"
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_button_new_clicked();

    void on_button_filter_sort_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_button_clear_clicked();

private:
    void update_table();
    QStandardItemModel* model;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
