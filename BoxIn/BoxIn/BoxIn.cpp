#include "BoxIn.h"

/*
* Constructor method for BoxIn.
* Sets up the main window making use of the ui xml and fixes sizes
* Links events
*/
BoxIn::BoxIn(QWidget *parent) : QMainWindow(parent){
	ui.setupUi(this);
	createActions();
	createTrayIcon();
	setFixedSize(WIDTH_WINDOW, HEIGHT_WINDOW); //size is not variable.
	setComponentSizes();
	linkEvents();
	setupMap();
	trayIcon->show();
}

BoxIn::~BoxIn(){
}

/*
* Setup method
* setComponentSizes deals with the sizes of the various items in the window. These are fixed constants
* declared in BoxIn.h
*/
void BoxIn::setComponentSizes(){
	ui.feedbackBox->setGeometry(0, HEIGHT_WINDOW - HEIGHT_NO_CLICK_ZONE - 3 * HEIGHT_SMALL - 2 * HEIGHT_BUFFER, WIDTH_WINDOW, HEIGHT_SMALL);
	ui.commandLabel->setGeometry(0, HEIGHT_WINDOW - HEIGHT_NO_CLICK_ZONE - 2 * HEIGHT_SMALL - HEIGHT_BUFFER, WIDTH_LABEL, HEIGHT_SMALL);
	ui.commandLine->setGeometry(WIDTH_LABEL, HEIGHT_WINDOW - HEIGHT_NO_CLICK_ZONE - 2 * HEIGHT_SMALL - HEIGHT_BUFFER, WIDTH_WINDOW - WIDTH_LABEL, HEIGHT_SMALL);
	ui.buttonExit->setGeometry(0, HEIGHT_WINDOW - HEIGHT_NO_CLICK_ZONE - HEIGHT_SMALL, WIDTH_WINDOW, HEIGHT_SMALL);
	DigitalClock *clock = new DigitalClock(this);
	clock->move(WIDTH_WINDOW - WIDTH_TIMER - WIDTH_LABEL / 2, HEIGHT_WINDOW - HEIGHT_NO_CLICK_ZONE - 2 * HEIGHT_SMALL - HEIGHT_TIMER - 3 * HEIGHT_BUFFER);
}

/*
* Setup method
* linkEvents deals with the events from keypresses and such, connecting them to the relevant function call
*
*/
void BoxIn::linkEvents(){
	QObject::connect(ui.buttonExit,SIGNAL(clicked()), this, SLOT(buttonExitClicked()));
	QObject::connect(ui.commandLine, SIGNAL(returnPressed()), this, SLOT(commandLineReturnPressed()));

	QObject::connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(messageClicked()));
    QObject::connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

/*
* Handles the event changes - particularly the minimizing and maximizing of the window to system tray.
*/
void BoxIn::changeEvent(QEvent *event){
	event->accept();
	if(windowState() == Qt::WindowMinimized){
		this->hide();
	}else if(windowState() == Qt::WindowMaximized){
		this->show();
	}
}

void BoxIn::setupMap(){
	stringToCommand[USER_COMMAND_ADD] = CommandAdd;
	stringToCommand[USER_COMMAND_DELETE] = CommandDelete;
	stringToCommand[USER_COMMAND_EDIT] = CommandEdit;
	stringToCommand[USER_COMMAND_UNDO] = CommandUndo;
	stringToCommand[USER_COMMAND_EXIT] = CommandExit;
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
	std::string feedback = handleUserInput(readCommandLine());
	displayFeedback(QString(feedback.c_str()));
	clearCommandLine();
	updateGUI();
}

void BoxIn::buttonExitClicked(){
	qApp->quit();
}

std::string BoxIn::handleUserInput(QString input){
	QStringList words = input.split(WHITESPACE, QString::KeepEmptyParts, Qt::CaseInsensitive);
	QString firstWord = words[FIRST_WORD_POSITION];
	std::string feedback = "Done!";
	switch(stringToCommand[firstWord]){
		case CommandAdd :
			logic.add(input.right(input.length() - USER_COMMAND_ADD.length()).toStdString());
			break;
		case CommandDelete :
			logic.del(input.right(input.length() - USER_COMMAND_DELETE.length()).toStdString());
			break;
		case CommandEdit :
			logic.edit(input.right(input.length() - USER_COMMAND_EDIT.length()).toStdString());
			break;
		case CommandExit :
			qApp->quit();
			break;
		case CommandUndo :
			break;
		default :
			feedback = "Command is not recognised";
			break;
	}
	return feedback;
}

void BoxIn::updateGUI(){
	std::vector<Event*> thingsToInclude = logic.getEvents();
	ui.displayFeedToday->clear();
	for(std::vector<Event*>::iterator iter = thingsToInclude.begin(); iter != thingsToInclude.end(); iter++){
		std::string itemText = (*iter)->getName() + " at " + (*iter)->getLocation() + " - " + (*iter)->getDate() + ", " + (*iter)->getTime();
		QListWidgetItem *item = new QListWidgetItem(QString(itemText.c_str()), ui.displayFeedToday);
	}
}

void BoxIn::createTrayIcon(){
	trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);
	trayIcon = new QSystemTrayIcon(this);
	trayIcon->setIcon(QIcon("BoxInSysTrayIco.jpg"));
    trayIcon->setContextMenu(trayIconMenu);
}

void BoxIn::createActions()
 {
     minimizeAction = new QAction(tr("Minimize"), this);
     QObject::connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

     restoreAction = new QAction(tr("Restore"), this);
     QObject::connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

     quitAction = new QAction(tr("Quit"), this);
     QObject::connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
 }

 void BoxIn::iconActivated(QSystemTrayIcon::ActivationReason reason){
	 if(reason == QSystemTrayIcon::DoubleClick){
		 this->showNormal();
		 this->raise();
		 this->activateWindow();
	 }
 }

 void BoxIn::setVisible(bool visible){
    minimizeAction->setEnabled(visible);
    restoreAction->setEnabled(isMaximized() || !visible);
    QMainWindow::setVisible(visible);
}