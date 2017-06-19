#pragma once
#include "Factory.h"
#include "ListClass.h"
//
//myfactory::myfactory()
//{
//}

void myfactory::construct(std::string const &n, char* init)
{
	map_type::iterator i = m_classes.find(n);
	if (i == m_classes.end()) return;
	auto it = m_mylistas.find(n);
	if (it == m_mylistas.end()) it = m_mylistas.find("GameObject");
	i->second(it->second, init);
}
//
//ListBase * myfactory::get_list(std::string const & n)
//{
//	return m_mylistas.find(n)->second;
//}

//template<class T>
//void myfactory::register_class(std::string const & n)
//{
//	m_classes.insert(std::make_pair(n, &constructor<T>));
//	m_mylistas.insert(std::make_pair(n, new ListChild<T*>()));
//}

//template<class T>
//void myfactory::clear_list(std::string const & n)
//{
//	static_cast<ListChild<T*>*>(m_mylistas.find(n)->second)->clear();
//}

//template<class T>
//void myfactory::update_list(std::string const &n)
//{
//	static_cast<ListChild<T*>*>(m_mylistas.find(n)->second)->update();
//}
//


