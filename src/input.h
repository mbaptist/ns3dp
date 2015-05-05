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




//input.h

//Class input declares the input parameters and is inherited
//by the problem class ns3d
//It is responsible for reading the configuration file and 
//seting the input parameters 

#ifndef INPUT_H
#define INPUT_H

#include <Python.h>

#include <iostream>
#include <string>

using namespace std;

class input
{
public:
  //constructor (requires filename)
  input(string cfg_fname){load_input(cfg_fname);}
  //destructor
  ~input(){};
 public:
  //input parameters
  int n1,n2,n3;//Spatial grid
  double l1,l2,l3;//Spatial extent
  //physical Parameters
  double visc;
  
  //basic fields
  string init_mode;

 private:
  //load from config file
  void load_input(string cfg_fname);
};    


//Python Parser class
class py_parser
{
private:
  //Filename to parse
  string filename;
  //Python objectts
  PyObject * module;
  PyObject * dict;

  PyObject * pval(const string & item);

public:
  //Constructor
  py_parser(string filename_);
  //Destructor
  ~py_parser();
  //Python to C++ conversion function
  void operator()(int & val,const string & item);
  void operator()(double & val,const string & item);
  void operator()(string & val,const string & item);
private:
  //Forbidden constructors
  py_parser();//default
  py_parser(const py_parser &);//copy
};




#endif
