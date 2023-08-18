#pragma once
#include <memory>
#include <vector>

class QSqlDatabase;
class Picture;

class PictureDao
{
public:
	explicit PictureDao(QSqlDatabase& database);
	void init() const;
	void addPictureInAlbum(int albumId, Picture& picture) const;
	void removePicture(int id) const;
	void removePicturesForAlbum(int albumId) const;
	std::vector<std::unique_ptr<Picture>> picturesForAlbum(int albumId) const;

private:
	QSqlDatabase& mDatabase;
};