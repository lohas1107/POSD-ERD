#ifndef _GRAPHICSATTRIBUTE_H_
#define _GRAPHICSATTRIBUTE_H_

#include "GraphicsItem.h"
#include <QPainter>
#include <QFontMetrics>

class GraphicsAttribute : public GraphicsItem
{
public:
	GraphicsAttribute(PresentationModel* presentationModel);
	~GraphicsAttribute();
	void doAdjustSize(QFontMetrics fontMetrics);
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	void setPrimaryKey(bool flag);

private:
	bool _isPrimaryKey;
};

#endif