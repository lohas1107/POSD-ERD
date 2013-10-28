#include "TextUI.h"
#include <iostream>
#include "Parser.h"

const string ONE = "1";
const string ONE_COMMAND = "1. Load ER diagram file";
const string TWO = "2";
const string TWO_COMMAND = "2. Save ER diagram file";
const string THREE = "3";
const string THREE_COMMAND = "3. Add a node";
const string FOUR = "4";
const string FOUR_COMMAND = "4. Connect two nodes";
const string FIVE = "5";
const string FIVE_COMMAND = "5. Display the current diagram";
const string SIX = "6";
const string SIX_COMMAND = "6. Set a primary key";
const string SEVEN = "7";
const string SEVEN_COMMAND = "7. Display the table";
const string EIGHT = "8";
const string EIGHT_COMMAND = "8. Delete a component";
const string NINE = "9";
const string NINE_COMMAND = "9. Undo";
const string TEN = "10";
const string TEN_COMMAND = "10.Redo";
const string ELEVEN = "11";
const string ELEVEN_COMMAND = "11.Exit";
const string GOODBYE = "Goodbye!";
const int NODE_NAME_SPACE = 80;
const string STRING_EMPTY = "";
const char NEXT_LINE = '\n';
const string CARDINALITY_ONE = "1";
const string CARDINALITY_N = "N";

TextUI::TextUI(PresentationModel* presentationModel)
{
	_presentationModel = presentationModel;
}

TextUI::~TextUI()
{
}

// ��ܿ��
void TextUI::displayMenu()
{
	cout << ONE_COMMAND << endl;
	cout << TWO_COMMAND << endl;
	cout << THREE_COMMAND << endl;
	cout << FOUR_COMMAND << endl;
	cout << FIVE_COMMAND << endl;
	cout << SIX_COMMAND << endl;
	cout << SEVEN_COMMAND << endl;
	cout << EIGHT_COMMAND << endl;
	cout << NINE_COMMAND << endl;
	cout << TEN_COMMAND << endl;
	cout << ELEVEN_COMMAND << endl;
	processCommand();
}

// �B�z�R�O
void TextUI::processCommand()
{
	string command;
	cin >> command;


	if (command == ONE)
	{
		loadFile();
	} 
	else if (command == TWO)
	{
		saveFile();
	}
	else if (command == THREE)
	{
		addNodeCommand();
	}
	else if (command == FOUR)
	{
		connectNodeCommand();
	}
	else if (command == FIVE)
	{
		displayDiagramCommand();
	}
	else if (command == SIX)
	{
		setPrimaryKeyCommand();
	}
	else if (command == SEVEN)
	{
		displayTableCommand();
	}
	else if (command == EIGHT)
	{
		deleteComponentCommand();
	}
	else if (command == NINE)
	{
		undo();
	}
	else if (command == TEN)
	{
		redo();
	}
	else if (command == ELEVEN)
	{
		remindSaveFile();
		cout << GOODBYE << endl;
		return;
	}

	displayMenu();
}

// Ū���ɮ�
void TextUI::loadFile()
{
	string filePath;
	cout << "Please input a file path: ";
	cin >> filePath;

	if (!_presentationModel->loadFile(filePath))
	{
		cout << "File not found!!" << endl;
		return;
	}
	displayDiagramCommand();
}

// �x�s�ɮ�
void TextUI::saveFile()
{
	string filePath;
	cout << "Please input a file path: ";
	cin >> filePath;

	if (!_presentationModel->saveFile(filePath))
	{
		cout << "Cannot save file!!" << endl;
		return;
	}
}

// �s�W����R�O
void TextUI::addNodeCommand()
{
	string nodeType;
	char nodeName[NODE_NAME_SPACE];
	cout << "What kind of node do you want to add?" << endl;
	cout << "[A]Attribute [E]Entity [R]Relation" << endl;
	cin >> nodeType;
	while (!_presentationModel->checkInputType(nodeType))
	{
		cout << "You entered an invalid node. Please enter a valid one again." << endl;
		cout << "[A]Attribute [E]Entity [R]Relation" << endl;
		cin >> nodeType;
	}

	cin.get();
	cout << "Enter the name of this node:" << endl;
	cin.getline(nodeName, NODE_NAME_SPACE);

	int id = _presentationModel->addNodeCommand(nodeType, nodeName);
	printf("A node [%s] has been added. ID: %d, Name: \"%s\"\n", _presentationModel->getNodeType(id).c_str(), id, _presentationModel->getNodeText(id).c_str());
	showComponents(all);
}

// ��ܤ����T
void TextUI::showComponents(Type type)
{
	cout << "Components:" << endl;
	cout << "------------------------------------" << endl;
	cout << " Type |  ID  |  Name" << endl;
	cout << "------+------+----------------------" << endl;
	cout << _presentationModel->getComponentLine(type);
	cout << "------------------------------------" << endl;
}

// �s���`�I�R�O
void TextUI::connectNodeCommand()
{
	if (_presentationModel->getComponentSize() <= 1)
	{
		cout << "Please add at least two nodes." << endl;
		return;
	}
	cout << "Please enter the first node ID" << endl;
	int firstNodeID = getInputID();
	cout << "Please enter the second node ID" << endl;
	int secondNodeID = getInputID();

	if (isValidID(firstNodeID, secondNodeID))
	{
		string cardinality = getCardinality(firstNodeID, secondNodeID);
		_presentationModel->connectNodeCommand(firstNodeID, secondNodeID, cardinality);
		if (_presentationModel->isCreationFail())
		{
			printf("The node '%d' cannot be connected by the node '%d'.\n", secondNodeID, firstNodeID);
			return;
		}
		printf("The node '%d' has been connected to the node '%d'.\n", firstNodeID, secondNodeID);
		printConnect();
	} 
}

// �O�_���X�k�� id
bool TextUI::isValidID(int firstNodeID, int secondNodeID)
{
	if (firstNodeID == secondNodeID)
	{		
		printf("The node '%d' cannot be connected to itself.\n", firstNodeID);
		return false;
	}

	if (_presentationModel->hasConnection(firstNodeID, secondNodeID))
	{
		printf("The node '%d' has already been connected to component '%d'.\n\n", firstNodeID, secondNodeID);
		return false;
	}

	return true;
}

// ���o cardinality
string TextUI::getCardinality(int firstNodeID, int secondNodeID)
{
	if (_presentationModel->needAskCardinality(firstNodeID, secondNodeID))
	{
		int cardinality = 0;
		cout << "Enter the type of the cardinality:\n[0]1 [1]N" << endl;

		while (!(cin >> cardinality) || abs(cardinality) > 1)
		{
			cin.clear();
			cin.ignore(INT_MAX, NEXT_LINE);
		}

		return _presentationModel->getCardinality(cardinality);
	}
	return STRING_EMPTY;
}

// ���o��J�� id
int TextUI::getInputID()
{
	int id = 0;
	while (!(cin >> id) || !_presentationModel->isIDExsit(id))
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "The node ID you entered does not exist. Please enter a valid one again." << endl;
	}
	return id;
}

// ��ܳs����T
void TextUI::printConnect()
{
	int id = _presentationModel->getNodeID();
	if (_presentationModel->getNodeText(id) != "")
	{
		printf("Its cardinality of the relationship is '%s'.\n", _presentationModel->getNodeText(id).c_str());
	}
	showConnections();
}

// ��ܳs���C��
void TextUI::showConnections()
{
	cout << "Connections:" << endl;
	cout << "--------------------------" << endl;
	cout << "Connection | node | node |" << endl;
	cout << "-----------+------+------|" << endl;
	cout << _presentationModel->getConnectionLine();
	cout << "--------------------------" << endl;
}

// ���ERD�R�O
void TextUI::displayDiagramCommand()
{
	cout << "The ER diagram is displayed as follows:" << endl;
	showComponents(all);
	showConnections();
}

// �]�w primary key �R�O
void TextUI::setPrimaryKeyCommand()
{
	int id = 0;
	if (!(_presentationModel->hasEntity()))
	{
		cout << "No entities!" << endl;
		return;
	} 	
	cout << "Entities:" << endl;
	showComponents(entity);
	cout << "Enter the ID of the entity:" << endl;	
	id = getInputID();
	while (!_presentationModel->isType(id, entity))
	{
		printf("The node '%d' is not an entity. Please enter a valid one again.\n", id);
		id = getInputID();
	}
	if (!(_presentationModel->hasAttribute(id)))
	{
		cout << "No attributes!" << endl;
		return;
	} 
	showAttribute(id);
	_presentationModel->setPrimaryKey(getAttributeID(id));
	printf("The entity '%d' has the primary key (%s).\n", id, _presentationModel->getPrimaryKey(id).c_str());
}

// ��ܩ��ݪ� attribues ��T
void TextUI::showAttribute(int id)
{
	printf("Attributes of the entity '%d'\n", id);
	cout << "------------------------------------" << endl;
	cout << " Type |  ID  |  Name" << endl;
	cout << "------+------+----------------------" << endl;
	cout << _presentationModel->getAttributeLine(id);
	cout << "------------------------------------" << endl;
}

// ���o attribute id
vector<int> TextUI::getAttributeID(int id)
{
	string ids;
	vector<int> primaryKey;
	cout << "Enter the IDs of the attributes (use a comma to separate two attributes):" << endl;
	cin >> ids;

	primaryKey = Parser::changeToVectorInt(Parser::split(ids, ','));
	for (unsigned i = 0; i < primaryKey.size(); i++)
	{
		while (!(_presentationModel->isAttribute(id, primaryKey[i])))
		{
			printf("The node '%d' does not belong to Entity '%d'. Please enter a valid one again.\n", primaryKey[i], id);
			cin >> ids;
			primaryKey = Parser::changeToVectorInt(Parser::split(ids, ','));
		}
	}

	return primaryKey;
}

// ��ܸ�Ʈw���R�O
void TextUI::displayTableCommand()
{
	if (!_presentationModel->displayTableCommand())
	{
		cout << "It has no table to display." << endl;
	}
	else
	{
		cout << "------------------------------------------------------------------" << endl;
		cout << "    Entity  |  Attribute" << endl;
		cout << "------------+-----------------------------------------------------" << endl;
		cout << _presentationModel->getTable();
		cout << "------------+-----------------------------------------------------" << endl;
	}
}

// �R������R�O
void TextUI::deleteComponentCommand()
{
	if (_presentationModel->getComponentSize() == 0)
	{
		cout << "No component to delete!" << endl;
		return;
	}

	cout << "Please enter the component ID" << endl;
	int id = getInputID();
	_presentationModel->deleteComponentCommand(id);

	printf("The component \"%d\" has been deleted.\n", id);
	displayDiagramCommand();
}

// �^�W�@�B
void TextUI::undo()
{
	if (!_presentationModel->canUndo())
	{
		cout << "Cannot undo." << endl;
		return;
	}

	_presentationModel->undo();
	cout << "Undo succeed!" << endl;
	displayDiagramCommand();
}

// ��U�@�B
void TextUI::redo()
{
	if (!_presentationModel->canRedo())
	{
		cout << "Cannot redo." << endl;
		return; 
	}

	_presentationModel->redo();
	cout << "Redo succeed!" << endl;
	displayDiagramCommand();
}

// �x�s�ɮ״���
void TextUI::remindSaveFile()
{
	string isSaveFile = STRING_EMPTY;
	cout << "Do you want to save the current diagram?" << endl;
	cout << "[Y]Yes [N]No" << endl;
	cin >> isSaveFile;

	if (isSaveFile == "Y" || isSaveFile == "y")
	{
		saveFile();
	}
	else if (isSaveFile == "N" || isSaveFile == "n")
	{
		return;
	}
}
