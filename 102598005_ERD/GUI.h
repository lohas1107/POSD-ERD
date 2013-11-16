#ifndef _GUI_H_
#define _GUI_H_

#include "PresentationModel.h"
#include "GraphicsManager.h"
#include <QMainWindow>
#include <QObject>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QScrollArea>

class GUI : public QMainWindow
{
	Q_OBJECT

public:
	GUI(PresentationModel* presentationModel);
	~GUI();
	void drawDiagram();

private slots:
	void openFile();
	void clickPointerEvent();

private:
	void createActions();
	void createMenus();
	void createToolBars();
	void createCanvas();
	PresentationModel* _presentationModel;
	GraphicsManager _graphicsManager;
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
	QGraphicsScene* _scene;
	QGraphicsView* _view;
	QHBoxLayout* _layout;
	QWidget* _widget;
};

#endif