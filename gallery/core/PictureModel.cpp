#include "PictureModel.h"

#include "AlbumModel.h"
#include "DatabaseManager.h"


PictureModel::PictureModel(const AlbumModel& albumModel, QObject* parent)
    : QAbstractListModel(parent)
    , mDb(DatabaseManager::instance())
    , mAlbumId(-1)
{
    connect(&albumModel, &AlbumModel::rowsRemoved, this, &PictureModel::deletePicturesForAlbum);
}

QModelIndex PictureModel::addPicture(const Picture& picture)
{
    int rows = rowCount();
    beginInsertRows(QModelIndex(), rows, rows);
    auto newPicture = std::make_unique<Picture>(picture);
    mDb.pictureDao.addPictureInAlbum(mAlbumId, *newPicture);
    mPictures.push_back(std::move(newPicture));
    endInsertRows();
    return index(rows, 0);
}

int PictureModel::rowCount(const QModelIndex& parent) const
{
    return mPictures.size();
}

QVariant PictureModel::data(const QModelIndex& index, int role) const
{
	using enum PictureRole;

	if (!isIndexValid(index))
	{
		return QVariant();
	}

	const auto& picture = mPictures.at(index.row());

	switch (role)
	{
	case static_cast<int>(FilePathRole):
		return picture->fileUrl();
	default:
		return QVariant();
	}
}

bool PictureModel::removeRows(int row, int count, const QModelIndex& parent)
{
    if (row < 0
        || row >= rowCount()
        || count < 0
        || (row + count) > rowCount()) {
        return false;
    }

    beginRemoveRows(parent, row, row + count - 1);
    int countLeft = count;
    while (countLeft--) {
        const Picture& picture = *mPictures.at(row + countLeft);
        mDb.pictureDao.removePicture(picture.id());
    }
    mPictures.erase(mPictures.begin() + row,
        mPictures.begin() + row + count);
    endRemoveRows();


    return true;
}

void PictureModel::setAlbumId(int albumId)
{
    if (albumId <= 0)
    {
        mPictures.clear();
    }
    mPictures = mDb.pictureDao.picturesForAlbum(albumId);
}

void PictureModel::clearAlbum()
{
    setAlbumId(-1);
}

void PictureModel::deletePicturesForAlbum()
{
    mDb.pictureDao.removePicturesForAlbum(mAlbumId);
    clearAlbum();
}

void PictureModel::loadPictures(int albumId)
{
    if (albumId <= 0) {
        mPictures.clear();
        return;
    }
    mPictures = mDb.pictureDao.picturesForAlbum(albumId);
}

bool PictureModel::isIndexValid(const QModelIndex& index) const
{
    if (index.row() < 0
        || index.row() >= rowCount()
        || !index.isValid()) {
        return false;
    }
    return true;
}