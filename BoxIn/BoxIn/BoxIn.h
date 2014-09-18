#ifndef BOXIN_H
#define BOXIN_H

#include <QMainWindow>
#include <QString>
#include <qlistview.h>
#include "ui_BoxIn.h"
#include "Logic.h"

static const int HEIGHT_WINDOW = 600;
static const int WIDTH_WINDOW = 800;

static const int HEIGHT_BUFFER = 10;
static const int HEIGHT_NO_CLICK_ZONE = 60;

static const int HEIGHT_SMALL = 20;
static const int HEIGHT_LARGE = 400;

static const int WIDTH_LABEL = 60;

static const int FIRST_WORD_POSITION = 0;
static const QString WHITESPACE = " ";


static const QString KEYWORD_PLACE = "place";
static const QString KEYWORD_DATE = "date";
static const QString KEYWORD_TIME = "time";
static const int NOT_FOUND_IN_COMMAND = -1;

static const QString USER_COMMAND_ADD = "add";
static const QString USER_COMMAND_DELETE = "delete";
static const QString USER_COMMAND_EDIT = "edit";
static const QString USER_COMMAND_EXIT = "exit";

enum CommandTypes {
	CommandAdd = 1,
	CommandDelete = 2,
	CommandEdit = 3,
	CommandExit = 4
};



class BoxIn : public QMainWindow
{
	Q_OBJECT

public:
	explicit BoxIn(QWidget *parent = 0);
	~BoxIn();

	void displayFeedback(QString feedback);
	void clearCommandLine();
	QString readCommandLine();

private:
	Ui::BoxInClass ui;
	std::map<QString, CommandTypes> stringToCommand;
	Logic logic;

	void setComponentSizes();
	void linkEvents();
	void setupMap();
	void handleUserInput(QString input);
	void extractKeywords(QStringList input);
	void updateGUI();

private slots:
	void commandLineReturnPressed();
	void buttonExitClicked();
};

#endif // BOXIN_H
