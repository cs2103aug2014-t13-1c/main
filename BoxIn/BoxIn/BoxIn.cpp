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
	startLabel = new QLabel("Time / Date", this);
	//endLabel = new QLabel("End", this);
    idxLabel = new QLabel("Index", this);
	commandLine = new QLineEdit(this);
    /*
	displayFeedName = new DisplayFeed(this, Name);
    displayFeedStartDate = new DisplayFeed(this, StartDate);
	displayFeedEndDate = new DisplayFeed(this, EndDate);
    displayFeedStartTime = new DisplayFeed(this, StartTime);
	displayFeedEndTime = new DisplayFeed(this, EndTime);
	displayFeedPlace = new DisplayFeed(this, Place);
    */
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
	// endLabel->setGeometry(800, 40, 50, 20);
	commandLine->setGeometry(80, 540, WIDTH_WINDOW - 80, 20);
    ui.feedbackBox->setGeometry(0, 500, WIDTH_WINDOW, 20);
    displayFeedIdx->setGeometry(20, 70, WIDTH_WINDOW - 2 * WIDTH_BUFFER, 350);
    //displayFeedName->setGeometry(60, 70, 340, 400);
    //displayFeedStartDate->setGeometry(600, 70, 100, 400);
    //displayFeedStartTime->setGeometry(700, 70, 100, 400);
    //displayFeedEndDate->setGeometry(800, 70, 100, 400);
    //displayFeedEndTime->setGeometry(900, 70, 100, 400);
    //displayFeedPlace->setGeometry(400, 70, 200, 400);
}

void BoxIn::setComponentColors(){
	nameLabel->setStyleSheet(TRANSPARENT);
	placeLabel->setStyleSheet(TRANSPARENT);
	startLabel->setStyleSheet(TRANSPARENT);
	//endLabel->setStyleSheet(TRANSPARENT);
    idxLabel->setStyleSheet(TRANSPARENT);
	commandLine->setStyleSheet(WHITE);
    /*
    displayFeedName->setStyleSheet(TRANSPARENT);
    displayFeedStartDate->setStyleSheet(TRANSPARENT);
    displayFeedStartTime->setStyleSheet(TRANSPARENT);
    displayFeedEndDate->setStyleSheet(TRANSPARENT);
    displayFeedEndTime->setStyleSheet(TRANSPARENT);
    displayFeedPlace->setStyleSheet(TRANSPARENT);
    */
    displayFeedIdx->setStyleSheet(TRANSPARENT);
}

/**
* Setup method
* linkEvents deals with the events from keypresses and such, connecting them to the relevant function call
*/
void BoxIn::linkEvents(){
	QObject::connect(commandLine, SIGNAL(returnPressed()), this, SLOT(commandLineReturnPressed()));
    QObject::connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    /*
	QObject::connect(displayFeedName, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(editItem(QListWidgetItem*)));
    QObject::connect(displayFeedStartDate, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(editItem(QListWidgetItem*)));
    QObject::connect(displayFeedStartTime, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(editItem(QListWidgetItem*)));
    QObject::connect(displayFeedEndDate, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(editItem(QListWidgetItem*)));
    QObject::connect(displayFeedEndTime, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(editItem(QListWidgetItem*)));
    QObject::connect(displayFeedPlace, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(editItem(QListWidgetItem*)));
    */
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

void BoxIn::commandLineReturnPressed(){
	std::string feedback = logic.handleUserInput(readCommandLine().toStdString());
	displayFeedback(QString(feedback.c_str()));
	clearCommandLine();
	updateGUI();
}

void BoxIn::updateGUI(){
	std::vector<Event*> thingsToInclude = logic.getEvents();
    /*
	displayFeedName->refresh(&thingsToInclude);
    displayFeedStartDate->refresh(&thingsToInclude);
    displayFeedEndDate->refresh(&thingsToInclude);
    displayFeedStartTime->refresh(&thingsToInclude);
    displayFeedEndTime->refresh(&thingsToInclude);
    displayFeedPlace->refresh(&thingsToInclude);
    */
    displayFeedIdx->refresh(&thingsToInclude);
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