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


#ifndef __DBUSMM_TOOLS_INTROSPECT_H
#define __DBUSMM_TOOLS_INTROSPECT_H

#ifdef HAVE_CONFIG_H
#include <dbusmm_config.h>
#endif

#include <dbusmm/dbus.h>
#include <string>

class IntrospectedObject : public DBus::IntrospectableProxy, public DBus::ObjectProxy
{
public:

	IntrospectedObject( DBus::Connection& conn, const char* path, const char* service )
	: DBus::ObjectProxy(conn, path, service)
	{}
};

#endif//__DBUSMM_TOOLS_INTROSPECT_H
