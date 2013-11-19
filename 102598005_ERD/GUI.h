#ifndef _GUI_H_
#define _GUI_H_

#include "PresentationModel.h"
#include <QMainWindow>
#include <QObject>
#include <QActionGroup>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QScrollArea>
#include "GraphicsScene.h"

class GUI : public QMainWindow
{
	Q_OBJECT

public:
	GUI(PresentationModel* presentationModel);
	~GUI();
	
private slots:
	void openFile();
	void clickPointerEvent();
	void clickConnectEvent();
	void clickAttributeEvent();
	void clickEntityEvent();
	void clickRelationEvent();
	void updatePointerButton();

private:
	void createActions();
	void createActionGroup();
	void createMenus();
	void createToolBars();
	void createCanvas();
	PresentationModel* _presentationModel;
	QActionGroup* _actionGroup;
	QAction* _fileAction;
	QAction* _exitAction;
	QAction* _pointerAction;
	QAction* _connectAction;
	QAction* _attributeAction;
	QAction* _entityAction;
	QAction* _relationAction;
	QMenu* _fileMenu;
	QMenu* _addMenu;
	QToolBar* _fileToolBar;
	QToolBar* _editToolBar;
	GraphicsScene* _scene;
	QGraphicsView* _view;
	QHBoxLayout* _layout;
	QWidget* _widget;
};

#endif