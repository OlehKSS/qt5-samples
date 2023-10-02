#include "AlbumListWidget.h"
#include "ui_AlbumListWidget.h"

#include <QInputDialog>

#include "AlbumModel.h"

AlbumListWidget::AlbumListWidget(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::AlbumListWidget)
{
	ui->setupUi(this);

	connect(ui->createAlbumButton, &QPushButton::clicked,
		this, &AlbumListWidget::createAlbum);
}

AlbumListWidget::~AlbumListWidget()
{
	delete ui;
}

void AlbumListWidget::setModel(AlbumModel* model)
{
	mAlbumModel = model;
	ui->albumList->setModel(mAlbumModel);
}

void AlbumListWidget::setSelectionModel(QItemSelectionModel* selectionModel)
{
	ui->albumList->setSelectionModel(selectionModel);
}

void AlbumListWidget::createAlbum()
{
	if (!mAlbumModel)
	{
		return;
	}

	auto ok = false;
	auto albumName = QInputDialog::getText(this,
		tr("Create a new album"),
		tr("Choose a name"),
		QLineEdit::Normal,
		tr("New album"),
		&ok);

	if (ok && !albumName.isEmpty())
	{
		Album album(albumName);
		auto createdIndex = mAlbumModel->addAlbum(album);
		ui->albumList->setCurrentIndex(createdIndex);
	}
}
