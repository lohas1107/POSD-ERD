#include "TableModel.h"
#include "ERComponent.h"

TableModel::TableModel(PresentationModel* presentationModel)
{
	_presentationModel = presentationModel;
}

TableModel::~TableModel()
{
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
	if (index.column() == 0 || !_presentationModel->isEditable(index.row()))
	{
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	}
	else
	{
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
	}
}

void TableModel::setTableData()
{
	vector<ERComponent*> components = _presentationModel->getComponents();

	for (unsigned i = 0; i < components.size(); i++)
	{
		setItem(i, 0, new QStandardItem(QString::fromStdString(components[i]->getType().second)));
		setItem(i, 1, new QStandardItem(QString::fromStdString(components[i]->getText())));
	}
}
