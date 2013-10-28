#include "DeleteComponentCommand.h"

DeleteComponentCommand::DeleteComponentCommand(ERModel* model, int id)
{
	_model = model;
	_id = id;

	vector<ERComponent*> deleteList = _model->getDeleteList(_id);

	for (unsigned i = 0; i < deleteList.size(); i++)
	{
		int index = _model->findIndex(deleteList[i]->getID());
		_deleteList.push_back(make_pair(index, deleteList[i]->clone()));
	}
}

DeleteComponentCommand::~DeleteComponentCommand()
{
	while (!_deleteList.empty())
	{
		ERComponent* toDelete = _deleteList.back().second;
		_deleteList.pop_back();
		delete toDelete;
	}
}

// 執行刪除元件命令
void DeleteComponentCommand::execute()
{
	_model->deleteComponent(_id);
}

// 反向執行刪除元件命令
void DeleteComponentCommand::unexecute()
{
	_model->revertComponent(_deleteList);
}
