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


#include "input.h"

#include "ns3dp.h"

#include "globals.h"

#include "ns3dp_rhs.h"

#include <goops.h>

#include <godess.h>

#include <iostream>

#include <fstream>

#include <sstream>

using namespace std;

using namespace cat;

int main()
{
  input_obj=new input("default.cfg");

  spectral_obj=new SpectralFourier(input_obj->n1,
				    input_obj->n2,
				    input_obj->n3,
				    input_obj->l1,
				    input_obj->l2,
				    input_obj->l3);

  rhs_obj=new ns3dp_rhs(*input_obj,*spectral_obj);

  initial=new init_cond(*input_obj,*spectral_obj,10,10,10);
  
	//initial=new init_cond(*input_obj,*spectral_obj,1,4,6.,1.);

  ofstream ofs("vort0");
	
  dVecArray3d vort(input_obj->n1,
		   input_obj->n2,
		   input_obj->n3);
  spectral_obj->fft.inverse_transform(vort,initial->vort_hat());
  ofs << vort << endl;

  
  cout << "Iteration 0" << endl;
      
  cout << "Energy: "
       << energy(initial->vort_hat())
       << "   Enstrophy: "
       << enstrophy(initial->vort_hat())
       << "   Helicity: "
       << helicity(initial->vort_hat())
       << endl;

  solver=new adams_bashford_4<ns3dp_rhs,cdVecArray3d,double>
    (*rhs_obj,
     initial->vort_hat(),
     0.,
     initial->get_cfl_dt());

  delete initial;

	for (int i=0;i<50;++i)
    {

      solver->iterate(100);
      cout << "Iteration " << solver->it() << endl;
      
      stringstream ss;
      ss << "vort";
      ss << solver->it();
      ofstream ofs(ss.str().c_str());
      dVecArray3d vort(input_obj->n1,
		       input_obj->n2,
		       input_obj->n3);
      spectral_obj->fft.inverse_transform(vort,solver->y());
      cout << "Energy: "
	   << energy(solver->y())
	   << "   Enstrophy: "
	   << enstrophy(solver->y())
	   << "   Helicity: "
	   << helicity(solver->y())
	   << endl;
      ofs << vort << endl;
      ofs.close();
    }

  delete solver;
  
  delete rhs_obj;

  delete spectral_obj;

  delete input_obj;
  
  return 0;
}

//Evaluate energy
double energy(const cdVecArray3d & vort_hat)
{
  cdVecArray3d velocity_hat
    (spectral_obj->poisson_hat
     (cdVecArray3d(-spectral_obj->curl_hat
                   (vort_hat))));
  return double(.5*spectral_obj->scalar_prod(velocity_hat,velocity_hat));
}
//Evaluate enstrophy
double enstrophy(const cdVecArray3d & vort_hat)
{
  return double(.5*spectral_obj->scalar_prod(vort_hat,vort_hat));
}
//Evaluate helicity
double helicity(const cdVecArray3d & vort_hat)
{
  cdVecArray3d velocity_hat
    (spectral_obj->poisson_hat
     (cdVecArray3d(-spectral_obj->curl_hat
                   (vort_hat))));
  return double(.5*spectral_obj->scalar_prod(velocity_hat,vort_hat));
}
