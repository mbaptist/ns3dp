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



#include <Python.h>

#include "input.h"

#include <string>
#include <sstream>
#include <fstream>

using namespace std;

//load from config file
void input::load_input(string cfg_fname)
{
  py_parser parse(cfg_fname);

  parse(n1,"n1");
  parse(n2,"n2");
  parse(n3,"n3");

  parse(l1,"l1");
  parse(l2,"l2");
  parse(l3,"l3");

  parse(visc,"visc");

}


py_parser::py_parser(string filename_):
  filename(filename_)
{

  Py_Initialize();

  stringstream ss;
  ss << "import sys\n" 
     << "sys.path.insert(0,'')\n"
     << "import imp\n"
     << "imp.load_source('input_module','"
     << filename
     << "')\n";

  PyRun_SimpleString(ss.str().c_str());

  module=PyImport_ImportModule("input_module");
  dict=PyModule_GetDict(module);

}

py_parser::~py_parser()
{
  Py_DECREF(dict);
  Py_DECREF(module);
  PyRun_SimpleString("if(imp.lock_held()):imp.release_lock()\n");
  Py_Finalize();
}

void py_parser::operator()(int & val, const string & item)
{
  //val=PyInt_AsLong(PyDict_GetItem(dict,PyString_FromString(item.c_str())));
  val=PyInt_AsLong(pval(item));
}

void py_parser::operator()(double & val, const string & item)
{
  // val=PyFloat_AsDouble(PyDict_GetItem(dict,PyString_FromString(item.c_str())));
  val=PyFloat_AsDouble(pval(item));
}

void py_parser::operator()(string & val, const string & item)
{
  //  val=PyString_AsString(PyDict_GetItem(dict,PyString_FromString(item.c_str())));
  val=PyString_AsString(pval(item));
}

PyObject * py_parser::pval(const string & item)
{
  PyObject * pyvalue=PyDict_GetItem(dict,PyString_FromString(item.c_str())); 
  if (pyvalue!=0)
    {
      return(pyvalue);
    }
  else
    {
      cout << item 
	   << " not defined in " 
	   << filename 
	   << " . Aborting... " 
	   << endl;
      exit(1);  
    }
}
