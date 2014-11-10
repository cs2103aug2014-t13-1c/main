
//@author A0128233M
#ifndef BoxInEventLISTH
#define BoxInEventLISTH

#include <string>
#include <list>
#include <memory>
#include <vector>
#include <map>
#include "Parser.h"

namespace BoxIn {
	
	class EventList : public BoxInObject {
	
	public:
	

		EventList();
		
		static const bool EventDEFAULTDONE;
		static const std::string EventDEFAULTCATEGORY;
		static const int EventDEFAULTPRIORITY;
		struct EventComparator;
		
		std::list<std::sharedptr<Event>>::iterator begin();
		std::list<std::sharedptr<Event>>::iterator end();
		std::list<std::sharedptr<Event>>::iterator EventListIterator;

		std::string getName() const;
		sizet getSize();
		std::sharedptr<EventList> getEvents();
		std::sharedptr<Event> getEvent(int EventIndex);
		std::sharedptr<Event> addEvent(std::string EventName);
		bool addEvent(std::sharedptr<Event> Event);
		bool contains(std::sharedptr<Event> Event);
		std::sharedptr<EventList> deleteEvent(int EventIndex);
		bool deleteEvent(std::sharedptr<Event> Event);
		bool deleteAll();
		bool hideEvent(std::sharedptr<Event> Event);
		bool showEvent(std::sharedptr<Event> Event);
		void resetDisplay();
		std::string serialize();
		void unserialize(std::string bundle);
		
		static bool findString(std::string content, std::string searchTerm,bool caseSensitive);
		static std::string toLower(std::string input);

		int getDefaultPriority();
		std::string getDefaultCategory();

		//Testing purposes only
		std::sharedptr<std::list<std::string>> getAllEvents();

	private:

		static const std::string EventLISTDEFAULTNAME; 

		static const std::string EventLISTSEPARATOR;

		std::list<std::sharedptr<Event>> Events;
		std::string name;
		std::map<std::sharedptr<Event>,bool> displayFlags;
		std::stack<std::sharedptr<Event>> deleteStack;
		typedef std::pair<std::sharedptr<Event>,bool> EventFlag;

		std::string retrieveEventData(std::sharedptr<Event> Event);
		void clearDeleteStack();
		void processDeleteStack();
		
	};

	
}

#endif /* BoxInEventLISTH */
