#ifndef _PRESENTATIONMODEL_H_
#define _PRESENTATIONMODEL_H_

#include "ERModel.h"
#include "CommandManager.h"
#include <vector>

class PresentationModel
{
	friend class PresentationModelTest;
	FRIEND_TEST(PresentationModelTest, addNodeCommand);
	FRIEND_TEST(PresentationModelTest, canUndo);

public:
	PresentationModel();
	PresentationModel(ERModel* erModel);
	~PresentationModel();
	bool checkInputType(string type);
	int addNodeCommand(string type, string name);
	int getNodeID();
	string getNodeType(int id);
	string getNodeText(int id);
	string getComponentLine(Type type);
	vector<ERComponent*> getComponents();
	void connectNodeCommand(int firstNodeID, int secondNodeID, string cardinality);
	int getComponentSize();
	bool isIDExsit(int id);
	string getCardinality(int cardinality);
	bool hasConnection(int firstNodeID, int secondNodeID);
	bool isCreationFail();
	bool needAskCardinality(int firstNodeID, int secondNodeID);
	string getConnectionLine();
	bool isType(int id, Type type);
	bool hasAttribute(int id);
	string getAttributeLine(int id);
	bool hasEntity();
	bool isAttribute(int entityID, int attribute);
	string getPrimaryKey(int entityID);
	void setPrimaryKey(vector<int> primaryKey);
	bool displayTableCommand();
	string getTable();
	bool loadFile(string filePath);
	bool saveFile(string filePath);
	void makeDirectory(string filePath);
	void deleteComponentCommand(int id);
	void undo();
	bool canUndo();
	void redo();
	bool canRedo();
	void composePosition();
private:
	ERModel* _erModel;
	CommandManager _commandManager;
};

#endif