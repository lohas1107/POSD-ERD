#include "AddNodeState.h"
#include "PointerState.h"
#include <QtGui/QDialog>
#include <QInputDialog>
#include "../src/corelib/io/qdebug.h"

AddNodeState::AddNodeState(PresentationModel* presentationModel) : State(presentationModel)
{
	//_isOK = false;
}

AddNodeState::~AddNodeState()
{
}

void AddNodeState::mousePressEvent(QPointF position)
{
	QString text = QInputDialog::getText(NULL, "Enter text", "Please enter the text", QLineEdit::Normal, "", &_isOK);
	if (_isOK && !text.isEmpty())
	{
		_presentationModel->addNodeCommand("E", text.toStdString());
	}
	_presentationModel->changeState(new PointerState(_presentationModel));
}

void AddNodeState::mouseMoveEvent(QPointF position)
{

}

void AddNodeState::mouseReleaseEvent(QPointF position)
{

	qDebug() << "release";


}
