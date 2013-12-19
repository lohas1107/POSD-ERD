#ifndef _CONNECTION_H_
#define _CONNECTION_H_

#include "ERComponent.h"

class Connector : public ERComponent
{
public:
	Connector();
	Connector(int id, string text);
	~Connector();
	void setText(string text);
	bool canConnectTo(ERComponent* component);
	string getConnectionLine();
	bool checkOneToOne(pair<int, int> relationPair);
	string getConnection();
	pair<int, int> getConnectionPair();
	ERComponent* clone();

	virtual void accept(ComponentVisitor* visitor);

};

#endif