#include "ConnectComponentCommand.h"

ConnectComponentCommand::ConnectComponentCommand()
{
}

ConnectComponentCommand::ConnectComponentCommand(ERModel* model, int firstNodeID, int secondNodeID, string cardinality)
{
	_model = model;
	_firstID = firstNodeID;
	_secondID = secondNodeID;
	_cardinality = cardinality;
}

ConnectComponentCommand::~ConnectComponentCommand()
{
}

// 執行連接元件命令
void ConnectComponentCommand::execute()
{
	_model->addConnection(_firstID, _secondID, _cardinality);
}

// 反向執行連接元件命令
void ConnectComponentCommand::unexecute()
{
	_model->deleteLastComponent();
}
