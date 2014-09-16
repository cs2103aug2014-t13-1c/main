#include "BoxIn.h"

/*
* Constructor method for BoxIn.
* Sets up the main window making use of the ui xml and fixes sizes
* Links events
*/
BoxIn::BoxIn(QWidget *parent) : QMainWindow(parent){
	QIcon icon("BoxIn.jpg");
	
	ui.setupUi(this);
	setWindowIcon(icon);
	setFixedSize(WIDTH_WINDOW, HEIGHT_WINDOW); //size is not variable.
	setComponentSizes();
	linkEvents();
	setupMap();
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

void BoxIn::setupMap(){
	stringToCommand["add"] = CommandAdd;
	stringToCommand["delete"] = CommandDelete;
	stringToCommand["edit"] = CommandEdit;
	stringToCommand["exit"] = CommandExit;
}


void BoxIn::displayFeedback(QString feedback){
	ui.feedbackBox->setText(feedback);
}

QString BoxIn::readCommandLine(){
	return ui.commandLine->text();
}

void BoxIn::clearCommandLine(){
	ui.commandLine->setText("");
}

void BoxIn::commandLineReturnPressed(){
	handleUserInput(readCommandLine());
}

void BoxIn::buttonExitClicked(){
	qApp->quit();
}

void BoxIn::handleUserInput(QString input){
	QStringList words = input.split(WHITESPACE, QString::KeepEmptyParts, Qt::CaseInsensitive);
	QString firstWord = words[FIRST_WORD_POSITION];
	clearCommandLine();
	switch(stringToCommand[firstWord]){
		case CommandAdd :
			displayFeedback(PROMPT_DATE);
			break;
		case CommandDelete :
			break;
		case CommandEdit :
			break;
		case CommandExit :
			break;
		default :
			displayFeedback(QString("Command is not recognised"));
			break;
	}

}

void BoxIn::extractKeywords(QStringList input){
	int indexPlace = input.indexOf(KEYWORD_PLACE);
	int indexDate = input.indexOf(KEYWORD_DATE);
	int indexTime = input.indexOf(KEYWORD_TIME);
	
	if(indexPlace > indexDate || indexDate > indexTime){
		displayFeedback(QString("Command format is wrong"));
	}else{
		if(indexPlace == NOT_FOUND_IN_COMMAND){
			displayFeedback(QString("Please enter a location"));
		}
		if(indexDate == NOT_FOUND_IN_COMMAND){
			displayFeedback(QString("Please enter a date"));
		}
		if(indexTime == NOT_FOUND_IN_COMMAND){
			displayFeedback(QString("Please enter a time"));
		}
	}
}