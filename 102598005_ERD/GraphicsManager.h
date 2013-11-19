#ifndef _GRAPHICSMANAGER_H_
#define _GRAPHICSMANAGER_H_

#include "GraphicsItem.h"
#include "ERComponent.h"
#include "PresentationModel.h"
#include <QGraphicsScene>
#include <QObject>
#include "State.h"

class State;
class GraphicsManager : public QGraphicsScene
{
	Q_OBJECT

public:
	GraphicsManager(PresentationModel* presentationModel);
	~GraphicsManager();
	void clearItem();
	void draw();
	PresentationModel* getPresentationModel();
	GraphicsItem* createGraphicsItem(Type type);
	//void composePosition();
	void changeState(State* state);
	void clickPointerEvent();
	void clickConnectEvent();
	void clickAttributeEvent();
	void clickEntityEvent();
	void clickRelationEvent();
	//bool eventFilter(QObject *object, QEvent *event);
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