#include "GraphicsRelation.h"

const int OFFSET = 5;
const double SCALE = 0.8;

GraphicsRelation::GraphicsRelation()
{
	//doCreateItem();
}

GraphicsRelation::~GraphicsRelation()
{
}

// ���͹ϧ�
//void GraphicsRelation::doCreateItem()
//{
//	//_item = new QGraphicsPolygonItem();
//}

// �ھڤ�r���e�վ�j�p
void GraphicsRelation::doAdjustSize(QFontMetrics fontMetrics)
{
	int width = fontMetrics.width(_text) + OFFSET;
	int height = width * SCALE;

	QPolygonF _polygon;
	_polygon << QPointF(-width, 0) << QPointF(0, height) << QPointF(width, 0) << QPointF(0, -height) << QPointF(-width, 0);
	((QGraphicsPolygonItem*)_item)->setPolygon(_polygon);
}
