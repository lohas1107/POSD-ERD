#ifndef _GUI_H_
#define  _GUI_H_

#include "PresentationModel.h"
#include <QMainWindow>
#include <QObject>
#include <QMenu>
#include <QAction>

class GUI : public QMainWindow
{
	Q_OBJECT

public:
	GUI(PresentationModel* presentationModel);
	~GUI();

private slots:
	void openFile();

private:
	void createMenus();
	PresentationModel* _presentationModel;
	QMenu* _fileMenu;

};

#endif