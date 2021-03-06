//@author A0111994B
#ifndef BOXIN_H
#define BOXIN_H

#include <QMainWindow>
#include <QString>
#include <qlistview.h>
#include "qsystemtrayicon.h"
#include <QMenu>
#include <qmessagebox.h>
#include <QCloseEvent>
#include "ui_BoxIn.h"
#include "Logic.h"
#include "digitalclock.h"
#include <qapplication.h>
#include "DisplayFeed.h"
#include <QLineEdit>
#include <QLabel>

static const int HEIGHT_WINDOW = 600;
static const int WIDTH_WINDOW = 1000;

static const int HEIGHT_BUFFER = 10;
static const int WIDTH_BUFFER = 20;
static const int HEIGHT_NO_CLICK_ZONE = 60;

static const int HEIGHT_SMALL = 20;
static const int HEIGHT_LARGE = 400;

static const int WIDTH_LABEL = 60;

static const QString PASTEL_BLUE = "rgb(141, 199, 187)";
static const QString TRANSPARENT = "background-color: rgba(255, 255, 255, 0)";
static const QString WHITE = "background-color: rgb(255, 255, 255)";

class BoxIn : public QMainWindow{
	Q_OBJECT
public:
	explicit BoxIn(QWidget *parent = 0);
	~BoxIn();

	void displayFeedback(QString feedback);
	void clearCommandLine();
	QString readCommandLine();
	void setVisible(bool visible);
	void updateGUI();
	void createComponents();
	void setComponentSizes();
	void setComponentColors();
	void linkEvents();

	void createTrayIcon();
	void createActions();
	void iconActivatd();
	void changeEvent(QEvent *event);

private:
	Ui::BoxInClass ui;
	Logic logic;

	QAction *minimizeAction;
	QAction *restoreAction;
	QAction *quitAction;

	DigitalClock *clock;
	QLabel *nameLabel;
	QLabel *placeLabel;
	QLabel *startLabel;
    QLabel *idxLabel;

	QSystemTrayIcon *trayIcon;
	QMenu *trayIconMenu;
    DisplayFeed *displayFeedIdx;
	QLineEdit *commandLine;

public slots:
	void commandLineReturnPressed();
	void iconActivated(QSystemTrayIcon::ActivationReason reason);
	void editItem(QListWidgetItem *item);
	void setCommand(std::string command);
};

#endif // BOXIN_H
