#include "PictureDao.h"
#include "Picture.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QVariant>

PictureDao::PictureDao(QSqlDatabase& database)
	: mDatabase(database)
{

}

void PictureDao::init() const
{
	if (!mDatabase.tables().contains("pictures"))
	{
		QSqlQuery query(mDatabase);
		query.exec("CREATE TABLE pictures"
			" (id INTEGER PRIMARY KEY AUTOINCREMENT, "
			"album_id INTEGER, "
			"url TEXT"
		);
	}
}

void PictureDao::addPictureInAlbum(int albumId, Picture& picture) const
{
	QSqlQuery query(mDatabase);
	query.prepare(QString("INSERT INTO pictures")
		+ " (album_id, url)"
		+ " VALUES ("
		+ ":album_id, "
		+ ":url"
		+ ")");
	query.bindValue(":album_id", albumId);
	query.bindValue(":url", picture.fileUrl());
	query.exec();
	picture.setId(query.lastInsertId().toInt());
	picture.setAlbumId(albumId);
}

void PictureDao::removePicture(int id) const
{
	QSqlQuery query(mDatabase);
	query.prepare("DELETE FROM pictures WHERE id = (:id)");
	query.bindValue(":id", id);
	query.exec();
}

void PictureDao::removePicturesForAlbum(int albumId) const
{
	QSqlQuery query(mDatabase);
	query.prepare("DELETE FROM pictures WHERE album_id = (:album_id)");
	query.bindValue(":album_id", albumId);
	query.exec();
}

std::vector<std::unique_ptr<Picture>> PictureDao::picturesForAlbum(int albumId) const
{
	QSqlQuery query(mDatabase);
	query.prepare("SELECT * FROM pictures WHERE album_id = (:album_id)");
	query.bindValue(":album_id", albumId);
	query.exec();

	std::vector<std::unique_ptr<Picture>> list;
	while (query.next()) {
		auto picture = std::make_unique<Picture>();
		picture->setId(query.value("id").toInt());
		picture->setAlbumId(query.value("album_id").toInt());
		picture->setFileUrl(query.value("url").toString());
		list.push_back(std::move(picture));
	}
	return list;
}
