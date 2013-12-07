#ifndef _TABLEVIEW_H_
#define _TABLEVIEW_H_

#include <QTableView>
#include <QObject>

class TableView : public QTableView
{
	Q_OBJECT

public:
	TableView();
	~TableView();

signals:
	void editChanged(const QModelIndex* index);

public slots:
	void doubleClicked(const QModelIndex &index);
	void closeEditor(QWidget* editor, QAbstractItemDelegate::EndEditHint hint);

private:
	const QModelIndex* _index;
};

#endif