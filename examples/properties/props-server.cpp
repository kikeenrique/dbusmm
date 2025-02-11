#include "props-server.h"
#include <signal.h>

static const char* PROPS_SERVER_NAME = "org.freedesktop.DBus.Examples.Properties";
static const char* PROPS_SERVER_PATH = "/org/freedesktop/DBus/Examples/Properties";

PropsServer::PropsServer( DBus::Connection& connection )
: DBus::ObjectAdaptor(connection, PROPS_SERVER_PATH)
{
	Version = 1;
	Message = "default message";
}

void PropsServer::on_set_property
	( DBus::InterfaceAdaptor& interface, const DBus::String& property, const DBus::Variant& value )
{
	if(property == "Message")
	{
		DBus::String msg = value;
		this->MessageChanged(msg);
	}
}

DBus::BusDispatcher dispatcher;

void niam( int sig )
{
	dispatcher.leave();
}

int main()
{
	signal(SIGTERM, niam);
	signal(SIGINT, niam);

	DBus::default_dispatcher = &dispatcher;

	DBus::Connection conn = DBus::Connection::SessionBus();
	conn.request_name(PROPS_SERVER_NAME);

	PropsServer server(conn);

	dispatcher.enter();

	return 0;
}
