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


#include <dbusmm/types.h>
#include <dbusmm/object.h>
#include <dbus/dbus.h>
#include <stdarg.h>
#include <iostream>
#include <stdlib.h>

#include "message_p.h"
#include "internalerror.h"

using namespace DBus;

Variant::Variant()
: _msg(CallMessage()) // dummy message used as temporary storage for variant data
{
}

Variant::Variant( MessageIter& it )
: _msg(CallMessage())
{
	MessageIter vi = it.recurse();
	MessageIter mi = _msg.writer();
	vi.copy_data(mi);
}

Variant& Variant::operator = ( const Variant& v )
{
	if(&v != this)
	{
		_msg = v._msg;
	}
	return *this;
}

void Variant::clear()
{
	CallMessage empty;
	_msg = empty;
}

const Signature Variant::signature() const
{
	char* sigbuf = reader().signature();

	Signature signature = sigbuf;

	free(sigbuf);

	return signature;
}

MessageIter& operator << ( MessageIter& iter, const Variant& val )
{
	const Signature sig = val.signature();

	MessageIter rit = val.reader();
	MessageIter wit = iter.new_variant(sig.c_str());

	rit.copy_data(wit);

	iter.close_container(wit);

	return iter;
}

MessageIter& operator >> ( MessageIter& iter, Variant& val )
{
	if(iter.type() != DBUS_TYPE_VARIANT)
		throw ErrorInvalidArgs("variant type expected");

	val.clear();

	MessageIter vit = iter.recurse();
	MessageIter mit = val.writer();

	vit.copy_data(mit);

	return ++iter;
}

std::ostream& operator << ( std::ostream& os, const Variant& val )
{
	MessageIter it = val.reader();

	switch (it.type()){
	    	case DBUS_TYPE_BYTE:
			os << it.get_byte();
			break;
	    	case DBUS_TYPE_BOOLEAN:
			os << it.get_bool();
			break;
	    	case DBUS_TYPE_INT16:
			os << it.get_int16();
			break;
	    	case DBUS_TYPE_UINT16:
			os << it.get_uint16();
			break;
	    	case DBUS_TYPE_INT32:
			os << it.get_int32();
			break;
	    	case DBUS_TYPE_UINT32:
			os << it.get_uint32();
			break;
	    	case DBUS_TYPE_INT64:
			os << it.get_int64();
			break;
	    	case DBUS_TYPE_UINT64:
			os << it.get_uint64();
			break;
	    	case DBUS_TYPE_DOUBLE:
			os << it.get_double();
			break;
	    	case DBUS_TYPE_STRING:
    			os << "(string) ";
			os << it.get_string();
			break;
		case DBUS_TYPE_ARRAY:
			os << "(array) ";
			switch (it.array_type()){
			    	case DBUS_TYPE_BYTE: 
					{
					std::vector<DBus::Byte> array;
					it.get_array(&array);
					os << array;
					break;
					}
			    	case DBUS_TYPE_BOOLEAN:
					{
					std::vector<DBus::Bool> array;
					it.get_array(&array);
					os << array;				    
					break;
					}
			    	case DBUS_TYPE_INT16:
					{
					std::vector<DBus::Int16> array;
					it.get_array(&array);
					os << array;				    
					break;
					}
			    	case DBUS_TYPE_UINT16:
					{
					std::vector<DBus::UInt16> array;
					it.get_array(&array);
					os << array;				    
					break;
					}
	    			case DBUS_TYPE_INT32:
					{
					std::vector<DBus::Int32> array;
					it.get_array(&array);
					os << array;				    
					break;
					}
			    	case DBUS_TYPE_UINT32:
					{
					std::vector<DBus::UInt32> array;
					it.get_array(&array);
					os << array;				    
					break;
					}
			    	case DBUS_TYPE_INT64:
					{
					std::vector<DBus::Int64> array;
					it.get_array(&array);
					os << array;				    
					break;
					}
	    			case DBUS_TYPE_UINT64:
					{
					std::vector<DBus::UInt16> array;
					it.get_array(&array);
					os << array;				    
					break;
					}
			    	case DBUS_TYPE_DOUBLE:
					{
					std::vector<DBus::Double> array;
					it.get_array(&array);
					os << array;				    
					break;
					}
			    	case DBUS_TYPE_STRING:
					{
					// MessageIter::get_array/() only works with fixed-length types
					std::vector<DBus::String> array;
					it >> array;
/*					std::vector<DBus::String>::iterator ait;
					for(ait = array.begin(); ait!=array.end(); ++ait)
					{
						os << *ait << ", ";
					}
*/					os << array;
					break;				
					}
				default:
	    				break;
			}
			break;
		case DBUS_TYPE_INVALID:
       			//FIXME Is a exception needed?
			throw DBus::ErrorInvalidArgs("Variant: single type expected");
		default:
    			//FIXME What could happend to use this switch path?
			std::cerr << "ostream " << it.type() << std::endl;
			break;
	}
	return os;
}
