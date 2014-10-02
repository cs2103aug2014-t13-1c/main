#include "Eventlist.h"

using namespace std;

namespace BoxIn {

        // The class constructor. : Sets up the eventlist.
        EventList::EventList() :
                _name("default"), _sortOrder(SortCriteria::TIME_END) {

        }

 
         //Returns the name of this event list

        string eventList::getName() const {
                return _name;
        }

         // Returns a list of shared pointers to events contained within this event list.

        list<Event>& EventList::getEvents() {
                return _events;
        }


        // Returns true if event is added successfully, false otherwise.

        bool EventList::addEvent(string name) {
             Event event;
             _events.push_back(event);
             sort(_sortOrder);
             return true;

        }
        
        
 
        // Returns true if event is deleted, false otherwise.

        bool EventList::deleteEvent(Event event) {
                if(contains(event)) {
                        //_event.remove(event);
                }
                if(contains(event)) {
                return false; //This should not happen
                } else {
                return true;
                }
        }

        
        /**
         * update the event given the parameter
         */
        /*bool EventList::updateEvent(Event event) {  
        
        }*/
        

         // Marks a even as done or undone
         // Parameter: True is done, False is not done

        bool EventList::markEvent(Event event, bool done) {
                if(event.setDone(done) == done) {
                         return true;
                } else {
                        return false;
                }
        }
        

         //Sorts the eventlist by the criteria given

        bool EventList::sort(SortCriteria criteria) {
                bool result;
                switch(criteria) {
                case SortCriteria::CATEGORY: {
                                _events.sort(compareEventsCategory);
                                break;
                        }
                case SortCriteria::TIME_ADDED: {
                                _events.sort(compareEventsTimeAdded);
                                break;
                        }
                case SortCriteria::TIME_END: default: {
                                _events.sort(compareEventsTimeEnd);
                                break;
                        }
                case SortCriteria::TIME_START: {
                                _events.sort(compareEventsTimeStart);
                                break;
                        }
                case SortCriteria::NAME: {
                                _events.sort(compareEventsName);
                                break;
                        }
                case SortCriteria::PRIORITY: {
                                _events.sort(compareEventsPriority);
                                break;
                        }
                }
                return true;
        }

        // Returns a list of shared pointers to events that fit the search criteria

        list<Event>& EventList::search(string criteria) {
                tempEvents.clear();
                for(eventIterator = _events.begin(); eventIterator != _events.end(); eventIterator++) {
                        if(eventIterator->contains(criteria)) {
                                tempEvents.push_back(*eventIterator);
                        }
                }
                return tempEvents;
        }
        
 
        // Check if event already exists inside the list

        bool EventList::contains(Event event) {
                return false;
        }

         // compares two events with the criteria given and returns true if the first is smaller, false otherwise 

        bool EventList::compareEventsTimeStart(Event event_a,Event event_b)
        {
                return true;
        }


        //compares two events with the criteria given and returns true if the first is smaller, false otherwise 

        bool EventList::compareEventsTimeEnd(Event event_a,Event event_b)
        {
                return true;
        }


         //compares two events with the criteria given and returns true if the first is smaller, 

        bool EventList::compareEventsTimeAdded(Event event_a,Event event_b)
        {
                return true;
        }


         // compares two events with the criteria given and returns true if the first is smaller, 

        bool EventList::compareEventsCategory(Event event_a,Event event_b)
        {
                return true;
                
        }

      
       //compares two events with the criteria given and returns true if the first is smaller, 

        bool EventList::compareEventsPriority(Event event_a,Event event_b)
        {
                if(event_a.getPriority() < event_b.getPriority()) {
                                        return true;
                                } else {
                                        return false;
                                }
        }


         //compares two events with the criteria given and returns true if the first is smaller, 

        bool EventList::compareEventsName(Event event_a,Event event_b)
        {
                        if((event_a.getName().compare(event_b.getName()) < 0)) {
                                return true;
                        } else {
                                return false;
                        }
        }

}