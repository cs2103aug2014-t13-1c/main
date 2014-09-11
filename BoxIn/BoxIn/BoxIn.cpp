#include "BoxIn.h"

BoxIn::BoxIn(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QObject::connect(ui.buttonExit,SIGNAL(clicked()), this, SLOT(buttonExitClicked()));
	QObject::connect(ui.commandLine, SIGNAL(returnPressed()), this, SLOT(commandLineReturnPressed()));

}

BoxIn::~BoxIn(){
}

void BoxIn::commandLineReturnPressed(){
	QString command = ui.commandLine->text();
	ui.displayFeed->addItem(command);
	ui.commandLine->setText("");
}

void BoxIn::buttonExitClicked(){
	qApp->quit();
}
