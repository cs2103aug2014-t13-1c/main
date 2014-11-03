//@author A0111994B

#include "BoxIn.h"

/*
* Constructor method for BoxIn.
* Sets up the main window making use of the ui xml and fixes sizes
* Links events
*/
BoxIn::BoxIn(QWidget *parent) : QMainWindow(parent){
	createActions();
	ui.setupUi(this);
	setFixedSize(WIDTH_WINDOW, HEIGHT_WINDOW); //size is not variable.
	createComponents();
	createTrayIcon();
	linkEvents();
	trayIcon->show();
    updateGUI();
}

BoxIn::~BoxIn(){
}

/*
* Initializes the relevant components of the UI
*/
void BoxIn::createComponents(){
	clock = new DigitalClock(this);
	nameLabel = new QLabel("Name", this);
	placeLabel = new QLabel("Place", this);
	startLabel = new QLabel("Time / Date", this);
    idxLabel = new QLabel("Index", this);
	commandLine = new QLineEdit(this);
    displayFeedIdx = new DisplayFeed(this, Index);
	setComponentSizes();
	setComponentColors();
}

/*
* Setup method
* setComponentSizes deals with the sizes of the various items in the window. These are fixed constants
* declared in BoxIn.h
*/
void BoxIn::setComponentSizes(){
	clock->move(WIDTH_WINDOW - 100, 450);
    idxLabel->setGeometry(20, 40, 40, 20);
	nameLabel->setGeometry(60, 40, 50, 20);
	placeLabel->setGeometry(400, 40, 50, 20);
	startLabel->setGeometry(550, 40, 100, 20);
	commandLine->setGeometry(80, 540, WIDTH_WINDOW - 80, 20);
    ui.feedbackBox->setGeometry(0, 500, WIDTH_WINDOW, 20);
    displayFeedIdx->setGeometry(20, 70, WIDTH_WINDOW - 2 * WIDTH_BUFFER, 350);
}

/*
* Makes use of stylesheets to set up background colors for the various components
*/
void BoxIn::setComponentColors(){
	nameLabel->setStyleSheet(TRANSPARENT);
	placeLabel->setStyleSheet(TRANSPARENT);
	startLabel->setStyleSheet(TRANSPARENT);
    idxLabel->setStyleSheet(TRANSPARENT);
	commandLine->setStyleSheet(WHITE);
    displayFeedIdx->setStyleSheet(TRANSPARENT);
}

/**
* Setup method
* linkEvents deals with the events from keypresses and such, connecting them to the relevant function call
*/
void BoxIn::linkEvents(){
	QObject::connect(commandLine, SIGNAL(returnPressed()), this, SLOT(commandLineReturnPressed()));
    QObject::connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    QObject::connect(displayFeedIdx, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(editItem(QListWidgetItem*)));
}

/**
* Handles the event changes - particularly the minimizing and maximizing of the window to system tray.
*/
void BoxIn::changeEvent(QEvent *event){
	if(event->type() == QEvent::Close){
        event->ignore();
        this->hide();
    }
    else{event->accept();}
	if(windowState() == Qt::WindowMinimized){
		this->hide();
	}else if(windowState() == Qt::WindowMaximized){
		this->show();
	}
}

void BoxIn::displayFeedback(QString feedback){
	ui.feedbackBox->setText(feedback);
}

QString BoxIn::readCommandLine(){
	return commandLine->text();
}

void BoxIn::clearCommandLine(){
	commandLine->setText("");
}

/*
* The main method for capturing the enter keypress from the user
* Calls the logic component to process user input and retrieve the appropriate feedback
* This is also the refresh signal for the display
*/
void BoxIn::commandLineReturnPressed(){
	std::string feedback = logic.handleUserInput(readCommandLine().toStdString());
	displayFeedback(QString(feedback.c_str()));
	clearCommandLine();
	updateGUI();
}

void BoxIn::updateGUI(){
	std::vector<Event*> thingsToInclude = logic.getEvents();
    displayFeedIdx->refresh(&thingsToInclude);
}

/*
* Sets up the system tray icon
*/
void BoxIn::createTrayIcon(){
	trayIcon = new QSystemTrayIcon(this);
	trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);
	trayIcon->setIcon(QIcon("BoxInSysTrayIco.png"));
    trayIcon->setContextMenu(trayIconMenu);
}

/*
* Sets up the system tray icon's menu
*/
void BoxIn::createActions(){
     minimizeAction = new QAction(tr("Minimize"), this);
     QObject::connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

     restoreAction = new QAction(tr("Restore"), this);
     QObject::connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

     quitAction = new QAction(tr("Quit"), this);
     QObject::connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
 }

/*
* Sets up the double click event for the icon to reopen the window
*/
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

 /*
 * Connects the clicking of any event on the display to the QEventEditor
 * Captures the formatted input and passes it through the command line as per normal
 */
void BoxIn::editItem(QListWidgetItem *item){
	QEventEditor *editor = new QEventEditor(dynamic_cast<QEventStore*>(item)->getEvent());
	QObject::connect(editor, SIGNAL(infoOut(std::string)), this, SLOT(setCommand(std::string)));
	QObject::connect(editor, SIGNAL(accepted()), this, SLOT(commandLineReturnPressed()));
	editor->exec();
}

void BoxIn::setCommand(std::string command){
	commandLine->setText(QString(command.c_str()));
}