#include "GUI.h"
#include <QMenuBar>
#include <QFileDialog>
#include "GraphicsItem.h"
#include "GraphicsEntity.h"
#include <QGraphicsScene>
#include <QLabel>
#include <QDebug>
#include <QMessageBox>

const int WIDTH = 1024;
const int HEIGHT = 768;
const int TABLE_VIEW_WIDTH = 220;
const string ABOUT_TITLE = "About Entity Relation Diagramming Tool";
const string ABOUT_CONTENT = "Entity Relation Diagramming Tool<br>Version: 1.0<br>Author: 102598005@ntut";

GUI::GUI(PresentationModel* presentationModel)
{
	_presentationModel = presentationModel;
	setWindowTitle("Entity Relation Diagramming Tool");	
	createActions();
	connectActions();
	createActionGroup();
	createMenus();
	createToolBars();
	createCanvas();
	setTableModel();
	updateButtonEnabled();
	_presentationModel->attach(this);
}

GUI::~GUI()
{
	delete _actionGroup;
	delete _loadFileAction;
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
	delete _saveFileAction;
	delete _saveXmlFileAction;
	delete _cutAction;
	delete _copyAction;
	delete _pasteAction;
	delete _aboutAction;
	delete _dbTableAction;
	delete _fileMenu;
	delete _addMenu;
	delete _editMenu;
	delete _helpMenu;
	delete _fileToolBar;
	delete _editToolBar;
	delete _scene;
	delete _view;
	delete _guiLayout;
	delete _tableLayout;
	delete _hLayout;
	delete _tableView;
	delete _tableModel;
	delete _textEdit;
	delete _widget;
	delete _presentationModel;
}

// 產生動作
void GUI::createActions()
{
	_loadFileAction = new QAction(QIcon("Resources/open.png"), "Open...", this);
	_loadFileAction->setShortcut(Qt::CTRL + Qt::Key_O);
	_saveFileAction = new QAction(QIcon("Resources/save.png"), "Save", this);
	_saveFileAction->setShortcut(Qt::CTRL + Qt::Key_S);
	_saveXmlFileAction = new QAction("Save as xml", this);
	_exitAction = new QAction(QIcon("Resources/exit.png"), "Exit", this);
	_exitAction->setShortcut(Qt::CTRL + Qt::Key_E);
	_undoAction = new QAction(QIcon("Resources/undo.png"), "Undo", this);
	_undoAction->setShortcut(Qt::CTRL + Qt::Key_Z);
	_redoAction = new QAction(QIcon("Resources/redo.png"), "Redo", this);
	_redoAction->setShortcut(Qt::CTRL + Qt::Key_Y);
	_cutAction = new QAction(QIcon("Resources/cut.png"), "Cut", this);
	_cutAction->setShortcut(Qt::CTRL + Qt::Key_X);
	_copyAction = new QAction(QIcon("Resources/copy.png"), "Copy", this);
	_copyAction->setShortcut(Qt::CTRL + Qt::Key_C);
	_pasteAction = new QAction(QIcon("Resources/paste.png"), "Paste", this);
	_pasteAction->setShortcut(Qt::CTRL + Qt::Key_V);
	_deleteAction = new QAction(QIcon("Resources/delete.png"), "Delete", this);
	_deleteAction->setShortcut(Qt::Key_Delete);
	_pointerAction = new QAction(QIcon("Resources/cursor.png"), "Pointer", this);
	_connectAction = new QAction(QIcon("Resources/line.png"), "Connect", this);
	_attributeAction = new QAction(QIcon("Resources/ellipse.png"), "Attribute", this);
	_entityAction = new QAction(QIcon("Resources/rectangle.png"), "Entity", this);
	_relationAction = new QAction(QIcon("Resources/rhombus.png"), "Relation", this);
	_keyAction = new QAction(QIcon("Resources/key.png"), "Primary key", this);
	_aboutAction = new QAction(QIcon("Resources/about.png"), "About", this);
	_dbTableAction = new QAction(QIcon("Resources/db.png"), "DB Table", this);
}

void GUI::connectActions()
{	
	connect(_loadFileAction, SIGNAL(triggered()), this, SLOT(openFile()));
	connect(_saveFileAction, SIGNAL(triggered()), this, SLOT(saveFile()));
	connect(_saveXmlFileAction, SIGNAL(triggered()), this, SLOT(saveXmlFile()));
	connect(_exitAction, SIGNAL(triggered()), this, SLOT(close()));
	connect(_undoAction, SIGNAL(triggered()), this, SLOT(clickUndoEvent()));
	connect(_redoAction, SIGNAL(triggered()), this, SLOT(clickRedoEvent()));
	connect(_cutAction, SIGNAL(triggered()), this, SLOT(clickCutEvent()));
	connect(_copyAction, SIGNAL(triggered()), this, SLOT(clickCopyEvent()));
	connect(_pasteAction, SIGNAL(triggered()), this, SLOT(clickPasteEvent()));
	connect(_deleteAction, SIGNAL(triggered()), this, SLOT(clickDeleteEvent()));
	connect(_pointerAction, SIGNAL(triggered()), this, SLOT(clickPointerEvent()));
	connect(_connectAction, SIGNAL(triggered()), this, SLOT(clickConnectEvent()));
	connect(_attributeAction, SIGNAL(triggered()), this, SLOT(clickAttributeEvent()));
	connect(_entityAction, SIGNAL(triggered()), this, SLOT(clickEntityEvent()));
	connect(_relationAction, SIGNAL(triggered()), this, SLOT(clickRelationEvent()));
	connect(_keyAction, SIGNAL(triggered()), this, SLOT(clickPrimaryKeyEvent()));
	connect(_aboutAction, SIGNAL(triggered()), this, SLOT(clickAboutEvent()));
	connect(_dbTableAction, SIGNAL(triggered()), this, SLOT(clickDBTableEvent()));
}

// 產生 ActionGroup
void GUI::createActionGroup()
{
	_actionGroup = new QActionGroup(this);
	_actionGroup->setExclusive(true);
	_pointerAction->setCheckable(true);
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
	_dbTableAction->setCheckable(true);
}

// 更新按鈕狀態
void GUI::updateButtonEnabled()
{
	_undoAction->setEnabled(_presentationModel->canUndo());
	_redoAction->setEnabled(_presentationModel->canRedo());
	_pointerAction->setChecked(_presentationModel->getPointerButtonChecked());
	_deleteAction->setEnabled(_presentationModel->isDeleteEnabled());
}

// 產生選單
void GUI::createMenus()
{
	_fileMenu = menuBar()->addMenu("File");
	_fileMenu->addAction(_loadFileAction);
	_fileMenu->addAction(_saveFileAction);
	_fileMenu->addAction(_saveXmlFileAction);
	_fileMenu->addAction(_exitAction);
	_addMenu = menuBar()->addMenu("Add");
	_addMenu->addAction(_attributeAction);
	_addMenu->addAction(_entityAction);
	_addMenu->addAction(_relationAction);
	_editMenu = menuBar()->addMenu("Edit");
	_editMenu->addAction(_undoAction);
	_editMenu->addAction(_redoAction);
	_editMenu->addAction(_cutAction);
	_editMenu->addAction(_copyAction);
	_editMenu->addAction(_pasteAction);
	_editMenu->addAction(_deleteAction);
	_helpMenu = menuBar()->addMenu("Help");
	_helpMenu->addAction(_aboutAction);
}

// 產生工具列
void GUI::createToolBars()
{
	_fileToolBar = addToolBar("File");
	_fileToolBar->addAction(_loadFileAction);
	_fileToolBar->addAction(_saveFileAction);
	_fileToolBar->addAction(_exitAction);
	_editToolBar = addToolBar("Edit");
	_editToolBar->addAction(_undoAction);
	_editToolBar->addAction(_redoAction);
	_editToolBar->addAction(_cutAction);
	_editToolBar->addAction(_copyAction);
	_editToolBar->addAction(_pasteAction);
	_editToolBar->addAction(_deleteAction);
	_editToolBar->addSeparator();
	_editToolBar->addAction(_pointerAction);
	_editToolBar->addAction(_connectAction);
	_editToolBar->addAction(_attributeAction);
	_editToolBar->addAction(_entityAction);
	_editToolBar->addAction(_relationAction);
	_editToolBar->addAction(_keyAction);
	_editToolBar->addAction(_dbTableAction);
}

// 產生畫布
void GUI::createCanvas()
{
	_scene = new GraphicsScene(_presentationModel);
	_scene->setSceneRect(QRectF(0, 0, WIDTH, HEIGHT));
	_view = new QGraphicsView(_scene);
	_scene->setParent(_view);
	_textEdit = new QTextEdit();
	_textEdit->setReadOnly(true);
	_textEdit->setHidden(true);
	_guiLayout = new QVBoxLayout();
	_guiLayout->addWidget(_view);
	_guiLayout->addWidget(_textEdit);
	_tableLayout = new QVBoxLayout();
	_tableLayout->addWidget(new QLabel("Components"), 0, Qt::AlignCenter);
	_tableView = new TableView();
	_tableView->setMinimumWidth(TABLE_VIEW_WIDTH);
	_tableLayout->addWidget(_tableView);
	_hLayout = new QHBoxLayout();
	_hLayout->addLayout(_guiLayout);
	_hLayout->addLayout(_tableLayout);
	_widget = new QWidget();
	_widget->setLayout(_hLayout);
	setCentralWidget(_widget);
}

// 設定 table model
void GUI::setTableModel()
{
	_tableModel = new TableModel(_presentationModel);
	_tableModel->setTableData();
	_tableView->setModel(_tableModel);
	connect(_tableView, SIGNAL(editChanged(const QModelIndex*)), _tableModel, SLOT(editChanged(const QModelIndex*)));
}

void GUI::close()
{
	QMessageBox messageBox;
	int isOK = messageBox.warning(NULL, "ERD", "Do you want to save the current diagram?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	if (isOK == QMessageBox::Yes)
	{
		saveFile();
	}
	QWidget::close();
}

// 開啟檔案
void GUI::openFile()
{
	clickPointerEvent();
	QString fileName = QFileDialog::getOpenFileName(this, "Open ERD files", "C:\\", "ERD Files (*.erd)");
	_presentationModel->loadFile(fileName.toStdString());
	//_presentationModel->composePosition();
	update();
}

void GUI::saveFile()
{
	QString fileName = QFileDialog::getSaveFileName(this, "Save ERD files", "C:\\", "ERD Files (*.erd);;XML files (*.xml)");
	_presentationModel->saveFile(fileName.toStdString());
}

void GUI::saveXmlFile()
{
	QString fileName = QFileDialog::getSaveFileName(this, "Save XML files", "C:\\", "XML files (*.xml)");
	_presentationModel->saveFile(fileName.toStdString());
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

// 點擊 primary key 事件
void GUI::clickPrimaryKeyEvent()
{
	_scene->clickPrimaryKeyEvent();
}

// 點擊 undo 事件
void GUI::clickUndoEvent()
{
	_presentationModel->undo();
	update();
	//_scene->clickUndoEvent();
}

// 點擊 redo 事件
void GUI::clickRedoEvent()
{
	_presentationModel->redo();
	update();
	//_scene->clickRedoEvent();
}

// 點擊刪除事件
void GUI::clickDeleteEvent()
{
	_presentationModel->deleteMultipleCommand();
	update();
	//_scene->clickDeleteEvent();
}

void GUI::clickCutEvent()
{
	_presentationModel->cut();
	update();
	//_scene->clickCutEvent();
}

void GUI::clickCopyEvent()
{
	_presentationModel->copy();
	//_scene->clickCopyEvent();
}

void GUI::clickPasteEvent()
{
	_presentationModel->paste();
	update();
	//_scene->clickPasteEvent();
}

void GUI::clickAboutEvent()
{
	QMessageBox::about(NULL, ABOUT_TITLE.c_str(), ABOUT_CONTENT.c_str());
	//_scene->clickAboutEvent();
}

void GUI::clickDBTableEvent()
{
	_textEdit->setHidden(!_textEdit->isHidden());
	update();
}

// 更新畫面
void GUI::update()
{
	updateButtonEnabled();
	_tableModel->setTableData();
	_scene->draw();
	_textEdit->setText(QString::fromStdString(_presentationModel->getGUITable()));
}
