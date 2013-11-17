#ifndef _GRAPHICSSCENE_H_
#define _GRAPHICSSCENE_H_

#include <QGraphicsScene>
#include "PresentationModel.h"

class GraphicsScene : public QGraphicsScene
{
public:
	GraphicsScene(PresentationModel* presentationModel);
	~GraphicsScene();
	void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
	void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);

protected:
	PresentationModel* _presentationModel;
};

#endif