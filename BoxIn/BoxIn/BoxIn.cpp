#include "BoxIn.h"

/*
* Constructor method for BoxIn.
* Sets up the main window making use of the ui xml and fixes sizes
* Links events
*/
BoxIn::BoxIn(QWidget *parent) : QMainWindow(parent){
	ui.setupUi(this);
	QIcon icon("BoxIn.jpg");
	setWindowIcon(icon);
	setFixedSize(WIDTH_WINDOW, HEIGHT_WINDOW); //size is not variable.
	setComponentSizes();
	linkEvents();
}

BoxIn::~BoxIn(){
}

/*
* Setup method
* setComponentSizes deals with the sizes of the various items in the window. These are fixed constants
* declared in BoxIn.h
*/
void BoxIn::setComponentSizes(){
	ui.displayFeed->setGeometry(0, 0, WIDTH_WINDOW, HEIGHT_LARGE);
	ui.feedbackBox->setGeometry(0, HEIGHT_LARGE + HEIGHT_BUFFER, WIDTH_WINDOW, HEIGHT_SMALL);
	ui.commandLabel->setGeometry(0, HEIGHT_LARGE + HEIGHT_SMALL + 2 * HEIGHT_BUFFER, WIDTH_LABEL, HEIGHT_SMALL);
	ui.commandLine->setGeometry(WIDTH_LABEL, HEIGHT_LARGE + HEIGHT_SMALL + 2 * HEIGHT_BUFFER, WIDTH_WINDOW - WIDTH_LABEL, HEIGHT_SMALL);
	ui.buttonExit->setGeometry(0, HEIGHT_LARGE + 2 * HEIGHT_SMALL + 3 * HEIGHT_BUFFER, WIDTH_WINDOW, HEIGHT_SMALL);
}

/*
* Setup method
* linkEvents deals with the events from keypresses and such, connecting them to the relevant function call
*
*/
void BoxIn::linkEvents(){
	QObject::connect(ui.buttonExit,SIGNAL(clicked()), this, SLOT(buttonExitClicked()));
	QObject::connect(ui.commandLine, SIGNAL(returnPressed()), this, SLOT(commandLineReturnPressed()));
}


void BoxIn::commandLineReturnPressed(){
	QString command = ui.commandLine->text();
	ui.displayFeed->addItem(command);
	ui.commandLine->setText("");
}

void BoxIn::buttonExitClicked(){
	qApp->quit();
}
