#include "State.h"
#include "GraphicsManager.h"
#include "PresentationModel.h"

State::State(GraphicsManager* scene)
{
	_scene = scene;
	_presentationModel = _scene->getPresentationModel();
}

State::~State()
{
}
