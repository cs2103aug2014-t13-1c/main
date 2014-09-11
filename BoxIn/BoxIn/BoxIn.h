#ifndef BOXIN_H
#define BOXIN_H

#include <QMainWindow>
#include <QString>
#include <qlistview.h>
#include "ui_BoxIn.h"
#include <map>

static const int HEIGHT_WINDOW = 600;
static const int WIDTH_WINDOW = 400;

static const int HEIGHT_BUFFER = 10;

static const int HEIGHT_SMALL = 20;
static const int HEIGHT_LARGE = 450;

static const int WIDTH_LABEL = 60;

static const QString PROMPT_DATE = "Please enter a date in the format DDMMYY";
static const QString PROMPT_TIME = "Please enter a time in the format HHMM";

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

	void setComponentSizes();
	void linkEvents();
	void setupMap();
	void handleUserInput(QString input);

private slots:
	void commandLineReturnPressed();
	void buttonExitClicked();
};

#endif // BOXIN_H
