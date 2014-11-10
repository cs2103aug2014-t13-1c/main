//@author A0111994B
#pragma once
#include "qcombobox.h"
#include "Event.h"
#include "qlabel.h"
#include "qlineedit.h"
#include "qpushbutton.h"
#include "Logic.h"
#include "qdialog.h"
#include "QEvent.h"
#include <map>
#include <sstream>

static const int WIDTH_POPUP = 400;
static const int HEIGHT_POPUP = 200;
static const int HEIGHT_TEXT = 20;

namespace Editor{
    static const std::string FIELD_NAME = "Name";
    static const std::string FIELD_LOCATION = "Place";
    static const std::string FIELD_START_DATE = "Start Date";
    static const std::string FIELD_END_DATE = "End Date";
    static const std::string FIELD_START_TIME = "Start Time";
    static const std::string FIELD_END_TIME = "End Time";
}

class QEventEditor :
	public QDialog
{
	Q_OBJECT
public:
	QEventEditor(Event* event, QWidget *parent = 0);
	~QEventEditor(void);
    void setupMap();

private:
	Event *event;
	QLabel *fieldLabel;
	QComboBox *fieldSelector;
	QLineEdit *valueLine;
	QPushButton *saveButton;
	QPushButton *cancelButton;
	QLineEdit *commandLine;

    std::map<std::string, std::string> fieldToEditor;

	void createObjects();
	void arrangeObjects();
	void setupComboBox();
	void setupButtons();
	void changeEvent(QEvent* event);
signals:
	void infoOut(std::string);
	void destroyed();
public slots:
	void setField(QString text);
	void saveInfo();
};

