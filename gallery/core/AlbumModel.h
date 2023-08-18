#pragma once
#include "exports.h"

#include <QAbstractListModel>
#include <QHash>
#include <vector>
#include <memory>

#include "Album.h"
#include "DatabaseManager.h"

class GALLERY_CORE_SHARED_EXPORT AlbumModel : public QAbstractListModel
{
    Q_OBJECT

public:

    enum class Roles
    {
        IdRole = Qt::UserRole + 1,
        NameRole
    };

    AlbumModel(QObject* parent = 0);

    QModelIndex addAlbum(const Album& album);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    bool removeRows(int rows, int count, const QModelIndex& parent) override;
    // Provides meta information, so that names can be accessed via QML
    // Can be ignored for desktop widgets
    QHash<int, QByteArray> roleNames() const override;

private:
    bool isIndexValid(const QModelIndex& index) const;

    DatabaseManager& mDb;
    std::vector<std::unique_ptr<Album>> mAlbums;
};
