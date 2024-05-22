
#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFont font("Segoe UI", 10, QFont::Bold); // Example font
    ui->tableView->horizontalHeader()->setFont(font);

    this->model = new QStandardItemModel(0, 3); // 0 rows, 3 collumns

    model->setHorizontalHeaderItem(0, new QStandardItem("Title"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Status"));
    model->setHorizontalHeaderItem(2, new QStandardItem("Due to"));

    this->ui->tableView->setModel(this->model);
    this->ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    auto& records = GlobalData::getRecords();
    for(int i = 1; i < 5; i++)
    {
        ToreadRecord record;
        record.title = "Record" + QString::number(i);
        record.status = (i < 2) ? "To read" : ((i < 4) ? "In progress" : "Done");
        record.due_to = QDateTime(QDate(2023, 6, i), QTime(i, i, 0));
        record.description = "";
        record.created = QDateTime::currentDateTime();
        record.last_edited = QDateTime::currentDateTime();

        record.book_title = "Book" + QString::number(i);
        record.book_author = "Author" + QString::number(i);
        record.book_pages =  i * 20;
        record.book_isbn = "ISBN" + QString::number(i);;
        record.book_genre = "Adventure";

        records.push_back(record);
    }

    update_table();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_button_new_clicked()
{
    CardWindow* window = new CardWindow(this);
    window->set_item_updated_callback(std::bind(&MainWindow::update_table, this));
    window->setModal(true);
    window->show();
}




void MainWindow::on_button_filter_sort_clicked()
{
    qInfo("Filter Sort button clicked");
    FilterSortWindow* window = new FilterSortWindow();
    window->setModal(true);
    window->show();
}


void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    if(index.isValid())
    {
        qInfo("Edit record");
        int row = index.row();
        CardWindow* window = new CardWindow(this);
        window->set_item_updated_callback(std::bind(&MainWindow::update_table, this));
        window->set_record_index(row);
        window->setModal(true);
        window->show();
    }
}

void MainWindow::update_table(){
    qInfo("Update table");
    model->removeRows(0, model->rowCount());
    for(auto record: GlobalData::getRecords())
    {
        QList<QStandardItem*> row;

        row = {new QStandardItem(record.title),
               new QStandardItem(record.status),
               new QStandardItem(record.due_to.toString("yyyy-MM-dd hh:mm:ss"))};

        this->model->appendRow(row);
    }
}

void MainWindow::on_button_clear_clicked()
{
    qInfo("Clear button clicked");
    int result = QMessageBox::question(this, "Confirm erasing records", "Do you really want to erase all records?");
    if(result == QMessageBox::Yes)
    {
        auto& records = GlobalData::getRecords();
        records.clear();

        update_table();
    }
}

