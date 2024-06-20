////////////////////////////////////////////////////////////////
// MSDN Magazine -- March 2006
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with Visual Studio .NET 2003 (V7.1) on Windows XP. Tab size=3.
//
// Generic event manager for native C++.
//
#pragma once

#include <list>
#include <algorithm>
using namespace std;

//////////////////
// Generic event manager. Holds list of client objects. Template class
// parameterized by the event interface.
//
// - Instantiate in event source class.
//
// - Source calls Raise to raise an event, passing functor object initialized
//	  with event params.
//
// - Clients derive from event interface and override event handlers. Clients
//   call Register/Unregister to add/remove themselves.
//

template <typename I>
class CEventMgr
{
protected:
	list<I*> m_clients; // list of registered client objects
public:
	CEventMgr() { }
	~CEventMgr() { }

	// Register: Add client to list.
	void Register(I* client)
	{
		m_clients.push_back(client);
	}

	// Unregiser: Remove client from list.
	void Unregister(I* client)
	{
		m_clients.remove(client);
	}

	// Nested template member function! This fn calls the function object F for
	// each registered client. It merely passes F to for_each. Use the
	// DEFINE_EVENT macros to generate the functors. See IPrimeEvents in
	// Prime.h for example.
	template <typename F>
	void Raise(F fn)
	{
		for_each(m_clients.begin(), m_clients.end(), fn);
	}
};

// Macro to get the functor name when raising events
#define EVENT(name) \
    name##Functor

// Macro to declare an event interface. Generates declarations for ctor/dtor.
#define DECLARE_EVENTS(name)											\
protected:																	\
	name() { }																\
	virtual ~name() = 0;													\

// Macro to implement event interface. Defines dtor
#define IMPLEMENT_EVENTS(name)										\
	inline name::~name() { }											\

// Macros to define events that use 0, 1 or 2 parameters. If you need more
// than two, you should define a struct/class and pass a pointer to it.

// Event with no args: Declare OnFoo handler and Foo functor.
#define DEFINE_EVENT0(iface,name)									\
virtual void name() { };											\
class name##Functor {				\
public:																		\
	name##Functor() { }																\
	void operator()(iface* obj)										\
	{																			\
		obj->name();													\
	}																			\
};																				\

// Event with one arg: Declare OnFoo handler and Foo functor.
#define DEFINE_EVENT1(iface,name,T1)								\
virtual void name(T1) { }											\
class name##Functor {				\
public:																	\
	T1 m_arg1;																\
	name##Functor(T1 a1) : m_arg1(a1) { }										\
	void operator()(iface* obj)										\
	{																			\
		obj->name(m_arg1);											\
	}																			\
};																				\


// Event with two args: Declare OnFoo handler and Foo functor.
#define DEFINE_EVENT2(iface,name,T1,T2)							\
virtual void name(T1, T2) { }									\
class name##Functor {				\
public:																	\
	T1 m_arg1;																\
	T2 m_arg2;																\
	name##Functor(T1 a1, T2 a2) : m_arg1(a1), m_arg2(a2) { }				\
	void operator()(iface* obj)										\
	{																			\
		obj->name(m_arg1, m_arg2);								\
	}																			\
};																				\

