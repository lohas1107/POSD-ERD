#include "State.h"
#include "GraphicsScene.h"
#include "PresentationModel.h"

State::State(GraphicsScene* scene)
{
	_scene = scene;
	_presentationModel = _scene->getPresentationModel();
	_presentationModel->setPointerButtonChecked(false);
	_presentationModel->notifyButtonEnabled();
	initialize();
}

State::~State()
{
	delete _pointItem;
}

// 初始化
void State::initialize()
{
	_pointItem = NULL;
	_pointID = INT_MIN;
}

// 取得選取item的id
int State::getItemID(QPointF position)
{
	_pointItem = _scene->itemAt(position);

	if (_pointItem != NULL)
	{
		_pointID = _pointItem->data(idData).toInt();
	}

	return _pointID;
}
