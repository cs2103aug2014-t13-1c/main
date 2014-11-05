//@author A0111994B
#include "QEventEditor.h"

QEventEditor::QEventEditor(Event* event, QWidget *parent)
{
	this->event = event;
	setModal(true);
	createObjects();
	arrangeObjects();
	setupComboBox();
	setupButtons();
    setupMap();
	show();
}

QEventEditor::~QEventEditor(void){
}

void QEventEditor::createObjects(){
	fieldLabel = new QLabel("Field:", this);
	fieldSelector = new QComboBox(this);
	valueLine = new QLineEdit(QString(event->getName().c_str()), this);
	saveButton = new QPushButton("Save", this);
	cancelButton = new QPushButton("Cancel", this);
}

void QEventEditor::arrangeObjects(){
	setFixedSize(WIDTH_POPUP, HEIGHT_POPUP);
	fieldLabel->setGeometry(0, HEIGHT_TEXT, WIDTH_POPUP / 8, HEIGHT_TEXT);
	fieldSelector->setGeometry(WIDTH_POPUP / 8, HEIGHT_TEXT, 100, HEIGHT_TEXT);
	valueLine->setGeometry(WIDTH_POPUP / 8 + 100, HEIGHT_TEXT, WIDTH_POPUP - (WIDTH_POPUP / 8 + 100), HEIGHT_TEXT);
	saveButton->setGeometry(0, HEIGHT_POPUP - 2 * HEIGHT_TEXT, WIDTH_POPUP / 2, HEIGHT_TEXT);
	cancelButton->setGeometry(WIDTH_POPUP / 2, HEIGHT_POPUP - 2 * HEIGHT_TEXT, WIDTH_POPUP / 2, HEIGHT_TEXT);
}

void QEventEditor::setupComboBox(){
	fieldSelector->addItem(QString(Editor::FIELD_NAME.c_str()));
	fieldSelector->addItem(QString(Editor::FIELD_START_DATE.c_str()));
    fieldSelector->addItem(QString(Editor::FIELD_START_TIME.c_str()));
    fieldSelector->addItem(QString(Editor::FIELD_END_DATE.c_str()));
	fieldSelector->addItem(QString(Editor::FIELD_END_TIME.c_str()));
	fieldSelector->addItem(QString(Editor::FIELD_LOCATION.c_str()));
	QObject::connect(fieldSelector, SIGNAL(currentIndexChanged(QString)), this, SLOT(setField(QString)));
}

void QEventEditor::setupButtons(){
	QObject::connect(saveButton, SIGNAL(pressed()), this, SLOT(saveInfo()));
	QObject::connect(saveButton, SIGNAL(pressed()), this, SLOT(accept()));
	QObject::connect(cancelButton, SIGNAL(pressed()), this, SLOT(reject()));
}

void QEventEditor::setField(QString text){
	if(text == QString(Editor::FIELD_NAME.c_str())){
		valueLine->setText(QString(event->getName().c_str()));
	}else if(text == QString(Editor::FIELD_START_DATE.c_str())){
		valueLine->setText(QString(event->getStartDate().c_str()));
	}else if(text == QString(Editor::FIELD_END_DATE.c_str())){
		valueLine->setText(QString(event->getEndDate().c_str()));
	}else if(text == QString(Editor::FIELD_START_TIME.c_str())){
		valueLine->setText(QString(event->getStartTime().c_str()));
	}else if(text == QString(Editor::FIELD_END_TIME.c_str())){
		valueLine->setText(QString(event->getEndTime().c_str()));
	}else if(text == QString(Editor::FIELD_LOCATION.c_str())){
		valueLine->setText(QString(event->getLocation().c_str()));
	}
}

/*
* Converts the edited item in the editor to a string which contains the standard
* Command for handling edits, and pushes the command to the commandLine
* The signal is caught in BoxIn.cpp and the command is processed as per normal
*/
void QEventEditor::saveInfo(){
    std::stringstream stream;
    stream << event->getIdx();
    std::string idx;
    stream >> idx;
    std::string input = "edit " + idx + " field " + fieldToEditor[fieldSelector->currentText().toStdString()] + " " + valueLine->text().toStdString();
	emit infoOut(input);
	close();
}

void QEventEditor::changeEvent(QEvent *event){
	if(event->type() == QEvent::Close){emit destroyed();}
	event->accept();
}

void QEventEditor::setupMap(){
    fieldToEditor[Editor::FIELD_NAME] = "name";
    fieldToEditor[Editor::FIELD_START_DATE] = "sdate";
    fieldToEditor[Editor::FIELD_END_DATE] = "edate";
    fieldToEditor[Editor::FIELD_START_TIME] = "stime";
    fieldToEditor[Editor::FIELD_END_TIME] = "etime";
    fieldToEditor[Editor::FIELD_LOCATION] = "place";
}