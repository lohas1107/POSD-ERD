#ifndef _ERCOMPONENT_H_
#define _ERCOMPONENT_H_

#include <string>
#include <vector>

using namespace std;

enum Type {
	none,
	entity,
	attribute,
	relation,
	connection,
	all
};

class ERComponent
{
public:
	ERComponent(pair<Type, string> type);
	virtual ~ERComponent();
	int getID();
	pair<Type, string> getType();
	string getText();
	vector<ERComponent*> getConnection();
	void setID(int id);
	void setText(string text);
	void setConnection(vector<ERComponent*> connections);
	bool isType(Type type);
	virtual void connectTo(ERComponent* component);
	virtual bool canConnectTo(ERComponent* component) = 0;
	void disconnectTo(int id);
	string getData(Type type);
	virtual ERComponent* clone();

protected:
	int _id;
	pair<Type, string> _type;
	string _text;
	vector<ERComponent*> _connections;
};

#endif