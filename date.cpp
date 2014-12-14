#include "date.h"

Date::Date() {

}

Date::Date(const QDate &D) {
    this->setDate(D.year(), D.month(), D.day());
}

Date Date::now() {
    return QDate::currentDate();
}

//Converts a string to a date using QDate functions
Date Date::fromString(string date) {
    return Date::fromString(QString::fromStdString(date));
}

Date Date::fromString(QString date){
    QDate d = QDate::fromString(date, "dd.MM.yyyy");
    return d;
}

//Converts a date to a string
string Date::toDateString() const{
    return toString("dd.MM.yyyy").toStdString();
}

ostream &operator<<( ostream &output, const Date &D) {
        output << D.toDateString();
        return output;
}
