#ifndef _EDITTEXTCOMMAND_H_
#define _EDITTEXTCOMMAND_H_

#include "Command.h"

class EditTextCommand : public Command
{
public:
	EditTextCommand(ERModel* model, int index, string previousText, string editText);
	~EditTextCommand();
	void execute();
	void unexecute();

private:
	int _index;
	string _previousText;
	string _editText;
};

#endif