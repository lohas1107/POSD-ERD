#include "GUI.h"
#include <QMenuBar>
#include <QFileDialog>
#include "..\src\gui\graphicsview\qgraphicsscene.h"
#include "..\src\gui\graphicsview\qgraphicsitem.h"
#include "..\src\gui\graphicsview\qgraphicsview.h"

GUI::GUI(PresentationModel* presentationModel)
{
	_presentationModel = presentationModel;
	setWindowTitle("Entity Relation Diagramming Tool");	
	createActions();
	createMenus();
	createToolBars();
}

GUI::~GUI()
{
	delete _fileAction;
	delete _exitAction;
	delete _fileMenu;
	delete _toolBar;
}

void GUI::createActions()
{
	_fileAction = new QAction(QIcon("Resources/open.png"), "Open...", this);
	_fileAction->setShortcut(Qt::CTRL + Qt::Key_O);
	connect(_fileAction, SIGNAL(triggered()), this, SLOT(openFile()));

	_exitAction = new QAction(QIcon("Resources/exit.png"), "Exit", this);
	_exitAction->setShortcut(Qt::CTRL + Qt::Key_X);
	connect(_exitAction, SIGNAL(triggered()), this, SLOT(close()));
}

void GUI::createMenus()
{
	_fileMenu = menuBar()->addMenu("File");
	_fileMenu->addAction(_fileAction);
	_fileMenu->addAction(_exitAction);
}

void GUI::openFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Open ERD files", "C:\\", "ERD Files (*.erd)");
	_presentationModel->loadFile(fileName.toStdString());
	//...
}

void GUI::createToolBars()
{
	_toolBar = addToolBar("Edit");
	_toolBar->addAction(_fileAction);
	_toolBar->addAction(_exitAction);
}
