#include "Picture.h"

Picture::Picture(const QString& filePath)
	: Picture(QUrl::fromLocalFile(filePath))
{

}

Picture::Picture(const QUrl& fileUrl)
	: mFileUrl(fileUrl)
{

}
