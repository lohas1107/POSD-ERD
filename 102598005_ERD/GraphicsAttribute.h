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
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	void doCreateItem();
	void doAdjustSize(QFontMetrics fontMetrics);
};

#endif