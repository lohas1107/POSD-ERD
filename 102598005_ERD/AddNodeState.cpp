#include "AddNodeState.h"
#include "PointerState.h"
#include <QInputDialog>

const string TITLE = "Enter text";
const string LABEL = "Please enter the text";
const string TEXT = "";

AddNodeState::AddNodeState(GraphicsScene* scene, pair<Type, string> type) : State(scene)
{
	_type = type;
	_item = _scene->createGraphicsItem(_type.first);
	_scene->addItem(_item);
}

AddNodeState::~AddNodeState()
{
	delete _item;
}

// ���U�ƹ��ƥ�
void AddNodeState::mousePressEvent(QPointF mousePosition)
{
	_scene->removeItem(_item);
}

// ���ʷƹ��ƥ�
void AddNodeState::mouseMoveEvent(QPointF mousePosition)
{
	_item->setPos(mousePosition);
}

// ��}�ƹ��ƥ�
void AddNodeState::mouseReleaseEvent(QPointF mousePosition)
{
	QString text = QInputDialog::getText(NULL, TITLE.c_str(), LABEL.c_str(), QLineEdit::Normal, TEXT.c_str(), &_isOK);

	if (_isOK && !text.isEmpty())
	{
		_presentationModel->addNodeCommand(_type.second, text.toStdString(), mousePosition);
		_presentationModel->notify();
		_scene->clickPointerEvent();
	}
	else
	{
		_scene->addItem(_item);
	}
}
