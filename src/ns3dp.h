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

//-*- C++ -*-

#ifndef NS3DP_H
#define NS3DP_H

#include "input.h"

#include "globals.h"

#include "ns3dp_rhs.h"

#include "init_cond.h"

#include <goops.h>

#include <godess.h>

input * input_obj;

SpectralFourier * spectral_obj;

ns3dp_rhs * rhs_obj;

init_cond * initial;

adams_bashford_4<ns3dp_rhs,cdVecArray3d,double> * solver;

double energy(const cdVecArray3d & vort_hat);

double enstrophy(const cdVecArray3d & vort_hat);

double helicity(const cdVecArray3d & vort_hat);

#endif
