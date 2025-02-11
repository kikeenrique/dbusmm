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


#ifndef __DBUSMM_SERVER_H
#define __DBUSMM_SERVER_H

#ifdef HAVE_CONFIG_H
#include <dbusmm_config.h>
#endif

#include <list>

#include "api.h"
#include "error.h"
#include "connection.h"
#include "util.h"
#include "dispatcher.h"

namespace DBus {

class Server;

typedef std::list<Server> ServerList;

class DMMAPI Server
{
public:

	Server( const char* address );

	Dispatcher* setup( Dispatcher* );

	virtual ~Server();

	bool listening() const;

	bool operator == ( const Server& ) const;

	void disconnect();

	struct Private;

protected:

	Server( const Server& s )
	{}

	virtual void on_new_connection( Connection& c ) = 0;

private:

	RefPtrI<Private> _pvt;
};

} /* namespace DBus */

#endif//__DBUSMM_SERVER_H
