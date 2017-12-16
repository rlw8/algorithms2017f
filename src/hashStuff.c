#include <simple_logger.h>
#include <string.h>
#include "hashStuff.h"




DataSet* dataInit(size_t size, int num)
{
	DataSet* stuffs;
	stuffs = malloc((size + sizeof(DataSet))*num);
	memset(stuffs, 0, (size + sizeof(DataSet))*num);

	stuffs->num = num;

	return stuffs;
}

long dataHash(char* key, int num)
{
	int hash = 0, i = 0;

	while (key[i] != '\0')
	{
		hash += (int)key[i];
		i++;
	}

	hash %= num;

	return hash;
}

void dataStore(char* key, void* data, DataSet** hashmap)
{
	int index;

	if (!key)return;
	if (!data)return;
	if (!hashmap)return;

	index = dataHash(key, (*hashmap)->num);

	if (strcmp((*hashmap)[index].key, "") == 0)
	{
		strcpy((*hashmap)[index].key, key, 512);
		(*hashmap)[index].data = data;
	}
	else 
	{
		slog("Collision detected");
		index++;
		if (index >= (*hashmap)->num)
		{
			*hashmap = dataRehash((*hashmap));
		}
		while (!(strcmp((*hashmap)[index].key, "")))
		{
			index++;

		}
		strncpy((*hashmap)[index].key, key, 512);
		(*hashmap)[index].data = data;
	}
	
}

void dataSearch(char* key, DataSet* bleh)
{
	long index, k = 0;
	index = dataHash(key, bleh->num);
	
	if (!(strcmp(key, bleh[index].key)))
	{
		slog("%s, %i", key, bleh[index].data);
		return;
	}

	while (1)
	{
		if (!(strcmp(key, bleh[index].key)))
		{
			slog("%s, %i", key, bleh[index].data);
			return;
		}

		k++;
		if (k >= bleh->num)
		{
			slog("Cannot find key: %s in current list", key);
			//slog("%s, %s", key, bleh[index].key);
			return;
		}
	}
}

void dataDelete(char* key, DataSet* bleh)
{
	long index, k = 0;
	index = dataHash(key, bleh->num);

	if (!(strcmp(key, bleh[index].key)))
	{
		strncpy(bleh[index].key, "", 512);
		bleh[index].data = 0;
		return;
	}

	while (1)
	{
		if (!(strcmp(key, bleh[index].key)))
		{
			strncpy(bleh[index].key, "", 512);
			bleh[index].data = 0;
			return;
		}

		k++;
		if (k >= bleh->num)
		{
			slog("Cannot find key: %s in current list", key);
			//slog("%s, %s", key, bleh[index].key);
			return;
		}
	}
}

DataSet* dataRehash(DataSet* bleh)
{
	int i = 0;

	DataSet* bigstuffs;
	bigstuffs = dataInit(bleh->dataSize, bleh->num * 2);

	for (i; i < bleh->num; i++)
	{
		dataStore(bleh[i].key, bleh[i].data, bigstuffs);
	}

	dataKill(bleh);

	return bigstuffs;
}

void dataKill(DataSet* bleh)
{
	memset(bleh, 0, (bleh->dataSize + sizeof(DataSet))* bleh->num);
}

