#ifndef _TABLEMODEL_H_
#define _TABLEMODEL_H_

#include <QStandardItemModel>

class TableModel : public QStandardItemModel
{
public:
	TableModel();
	~TableModel();
	Qt::ItemFlags flags (const QModelIndex &index) const;
};

#endif