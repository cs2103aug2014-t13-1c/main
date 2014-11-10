//@author A0111994B
#include "QHelpWindow.h"

QHelpWindow::QHelpWindow(QWidget *parent) : QWidget(parent){
    ui.setupUi(this);
    setFixedSize(400, 200);
    selector = new QComboBox(this);
    setupSelector();
    display = new QTextEdit(this);
    display->setReadOnly(true);
    display->setGeometry(50, 40, 300, 150);
    changed(HelpOptions::GENERAL);
}

QHelpWindow::~QHelpWindow(){
}

//add the options for each components so people can get the help window
void QHelpWindow::setupSelector(){
    selector->addItem(HelpOptions::GENERAL);
    selector->addItem(HelpOptions::ADD);
    selector->addItem(HelpOptions::DELETE);
    selector->addItem(HelpOptions::EDIT);
    selector->addItem(HelpOptions::MARK);
    selector->addItem(HelpOptions::VIEW);
    selector->addItem(HelpOptions::UNDO);
    selector->setGeometry(150, 10, 100, 20);
    QObject::connect(selector, SIGNAL(currentIndexChanged(QString)), this, SLOT(changed(QString)));
}

//this is the text displayed after clicking on the selectors above
void QHelpWindow::changed(QString option){
    if(option == HelpOptions::GENERAL){
        display->setText("BoxIn commands have the first word as the type of action desired.\n\nDifferent options are prefixed by the tags place, sdate (start date), stime (start time), edate (end date) and etime (endtime)\n\nDates are represented in the format DDMMYY or YYYY-Mon-DD where Mon is the 3-letter representation of the month\nAlternatively, it is possible to use special days such as today or tomorrow\nUsing a day of week (for example, tuesday) will return the nearest (tuesday) to today, today inclusive.\n\nTimes are stored in a 24-hour format HHMM or HH:MM\n\nIn the case where a word the user intends to type is a keyword, it can be escaped by prefixing the word with a . - for example, .place");
    }else if(option == HelpOptions::ADD){
        display->setText("The add command follows the following syntax:\n\nadd <name> <optional fields>\n\nA full example is given below\nadd Change the world edate 311299 place Mars\n\nThis represents a plan to change the world before 31st December 2099 on Mars");
    }else if(option == HelpOptions::DELETE){
        display->setText("The delete command follows the following syntax:\n\ndelete <indexnumber>\nFor example:\ndelete 1\n\nThis deletes the item which matches the index 1. The index is found to the left of the event name.");
    }else if(option == HelpOptions::EDIT){
        display->setText("The easiest way to edit an event is to double click it and use the GUI interface\nAlternatively, the format for doing so is \nedit <indexnumber> field <fieldtag> <newvalue>\n\nA full example is given below\nedit 1 field name Change the Universe");
    }else if(option == HelpOptions::MARK){
        display->setText("The mark command changes the done/undone status of an event. The syntax for doing so is \nmark <indexnumber>\n\nFor example,\nmark 1\nwill mark the Change the Universe event as done");
    }else if(option == HelpOptions::VIEW){
        display->setText("The view command shows only specific events. By default, all events are displayed. The different options to view are\n\nall, past, upcoming, done and pending\n\nThe format for doing so is \nview <option>\nFor example,\nview done");
    }else if(option == HelpOptions::UNDO){
        display->setText("The undo function allows a user to undo as many actions as they want up to the point the app was started. The syntax for doing so is simply to type \nundo");
    }
}
