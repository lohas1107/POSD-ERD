#ifndef _PASTECOMMAND_H_
#define _PASTECOMMAND_H_

#include "Command.h"

class PasteCommand : public Command
{
public:
	PasteCommand(ERModel* model);
	~PasteCommand();
	void execute();
	void unexecute();
};

#endif