#ifndef _GRAPHICSITEM_H_
#define _GRAPHICSITEM_H_

#include <QGraphicsItem>
#include <string>

using namespace std;

enum Data {
	id,
	text
};

class GraphicsItem : public QGraphicsItem
{
public:
	GraphicsItem();
	virtual ~GraphicsItem();
	virtual void doAdjustSize(QFontMetrics fontMetrics);
	QRectF boundingRect() const;
	QPainterPath shape() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);

protected:
	QGraphicsItem* _item;
	bool _isSelected;
};

#endif