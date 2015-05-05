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

#include "globals.h"

#include "init_cond.h"

#include <goops.h>

#include <cmath>

using namespace std;

//Accessors

cdVecArray3d init_cond::vort_hat() const
{
  return vort_hat_;
}


//Constructors

//ABC Flow (\nabla \times V = \lambda V , \lambda=1)
init_cond::init_cond(input & input_obj__,
		     SpectralFourier & spectral_obj__,
		     const double & a,
		     const double & b,
		     const double & c):
  input_obj(input_obj__),
  spectral_obj(spectral_obj__),
  n1(input_obj.n1),
  n2(input_obj.n2),
  n3(input_obj.n3),
  l1(input_obj.l1),
  l2(input_obj.l2),
  l3(input_obj.l3),
  vort_hat_(n1,n2,n3/2+1)
{

  dVecArray3d velocity(n1,n2,n3);

  //Define (evaluate) the velocity field
  for(int i=0;i<n1;++i)
    for(int j=0;j<n2;++j)
      for(int k=0;k<n3;++k)
      {
        velocity(i,j,k)=cat::Tvector<double,3>(
          a*sin(k*l3/n3)+c*cos(j*l2/n2),
          b*sin(i*l1/n1)+a*cos(k*l3/n3),
          c*sin(j*l2/n2)+b*cos(i*l1/n1) );
      }

  cdVecArray3d velocity_hat(n1,n2,n3/2+1);
  spectral_obj.fft.direct_transform(velocity_hat,velocity);
  vort_hat_=spectral_obj.curl_hat(velocity_hat);
}


//Excite spectrum from ki to kf with rnadomly generated phases and amplitudes
init_cond::init_cond(input & input_obj__,
		     SpectralFourier & spectral_obj__,
		     const int & ki, 
		     const int & kf,
		     const double & alpha,
		     const double & p):
  input_obj(input_obj__),
  spectral_obj(spectral_obj__),
  n1(input_obj.n1),
  n2(input_obj.n2),
  n3(input_obj.n3),
  l1(input_obj.l1),
  l2(input_obj.l2),
  l3(input_obj.l3),
  vort_hat_(n1,n2,n3/2+1)
{

  random_generator random;

  cdVecArray3d velocity_hat(vort_hat_);
  
  double wv2step(max(spectral_obj.wv2)/(n1-1));

  //Randomly generate velocity components in Fourer
  for(int i=0;i<n1;++i)
    for(int j=0;j<n2;++j)
      for(int k=0;k<n3/2+1;++k)
	for(int m=0;m<3;m++)
	  {
	    double wv_norm=spectral_obj.wv2(i,j,k);
	    if (wv_norm>=ki*ki*wv2step && wv_norm<kf*kf*wv2step)
	      velocity_hat(i,j,k)[m]=random(0.,1.)*exp(I*random(0.,2*M_PI));
	    else
	      velocity_hat(i,j,k)[m]=0;
	  }

  //Impose hermitian symmetry
  for(int i=0;i<n1/2+1;++i)
    for(int j=0;j<n2/2+1;++j)
	velocity_hat(n1-i,n2-j,0)=velocity_hat(i,j,0);

  //Impose zero average
  velocity_hat(0,0,0)=0;
  

  //Eval spectrum
  cat::Array<double,1> energ_spec
    (spectral_obj.eval_energ_spec(velocity_hat));
  
  cout << energ_spec << endl;

  //Normalise
  //double wv2step(max(spectral_obj.wv2)/(energ_spec.size()-1));
	cat::Array<cat::Tvector<complex<double>,3>,3>::iterator
    velocity_hat_iterator(velocity_hat);
	cat::Array<double,3>::iterator wv2_iterator(spectral_obj.wv2);
  for(velocity_hat_iterator=velocity_hat.begin(),
	wv2_iterator=spectral_obj.wv2.begin();
      velocity_hat_iterator!=velocity_hat.end(),
	wv2_iterator!=spectral_obj.wv2.end();
      ++velocity_hat_iterator,
	++wv2_iterator)
    {
      int index=static_cast<int>((*wv2_iterator)/wv2step);
      if(index>=ki && index<kf)
	{
	  double power=pow(double(*wv2_iterator),-alpha);
	  (*velocity_hat_iterator)*=sqrt(power/energ_spec(index));
	}
    }

  //Re-eval energ_spec
  energ_spec=spectral_obj.eval_energ_spec(velocity_hat);

  //Normalise for RMS vel,mag,temp = p
  velocity_hat*=(p/sqrt(2*sum(energ_spec)));

  //Re-eval energ_spec
  energ_spec=spectral_obj.eval_energ_spec(velocity_hat);

  vort_hat_=spectral_obj.curl_hat(velocity_hat);

}

//Destructor
init_cond::~init_cond()
{
}

double init_cond::get_cfl_dt()
{
  dVecArray3d vort(n1,n2,n3);
  spectral_obj.fft.inverse_transform(vort,vort_hat_);
	double vort_max=max(dArray3d(dot_product(vort,vort)));
  double dt=.8/(norm(spectral_obj.wv(n1/2,n2/2,n3/2))*vort_max);
  cout << "dt = " << dt << " (evaluated by CFL)" << endl;
  return dt;
}

bool init_cond::check_cfl(const double & dt)
{ 
  dVecArray3d vort(n1,n2,n3);
  spectral_obj.fft.inverse_transform(vort,vort_hat_);
	double vort_max=max(dArray3d(dot_product(vort,vort)));
  //check if cfl is verified - if not, set dt to -1
  if (dt*norm(spectral_obj.wv(n1/2,n2/2,n3/2))*vort_max>=1)
    {
      cout << "CFL condition not verified." << endl;
      return 0;
    }
  else
    {
      cout << "CFL condition verified!" << endl;
      return 1;
    }
}

