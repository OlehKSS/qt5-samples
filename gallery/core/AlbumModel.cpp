#include "AlbumModel.h"

AlbumModel::AlbumModel(QObject* parent)
	: QAbstractListModel(parent)
	, mDb(DatabaseManager::instance())
	, mAlbums(mDb.albumDao.albums())
{

}

QModelIndex AlbumModel::addAlbum(const Album& album)
{
	auto rowIndex = rowCount();
	beginInsertRows(QModelIndex(), rowIndex, rowIndex);
	auto newAlbum = std::make_unique<Album>(album);
	mDb.albumDao.addAlbum(*newAlbum);
	mAlbums.push_back(std::move(newAlbum));
	endInsertRows();
	return index(rowIndex, 0);
}

int AlbumModel::rowCount(const QModelIndex& parent) const
{
	return mAlbums.size();
}

QVariant AlbumModel::data(const QModelIndex& index, int role) const
{
	using enum Roles;

	if (!isIndexValid(index))
	{
		return QVariant();
	}

	const auto& album = mAlbums.at(index.row());

	switch (role)
	{
	case static_cast<int>(IdRole):
		return album->id();
	case static_cast<int>(NameRole):
	case Qt::DisplayRole:
		return album->name();
	default:
		return QVariant();
	}
}

bool AlbumModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (!isIndexValid(index) || role != static_cast<int>(Roles::NameRole))
	{
		return false;
	}

	auto& album = *mAlbums.at(index.row());
	album.setName(value.toString());
	mDb.albumDao.updateAlbum(album);
	emit dataChanged(index, index);
	return true;
}

bool AlbumModel::removeRows(int row, int count, const QModelIndex& parent)
{
	if (row < 0 || row >= rowCount() || count < 0
		|| (row + count) > rowCount())
	{
		return false;
	}

	beginRemoveRows(parent, row, row + count - 1);
	int countLeft = count;
	while (countLeft--)
	{
		const auto& album = *mAlbums.at(row + countLeft);
		mDb.albumDao.removeAlbum(album.id());
	}

	mAlbums.erase(mAlbums.begin() + row, mAlbums.begin() + row + count);
	endRemoveRows();
	return true;
}

QHash<int, QByteArray> AlbumModel::roleNames() const
{
	using enum Roles;
	QHash<int, QByteArray> roles;
	roles[static_cast<int>(IdRole)] = "id";
	roles[static_cast<int>(NameRole)] = "name";
	return roles;
}

bool AlbumModel::isIndexValid(const QModelIndex& index) const
{
	if (index.row() < 0
		|| index.row() >= rowCount()
		|| !index.isValid()) {
		return false;
	}
	return true;
}
