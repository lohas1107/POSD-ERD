#include "TableView.h"

TableView::TableView()
{
	_index = NULL;
	connect(this, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(doubleClicked(const QModelIndex &)));
}

TableView::~TableView()
{
	delete _index;
}

// �B�z�I����U�ƥ�
void TableView::doubleClicked(const QModelIndex &index)
{
	_index = &index;
}

// �����s�边�ƥ�
void TableView::closeEditor(QWidget* editor, QAbstractItemDelegate::EndEditHint hint)
{
	QTableView::closeEditor(editor, hint);
	emit editChanged(_index);
	_index = NULL;
}
