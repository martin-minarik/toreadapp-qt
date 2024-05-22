
#ifndef TOREADRECORD_H
#define TOREADRECORD_H
#include <QString>
#include <QString>
#include <QTime>
#include <QDateTime>



class ToreadRecord
{
public:
    ToreadRecord();
    QString title;
    QString status;
    QDateTime due_to;
    QString description;
    QDateTime created;
    QDateTime last_edited;

    QString book_title;
    QString book_author;
    int book_pages;
    QString book_isbn;
    QString book_genre;
};

#endif // TOREADRECORD_H
