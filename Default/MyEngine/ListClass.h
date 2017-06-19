#pragma once
#include "stdafx.h"

class GameObject;

class ListBase {};

template <class T>
class ListChild :public ListBase {
private:
	std::list<T> list;
public:
	void add(GameObject* temp, char* n) {
		temp->Initialize(n); list.push_back(dynamic_cast<T>(temp));
	}
	void clear() {
		for (auto it = list.begin(); it != list.end();)
		{
			delete *it++;
		}
		list.clear();
	}
	void update() {
		for (auto it = list.begin(); it != list.end();)
		{
			switch (updateobj(*it))
			{
			case Default:
				it++;
				break;
			case Destroy:
				delete *it;
				list.erase(it++);
				break;
			}
		}
	}
	std::list<T>* getter() {
		{ return &list; }
	}
private:
	RESULT updateobj(GameObject* obj) {
		return obj->Update();
	}
};

typedef std::map<std::string, ListBase*> ListAs;