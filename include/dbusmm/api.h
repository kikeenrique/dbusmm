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


#ifndef __DBUSMM_API_H
#define __DBUSMM_API_H

#ifdef HAVE_CONFIG_H
#include <dbusmm_config.h>
#endif

#ifdef GCC_HASCLASSVISIBILITY
# define DMMAPILOCAL __attribute__ ((visibility("hidden")))
# define DMMAPIPUBLIC __attribute__ ((visibility("default")))
#else
# define DMMAPILOCAL
# define DMMAPIPUBLIC
#endif

#define DMMAPI DMMAPIPUBLIC

#endif//__DBUSMM_API_H
