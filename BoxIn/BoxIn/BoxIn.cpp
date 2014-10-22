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

void BoxIn::createComponents(){
	clock = new DigitalClock(this);
	nameLabel = new QLabel("Name", this);
	placeLabel = new QLabel("Place", this);
	dateLabel = new QLabel("Date", this);
	timeLabel = new QLabel("Time", this);
	commandLine = new QLineEdit(this);
	displayFeedName = new DisplayFeed(this, "Name");
	displayFeedDate = new DisplayFeed(this, "Date");
	displayFeedTime = new DisplayFeed(this, "Time");
	displayFeedPlace = new DisplayFeed(this, "Place");
	setComponentSizes();
	setComponentColors();
}

/*
* Setup method
* setComponentSizes deals with the sizes of the various items in the window. These are fixed constants
* declared in BoxIn.h
*/
void BoxIn::setComponentSizes(){
	clock->move(WIDTH_WINDOW - WIDTH_TIMER - WIDTH_LABEL / 2, HEIGHT_WINDOW - HEIGHT_NO_CLICK_ZONE - 2 * HEIGHT_SMALL - HEIGHT_TIMER - 3 * HEIGHT_BUFFER);
	nameLabel->setGeometry(20, 40, 50, 20);
	placeLabel->setGeometry(400, 40, 50, 20);
	dateLabel->setGeometry(600, 40, 50, 20);
	timeLabel->setGeometry(700, 40, 50, 20);
	commandLine->setGeometry(60, 500, 800, 20);
    displayFeedName->setGeometry(20, 70, 380, 300);
    displayFeedDate->setGeometry(600, 70, 100, 300);
    displayFeedTime->setGeometry(700, 70, 80, 300);
    displayFeedPlace->setGeometry(400, 70, 200, 300);
}

void BoxIn::setComponentColors(){
	nameLabel->setStyleSheet(TRANSPARENT);
	placeLabel->setStyleSheet(TRANSPARENT);
	dateLabel->setStyleSheet(TRANSPARENT);
	timeLabel->setStyleSheet(TRANSPARENT);
	commandLine->setStyleSheet(WHITE);
    displayFeedName->setStyleSheet(TRANSPARENT);
    displayFeedDate->setStyleSheet(TRANSPARENT);
    displayFeedTime->setStyleSheet(TRANSPARENT);
    displayFeedPlace->setStyleSheet(TRANSPARENT);
}

/**
* Setup method
* linkEvents deals with the events from keypresses and such, connecting them to the relevant function call
*/
void BoxIn::linkEvents(){
	QObject::connect(ui.buttonExit,SIGNAL(pressed()), this, SLOT(buttonExitClicked()));
	QObject::connect(commandLine, SIGNAL(returnPressed()), this, SLOT(commandLineReturnPressed()));
    QObject::connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
	QObject::connect(displayFeedName, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(editItem(QListWidgetItem*)));
    QObject::connect(displayFeedDate, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(editItem(QListWidgetItem*)));
    QObject::connect(displayFeedTime, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(editItem(QListWidgetItem*)));
    QObject::connect(displayFeedPlace, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(editItem(QListWidgetItem*)));
}

/**
* Handles the event changes - particularly the minimizing and maximizing of the window to system tray.
*/
void BoxIn::changeEvent(QEvent *event){
	if(event->type() == QEvent::Close){qApp->quit();}
	event->accept();
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

void BoxIn::commandLineReturnPressed(){
	std::string feedback = logic.handleUserInput(readCommandLine().toStdString());
	displayFeedback(QString(feedback.c_str()));
	clearCommandLine();
	updateGUI();
}

void BoxIn::buttonExitClicked(){
	qApp->quit();
}

void BoxIn::updateGUI(){
	std::vector<Event*> thingsToInclude = logic.getEvents();
	displayFeedName->refresh(&thingsToInclude);
    displayFeedDate->refresh(&thingsToInclude);
    displayFeedTime->refresh(&thingsToInclude);
    displayFeedPlace->refresh(&thingsToInclude);
}

void BoxIn::createTrayIcon(){
	trayIcon = new QSystemTrayIcon(this);
	trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);
	trayIcon->setIcon(QIcon("BoxInSysTrayIco.jpg"));
    trayIcon->setContextMenu(trayIconMenu);
}

void BoxIn::createActions(){
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

void BoxIn::editItem(QListWidgetItem *item){
	QEventEditor *editor = new QEventEditor(dynamic_cast<QEventStore*>(item)->getEvent());
	QObject::connect(editor, SIGNAL(infoOut(std::string)), this, SLOT(setCommand(std::string)));
	QObject::connect(editor, SIGNAL(accepted()), this, SLOT(commandLineReturnPressed()));
	editor->exec();
}

void BoxIn::setCommand(std::string command){
	commandLine->setText(QString(command.c_str()));
}