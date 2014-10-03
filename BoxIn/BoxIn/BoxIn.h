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

static const int HEIGHT_WINDOW = 600;
static const int WIDTH_WINDOW = 800;

static const int HEIGHT_BUFFER = 10;
static const int HEIGHT_NO_CLICK_ZONE = 60;

static const int HEIGHT_SMALL = 20;
static const int HEIGHT_LARGE = 400;

static const int WIDTH_LABEL = 60;

class BoxIn : public QMainWindow
{
	Q_OBJECT

public:
	explicit BoxIn(QWidget *parent = 0);
	~BoxIn();

	void displayFeedback(QString feedback);
	void clearCommandLine();
	QString readCommandLine();
	void setVisible(bool visible);

private:
	Ui::BoxInClass ui;
	Logic logic;

	void setComponentSizes();
	void linkEvents();
	void updateGUI();

	// for the tray icon

	void createTrayIcon();
	void createActions();
	void iconActivatd();
	void changeEvent(QEvent *event);

	QAction *minimizeAction;
	QAction *restoreAction;
	QAction *quitAction;

	QSystemTrayIcon *trayIcon;
	QMenu *trayIconMenu;

private slots:
	void commandLineReturnPressed();
	void buttonExitClicked();
	void iconActivated(QSystemTrayIcon::ActivationReason reason);
};

#endif // BOXIN_H
