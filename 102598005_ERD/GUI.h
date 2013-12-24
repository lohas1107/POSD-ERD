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
#include <QVBoxLayout>
#include <QScrollArea>
#include "GraphicsScene.h"
#include "Observer.h"
#include "TableModel.h"
#include "TableView.h"

class GUI : public QMainWindow, public Observer
{
	Q_OBJECT

public:
	GUI(PresentationModel* presentationModel);
	~GUI();
	void update();
	
private slots:
	void close();
	void openFile();
	void saveFile();
	void saveXmlFile();
	void clickPointerEvent();
	void clickConnectEvent();
	void clickAttributeEvent();
	void clickEntityEvent();
	void clickRelationEvent();
	void clickUndoEvent();
	void clickRedoEvent();
	void clickPrimaryKeyEvent();
	void clickDeleteEvent();
	void clickCutEvent();
	void clickCopyEvent();
	void clickPasteEvent();
	void clickAboutEvent();
	void updateButtonEnabled();

private:
	void createActions();
	void connectActions();
	void createActionGroup();
	void createMenus();
	void createToolBars();
	void createCanvas();
	void setTableModel();
	PresentationModel* _presentationModel;
	QActionGroup* _actionGroup;
	QAction* _loadFileAction;
	QAction* _exitAction;
	QAction* _undoAction;
	QAction* _redoAction;
	QAction* _pointerAction;
	QAction* _connectAction;
	QAction* _attributeAction;
	QAction* _entityAction;
	QAction* _relationAction;
	QAction* _keyAction;
	QAction* _deleteAction;
	QAction* _saveFileAction;
	QAction* _saveXmlFileAction;
	QAction* _cutAction;
	QAction* _copyAction;
	QAction* _pasteAction;
	QAction* _aboutAction;
	//QAction* _dbTableAction;
	QMenu* _fileMenu;
	QMenu* _addMenu;
	QMenu* _editMenu;
	QMenu* _helpMenu;
	QToolBar* _fileToolBar;
	QToolBar* _editToolBar;
	GraphicsScene* _scene;
	QGraphicsView* _view;
	QHBoxLayout* _hLayout;
	QVBoxLayout* _vLayout;
	TableView* _tableView;
	TableModel* _tableModel;
	QWidget* _widget;
};

#endif