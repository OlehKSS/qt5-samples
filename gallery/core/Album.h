#pragma once
#include "exports.h"

#include <QString>

class GALLERY_CORE_SHARED_EXPORT Album
{
public:
	explicit Album(const QString& name = "");

	int id() const { return mId; };
	void setId(int id) { mId = id; };
	QString name() const { return mName; };
	void setName(const QString& name) { mName = name; };

private:
	int mId;
	QString mName;
};