#include "GraphicsScene.h"

GraphicsScene::GraphicsScene(PresentationModel* presentationModel)
{
	_presentationModel = presentationModel;
}

GraphicsScene::~GraphicsScene()
{
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	QGraphicsScene::mousePressEvent(mouseEvent);
	_presentationModel->mousePressEvent(mouseEvent);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
