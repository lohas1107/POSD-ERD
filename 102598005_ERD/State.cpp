#include "State.h"
#include "GraphicsScene.h"
#include "PresentationModel.h"

State::State(GraphicsScene* scene)
{
	_scene = scene;
	_presentationModel = _scene->getPresentationModel();
	initialize();
}

State::~State()
{
	delete _pointItem;
}

void State::initialize()
{
	_pointItem = NULL;
	_pointId = INT_MIN;
}

int State::getItemId(QPointF position)
{
	_pointItem = _scene->itemAt(position);

	if (_pointItem != NULL)
	{
		_pointId = _pointItem->data(idData).toInt();
	}

	return _pointId;
}
