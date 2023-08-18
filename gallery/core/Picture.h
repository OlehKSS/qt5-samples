#pragma once
#include "exports.h"

#include <QUrl>
#include <QString>

class GALLERY_CORE_SHARED_EXPORT Picture
{
public:
	Picture(const QString& filePath = "");
	Picture(const QUrl& fileUrl);

	int id() const { return mId; };
	void setId(int id) { mId = id; };

	int albumId() const { return mAlbumId; };
	void setAlbumId(int albumId) { mAlbumId = albumId; };

	QUrl fileUrl() const { return mFileUrl; };
	void setFileUrl(const QUrl& fileUrl) { mFileUrl = fileUrl; };

private:
	int mId = -1;
	int mAlbumId = -1;
	QUrl mFileUrl;
};