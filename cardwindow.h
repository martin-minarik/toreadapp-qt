#ifndef CARDWINDOW_H
#define CARDWINDOW_H

#include <QDialog>
#include <functional>
#include <list>
#include "toreadrecord.h"
#include <optional>
#include "globaldata.h"
#include <QMessageBox>

namespace Ui {
class CardWindow;
}

class CardWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CardWindow(QWidget *parent = nullptr);
    ~CardWindow();

    void set_item_updated_callback(std::function<void()> callback);
    void set_record_index(unsigned int index);

private slots:
    void on_button_delete_clicked();

    void on_button_save_clicked();

private:
    std::optional<int> record_index;
    Ui::CardWindow *ui;
    std::function<void()> item_updated_callback;
};

#endif // CARDWINDOW_H
