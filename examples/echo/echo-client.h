#ifndef __DEMO_ECHO_CLIENT_H
#define __DEMO_ECHO_CLIENT_H

#include <dbusmm/dbus.h>
#include "echo-client-glue.h"

class EchoClient
: public org::freedesktop::DBus::EchoDemo,
  public DBus::IntrospectableProxy,
  public DBus::ObjectProxy
{
public:

	EchoClient( DBus::Connection& connection, const char* path, const char* name );

	void Echoed( const DBus::Variant& value );
};

#endif//__DEMO_ECHO_CLIENT_H
