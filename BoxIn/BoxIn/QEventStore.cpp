#include "QEventStore.h"

QEventStore::QEventStore(QWidget *parent, Event* event){
	this->event = event;
}


QEventStore::~QEventStore(void){
}

QString QEventStore::repr(){
	QString rep = QString(event->getName().c_str());
	if(event->getLocation() != ""){rep = rep + " at " + QString(event->getLocation().c_str());}
	if(event->getDate() != ""){rep = rep + " on " + QString(event->getDate().c_str());}
	if(event->getTime() != ""){rep = rep + " at " + QString(event->getTime().c_str()) + "hrs";}
	return rep;
}