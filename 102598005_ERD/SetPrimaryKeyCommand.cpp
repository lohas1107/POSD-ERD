#include "SetPrimaryKeyCommand.h"
#include "AttributeNode.h"

SetPrimaryKeyCommand::SetPrimaryKeyCommand(ERModel* model, int id) : Command(model)
{
	_id = id;
	_isPrimaryKey = ((AttributeNode*)_model->getComponent(id))->isPrimaryKey();
}

SetPrimaryKeyCommand::~SetPrimaryKeyCommand()
{
}

// 執行設定 primary key
void SetPrimaryKeyCommand::execute()
{
	_model->setNodePrimaryKey(_id, !_isPrimaryKey);
}

// 反向執行設定 primary key
void SetPrimaryKeyCommand::unexecute()
{
	_model->setNodePrimaryKey(_id, _isPrimaryKey);
}
