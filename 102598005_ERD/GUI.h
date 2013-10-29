#ifndef _GUI_H_
#define  _GUI_H_

#include <QMainWindow>

class GUI : public QMainWindow
{
public:
	GUI();
	~GUI();
	void createMenus();
};

#endif