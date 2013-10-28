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

// ����s������R�O
void ConnectComponentCommand::execute()
{
	_model->addConnection(_firstID, _secondID, _cardinality);
}

// �ϦV����s������R�O
void ConnectComponentCommand::unexecute()
{
	_model->deleteLastComponent();
}
