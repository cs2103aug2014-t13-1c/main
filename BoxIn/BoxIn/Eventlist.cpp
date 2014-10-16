
#include "boost/foreach.hpp"
#include "EventList.h"

using namespace std;

namespace BoxIn {


	const string EventList::event_DEFAULT_CATEGORY = "Uncategorized";
	const int EventList::event_DEFAULT_PRIORITY = 0;
	const bool EventList::event_DEFAULT_DONE = false;

	const string EventList::EventList_DEFAULT_NAME = "default";
	const EventList::sortType EventList::EventList_DEFAULT_SORTORDER = EventList::sortType(EventList::TIME_END,true);

	const string EventList::EventList_SEPARATOR = "|";

	// Sets up the EventList. 

	EventList::EventList() :
		_name(EventList_DEFAULT_NAME) {
			_sortOrder.clear();
			_sortOrder.push_back(EventList_DEFAULT_SORTORDER);
	}

	

	list<shared_ptr<event>>::iterator EventList::begin()
	{
		return _events.begin(); 
			
	}
	
	
	list<shared_ptr<event>>::iterator EventList::end()
	{
		return _events.end(); 
			
	}


	// Returns the name of this event list

	string EventList::getName() const {
		return _name;
	}

	// Returns the size of this event list
	 
	size_t EventList::getSize() {
		return _events.size();
	}

	// Returns all events that are set to be displayed.,Displayable events are events where the flag is set to true;
	 
	shared_ptr<EventList> EventList::getevents() {
		shared_ptr<EventList> tempList = make_shared<EventList>();
		for(EventListIterator = _events.begin(); EventListIterator != _events.end(); EventListIterator++) {
			if(_displayFlags.at(*EventListIterator)) {
				tempList->addevent(*EventListIterator);
			}
		}
		return tempList;
	}
	
	// Get event that matches the index given from the list of events return on the previous iteration, If event is not found, a null pointer is returned
	
	shared_ptr<event> EventList::getevent(int index) {
		int count = 0;
		for(EventListIterator = _events.begin(); EventListIterator != _events.end(); EventListIterator++) {
			if(_displayFlags.at(*EventListIterator)) {
				count++;
			}
			if(count == index) {
				return *EventListIterator;
			}
		 }
		return nullptr;
	}
	
	//* Returns a pointer to the event created with the input parameters

	shared_ptr<event> EventList::addevent(string name) {
			shared_ptr<event> event = make_shared<event> ();
			event->setName(name); //Creates event
			event->setDone(event_DEFAULT_DONE);
			event->setPriority(event_DEFAULT_PRIORITY);
			event->setCategory(event_DEFAULT_CATEGORY);
			_displayFlags.insert(_eventFlag(event,true)); //Insert event into eventflag map
			_events.push_back(event); //Inserts event into EventList
			sort(_sortOrder);
			return event;
	}
	
	// Adds the event referenced by the pointer to the EventList.  If the event exists, false is returned, otherwise, true is returned.
	
	bool EventList::addevent(shared_ptr<event> event) {
			if(contains(event)) {
				return false;
			} else {
				_events.push_back(event);
				_displayFlags.insert(_eventFlag(event,true)); 
				//Redundancy check in case flag already exists. Shouldn't happen
				showevent(event); 
				sort(_sortOrder);
			}
			return true;
	}

	//* Method: contains,Checks whether a event exists inside the EventList
	
	bool EventList::contains(shared_ptr<event> event) {
		BOOST_FOREACH (shared_ptr<event>& event_in_list, _events) {
			if (event == event_in_list) {
				return true;
			}
		}
		
		return false;
	}
	
	// Returns true if event is deleted, false if event does not exist.

	bool EventList::deleteevent(shared_ptr<event> event) {
		if(contains(event)) {
			_events.remove(event);
			return true;
		} else {
			return false;
		}
	}
	
	// Deletes the n-th event whose display flag is set to true, where n is the index.

	shared_ptr<EventList> EventList::deleteevent(int index) {
		shared_ptr<event> tempevent = getevent(index);
		if(tempevent != nullptr) {
			deleteevent(tempevent);
		}
		return getevents();
	}
	
	//Deletes all events returned on the previous display/search call

	bool EventList::deleteAll() {
		clearDeleteStack();
		for(EventListIterator = _events.begin(); EventListIterator != _events.end(); EventListIterator++) {
				if(_displayFlags.at(*EventListIterator)) {
					_deleteStack.push(*EventListIterator);
				}
		}
		processDeleteStack();
		return true;
	}
	
	// Sorts the EventList by the criteria given.  Criteria: event detail, followed by true for ascending, false for descending.

	EventList* EventList::sort(vector<pair<EventList::eventDetail,bool>> sortCriteriaList) {
		_sortOrder = sortCriteriaList;
		_events.sort(eventComparator(&_sortOrder));
		return this;
	}
	
	//Sorts the EventList by default. If the event criteria is set previously, the EventList will be sorted by that.

	EventList* EventList::sort() {
		_events.sort(eventComparator(&_sortOrder));
		return this;
	}
	
	
	// Method resetDisplay
	
	void EventList::resetDisplay()
	{
		for(EventListIterator = _events.begin(); EventListIterator != _events.end(); EventListIterator++)
		{
			_displayFlags.erase(*EventListIterator);
			_displayFlags.insert(_eventFlag(*EventListIterator,true));
		}
	}
	
	//Sets event's display to false; event will not be displayed, If event is already hidden, method will return false

	bool EventList::hideevent(shared_ptr<event> event)
	{
		if(_displayFlags.at(event)) {
			_displayFlags.erase(event);
			_displayFlags.insert(_eventFlag(event,false));
			return true;
		} else {
			return false;
		}
	}

	
	// Sets event's display to true; event will be displayed , If event is already shown, method will return false

	bool EventList::showevent(shared_ptr<event> event)
	{
		if(!_displayFlags.at(event)) {
			_displayFlags.erase(event);
			_displayFlags.insert(_eventFlag(event,true));
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
		for (size_t i = 0; i < temp.length(); i++) {
		temp[i] = tolower(temp[i]);
	}
	return temp;
	}
	

	/**
	* Method getAllevents
	* Returns a list of serialized events
	* NOTE: This method is for testing purposes only
	*/
	shared_ptr<list<string>> EventList::getAllevents()
	{
		shared_ptr<list<string>> tempevents = make_shared<list<string>>();
		for(EventListIterator = _events.begin(); EventListIterator != _events.end(); EventListIterator++)
		{
			tempevents->push_back((*EventListIterator)->serialize());
		}
		return tempevents;
	}

	
	// returns all data inside the event as a string

	string EventList::retrieveeventData(shared_ptr<event> event) {
		stringstream out_ss (stringstream::in | stringstream::out);
		out_ss << event->getName() << EventList_SEPARATOR;
		out_ss << event->getDescription() << EventList_SEPARATOR;
		out_ss << event->getCategory() << EventList_SEPARATOR;
		out_ss << event->toString(event->getPriority()) << EventList_SEPARATOR;
		out_ss << boost::posix_time::to_simple_string(event->getStartTime()) << EventList_SEPARATOR;
		out_ss << boost::posix_time::to_simple_string(event->getEndTime()) << EventList_SEPARATOR;

		return out_ss.str();
	}

	/**
	* Method: clearDeleteStack
	* Removes all elements from the delete stack;
	*/
	void EventList::clearDeleteStack()
	{
		while(!_deleteStack.empty())
		{
			_deleteStack.pop();
		}
	}

	/**
	* Method: processDeleteStack
	* Deletes each element and removes it from the delete stack
	*/
	void EventList::processDeleteStack()
	{
		shared_ptr<event> tempevent;
		while(!_deleteStack.empty())
		{
			tempevent = _deleteStack.top();
			deleteevent(tempevent);
			_deleteStack.pop();
		}
	}

	/**
	 * Method: serialize
	 * Inherited from: BoxInObject
	 */
	string EventList::serialize() {
		stringstream out_ss (stringstream::in | stringstream::out);
		BOOST_FOREACH (const shared_ptr<event>& event, _events) {
			out_ss << event->serialize() << endl;
		}

		return out_ss.str();
	}

	/**
	 * Method: unserialize
	 * Inherited from: BoxInObject
	 */
	void EventList::unserialize(string bundle) {
		// Tokenize the bundle
		stringstream bundle_ss (bundle);
		string buffer;
		
		while (!bundle_ss.eof()) {
			buffer.clear();
			getline(bundle_ss, buffer);

			// Ignore empty lines
			if (buffer.size() > 0) {
				shared_ptr<event> event = make_shared<event>();
				event->unserialize(buffer);
				addevent(event);
			}
		}
	}

}