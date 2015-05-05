// -*- C++ -*-
/*

Copyright 2004,2005,2006 Manuel Baptista

This file is part of NS3DP

NS3DP is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

NS3DP is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/



#ifndef NS3DP_GLOBALS_H
#define NS3DP_GLOBALS_H

#include <cat.h>

//Names used in ns3d
//vectors
typedef cat::Tvector<double,3> dVec;
typedef cat::Tvector<complex<double>,3> cdVec;
//3D scalar fields
typedef cat::Array<double,3> dArray3d;
typedef cat::Array<complex<double>,3> cdArray3d;
//3D vector fields
typedef cat::Array<cat::Tvector<double,3>,3> dVecArray3d;
typedef cat::Array<cat::Tvector<complex<double>,3>,3> cdVecArray3d;

static const complex<double> I=complex<double>(0,1);

#endif

