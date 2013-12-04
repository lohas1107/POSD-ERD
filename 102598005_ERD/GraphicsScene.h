#ifndef _GRAPHICSMANAGER_H_
#define _GRAPHICSMANAGER_H_

#include "GraphicsItem.h"
#include "ERComponent.h"
#include "PresentationModel.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include "State.h"

class State;
class GraphicsScene : public QGraphicsScene
{
	Q_OBJECT

public:
	GraphicsScene(PresentationModel* presentationModel);
	~GraphicsScene();
	void clearItem();
	void draw();
	PresentationModel* getPresentationModel();
	GraphicsItem* createGraphicsItem(Type type);
	void changeState(State* state);
	void clickPointerEvent();
	void clickConnectEvent();
	void clickAttributeEvent();
	void clickEntityEvent();
	void clickRelationEvent();
	void clickPrimaryKeyEvent();
	void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
	void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
	void updateChecked();

signals:
	void updateButton();

private:
	vector<GraphicsItem*> _graphicsItems;
	PresentationModel* _presentationModel;
	State* _currentState;
};

#endif