#include "TableModel.h"

TableModel::TableModel()
{
}

TableModel::~TableModel()
{
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
	if (index.column() == 0)
	{
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	}
	else
	{
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
	}
}
