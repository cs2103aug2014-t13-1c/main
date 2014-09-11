#include "BoxIn.h"

BoxIn::BoxIn(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	this->setFixedSize(WIDTH_WINDOW, HEIGHT_WINDOW);

	ui.displayFeed->setGeometry(0, 0, WIDTH_WINDOW, HEIGHT_LARGE);
	ui.feedbackBox->setGeometry(0, HEIGHT_LARGE + HEIGHT_BUFFER, WIDTH_WINDOW, HEIGHT_SMALL);
	ui.commandLabel->setGeometry(0, HEIGHT_LARGE + HEIGHT_SMALL + 2 * HEIGHT_BUFFER, WIDTH_LABEL, HEIGHT_SMALL);
	ui.commandLine->setGeometry(WIDTH_LABEL, HEIGHT_LARGE + HEIGHT_SMALL + 2 * HEIGHT_BUFFER, WIDTH_WINDOW - WIDTH_LABEL, HEIGHT_SMALL);
	ui.buttonExit->setGeometry(0, HEIGHT_LARGE + 2 * HEIGHT_SMALL + 3 * HEIGHT_BUFFER, WIDTH_WINDOW, HEIGHT_SMALL);

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
