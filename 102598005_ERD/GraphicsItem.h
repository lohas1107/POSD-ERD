#ifndef _GRAPHICSITEM_H_
#define _GRAPHICSITEM_H_

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QString>
#include <string>

using namespace std;

class GraphicsItem : public QGraphicsItem
{
public:
	GraphicsItem();
	virtual ~GraphicsItem();
	virtual void doCreateItem() = 0;
	virtual void doAdjustSize(QFontMetrics fontMetrics);
	QRectF boundingRect() const;
	QPainterPath shape() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	void setText(QString text);

protected:
	QGraphicsItem* _item;
	QString _text;
};

#endif