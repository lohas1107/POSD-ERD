#include "GUI.h"
#include <QMenuBar>
#include <QFileDialog>
#include "GraphicsItem.h"
#include "GraphicsEntity.h"
#include <QGraphicsScene>

const int WIDTH = 1024;
const int HEIGHT = 768;

GUI::GUI(PresentationModel* presentationModel)
{
	_presentationModel = presentationModel;
	setWindowTitle("Entity Relation Diagramming Tool");	
	createActions();
	createActionGroup();
	createMenus();
	createToolBars();
	createCanvas();
	connect(_scene, SIGNAL(updateButton()), this, SLOT(updatePointerButton()));
}

GUI::~GUI()
{
	delete _actionGroup;
	delete _fileAction;
	delete _exitAction;
	delete _undoAction;
	delete _redoAction;
	delete _pointerAction;
	delete _connectAction;
	delete _attributeAction;
	delete _entityAction;
	delete _relationAction;
	delete _keyAction;
	delete _deleteAction;
	delete _fileMenu;
	delete _addMenu;
	delete _fileToolBar;
	delete _editToolBar;
	delete _scene;
	delete _view;
	delete _layout;
	delete _widget;
	delete _presentationModel;
}

// 產生動作
void GUI::createActions()
{
	_fileAction = new QAction(QIcon("Resources/open.png"), "Open...", this);
	_fileAction->setShortcut(Qt::CTRL + Qt::Key_O);
	connect(_fileAction, SIGNAL(triggered()), this, SLOT(openFile()));
	_exitAction = new QAction(QIcon("Resources/exit.png"), "Exit", this);
	_exitAction->setShortcut(Qt::CTRL + Qt::Key_X);
	connect(_exitAction, SIGNAL(triggered()), this, SLOT(close()));
	_undoAction = new QAction(QIcon("Resources/undo.png"), "Undo", this);
	connect(_undoAction, SIGNAL(triggered()), this, SLOT(clickUndoEvent()));
	_redoAction = new QAction(QIcon("Resources/redo.png"), "Redo", this);
	connect(_redoAction, SIGNAL(triggered()), this, SLOT(clickRedoEvent()));
	_pointerAction = new QAction(QIcon("Resources/cursor.png"), "Pointer", this);
	connect(_pointerAction, SIGNAL(triggered()), this, SLOT(clickPointerEvent()));
	_connectAction = new QAction(QIcon("Resources/line.png"), "Connect", this);
	connect(_connectAction, SIGNAL(triggered()), this, SLOT(clickConnectEvent()));
	_attributeAction = new QAction(QIcon("Resources/ellipse.png"), "Attribute", this);
	connect(_attributeAction, SIGNAL(triggered()), this, SLOT(clickAttributeEvent()));
	_entityAction = new QAction(QIcon("Resources/rectangle.png"), "Entity", this);
	connect(_entityAction, SIGNAL(triggered()), this, SLOT(clickEntityEvent()));
	_relationAction = new QAction(QIcon("Resources/rhombus.png"), "Relation", this);
	connect(_relationAction, SIGNAL(triggered()), this, SLOT(clickRelationEvent()));
	_keyAction = new QAction(QIcon("Resources/key.png"), "Primary key", this);
	connect(_keyAction, SIGNAL(triggered()), this, SLOT(clickPrimaryKeyEvent()));
	_deleteAction = new QAction(QIcon("Resources/delete.png"), "Delete", this);
	connect(_deleteAction, SIGNAL(triggered()), this, SLOT(clickDeleteEvent()));
}

// 產生 ActionGroup
void GUI::createActionGroup()
{
	_actionGroup = new QActionGroup(this);
	_actionGroup->setExclusive(true);
	_pointerAction->setCheckable(true);
	updatePointerButton();
	_actionGroup->addAction(_pointerAction);
	_connectAction->setCheckable(true);
	_actionGroup->addAction(_connectAction);
	_attributeAction->setCheckable(true);
	_actionGroup->addAction(_attributeAction);
	_entityAction->setCheckable(true);
	_actionGroup->addAction(_entityAction);
	_relationAction->setCheckable(true);
	_actionGroup->addAction(_relationAction);
	_keyAction->setCheckable(true);
	_actionGroup->addAction(_keyAction);
	//_deleteAction->setCheckable(true);
	//_actionGroup->addAction(_deleteAction);
}

// 更新選取 pointer button
void GUI::updatePointerButton()
{
	_pointerAction->setChecked(true);
}

// 產生選單
void GUI::createMenus()
{
	_fileMenu = menuBar()->addMenu("File");
	_fileMenu->addAction(_fileAction);
	_fileMenu->addAction(_exitAction);
	_addMenu = menuBar()->addMenu("Add");
	_addMenu->addAction(_attributeAction);
	_addMenu->addAction(_entityAction);
	_addMenu->addAction(_relationAction);
}

// 產生工具列
void GUI::createToolBars()
{
	_fileToolBar = addToolBar("File");
	_fileToolBar->addAction(_fileAction);
	_fileToolBar->addAction(_exitAction);
	_fileToolBar->addAction(_undoAction);
	_fileToolBar->addAction(_redoAction);
	_editToolBar = addToolBar("Edit");
	_editToolBar->addAction(_pointerAction);
	_editToolBar->addAction(_connectAction);
	_editToolBar->addSeparator();
	_editToolBar->addAction(_attributeAction);
	_editToolBar->addAction(_entityAction);
	_editToolBar->addAction(_relationAction);
	_editToolBar->addAction(_keyAction);
	_editToolBar->addAction(_deleteAction);
}

// 產生畫布
void GUI::createCanvas()
{
	_scene = new GraphicsScene(_presentationModel);
	_scene->setSceneRect(QRectF(0, 0, WIDTH, HEIGHT));
	_view = new QGraphicsView(_scene);
	_scene->setParent(_view);
	_layout = new QHBoxLayout();
	_widget = new QWidget();
	_layout->addWidget(_view);
	_widget->setLayout(_layout);
	setCentralWidget(_widget);
}

// 開啟檔案
void GUI::openFile()
{
	updatePointerButton();
	clickPointerEvent();
	QString fileName = QFileDialog::getOpenFileName(this, "Open ERD files", "C:\\", "ERD Files (*.erd)");
	_presentationModel->loadFile(fileName.toStdString());
	_presentationModel->composePosition();
	_scene->draw();
}

// 點擊 pointer 事件
void GUI::clickPointerEvent()
{
	_scene->clickPointerEvent();
}

// 點擊 connect 事件
void GUI::clickConnectEvent()
{
	_scene->clickConnectEvent();
}

// 點擊 attribute 事件
void GUI::clickAttributeEvent()
{
	_scene->clickAttributeEvent();
}

// 點擊 entity 事件
void GUI::clickEntityEvent()
{
	_scene->clickEntityEvent();
}

// 點擊 relation 事件
void GUI::clickRelationEvent()
{
	_scene->clickRelationEvent();
}

void GUI::clickUndoEvent()
{
	
}

void GUI::clickRedoEvent()
{
	
}

void GUI::clickPrimaryKeyEvent()
{
	
}

void GUI::clickDeleteEvent()
{
	
}
