#pragma once
#include <stdlib.h>

typedef struct DataSet_S
{

	char key[512];
	void* data;
	size_t dataSize;
	int num;

}DataSet;

//Start up the data set
DataSet* dataInit(size_t size, int num);

//Hash a key and store at the created index, takes key and data
void dataStore(char* key, void* data, DataSet** bleh);

//Search for a data set using the key
void dataSearch(char* key, DataSet* bleh);

//Delete selected data set using the key
void dataDelete(char* key, DataSet* bleh);

//Rehash the data set to add more room
DataSet* dataRehash(DataSet* bleh);

//Destroy the entire data set and free the space
void dataKill(DataSet* bleh);