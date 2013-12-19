#ifndef _ERCOMPONENT_H_
#define _ERCOMPONENT_H_

#include <string>
#include <vector>
#include <QPointF>
//#include "ComponentVisitor.h"

using namespace std;

enum Type {
	none,
	entity,
	attribute,
	relation,
	connection,
	all
};

class ComponentVisitor;
class ERComponent
{
public:
	ERComponent(pair<Type, std::string> type);
	virtual ~ERComponent();
	int getID();
	void setID(int id);
	pair<Type, std::string> getType();
	bool isType(Type type);
	std::string getText();
	virtual void setText(std::string text);
	vector<ERComponent*> getConnection();
	void setConnection(vector<ERComponent*> connections);
	bool hasConnection(int id);
	QPointF getPosition();
	void setPosition(QPointF position);
	bool isSelected();
	void setSelected(bool isSelected);
	virtual void connectTo(ERComponent* component);
	virtual bool canConnectTo(ERComponent* component) = 0;
	void disconnectTo(int id);
	std::string getData(Type type);
	virtual ERComponent* clone();
	virtual void accept(ComponentVisitor* visitor) = 0;

protected:
	int _id;
	pair<Type, string> _type;
	string _text;
	QPointF _position;
	bool _isSelected;
	vector<ERComponent*> _connections;
};

#endif