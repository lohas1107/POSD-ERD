#include "GraphicsRelation.h"

const int OFFSET = 5;
const double SCALE = 0.8;

GraphicsRelation::GraphicsRelation()
{
}

GraphicsRelation::~GraphicsRelation()
{
}

// �ھڤ�r���e�վ�j�p
void GraphicsRelation::doAdjustSize(QFontMetrics fontMetrics)
{
	int width = fontMetrics.width(data(textData).toString()) + OFFSET;
	int height = width * SCALE;

	QPolygonF _polygon;
	_polygon << QPointF(-width, 0) << QPointF(0, height) << QPointF(width, 0) << QPointF(0, -height) << QPointF(-width, 0);
	((QGraphicsPolygonItem*)_item)->setPolygon(_polygon);
}
