#include "ThumbnailProxyModel.h"

#include "PictureModel.h"

const unsigned THUMBNAIL_SIZE = 350;

ThumbnailProxyModel::ThumbnailProxyModel(QObject* parent)
	: QIdentityProxyModel(parent)
{

}

QVariant ThumbnailProxyModel::data(const QModelIndex& index, int role) const
{
	if (role != Qt::DecorationRole)
	{
		return QIdentityProxyModel::data(index, role);
	}

	auto filepath = sourceModel()->data(index,
		static_cast<int>(PictureModel::PictureRole::FilePathRole)).toString();

	return *mThumbnails[filepath];
}

PictureModel* ThumbnailProxyModel::pictureModel() const
{
	return static_cast<PictureModel*>(sourceModel());
}

void ThumbnailProxyModel::generateThumbnails(const QModelIndex& startIndex, int count)
{
	if (!startIndex.isValid())
	{
		return;
	}

	auto model = startIndex.model();
	auto lastIndex = startIndex.row() + count;

	for (auto row = startIndex.row(); row < lastIndex; ++row)
	{
		const auto role = static_cast<int>(PictureModel::PictureRole::FilePathRole);
		auto filepath = model->data(model->index(row, 0), role).toString();
		QPixmap pixmap(filepath);
		auto thumbnail = new QPixmap(pixmap.scaled(THUMBNAIL_SIZE, THUMBNAIL_SIZE, Qt::KeepAspectRatio,
			Qt::SmoothTransformation));
		mThumbnails.insert(filepath, thumbnail);
	}
}

void ThumbnailProxyModel::reloadThumbnails()
{
	qDeleteAll(mThumbnails);
	mThumbnails.clear();
	generateThumbnails(index(0, 0), rowCount());
}

void ThumbnailProxyModel::setSourceModel(QAbstractItemModel* sourceModel)
{
	QIdentityProxyModel::setSourceModel(sourceModel);

	if (!sourceModel)
	{
		return;
	}

	connect(sourceModel, &QAbstractItemModel::modelReset,
		[this]
		{
			reloadThumbnails();
		});

	connect(sourceModel, &QAbstractItemModel::rowsInserted,
		[this](const QModelIndex& parent, int first, int last)
		{
			generateThumbnails(index(first, 0), last - first + 1);
		});
}