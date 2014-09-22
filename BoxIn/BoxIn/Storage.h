/**
BoxIn To-Do Task Manager
In this file, the Storage component is added on
**/

#ifndef BoxInStorage
#define BoxInStorage

#include <string>
#include <list>
#include <vector>

using namespace std;

namespace BoxIn {

	class Inputlist;
	class Storage{
	public:
		Storage();
		vector<InputList> getInputList;
		bool commit();

	protected:
		void setBoxes; //put the stuff in specific boxes/directories
		void setBoxFiles;
		string getBoxes;
		string getboxfiles;
		void clearFileStream();
		void setFileStream();
		void setUpInputList();

	private:
		string dataBoxesPath;
		string dataFilePath;
		vector<fstream> dataFileStream;
		vector<InputList> _inputList;
	}
}

#endif