#include "TextUI.h"
#include "PresentationModel.h"
#include "ERModel.h"
#include <QApplication>
#include "GUI.h"

const string GUI_MODE = "guimode";
const string TEXT_MODE = "textmode";

int main(int argc, char* argv[])
{
	ERModel* erModel = new ERModel();
	PresentationModel* presentationModel = new PresentationModel(erModel);

	if (argc == 1 || argv[1] == GUI_MODE)
	{
		QApplication application(argc, argv);
		GUI gui(presentationModel);
		gui.show();
		return application.exec();
	}
	else if (argc > 1 && argv[1] == TEXT_MODE)
	{

		TextUI textUI(presentationModel);
		textUI.displayMenu();
		system("pause");
	}

	delete erModel;
	delete presentationModel;
}
