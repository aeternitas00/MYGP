#include "stdafx.h"
#include "ListClass.h"
#include "Factory.h"

//template<class T>
//void ListChild<T>::add(GameObject* temp, char * n)
//{
//	temp->Initialize(n); list.push_back(dynamic_cast<T>(temp));
//}
//
//template<class T>
//void ListChild<T>::clear()
//{
//	for (auto it = list.begin(); it != list.end();)
//	{
//		delete *it++;
//	}
//	list.clear();
//}
//
//template<class T>
//void ListChild<T>::update() {
//	for (auto it = list.begin(); it != list.end();)
//	{
//		updateobj(*it);
//		it++;
//	}
//}
//
//template<class T>
//std::list<T> ListChild<T>::getter() { return list; }
//
//template<class T>
//RESULT ListChild<T>::updateobj(GameObject *obj)
//{
//	return obj->Update();
//}