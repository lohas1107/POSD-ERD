#ifndef _GRAPHICSMANAGER_H_
#define _GRAPHICSMANAGER_H_

#include "GraphicsItem.h"
#include "ERComponent.h"
#include "PresentationModel.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include "State.h"

class State;
class GraphicsScene : public QGraphicsScene
{
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
	//void clickDeleteEvent();
	//void clickUndoEvent();
	//void clickRedoEvent();
	//void clickAboutEvent();
	//void clickCutEvent();
	//void clickCopyEvent();
	//void clickPasteEvent();
	void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
	void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);

private:
	vector<GraphicsItem*> _graphicsItems;
	PresentationModel* _presentationModel;
	State* _currentState;
};

#endif