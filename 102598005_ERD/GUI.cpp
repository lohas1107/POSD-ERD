#include "GUI.h"
#include <QMenuBar>
#include <QFileDialog>

GUI::GUI(PresentationModel* presentationModel)
{
	_presentationModel = presentationModel;
	setWindowTitle("Entity Relation Diagramming Tool");	
	createMenus();
}

GUI::~GUI()
{
	delete _fileMenu;
}

void GUI::createMenus()
{
	_fileMenu = menuBar()->addMenu("File");
	_fileMenu->addAction(QIcon("Resources/open.png"), "Open...", this, SLOT(openFile()), Qt::CTRL + Qt::Key_O);
	_fileMenu->addAction(QIcon("Resources/exit.png"), "Exit", this, SLOT(close()), Qt::CTRL + Qt::Key_X);
}

void GUI::openFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Open ERD files", "C:\\", "ERD Files (*.erd)");
	_presentationModel->loadFile(fileName.toStdString());
	//...
}
