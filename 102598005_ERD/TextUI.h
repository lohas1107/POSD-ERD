#ifndef _TEXTUI_H_
#define _TEXTUI_H_

#include "PresentationModel.h"

class TextUI
{
public:
	TextUI(PresentationModel* presentationModel);
	~TextUI();
	void displayMenu();
	void processCommand();
	void loadFile();
	void saveFile();
	void addNodeCommand();
	void showComponents(Type type);
	void connectNodeCommand();
	int getInputID();
	bool isValidID(int firstNodeID, int secondNodeID);
	string getCardinality(int firstNodeID, int secondNodeID);
	void printConnections();
	void showConnections();
	void displayDiagramCommand();
	void setPrimaryKeyCommand();
	void showAttribute(int id);
	vector<int> getAttributeID(int id);
	void displayTableCommand();
	void deleteComponentCommand();
	void undo();
	void redo();
	void remindSaveFile();

private:
	PresentationModel* _presentationModel;
};

#endif