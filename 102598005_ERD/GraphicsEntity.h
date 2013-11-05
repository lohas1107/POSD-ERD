#ifndef _GRAPHICSENTITY_H_
#define _GRAPHICSENTITY_H_

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include "GraphicsItem.h"

class GraphicsEntity : public GraphicsItem
{
public:
	GraphicsEntity();
	~GraphicsEntity();
	void doCreateItem();
	void doAdjustSize(QFontMetrics fontMetrics);
};

#endif