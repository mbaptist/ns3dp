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



//init_cond.h
//Possible inital conditions

#ifndef INIT_COND_H
#define INIT_COND_H

#include "input.h"

#include "globals.h"

#include <goops.h>


class init_cond
{

private:
  //Members
  input & input_obj;
  SpectralFourier & spectral_obj;
  int & n1;
  int & n2;
  int & n3;
  double & l1;
  double & l2;
  double & l3;
  cdVecArray3d vort_hat_;

public:
  //Accessors
  cdVecArray3d vort_hat() const;

  //Constructors
  init_cond(input & input_obj__,
	    SpectralFourier & spectral_obj__,
	    const double & a,
	    const double & b,
	    const double & c);//ABC flow

  init_cond(input & input_obj__,
	    SpectralFourier & spectral_obj__,
	    const int & ki, 
	    const int & kf,
	    const double & alpha,
	    const double & p);//Random phases and amplitudes


  //Destructor
  ~init_cond();

  //Public methods
  double get_cfl_dt();
  bool check_cfl(const double & dt);

};


#endif
