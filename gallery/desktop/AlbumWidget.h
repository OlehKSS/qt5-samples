#pragma once

#include <QWidget>
#include <QModelIndex>

namespace Ui
{
	class AlbumWidget;
}

class AlbumModel;
class PictureModel;
class QItemSelectionModel;
class ThumbnailProxyModel;

class AlbumWidget : public QWidget
{
	Q_OBJECT

public:
	explicit AlbumWidget(QWidget* parent = 0);
	~AlbumWidget();

	void setAlbumModel(AlbumModel* albumModel);
	void setAlbumSelectionModel(QItemSelectionModel* albumSelectionModel);
	void setPictureModel(ThumbnailProxyModel* pictureModel);
	void setPictureSelectionModel(QItemSelectionModel* selectionModel);

signals:
	void pictureActivated(const QModelIndex& index);

private slots:
	void deleteAlbum();
	void editAlbum();
	void addPictures();

private:
	void clearUi();
	void loadAlbum(const QModelIndex& albumIndex);

	Ui::AlbumWidget* ui;
	AlbumModel* mAlbumModel = nullptr;
	QItemSelectionModel* mAlbumSelectionModel = nullptr;
	
	ThumbnailProxyModel* mPictureModel = nullptr;
	QItemSelectionModel* mPictureSelectionModel = nullptr;
};