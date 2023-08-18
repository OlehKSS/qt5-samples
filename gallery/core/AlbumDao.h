#pragma once
#include <memory>
#include <vector>

class QSqlDatabase;
class Album;

class AlbumDao
{
public:
	explicit AlbumDao(QSqlDatabase& database);
	void init() const;
	void addAlbum(Album& album) const;
	void updateAlbum(const Album& album) const;
	void removeAlbum(int id) const;
	std::vector<std::unique_ptr<Album>> albums() const;

private:
	QSqlDatabase& mDatabase;
};