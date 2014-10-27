//@author A0111994B
#include "QEventStore.h"

QEventStore::QEventStore(QWidget *parent, Event* event){
	assert(event!=NULL);
	this->event = event;
}

QEventStore::~QEventStore(void){
}

Event* QEventStore::getEvent(){
	return event;
}