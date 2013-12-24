#ifndef _PRESENTATIONMODEL_H_
#define _PRESENTATIONMODEL_H_

#include "ERModel.h"
#include "CommandManager.h"
#include <vector>
#include <QPointF>
#include "SaveComponentVisitor.h"

class PresentationModel
{
public:
	PresentationModel(ERModel* erModel);
	~PresentationModel();
	bool checkInputType(string type);
	void addNodeCommand(string type, string name, QPointF position);
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
	bool isOneToOneExist();
	string getTable();
	bool loadFile(string filePath);
	bool saveFile(string filePath);
	void savePosition(string filePath, ComponentVisitor* visitor);
	void makeDirectory(string filePath);
	void deleteComponentCommand(int id);
	void undo();
	bool canUndo();
	void redo();
	bool canRedo();
	void composePosition();
	void setNodePosition(int id, QPointF position);
	void attach(Observer* observer);
	bool isEditable(int index);
	void notify();
	void notifyButtonEnabled();
	bool isComponentEmpty();
	bool canSetPrimaryKey(int id);
	void setNodePrimaryKey(int pointID);
	void setNodeSelected(int id, bool isSelected);
	vector<int> getSelectedID();
	bool getPointerButtonChecked();
	void setPointerButtonChecked(bool isChecked);
	bool isDeleteEnabled();
	void clearSelected();
	void editText(int index, string text);
	void cut();
	void deleteMultipleCommand();

private:
	ERModel* _erModel;
	CommandManager _commandManager;
	bool _isPointerChecked;
	bool _isDeleteEnabled;
};

#endif