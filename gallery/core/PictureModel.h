#pragma once
#include "exports.h"

#include <QAbstractListModel>
#include <QHash>
#include <vector>
#include <memory>

#include "Picture.h"

class Album;
class AlbumModel;
class DatabaseManager;

class GALLERY_CORE_SHARED_EXPORT PictureModel : public QAbstractListModel
{
    Q_OBJECT

public:

    enum class PictureRole
    {
        FilePathRole = Qt::UserRole + 1,
    };

    PictureModel(const AlbumModel& albumModel, QObject* parent = 0);

    QModelIndex addPicture(const Picture& picture);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    bool removeRows(int rows, int count, const QModelIndex& parent) override;

    void setAlbumId(int albumId);
    void clearAlbum();

public slots:
    void deletePicturesForAlbum();

private:
    void loadPictures(int albumId);
    bool isIndexValid(const QModelIndex& index) const;

    DatabaseManager& mDb;
    int mAlbumId;
    std::vector<std::unique_ptr<Picture>> mPictures;
};
