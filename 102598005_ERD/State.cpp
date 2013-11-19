#include "State.h"
#include "GraphicsScene.h"
#include "PresentationModel.h"

State::State(GraphicsScene* scene)
{
	_scene = scene;
	_presentationModel = _scene->getPresentationModel();
}

State::~State()
{
}
