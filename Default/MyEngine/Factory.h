#pragma once

#include "stdafx.h"
#include "ListClass.h"

class GameObject;

class myfactory
{
private:
	typedef void(*constructor_t)(ListBase*, char*);
	typedef std::map<std::string, constructor_t> map_type;

	map_type m_classes;
	ListAs m_mylistas;
public:
	void construct(std::string const & n, char * init)
	{
		map_type::iterator i = m_classes.find(n);
		if (i == m_classes.end()) return;
		auto it = m_mylistas.find(n);
		if (it == m_mylistas.end()) it = m_mylistas.find("GameObject");
		i->second(it->second, init);
	}

	//ListBase* get_listas(std::string const& n) {
	//	return m_mylistas.find(n)->second;
	//}

	template <class T>
	std::list<T*>* get_list(std::string const& n) {
		auto rv= static_cast<ListChild<T*>*>(m_mylistas.find(n)->second)->getter();
		return rv;
	}

	template <class T>
	void register_class(std::string const& n) {
		m_classes.insert(std::make_pair(n, &constructor<T>));
		m_mylistas.insert(std::make_pair(n, new ListChild<T*>()));
	}

	template <class T>
	void register_class_sub(std::string const& n,std::string const& ocp) {
		m_classes.insert(std::make_pair(n, &constructor<T>));
		m_mylistas.insert(std::make_pair(n, m_mylistas.find(ocp)->second));
	}

	template <class T>
	void clear_list(std::string const& n) {
		static_cast<ListChild<T*>*>(m_mylistas.find(n)->second)->clear();
	}
	template <class T>
	void update_list(std::string const& n) {
		static_cast<ListChild<T*>*>(m_mylistas.find(n)->second)->update();
	}
};
