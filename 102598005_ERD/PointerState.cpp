#include "PointerState.h"
#include <iostream>
#include "..\src\corelib\io\qdebug.h"

PointerState::PointerState(GraphicsManager* scene) : State(scene)
{
}

PointerState::~PointerState()
{
}

void PointerState::mousePressEvent(QPointF position)
{


	qDebug() << position;
}

void PointerState::mouseMoveEvent(QPointF position)
{

	qDebug() << position;
}

void PointerState::mouseReleaseEvent(QPointF position)
{

	qDebug() << position;
}
