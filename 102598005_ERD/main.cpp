#include "TextUI.h"
#include "PresentationModel.h"
#include "ERModel.h"
#include <QApplication>
#include "GUI.h"

const string GUI_MODE = "guimode";
const string TEXT_MODE = "textmode";

int main(int argc, char* argv[])
{
	if (argc == 1 || argv[1] == GUI_MODE)
	{
		QApplication application(argc, argv);
		GUI gui;
		gui.show();

		return application.exec();
	}
	else if (argc > 1 && argv[1] == TEXT_MODE)
	{
		ERModel* erModel = new ERModel();
		PresentationModel* presentationModel = new PresentationModel(erModel);
		TextUI textUI(presentationModel);
		textUI.displayMenu();
		delete erModel;
		delete presentationModel;

		system("pause");
	}
}
