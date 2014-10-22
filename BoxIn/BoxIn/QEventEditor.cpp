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
	show();
}

QEventEditor::~QEventEditor(void){
}

void QEventEditor::createObjects(){
	fieldLabel = new QLabel("     Field:", this);
	fieldSelector = new QComboBox(this);
	valueLine = new QLineEdit(QString(event->getName().c_str()), this);
	saveButton = new QPushButton("Save", this);
	cancelButton = new QPushButton("Cancel", this);
}

void QEventEditor::arrangeObjects(){
	setFixedSize(WIDTH_POPUP, HEIGHT_POPUP);
	fieldLabel->setGeometry(0, HEIGHT_TEXT, WIDTH_POPUP / 8, HEIGHT_TEXT);
	fieldSelector->setGeometry(WIDTH_POPUP / 8, HEIGHT_TEXT, 50, HEIGHT_TEXT);
	valueLine->setGeometry(WIDTH_POPUP / 4, HEIGHT_TEXT, WIDTH_POPUP * 3 / 4, HEIGHT_TEXT);
	saveButton->setGeometry(0, HEIGHT_POPUP - 2 * HEIGHT_TEXT, WIDTH_POPUP / 2, HEIGHT_TEXT);
	cancelButton->setGeometry(WIDTH_POPUP / 2, HEIGHT_POPUP - 2 * HEIGHT_TEXT, WIDTH_POPUP / 2, HEIGHT_TEXT);
}

void QEventEditor::setupComboBox(){
	fieldSelector->addItem(QString(FIELD_NAME.c_str()));
	fieldSelector->addItem(QString(FIELD_DATE.c_str()));
	fieldSelector->addItem(QString(FIELD_TIME.c_str()));
	fieldSelector->addItem(QString(FIELD_LOCATION.c_str()));
	QObject::connect(fieldSelector, SIGNAL(currentIndexChanged(QString)), this, SLOT(setField(QString)));
}

void QEventEditor::setupButtons(){
	QObject::connect(saveButton, SIGNAL(pressed()), this, SLOT(saveInfo()));
	QObject::connect(saveButton, SIGNAL(pressed()), this, SLOT(accept()));
	QObject::connect(cancelButton, SIGNAL(pressed()), this, SLOT(reject()));
}

void QEventEditor::setField(QString text){
	if(text == QString(FIELD_NAME.c_str())){
		valueLine->setText(QString(event->getName().c_str()));
	}else if(text == QString(FIELD_DATE.c_str())){
		valueLine->setText(QString(event->getDate().c_str()));
	}else if(text == QString(FIELD_TIME.c_str())){
		valueLine->setText(QString(event->getTime().c_str()));
	}else if(text == QString(FIELD_LOCATION.c_str())){
		valueLine->setText(QString(event->getLocation().c_str()));
	}
}

void QEventEditor::saveInfo(){
	std::string input = "edit " + event->getName() + " date " + event->getDate() + " field " + fieldSelector->currentText().toStdString() + " " + valueLine->text().toStdString();
	emit infoOut(input);
	close();
}

void QEventEditor::changeEvent(QEvent *event){
	if(event->type() == QEvent::Close){emit destroyed();}
	event->accept();
}