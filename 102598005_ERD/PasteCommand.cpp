#include "PasteCommand.h"

PasteCommand::PasteCommand(ERModel* model) : Command(model)
{
}

PasteCommand::~PasteCommand()
{
	_idTable.clear();
}

void PasteCommand::execute()
{
	_model->paste(_idTable);
}

void PasteCommand::unexecute()
{
	vector<int> deleteID;

	for (unsigned i = 0; i < _idTable.size(); i++)
	{
		deleteID.push_back(_idTable[i].second);
	}

	_model->deleteMultiple(deleteID);
}
