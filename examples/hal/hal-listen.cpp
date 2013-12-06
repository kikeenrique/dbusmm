#include "hal-listen.h"

#include <signal.h>
#include <iostream>

#define DBUS_TYPE_STRUCT        ((int) 'r')
#define DBUS_TYPE_STRING        ((int) 's')
#define DBUS_TYPE_ARRAY         ((int) 'a')
#define DBUS_TYPE_VARIANT       ((int) 'v')
#define DBUS_TYPE_DICT_ENTRY    ((int) 'e')

///////////
/////////// Hal Manager
///////////

HalManagerProxy::HalManagerProxy( DBus::Connection& connection )
: DBus::InterfaceProxy("org.freedesktop.Hal.Manager"),
  DBus::ObjectProxy(connection, "/org/freedesktop/Hal/Manager", "org.freedesktop.Hal")
{
	connect_signal(HalManagerProxy, DeviceAdded, DeviceAddedCb);
	connect_signal(HalManagerProxy, DeviceRemoved, DeviceRemovedCb);

	std::vector< DBus::String > devices = GetAllDevices();
	std::vector< DBus::String >::iterator it;
	for(it = devices.begin(); it != devices.end(); ++it) {
		DBus::Path udi = *it;
		_devices[udi] = new HalDeviceProxy(connection, udi);

		if ( udi.find("proc", 0) != DBus::String::npos ) {
			std::cout << "procmon device " << udi << std::endl;
			std::cout << "device properties: " << std::endl;
			std::map< DBus::String, DBus::Variant > properties = GetAllProterties(_devices[udi]);
			std::map< DBus::String, DBus::Variant >::iterator it_properties;
			for(it_properties = properties.begin(); it_properties != properties.end(); ++it_properties){
				std::cout << '\t' << "[" << it_properties->first << "->";
				std::cout << it_properties->second;
				std::cout << "]" << std::endl;
			}
	 	} else {
			std::cout << "found device " << udi << std::endl;
		}
/*
		std::cout << "device " << udi << std::endl;
		std::cout << "device properties: " << std::endl;
		std::map< DBus::String, DBus::Variant > properties = GetAllProterties(_devices[udi]);
		std::map< DBus::String, DBus::Variant >::iterator it_properties;
		for(it_properties = properties.begin(); it_properties != properties.end(); ++it_properties){
			std::cout << '\t' << "[" << it_properties->first << "->";
			std::cout << it_properties->second;
			std::cout << "]" << std::endl;
		}
*/		    	     
	}
}

/*
 * GetAllProterties  returns  type = a{sv} -> an array of dict entry 
 * (which DBus protocol suggest as a map, hash table or dict object)
 */
std::map< DBus::String, DBus::Variant > HalManagerProxy::GetAllProterties(DBus::RefPtr< HalDeviceProxy > device)
{
   	std::map< DBus::String, DBus::Variant >  properties;
	DBus::CallMessage call;

	call.member("GetAllProperties");
    
	try {
		DBus::Message reply = device->invoke_method(call);
	    	DBus::MessageIter it = reply.reader();
	    
    		it >> properties;

/*		if ( it.is_dict() == true ) {
			std::cout << "TRUE" << std::endl;
		} else {
			std::cout << "FALSE" << std::endl;
		}
		std::cout << it.signature() << std::endl;	     
     		switch ( it.array_type() ) {
	                case DBUS_TYPE_VARIANT:
				std::cout << "variant" << std::endl;
	                case DBUS_TYPE_STRING:
				std::cout << "string" << std::endl;
	                case DBUS_TYPE_STRUCT:
				std::cout << "struct" << std::endl;
	                case DBUS_TYPE_DICT_ENTRY:
				std::cout << "dict entry" << std::endl;			
			default :
    				std::cout << "nothing" << std::endl;
			;
		}
*/	    
	}
	catch (const DBus::Error& exception){
		std::cerr << exception.what() << std::endl;
    		std::cerr << exception.name() << std::endl;
       		std::cerr << exception.message() << std::endl;
	}

	return properties;
}

/*
 */
std::vector< DBus::String > HalManagerProxy::GetAllDevices()
{
	std::vector< DBus::String > udis;
	DBus::CallMessage call;

	call.member("GetAllDevices");
    
	DBus::Message reply = invoke_method(call);
	DBus::MessageIter it = reply.reader();

	it >> udis;
	return udis;
}

void HalManagerProxy::DeviceAddedCb( const DBus::SignalMessage& sig )
{
	DBus::MessageIter it = sig.reader();
	DBus::String devname;

	it >> devname;

	DBus::Path udi(devname);

	_devices[devname] = new HalDeviceProxy(conn(), udi);
	std::cout << "added device " << udi << std::endl;
}

void HalManagerProxy::DeviceRemovedCb( const DBus::SignalMessage& sig )
{
	DBus::MessageIter it = sig.reader();
	DBus::String devname;

	it >> devname;

	std::cout << "removed device " << devname << std::endl;

	_devices.erase(devname);
}


///////////
/////////// Hal Device
///////////
HalDeviceProxy::HalDeviceProxy( DBus::Connection& connection, DBus::Path& udi )
: DBus::InterfaceProxy("org.freedesktop.Hal.Device"),
  DBus::ObjectProxy(connection, udi, "org.freedesktop.Hal")
{
	connect_signal(HalDeviceProxy, PropertyModified, PropertyModifiedCb);
	connect_signal(HalDeviceProxy, Condition, ConditionCb);
}

void HalDeviceProxy::PropertyModifiedCb( const DBus::SignalMessage& sig )
{
	typedef DBus::Struct< DBus::String, DBus::Bool, DBus::Bool > HalProperty;

	DBus::MessageIter it = sig.reader();
	DBus::Int32 number;

	it >> number;
	std::cout << "#modified properties " << number << std::endl;

	DBus::MessageIter arr = it.recurse();

	for(int i = 0; i < number && !(arr.at_end()) ; ++i, ++arr)
	{
		HalProperty hp;

		arr >> hp;

		std::cout << "modified property " << hp._1 << " in " << path() << std::endl;
	}
}

void HalDeviceProxy::ConditionCb( const DBus::SignalMessage& sig )
{
	DBus::MessageIter it = sig.reader();
	DBus::String condition;

	it >> condition;

	std::cout << "encountered condition " << condition << " in " << path() << std::endl;
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

	DBus::Connection conn = DBus::Connection::SystemBus();

	HalManagerProxy hal(conn);	
   
	dispatcher.enter();

	return 0;
}
