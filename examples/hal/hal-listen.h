#ifndef __DEMO_HAL_LISTEN_H
#define __DEMO_HAL_LISTEN_H

#include <dbusmm/dbus.h>
#include <vector>
#include <map>
#include <iostream>

class HalDeviceProxy;

class HalManagerProxy
: public DBus::InterfaceProxy,
  public DBus::ObjectProxy
{
public:

	HalManagerProxy( DBus::Connection& connection );

	std::vector< DBus::String > GetAllDevices ();
	std::map< DBus::String, DBus::Variant > GetAllProterties (DBus::RefPtr<HalDeviceProxy>);

private:

	void DeviceAddedCb( const DBus::SignalMessage& sig );

	void DeviceRemovedCb( const DBus::SignalMessage& sig );

	std::map< DBus::String, DBus::RefPtr<HalDeviceProxy> > _devices;
};

class HalDeviceProxy
: public DBus::InterfaceProxy,
  public DBus::ObjectProxy
{
public:

	HalDeviceProxy( DBus::Connection& connection, DBus::Path& udi );

private:

	void PropertyModifiedCb( const DBus::SignalMessage& sig );

	void ConditionCb( const DBus::SignalMessage& sig );
};

#endif//__DEMO_HAL_LISTEN_H
