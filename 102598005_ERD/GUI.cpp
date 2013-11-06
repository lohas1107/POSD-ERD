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
	delete _fileMenu;
	delete _toolBar;
	delete _scene;
	delete _view;
	delete _layout;
	delete _widget;
}

// ���Ͱʧ@
void GUI::createActions()
{
	_fileAction = new QAction(QIcon("Resources/open.png"), "Open...", this);
	_fileAction->setShortcut(Qt::CTRL + Qt::Key_O);
	connect(_fileAction, SIGNAL(triggered()), this, SLOT(openFile()));

	_exitAction = new QAction(QIcon("Resources/exit.png"), "Exit", this);
	_exitAction->setShortcut(Qt::CTRL + Qt::Key_X);
	connect(_exitAction, SIGNAL(triggered()), this, SLOT(close()));
}

// ���Ϳ��
void GUI::createMenus()
{
	_fileMenu = menuBar()->addMenu("File");
	_fileMenu->addAction(_fileAction);
	_fileMenu->addAction(_exitAction);
}

// ���ͤu��C
void GUI::createToolBars()
{
	_toolBar = addToolBar("Edit");
	_toolBar->addAction(_fileAction);
	_toolBar->addAction(_exitAction);
}

// ���͵e��
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

// �}���ɮ�
void GUI::openFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Open ERD files", "C:\\", "ERD Files (*.erd)");
	_presentationModel->loadFile(fileName.toStdString());
	_presentationModel->composePosition();
	drawDiagram();
}

// �eERD
void GUI::drawDiagram()
{
	vector<ERComponent*> components = _presentationModel->getComponents();
	_scene->clear();
	_graphicsManager.draw(_scene, components);
	_scene->update(0, 0, _scene->width(), _scene->height());
}
