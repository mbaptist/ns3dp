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



#ifndef NS3DP_RHS_H
#define NS3DP_RHS_H

#include "input.h"

#include "globals.h"

#include <goops.h>

class ns3dp_rhs
{
  
 private:
  input & input_obj;
  SpectralFourier & spectral_obj;

 public:
  //Constructor
  ns3dp_rhs(input & input_obj__,
	    SpectralFourier & spectral_obj__);
  //Destructor
  ~ns3dp_rhs();
  
 private:
  //Forbidden constructors
  ns3dp_rhs();
  ns3dp_rhs(const ns3dp_rhs &);

 public:
  //RHS application operator
  cdVecArray3d operator()(const cdVecArray3d & vort_hat,double t); 
  
};

#endif

