#ifndef _TABLEMODEL_H_
#define _TABLEMODEL_H_

#include <QStandardItemModel>
#include "PresentationModel.h"
#include <QObject>

class TableModel : public QStandardItemModel
{
	Q_OBJECT

public:
	TableModel(PresentationModel* presentationModel);
	~TableModel();
	void setTableData();
	Qt::ItemFlags flags(const QModelIndex &index) const;

public slots:
	void editChanged(const QModelIndex* index);

private:
	PresentationModel* _presentationModel;
};

#endif