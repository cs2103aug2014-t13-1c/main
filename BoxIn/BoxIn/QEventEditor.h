#pragma once
#include "qcombobox.h"
#include "Event.h"
#include "qlabel.h"
#include "qlineedit.h"
#include "qpushbutton.h"
#include "Logic.h"
#include "qdialog.h"
#include "QEvent.h"

static const int WIDTH_POPUP = 400;
static const int HEIGHT_POPUP = 200;
static const int HEIGHT_TEXT = 20;

class QEventEditor :
	public QDialog
{
	Q_OBJECT
public:
	QEventEditor(Event* event, QWidget *parent = 0);
	~QEventEditor(void);

private:
	Event *event;
	QLabel *fieldLabel;
	QComboBox *fieldSelector;
	QLineEdit *valueLine;
	QPushButton *saveButton;
	QPushButton *cancelButton;
	QLineEdit *commandLine;

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

