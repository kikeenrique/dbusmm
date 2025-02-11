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


#ifndef __DBUSMM_ERROR_H
#define __DBUSMM_ERROR_H

#ifdef HAVE_CONFIG_H
#include <dbusmm_config.h>
#endif

#include "api.h"
#include "util.h"

#include <exception>

namespace DBus {

class Message;
class InternalError;

class DMMAPI Error : public std::exception
{
public:

	Error();

	Error( InternalError& );

	Error( const char* name, const char* message );
	
	Error( Message& );

	~Error() throw();

	const char* what() const throw();

	const char* name() const;

	const char* message() const;

	void set( const char* name, const char* message );
	// parameters MUST be static strings

	bool is_set() const;

	operator bool() const
	{
		return is_set();
	}

private:

	RefPtrI<InternalError> _int;
};

struct DMMAPI ErrorFailed : public Error
{
	ErrorFailed( const char* message )
	: Error("org.freedesktop.DBus.Error.Failed", message)
	{}
};

struct DMMAPI ErrorNoMemory : public Error
{
	ErrorNoMemory( const char* message )
	: Error("org.freedesktop.DBus.Error.NoMemory", message)
	{}
};

struct DMMAPI ErrorServiceUnknown : public Error
{
	ErrorServiceUnknown( const char* message )
	: Error("org.freedesktop.DBus.Error.ServiceUnknown", message)
	{}
};

struct DMMAPI ErrorNameHasNoOwner : public Error
{
	ErrorNameHasNoOwner( const char* message )
	: Error("org.freedesktop.DBus.Error.NameHasNoOwner", message)
	{}
};

struct DMMAPI ErrorNoReply : public Error
{
	ErrorNoReply( const char* message )
	: Error("org.freedesktop.DBus.Error.NoReply", message)
	{}
};

struct DMMAPI ErrorIOError : public Error
{
	ErrorIOError( const char* message )
	: Error("org.freedesktop.DBus.Error.IOError", message)
	{}
};

struct DMMAPI ErrorBadAddress : public Error
{
	ErrorBadAddress( const char* message )
	: Error("org.freedesktop.DBus.Error.BadAddress", message)
	{}
};

struct DMMAPI ErrorNotSupported : public Error
{
	ErrorNotSupported( const char* message )
	: Error("org.freedesktop.DBus.Error.NotSupported", message)
	{}
};

struct DMMAPI ErrorLimitsExceeded : public Error
{
	ErrorLimitsExceeded( const char* message )
	: Error("org.freedesktop.DBus.Error.LimitsExceeded", message)
	{}
};

struct DMMAPI ErrorAccessDenied : public Error
{
	ErrorAccessDenied( const char* message )
	: Error("org.freedesktop.DBus.Error.AccessDenied", message)
	{}
};

struct DMMAPI ErrorAuthFailed : public Error
{
	ErrorAuthFailed( const char* message )
	: Error("org.freedesktop.DBus.Error.AuthFailed", message)
	{}
};

struct DMMAPI ErrorNoServer : public Error
{
	ErrorNoServer( const char* message )
	: Error("org.freedesktop.DBus.Error.NoServer", message)
	{}
};

struct DMMAPI ErrorTimeout : public Error
{
	ErrorTimeout( const char* message )
	: Error("org.freedesktop.DBus.Error.Timeout", message)
	{}
};

struct DMMAPI ErrorNoNetwork : public Error
{
	ErrorNoNetwork( const char* message )
	: Error("org.freedesktop.DBus.Error.NoNetwork", message)
	{}
};

struct DMMAPI ErrorAddressInUse : public Error
{
	ErrorAddressInUse( const char* message )
	: Error("org.freedesktop.DBus.Error.AddressInUse", message)
	{}
};

struct DMMAPI ErrorDisconnected : public Error
{
	ErrorDisconnected( const char* message )
	: Error("org.freedesktop.DBus.Error.Disconnected", message)
	{}
};

struct DMMAPI ErrorInvalidArgs : public Error
{
	ErrorInvalidArgs( const char* message )
	: Error("org.freedesktop.DBus.Error.InvalidArgs", message)
	{}
};

struct DMMAPI ErrorFileNotFound : public Error
{
	ErrorFileNotFound( const char* message )
	: Error("org.freedesktop.DBus.Error.FileNotFound", message)
	{}
};

struct DMMAPI ErrorUnknownMethod : public Error
{
	ErrorUnknownMethod( const char* message )
	: Error("org.freedesktop.DBus.Error.UnknownMethod", message)
	{}
};

struct DMMAPI ErrorTimedOut : public Error
{
	ErrorTimedOut( const char* message )
	: Error("org.freedesktop.DBus.Error.TimedOut", message)
	{}
};

struct DMMAPI ErrorMatchRuleNotFound : public Error
{
	ErrorMatchRuleNotFound( const char* message )
	: Error("org.freedesktop.DBus.Error.MatchRuleNotFound", message)
	{}
};

struct DMMAPI ErrorMatchRuleInvalid : public Error
{
	ErrorMatchRuleInvalid( const char* message )
	: Error("org.freedesktop.DBus.Error.MatchRuleInvalid", message)
	{}
};

struct DMMAPI ErrorSpawnExecFailed : public Error
{
	ErrorSpawnExecFailed( const char* message )
	: Error("org.freedesktop.DBus.Error.Spawn.ExecFailed", message)
	{}
};

struct DMMAPI ErrorSpawnForkFailed : public Error
{
	ErrorSpawnForkFailed( const char* message )
	: Error("org.freedesktop.DBus.Error.Spawn.ForkFailed", message)
	{}
};

struct DMMAPI ErrorSpawnChildExited : public Error
{
	ErrorSpawnChildExited( const char* message )
	: Error("org.freedesktop.DBus.Error.Spawn.ChildExited", message)
	{}
};

struct DMMAPI ErrorSpawnChildSignaled : public Error
{
	ErrorSpawnChildSignaled( const char* message )
	: Error("org.freedesktop.DBus.Error.Spawn.ChildSignaled", message)
	{}
};

struct DMMAPI ErrorSpawnFailed : public Error
{
	ErrorSpawnFailed( const char* message )
	: Error("org.freedesktop.DBus.Error.Spawn.Failed", message)
	{}
};

struct DMMAPI ErrorInvalidSignature : public Error
{
	ErrorInvalidSignature( const char* message )
	: Error("org.freedesktop.DBus.Error.InvalidSignature", message)
	{}
};

struct DMMAPI ErrorUnixProcessIdUnknown : public Error
{
	ErrorUnixProcessIdUnknown( const char* message )
	: Error("org.freedesktop.DBus.Error.UnixProcessIdUnknown", message)
	{}
};

struct DMMAPI ErrorSELinuxSecurityContextUnknown : public Error
{
	ErrorSELinuxSecurityContextUnknown( const char* message )
	: Error("org.freedesktop.DBus.Error.SELinuxSecurityContextUnknown", message)
	{}
};

} /* namespace DBus */

#endif//__DBUSMM_ERROR_H
