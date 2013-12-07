#include "AddComponentCommand.h"

AddComponentCommand::AddComponentCommand()
{
}

AddComponentCommand::AddComponentCommand(ERModel* model, pair<Type, string> type, string text, QPointF position) : Command(model)
{
	_type = type;
	_text = text;
	_position = position;
}

AddComponentCommand::~AddComponentCommand()
{
}

// ����s�W����
void AddComponentCommand::execute()
{
	_model->addComponent(_type, _text, _position);
}

// �ϦV����s�W����
void AddComponentCommand::unexecute()
{
	_model->deleteLastComponent();
}
