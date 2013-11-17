#include "PointerState.h"
#include <iostream>
#include "..\src\corelib\io\qdebug.h"

PointerState::PointerState(PresentationModel* presentationModel) : State(presentationModel)
{
}

PointerState::~PointerState()
{
}

void PointerState::mousePressEvent(QPointF position)
{
	//cout << position.x();

	//qDebug() << position;
}

void PointerState::mouseMoveEvent(QPointF position)
{
	////cout << position.x();
	//qDebug() << position;
}

void PointerState::mouseReleaseEvent(QPointF position)
{
	//cout << position.x();
	//qDebug() << position;
}
