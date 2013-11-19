#ifndef _ERCOMPONENT_H_
#define _ERCOMPONENT_H_

#include <string>
#include <vector>
#include <QPointF>

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
	void setID(int id);
	pair<Type, string> getType();
	bool isType(Type type);
	string getText();
	void setText(string text);
	vector<ERComponent*> getConnection();
	void setConnection(vector<ERComponent*> connections);
	bool hasConnection(int id);
	QPointF getPosition();
	void setPosition(QPointF position);
	virtual void connectTo(ERComponent* component);
	virtual bool canConnectTo(ERComponent* component) = 0;
	void disconnectTo(int id);
	string getData(Type type);
	virtual ERComponent* clone();

protected:
	int _id;
	pair<Type, string> _type;
	string _text;
	QPointF _position;
	vector<ERComponent*> _connections;
};

#endif