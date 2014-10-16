
#ifndef __BoxIn_EventLIST_H__
#define __BoxIn_EventLIST_H__

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
		
		static const bool Event_DEFAULT_DONE;
		static const std::string Event_DEFAULT_CATEGORY;
		static const int Event_DEFAULT_PRIORITY;
		struct EventComparator;
		
		std::list<std::shared_ptr<Event>>::iterator begin();
		std::list<std::shared_ptr<Event>>::iterator end();
		std::list<std::shared_ptr<Event>>::iterator EventListIterator;

		std::string getName() const;
		size_t getSize();
		std::shared_ptr<EventList> getEvents();
		std::shared_ptr<Event> getEvent(int EventIndex);
		std::shared_ptr<Event> addEvent(std::string EventName);
		bool addEvent(std::shared_ptr<Event> Event);
		bool contains(std::shared_ptr<Event> Event);
		std::shared_ptr<EventList> deleteEvent(int EventIndex);
		bool deleteEvent(std::shared_ptr<Event> Event);
		bool deleteAll();
		bool hideEvent(std::shared_ptr<Event> Event);
		bool showEvent(std::shared_ptr<Event> Event);
		void resetDisplay();
		std::string serialize();
		void unserialize(std::string bundle);
		
		static bool findString(std::string content, std::string searchTerm,bool caseSensitive);
		static std::string toLower(std::string input);

		int getDefaultPriority();
		std::string getDefaultCategory();

		//Testing purposes only
		std::shared_ptr<std::list<std::string>> getAllEvents();

	private:

		static const std::string EventLIST_DEFAULT_NAME; 

		static const std::string EventLIST_SEPARATOR;

		std::list<std::shared_ptr<Event>> _Events;
		std::string _name;
		std::map<std::shared_ptr<Event>,bool> _displayFlags;
		std::stack<std::shared_ptr<Event>> _deleteStack;
		typedef std::pair<std::shared_ptr<Event>,bool> _EventFlag;

		std::string retrieveEventData(std::shared_ptr<Event> Event);
		void clearDeleteStack();
		void processDeleteStack();
		
	};

	
}

#endif /* __BoxIn_EventLIST_H__ */
