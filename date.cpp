#include "date.h"

Date::Date(){

}

Date::Date(const QDate& D){
    this->setDate(D.year(), D.month(), D.day());
}

Date Date::fromString(string date){
    QDate d = QDate::fromString(QString::fromUtf8(date.c_str()), "dd.MM.yyyy");
    Date n = d;
    return n;

}

istream &operator>>( istream  &input, Date &D ){
        int d, m, y;
        input >> d >> m >> y;
        D.setDate(y, m, d);
        return input;
}

ostream &operator<<( ostream &output, const Date &D){
        output << D.toString("dd.MM.yyyy").toStdString();
        return output;
}

