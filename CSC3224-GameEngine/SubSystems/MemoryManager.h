#pragma once

#include <vector>

/*Memory Manager class used to store the game assets in memory.. */

template<class T>
class MemoryManager {

public:

	//Instantiate Memory manager of given size
	MemoryManager(int s) {
		MaxSize = s;
		Init(s);
	}

	~MemoryManager() {
		delete[] items_data;
	}

	//Return a pointer to the array of a free object, null if the memory manager size has been filled up.. Needs further work on this class
	T* create() {
		if (managerSize >= MaxSize) {
			return nullptr;
		}
		else {
			return &items_data[managerSize++];
		}
	}
	
	//Free space in the array.. not sure about this one either but I tried
	void free() {
		for (int i = 0; i < managerSize; i++) {
			items_data[i] = nullptr;
		}
	}

	void remove(int iToRem) {
		items_data[iToRem] = nullptr;
	}
	
	T* get(int iToGet) {
		if (iToGet < 0 || iToGet > managerSize) {
			return nullptr;
		}
		else {
			return &items_data[iToGet];
		}
	}

	int getSize() {
		return managerSize;
	}

private:

	//Initialise memory manager array given size wished for
	void Init(int SSize) {
		items_data = new T[SSize];
		managerSize = 0;
	}

	int managerSize;
	int MaxSize;
	
	T* items_data;

};