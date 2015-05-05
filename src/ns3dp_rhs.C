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



#include "ns3dp_rhs.h"

#include "globals.h"

#include <goops.h>

using namespace cat;

ns3dp_rhs::ns3dp_rhs(input & input_obj__,
		     SpectralFourier & spectral_obj__):
  input_obj(input_obj__),
  spectral_obj(spectral_obj__)
{
}

ns3dp_rhs::~ns3dp_rhs()
{
}

cdVecArray3d ns3dp_rhs::operator()(const cdVecArray3d & vort_hat,double t)
{

  //Diffusive term

  cdVecArray3d out(spectral_obj.lap_hat(vort_hat));
  out*=input_obj.visc;

  //Nonlinear term ( curl(v x w)_hat ) 

  //Eavaluate velocity_hat
  // lap v = - curl vort
  cdVecArray3d velocity_hat(spectral_obj.poisson_hat(
	  cdVecArray3d(-spectral_obj.curl_hat(vort_hat)))
                           );
  
  //Transform velocity and vort to real space
  dVecArray3d velocity(input_obj.n1,input_obj.n2,input_obj.n3);
  dVecArray3d vort(input_obj.n1,input_obj.n2,input_obj.n3);
  spectral_obj.fft.inverse_transform(velocity,velocity_hat);
  spectral_obj.fft.inverse_transform(vort,vort_hat);

  //Evaluate cross product v x w in real space
  dVecArray3d nonlinear(cross_product(velocity,vort));
  
  //Transform v x w to fourier space
  cdVecArray3d nonlinear_hat(vort_hat.shape());
  spectral_obj.fft.direct_transform(nonlinear_hat,nonlinear);

  //Perform dealiasing on (v x w)_hat
  spectral_obj.dealias(nonlinear_hat);

  //Take curl of (v x w)_hat and add to diffusive term
  out+=spectral_obj.curl_hat(nonlinear_hat);

  //Remove gradient
  spectral_obj.remove_gradient(out);

  return out;

}
