#ifndef _TABLEMODEL_H_
#define _TABLEMODEL_H_

#include <QStandardItemModel>
#include "PresentationModel.h"

class TableModel : public QStandardItemModel
{
public:
	TableModel(PresentationModel* presentationModel);
	~TableModel();
	void setTableData();
	Qt::ItemFlags flags (const QModelIndex &index) const;

private:
	PresentationModel* _presentationModel;
};

#endif