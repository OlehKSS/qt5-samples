#include "DatabaseManager.h"

#include <QSqlDatabase>

DatabaseManager& DatabaseManager::instance()
{
	static DatabaseManager singleton;
	return singleton;
}

DatabaseManager::DatabaseManager(const QString& path)
	: mDatabase(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE")))
	, albumDao(*mDatabase)
	, pictureDao(*mDatabase)
{
	mDatabase->setDatabaseName(path);
	mDatabase->open();

	albumDao.init();
	pictureDao.init();
}

// So that we can use std::unique_ptr with an incomplete type
DatabaseManager::~DatabaseManager() = default;
