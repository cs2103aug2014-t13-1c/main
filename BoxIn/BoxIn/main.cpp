#include <QApplication>
#include "BoxIn.h"
//@author A0111994B
void setIcon(QApplication &app);

int main(int argc, char *argv[]){
	QApplication app(argc, argv);
	BoxIn w;
	setIcon(app);
	w.show();
	return app.exec();
}

void setIcon(QApplication &app){
	QIcon icon("BoxIn.jpg");
	app.setWindowIcon(icon);
}