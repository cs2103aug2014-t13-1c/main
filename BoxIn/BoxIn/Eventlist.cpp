
#include "boost/foreach.hpp"
#include "EventList.h"

using namespace std;

namespace BoxIn {


	const string EventList::eventDEFAULTCATEGORY = "Uncategorized";
	const int EventList::eventDEFAULTPRIORITY = 0;
	const bool EventList::eventDEFAULTDONE = false;

	const string EventList::EventListDEFAULTNAME = "default";
	const EventList::sortType EventList::EventListDEFAULTSORTORDER = EventList::sortType(EventList::TIMEEND,true);

	const string EventList::EventListSEPARATOR = "|";

	// Sets up the EventList. 

	EventList::EventList() :
		name(EventListDEFAULTNAME) {
			sortOrder.clear();
			sortOrder.pushback(EventListDEFAULTSORTORDER);
	}

	

	list<sharedptr<event>>::iterator EventList::begin()
	{
		return events.begin(); 
			
	}
	
	
	list<sharedptr<event>>::iterator EventList::end()
	{
		return events.end(); 
			
	}


	// Returns the name of this event list

	string EventList::getName() const {
		return name;
	}

	// Returns the size of this event list
	 
	sizet EventList::getSize() {
		return events.size();
	}

	// Returns all events that are set to be displayed.,Displayable events are events where the flag is set to true;
	 
	sharedptr<EventList> EventList::getevents() {
		sharedptr<EventList> tempList = makeshared<EventList>();
		for(EventListIterator = events.begin(); EventListIterator != events.end(); EventListIterator++) {
			if(displayFlags.at(*EventListIterator)) {
				tempList->addevent(*EventListIterator);
			}
		}
		return tempList;
	}
	
	// Get event that matches the index given from the list of events return on the previous iteration, If event is not found, a null pointer is returned
	
	sharedptr<event> EventList::getevent(int index) {
		int count = 0;
		for(EventListIterator = events.begin(); EventListIterator != events.end(); EventListIterator++) {
			if(displayFlags.at(*EventListIterator)) {
				count++;
			}
			if(count == index) {
				return *EventListIterator;
			}
		 }
		return nullptr;
	}
	
	//* Returns a pointer to the event created with the input parameters

	sharedptr<event> EventList::addevent(string name) {
			sharedptr<event> event = makeshared<event> ();
			event->setName(name); //Creates event
			event->setDone(eventDEFAULTDONE);
			event->setPriority(eventDEFAULTPRIORITY);
			event->setCategory(eventDEFAULTCATEGORY);
			displayFlags.insert(eventFlag(event,true)); //Insert event into eventflag map
			events.pushback(event); //Inserts event into EventList
			sort(sortOrder);
			return event;
	}
	
	// Adds the event referenced by the pointer to the EventList.  If the event exists, false is returned, otherwise, true is returned.
	
	bool EventList::addevent(sharedptr<event> event) {
			if(contains(event)) {
				return false;
			} else {
				events.pushback(event);
				displayFlags.insert(eventFlag(event,true)); 
				//Redundancy check in case flag already exists. Shouldn't happen
				showevent(event); 
				sort(sortOrder);
			}
			return true;
	}

	//* Method: contains,Checks whether a event exists inside the EventList
	
	bool EventList::contains(sharedptr<event> event) {
		BOOSTFOREACH (sharedptr<event>& eventinlist, events) {
			if (event == eventinlist) {
				return true;
			}
		}
		
		return false;
	}
	
	// Returns true if event is deleted, false if event does not exist.

	bool EventList::deleteevent(sharedptr<event> event) {
		if(contains(event)) {
			events.remove(event);
			return true;
		} else {
			return false;
		}
	}
	
	// Deletes the n-th event whose display flag is set to true, where n is the index.

	sharedptr<EventList> EventList::deleteevent(int index) {
		sharedptr<event> tempevent = getevent(index);
		if(tempevent != nullptr) {
			deleteevent(tempevent);
		}
		return getevents();
	}
	
	//Deletes all events returned on the previous display/search call

	bool EventList::deleteAll() {
		clearDeleteStack();
		for(EventListIterator = events.begin(); EventListIterator != events.end(); EventListIterator++) {
				if(displayFlags.at(*EventListIterator)) {
					deleteStack.push(*EventListIterator);
				}
		}
		processDeleteStack();
		return true;
	}
	
	// Sorts the EventList by the criteria given.  Criteria: event detail, followed by true for ascending, false for descending.

	EventList* EventList::sort(vector<pair<EventList::eventDetail,bool>> sortCriteriaList) {
		sortOrder = sortCriteriaList;
		events.sort(eventComparator(&sortOrder));
		return this;
	}
	
	//Sorts the EventList by default. If the event criteria is set previously, the EventList will be sorted by that.

	EventList* EventList::sort() {
		events.sort(eventComparator(&sortOrder));
		return this;
	}
	
	
	// Method resetDisplay
	
	void EventList::resetDisplay()
	{
		for(EventListIterator = events.begin(); EventListIterator != events.end(); EventListIterator++)
		{
			displayFlags.erase(*EventListIterator);
			displayFlags.insert(eventFlag(*EventListIterator,true));
		}
	}
	
	//Sets event's display to false; event will not be displayed, If event is already hidden, method will return false

	bool EventList::hideevent(sharedptr<event> event)
	{
		if(displayFlags.at(event)) {
			displayFlags.erase(event);
			displayFlags.insert(eventFlag(event,false));
			return true;
		} else {
			return false;
		}
	}

	
	// Sets event's display to true; event will be displayed , If event is already shown, method will return false

	bool EventList::showevent(sharedptr<event> event)
	{
		if(!displayFlags.at(event)) {
			displayFlags.erase(event);
			displayFlags.insert(eventFlag(event,true));
			return true;
		} else {
			return false;
		}
	}


	/**
	* Method findString
	* Compares the second string to the first, and returns true if the 
	* second is found inside the first. Set caseSenstive flag to true 
	* to compare with case considerations.
	*/
	bool EventList::findString(string content, string searchTerm, bool caseSensitive)
	{
		bool result;
		if(caseSensitive) {
			if(content.find(searchTerm) != string::npos) { //found
				result = true;
			} else {
				result = false;
			}
		} else {
			if(toLower(content).find(toLower(searchTerm)) != string::npos) {
				result = true;
			} else {
				result = false;
			}
		}
		return result;
	}

	string EventList::toLower(string value) {
		string temp = value;
		for (sizet i = 0; i < temp.length(); i++) {
		temp[i] = tolower(temp[i]);
	}
	return temp;
	}
	

	/**
	* Method getAllevents
	* Returns a list of serialized events
	* NOTE: This method is for testing purposes only
	*/
	sharedptr<list<string>> EventList::getAllevents()
	{
		sharedptr<list<string>> tempevents = makeshared<list<string>>();
		for(EventListIterator = events.begin(); EventListIterator != events.end(); EventListIterator++)
		{
			tempevents->pushback((*EventListIterator)->serialize());
		}
		return tempevents;
	}

	
	// returns all data inside the event as a string

	string EventList::retrieveeventData(sharedptr<event> event) {
		stringstream outss (stringstream::in | stringstream::out);
		outss << event->getName() << EventListSEPARATOR;
		outss << event->getDescription() << EventListSEPARATOR;
		outss << event->getCategory() << EventListSEPARATOR;
		outss << event->toString(event->getPriority()) << EventListSEPARATOR;
		outss << boost::posixtime::tosimplestring(event->getStartTime()) << EventListSEPARATOR;
		outss << boost::posixtime::tosimplestring(event->getEndTime()) << EventListSEPARATOR;

		return outss.str();
	}

	/**
	* Method: clearDeleteStack
	* Removes all elements from the delete stack;
	*/
	void EventList::clearDeleteStack()
	{
		while(!deleteStack.empty())
		{
			deleteStack.pop();
		}
	}

	/**
	* Method: processDeleteStack
	* Deletes each element and removes it from the delete stack
	*/
	void EventList::processDeleteStack()
	{
		sharedptr<event> tempevent;
		while(!deleteStack.empty())
		{
			tempevent = deleteStack.top();
			deleteevent(tempevent);
			deleteStack.pop();
		}
	}

	/**
	 * Method: serialize
	 * Inherited from: BoxInObject
	 */
	string EventList::serialize() {
		stringstream outss (stringstream::in | stringstream::out);
		BOOSTFOREACH (const sharedptr<event>& event, events) {
			outss << event->serialize() << endl;
		}

		return outss.str();
	}

	/**
	 * Method: unserialize
	 * Inherited from: BoxInObject
	 */
	void EventList::unserialize(string bundle) {
		// Tokenize the bundle
		stringstream bundless (bundle);
		string buffer;
		
		while (!bundless.eof()) {
			buffer.clear();
			getline(bundless, buffer);

			// Ignore empty lines
			if (buffer.size() > 0) {
				sharedptr<event> event = makeshared<event>();
				event->unserialize(buffer);
				addevent(event);
			}
		}
	}

}