#ifndef UNITTEST_H
#define UNITTEST_H

#include "qobject.h"
#include "unittest_global.h"
#include <SDKDDKVer.h>
#include "CppUnitTest.h"
#include "qapplication.h"

#include "json_spirit.h"
#include "BoxIn.h"
#include "QEventEditor.h"
#include "QEventStore.h"
#include "digitalclock.h"
#include "DisplayFeed.h"
#include "Logic.h"
#include "Action.h"
#include "Add.h"
#include "Delete.h"
#include "Edit.h"
#include "Mark.h"
#include "Search.h"
#include "QHelpWindow.h"
#include "Event.h"
#include "SimpleParser.h"
#include "SimpleStorage.h"
#include "TimeParser.h"
#include "FileStorage.h"

#include "BoxIn.cpp"
#include "QEventEditor.cpp"
#include "QEventStore.cpp"
#include "digitalclock.cpp"
#include "DisplayFeed.cpp"
#include "Logic.cpp"
#include "Action.cpp"
#include "Add.cpp"
#include "Delete.cpp"
#include "Edit.cpp"
#include "Mark.cpp"
#include "Search.cpp"
#include "QHelpWindow.cpp"
#include "Event.cpp"
#include "SimpleParser.cpp"
#include "SimpleStorage.cpp"
#include "TimeParser.cpp"
#include "FileStorage.cpp"

#include "moc_BoxIn.cpp"
#include "moc_digitalclock.cpp"
#include "moc_DisplayFeed.cpp"
#include "moc_QEventEditor.cpp"
#include "moc_QEventStore.cpp"
#include "moc_QHelpWindow.cpp"

class UNITTEST_EXPORT UnitTest{
public:
    UnitTest();
    ~UnitTest();

private:

};

#endif // UNITTEST_H
