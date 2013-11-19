#ifndef _GRAPHICSCONNECTOR_H_
#define _GRAPHICSCONNECTOR_H_

#include "GraphicsItem.h"
#include <QFontMetrics>

class GraphicsConnector : public GraphicsItem
{
public:
	GraphicsConnector();
	~GraphicsConnector();
	void doAdjustSize(QFontMetrics fontMetrics);
	void setLine(QLineF line);
};

#endif