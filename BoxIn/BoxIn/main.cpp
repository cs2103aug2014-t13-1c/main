#include <QApplication>
#include "BoxIn.h"

int main(int argc, char *argv[]){
	QApplication a(argc, argv);
	BoxIn w;
	w.show();
	return a.exec();
}
