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


#ifndef __DBUSMM_DISPATCHER_P_H
#define __DBUSMM_DISPATCHER_P_H

#ifdef HAVE_CONFIG_H
#include <dbusmm_config.h>
#endif

#include <dbusmm/dispatcher.h>

#include <dbus/dbus.h>

#include "internalerror.h"

namespace DBus {

struct DMMAPILOCAL Dispatcher::Private
{
	static dbus_bool_t on_add_watch( DBusWatch* watch, void* data );

	static void on_rem_watch( DBusWatch* watch, void* data );

	static void on_toggle_watch( DBusWatch* watch, void* data );

	static dbus_bool_t on_add_timeout( DBusTimeout* timeout, void* data );

	static void on_rem_timeout( DBusTimeout* timeout, void* data );

	static void on_toggle_timeout( DBusTimeout* timeout, void* data );
};

} /* namespace DBus */

#endif//__DBUSMM_DISPATCHER_P_H
