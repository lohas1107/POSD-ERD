#include "TextUI.h"
#include "PresentationModel.h"
#include "ERModel.h"

int main(int argc, char* argv[])
{
	ERModel* erModel = new ERModel();
	PresentationModel* presentationModel = new PresentationModel(erModel);

	TextUI textUI(presentationModel);
	textUI.displayMenu();
	
	delete erModel;
	delete presentationModel;

	system("pause");
	return 0;
}
