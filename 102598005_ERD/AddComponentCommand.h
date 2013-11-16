#ifndef _ADDCOMPONENTCOMMAND_H_
#define _ADDCOMPONENTCOMMAND_H_

#include "ERModel.h"
#include "Command.h"

class AddComponentCommand : public Command
{
public:
	AddComponentCommand();
	AddComponentCommand(ERModel* model, pair<Type, string> type, string text);
	~AddComponentCommand();
	void execute();
	void unexecute();

private:
	pair<Type, string> _type;
	string _text;
};

#endif