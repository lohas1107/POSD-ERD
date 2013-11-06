#ifndef _GRAPHICSATTRIBUTE_H_
#define _GRAPHICSATTRIBUTE_H_

#include "GraphicsItem.h"
#include <QPainter>
#include <QFontMetrics>

class GraphicsAttribute : public GraphicsItem
{
public:
	GraphicsAttribute();
	~GraphicsAttribute();
	void doCreateItem();
	void setPrimaryKey(bool flag);

private:
	bool _isPrimaryKey;
};

#endif