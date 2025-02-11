/*
 *
 *  D-Bus++ - C++ bindings for D-Bus
 *
 *  Copyright (C) 2005-2007  Paolo Durante <shackan@gmail.com>
 *
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */


#ifndef __DBUSMM_INTERFACE_H
#define __DBUSMM_INTERFACE_H

#ifdef HAVE_CONFIG_H
#include <dbusmm_config.h>
#endif

#include <string>
#include <map>
#include "api.h"
#include "util.h"
#include "types.h"

#include "message.h"

namespace DBus {

//todo: this should belong to to properties.h
struct DMMAPI PropertyData
{
	bool		read;
	bool		write;
	std::string	sig;
	Variant		value;
};

typedef std::map<std::string, PropertyData>	PropertyTable;

class IntrospectedInterface;

class ObjectAdaptor;
class InterfaceAdaptor;
class SignalMessage;

typedef std::map<std::string, InterfaceAdaptor*> InterfaceAdaptorTable;

class DMMAPI AdaptorBase
{
public:

	virtual const ObjectAdaptor* object() const = 0 ;

protected:

	InterfaceAdaptor* find_interface( const std::string& name );

	virtual ~AdaptorBase()
	{}

	virtual void _emit_signal( SignalMessage& ) = 0;

	InterfaceAdaptorTable _interfaces;
};

/*
*/

class ObjectProxy;
class InterfaceProxy;
class CallMessage;

typedef std::map<std::string, InterfaceProxy*> InterfaceProxyTable;

class DMMAPI ProxyBase
{
public:

	virtual const ObjectProxy* object() const = 0 ;

protected:

	InterfaceProxy* find_interface( const std::string& name );

	virtual ~ProxyBase()
	{}

	virtual Message _invoke_method( CallMessage& ) = 0;

	InterfaceProxyTable _interfaces;
};

class DMMAPI Interface
{
public:
	
	Interface( const std::string& name );
	
	virtual ~Interface();

	inline const std::string& name() const;

private:

	std::string 	_name;
};

/*
*/

const std::string& Interface::name() const
{
	return _name;
}

/*
*/

typedef std::map< std::string, Slot<Message, const CallMessage&> > MethodTable;

class DMMAPI InterfaceAdaptor : public Interface, public virtual AdaptorBase
{
public:

	InterfaceAdaptor( const std::string& name );

	Message dispatch_method( const CallMessage& );

	void emit_signal( const SignalMessage& );

	Variant* get_property( const std::string& name );

	void set_property( const std::string& name, Variant& value );

	virtual IntrospectedInterface* const introspect() const
	{
		return NULL;
	}

protected:

	MethodTable	_methods;
	PropertyTable	_properties;
};

/*
*/

typedef std::map< std::string, Slot<void, const SignalMessage&> > SignalTable;

class DMMAPI InterfaceProxy : public Interface, public virtual ProxyBase
{
public:

	InterfaceProxy( const std::string& name );

	Message invoke_method( const CallMessage& );

	bool dispatch_signal( const SignalMessage& );

protected:

	SignalTable	_signals;
};

# define register_method(interface, method, callback) \
	InterfaceAdaptor::_methods[ #method ] = \
		new ::DBus::Callback< interface, ::DBus::Message, const ::DBus::CallMessage& >(this, & interface :: callback );

# define bind_property(variable, type, can_read, can_write) \
	InterfaceAdaptor::_properties[ #variable ].read = can_read; \
	InterfaceAdaptor::_properties[ #variable ].write = can_write; \
	InterfaceAdaptor::_properties[ #variable ].sig = type; \
	variable.bind( InterfaceAdaptor::_properties[ #variable ] );
	
# define connect_signal(interface, signal, callback) \
	InterfaceProxy::_signals[ #signal ] = \
		new ::DBus::Callback< interface, void, const ::DBus::SignalMessage& >(this, & interface :: callback );

} /* namespace DBus */

#endif//__DBUSMM_INTERFACE_H
