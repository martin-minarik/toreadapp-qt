#include "cardwindow.h"
#include "ui_cardwindow.h"

CardWindow::CardWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CardWindow)
{
    ui->setupUi(this);
    ui->calendar->setSelectedDate(QDate::currentDate());
    ui->time_edit->setTime(QTime::currentTime());
}

CardWindow::~CardWindow()
{
    delete ui;
}

void CardWindow::set_record_index(unsigned int index)
{
    this->record_index = index;
    auto& records = GlobalData::getRecords();
    if(index < records.size())
    {
        auto &record = records[index];
        ui->line_edit_title->setText(record.title);
        ui->combo_box_status->setCurrentText(record.status);
        ui->label_created_value->setText(record.created.toString("yyyy-MM-dd hh:mm:ss"));
        ui->label_last_edit_value->setText(record.last_edited.toString("yyyy-MM-dd hh:mm:ss"));
        ui->calendar->setSelectedDate(record.due_to.date());
        ui->time_edit->setTime(record.due_to.time());
        ui->text_edit_description->setPlainText(record.description);

        ui->line_edit_book_title->setText(record.book_title);
        ui->line_edit_book_author->setText(record.book_author);
        ui->spin_box_book_pages->setValue(record.book_pages);
        ui->line_edit_book_isbn->setText(record.book_isbn);
        ui->combo_box_book_genre->setCurrentText(record.book_genre);
    }
}


void CardWindow::on_button_delete_clicked()
{

    qInfo("Delete button clicked");

    int result = QMessageBox::question(this, "Confirm deleting record", "Do you really want to delete the record?");
    if(result == QMessageBox::No)
        return;

    if(this->record_index.has_value())
    {
        auto& records = GlobalData::getRecords();
        records.erase(records.begin() + this->record_index.value());

        if(item_updated_callback)
            item_updated_callback();
    }

    this->close();
}


void CardWindow::on_button_save_clicked()
{
    qInfo("Save button clicked");

    if(ui->line_edit_title->text().isEmpty())
    {
        QMessageBox::warning(this, "Invalid title", "Invalid title");
        return;
    }


    auto& records = GlobalData::getRecords();
    ToreadRecord *record;
    if(this->record_index.has_value())
    {
        record = &records[this->record_index.value()];

    }
    else{
        record = new ToreadRecord();
        record->created = QDateTime::currentDateTime();
    }

    record->title = ui->line_edit_title->text();
    record->status =  ui->combo_box_status->currentText();
    record->due_to = QDateTime(ui->calendar->selectedDate(), ui->time_edit->time());
    record->description = ui->text_edit_description->toPlainText();
    record->last_edited = QDateTime::currentDateTime();
    record->book_title = ui->line_edit_book_title->text();
    record->book_author =ui->line_edit_book_author->text();
    record->book_pages =  ui->spin_box_book_pages->value();
    record->book_isbn = ui->line_edit_book_isbn->text();
    record->book_genre = ui->combo_box_book_genre->currentText();

    if(!this->record_index.has_value())
    {
        records.push_back(*record);
        delete record;
    }


    if(item_updated_callback)
        item_updated_callback();

    this->close();
}

void CardWindow::set_item_updated_callback(std::function<void()> callback)
{
    item_updated_callback = callback;
}

