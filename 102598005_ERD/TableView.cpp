#include "TableView.h"
#include <QDebug>

TableView::TableView()
{
	_index = NULL;
	connect(this, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(doubleClicked(const QModelIndex &)));
}

TableView::~TableView()
{
	delete _index;
}

// 處理點擊兩下事件
void TableView::doubleClicked(const QModelIndex &index)
{
	_index = &index;
}

void TableView::closeEditor(QWidget* editor, QAbstractItemDelegate::EndEditHint hint)
{
	QTableView::closeEditor(editor, hint);
	emit editChanged(_index);
	_index = NULL;
}
