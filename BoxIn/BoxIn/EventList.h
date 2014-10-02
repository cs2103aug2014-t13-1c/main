#include <string>
#include <list>
#include <memory>
#include "event.h"


namespace BoxIn {

        
        class EventList : public BoxInObject{
        
        public:
                enum SortCriteria{
                        TIME_START,TIME_END,PRIORITY,NAME,TIME_ADDED,CATEGORY
                };

                EventList();
                std::string getName() const;
                std::list<Event>& getEvents();
                bool addEvent(std::string);
                //bool updateEvent(Event); --> need future implementation
                bool deleteEvent(Event);
                bool markEvent(Event,bool);
                bool sort(SortCriteria);
                std::list<Event>& search(std::string);


        

        private:

                static bool compareEventsTimeEnd(Event,Event);
                static bool compareEventsTimeStart(Event,Event);
                static bool compareEventsTimeAdded(Event,Event);
                static bool compareEventsCategory(Event,Event);
                static bool compareEventsPriority(Event,Event);
                static bool compareEventsName(Event,Event);
                bool contains(Event);
                std::list<Event> tempEvents;
                SortCriteria _sortOrder;
                std::string _name;
                std::list<Event> _events;
                std::list<Event>::iterator eventIterator;
        };

        
}
