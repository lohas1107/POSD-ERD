#ifndef _GRAPHICSRELATION_H_
#define _GRAPHICSRELATION_H_

#include "GraphicsItem.h"
#include <QFontMetrics>

class GraphicsRelation : public GraphicsItem
{
public:
	GraphicsRelation(PresentationModel* presentationModel);
	~GraphicsRelation();
	void doAdjustSize(QFontMetrics fontMetrics);
};

#endif