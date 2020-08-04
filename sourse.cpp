#include "sourse.h"


QSqlDatabase Sourse::db=QSqlDatabase::addDatabase("QSQLITE");
bool Sourse::createConnection()
{
    Sourse::db.setDatabaseName("gameInformation.db");
    Sourse::db.open();
        if(!Sourse::db.open())
        {
            QMessageBox::critical(0,"Cannot open database",
            "Unable to establish a database connection." ,QMessageBox::Cancel);
            return false;
        }
    return true;
}
