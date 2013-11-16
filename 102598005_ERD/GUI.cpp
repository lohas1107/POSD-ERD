#include "GUI.h"
#include <QMenuBar>
#include <QFileDialog>
#include "GraphicsItem.h"
#include "GraphicsEntity.h"

const int WIDTH = 1024;
const int HEIGHT = 768;

GUI::GUI(PresentationModel* presentationModel)
{
	_presentationModel = presentationModel;
	setWindowTitle("Entity Relation Diagramming Tool");	
	createActions();
	createMenus();
	createToolBars();
	createCanvas();
}

GUI::~GUI()
{
	delete _fileAction;
	delete _exitAction;
	delete _pointerAction;
	delete _connectAction;
	delete _attributeAction;
	delete _entityAction;
	delete _relationAction;
	delete _fileMenu;
	delete _addMenu;
	delete _fileToolBar;
	delete _editToolBar;
	delete _scene;
	delete _view;
	delete _layout;
	delete _widget;
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

	_pointerAction = new QAction(QIcon("Resources/cursor.png"), "Pointer", this);
	connect(_pointerAction, SIGNAL(triggered()), this, SLOT(clickPointerEvent()));
}

// 產生選單0
void GUI::createMenus()
{
	_fileMenu = menuBar()->addMenu("File");
	_fileMenu->addAction(_fileAction);
	_fileMenu->addAction(_exitAction);
	_addMenu = menuBar()->addMenu("Add");
}

// 產生工具列
void GUI::createToolBars()
{
	_fileToolBar = addToolBar("File");
	_fileToolBar->addAction(_fileAction);
	_fileToolBar->addAction(_exitAction);

	_editToolBar = addToolBar("Edit");
	_editToolBar->addAction(_pointerAction);
}

// 產生畫布
void GUI::createCanvas()
{
	_scene = new QGraphicsScene();
	_scene->setSceneRect(QRectF(0, 0, WIDTH, HEIGHT));
	_view = new QGraphicsView(_scene);
	_layout = new QHBoxLayout();
	_widget = new QWidget();
	_layout->addWidget(_view);
	_widget->setLayout(_layout);
	setCentralWidget(_widget);
}

// 開啟檔案
void GUI::openFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Open ERD files", "C:\\", "ERD Files (*.erd)");
	_presentationModel->loadFile(fileName.toStdString());
	_presentationModel->composePosition();
	drawDiagram();
}

// 畫ERD
void GUI::drawDiagram()
{
	vector<ERComponent*> components = _presentationModel->getComponents();
	_graphicsManager.clearItem();
	_scene->clear();
	_graphicsManager.draw(_scene, components);
	_scene->update(0, 0, _scene->width(), _scene->height());
}

void GUI::clickPointerEvent()
{
	_presentationModel->clickPointerEvent();
	//updateState();
}
