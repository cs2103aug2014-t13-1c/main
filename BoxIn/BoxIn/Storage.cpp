
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "storage.h"

using namespace std;

namespace BoxIn {
	
	/**
	 * Class constructor.
	 * Initializes the storage layer.
	 */
	Storage::Storage() {
		// Find important paths.
		dataBoxesPath = setBoxes();
		dataFilePath = boxFiles();

		// Set up a stream.
		setUpFileStream();
	}


	/**
	 Returns the path to the directory where BoxIn stores its data.
	 */
	string Storage::getBoxes() {
		return getAppDataPath().append("/BoxIn");
	}

	/**
	 * Returns the path to the file where BoxIn stores its data.
	 */
	string Storage::getBoxFiles() {
		return getBoxes().append("/BoxIn.txt");
	}

	/**
	 * Sets up the file stream for the data store.
	 */
	void Storage::setUpFileStream() {


		// Create the file.
		dataFileStream = make_shared<fstream> (dataFilePath, fstream::in | fstream::out);
		if (dataFileStream->fail()) {
			// Try to see if we failed because the file didn't exist.
			dataFileStream.reset();
			dataFileStream = make_shared <fstream> (dataFilePath, fstream::out);
			dataFileStream.reset();
			dataFileStream = make_shared <fstream> (dataFilePath, fstream::in | fstream::out);
		}

		// Check state after a possible re-try.
		if (dataFileStream->fail()) {
			throw runtime_error("[Storage] Unable to create the data file. ");
		}
	}

}
