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


#ifndef __DBUSMM_CONNECTION_P_H
#define __DBUSMM_CONNECTION_P_H

#ifdef HAVE_CONFIG_H
#include <dbusmm_config.h>
#endif

#include <dbusmm/connection.h>
#include <dbusmm/server.h>
#include <dbusmm/dispatcher.h>
#include <dbusmm/refptr_impl.h>

#include <dbus/dbus.h>

#include <string>

namespace DBus {

struct DMMAPILOCAL Connection::Private
{
	DBusConnection*	conn;

	std::vector<std::string> names;

	Dispatcher* dispatcher;
	bool do_dispatch();

	MessageSlot disconn_filter;
	bool disconn_filter_function( const Message& );

	Server::Private* server;
	void detach_server();

	Private( DBusConnection*, Server::Private* = NULL );

	Private( DBusBusType );

	~Private();

	void init();

	static void dispatch_status_stub( DBusConnection*, DBusDispatchStatus, void* );

	static DBusHandlerResult message_filter_stub( DBusConnection*, DBusMessage*, void* );
};

} /* namespace DBus */

#endif//__DBUSMM_CONNECTION_P_H
