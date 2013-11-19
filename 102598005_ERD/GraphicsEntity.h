#ifndef _GRAPHICSENTITY_H_
#define _GRAPHICSENTITY_H_

#include "GraphicsItem.h"

class GraphicsEntity : public GraphicsItem
{
public:
	GraphicsEntity();
	~GraphicsEntity();
	void doAdjustSize(QFontMetrics fontMetrics);
};

#endif