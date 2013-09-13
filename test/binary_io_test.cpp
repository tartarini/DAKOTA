/*  _______________________________________________________________________

    DAKOTA: Design Analysis Kit for Optimization and Terascale Applications
    Copyright (c) 2010, Sandia National Laboratories.
    This software is distributed under the GNU Lesser General Public License.
    For more information, see the README file in the top Dakota directory.
    _______________________________________________________________________ */

#include "BinaryIO_Helper.hpp"

#include <boost/assign/std/vector.hpp>

#include <cassert>
#include <iostream>
#include <string>

using namespace boost::assign;
using namespace Dakota;

#define RANK 2

int main()
{
  double rval_out = 3.14159, rval_in = 0.0;
  int ival_out = 314159, ival_in = 0;
  std::string pi_tag("/DakPi");
  std::string file_name("binary_io_test.h5");

  std::vector<hsize_t> rdims;
  rdims += 2, 2;
  std::vector<hsize_t> idims;
  idims += 3;

  RealMatrix rmatrix_out(rdims[0], rdims[1]);
  rmatrix_out(0, 0) = rval_out;
  rmatrix_out(0, 1) = 0.23;
  rmatrix_out(1, 0) = 0.23;
  rmatrix_out(1, 1) = rval_out;

  std::vector<int> ivec_out;
  ivec_out += ival_out, 23, 333;
  hsize_t isize = ivec_out.size();

  assert(rdims.size() == RANK);
  assert(rmatrix_out.numRows() == 2);
  assert(rmatrix_out.numCols() == 2);
  assert(rval_out == rmatrix_out(0, 0));
  assert(rval_out == rmatrix_out(1, 1));
  assert(ival_out == ivec_out[0]);
  assert(isize == 3);

  bool file_exist = false;
  bool read_only = false;
  herr_t status;

  // WJB - ToDo: split out into functions

  // scope within which file write takes place
  {
    // open/create file
    SimpleBinaryStream binary_file(file_name, file_exist, read_only);
    
    //binary_File.addVar(pi_tag, rval_out);

    // write data 
    // single value
#if 1
    // WJB: hack to make a single value look like an array of len==1
    std::vector<double> dummy_buf;
    dummy_buf += rval_out;

    std::vector<hsize_t> dummy_dims;
    dummy_dims += 1;
    // WJB: assertions should be replaced with "exceptions" in store_data
    assert(dummy_dims.size() == 1);
    assert(dummy_dims[0]     == 1);

    status = binary_file.store_data<double,1>(pi_tag.c_str(), dummy_dims,
               dummy_buf);
    assert(status >= 0);
#else
    herr_t status = binary_file.store_data(pi_tag.c_str(), rval_out);
#endif

    // RealMatrix
    status = binary_file.store_data("/RealMatrixData", rmatrix_out);
    assert(status >= 0);

    // std::vector<int>
    status = binary_file.store_data<int, 1>("/IntVectorData", idims, ivec_out);
    assert(status >= 0);

    // binary stream goes out of scope... (file close)
  }

  // WJB - ToDo: split out into functions

  // scope within which file read takes place
  {
    // open/read file
    file_exist = true;
    read_only = true;
    SimpleBinaryStream binary_file(file_name, file_exist, read_only);
  
    // read data 
    // WJB:  Easy via NetCDF4! binary_File.getVar(pi_tag.c_str(), rval_in);

    //RealMatrix rmatrix_in;

    //herr_t status = binary_file.read_data<double, RANK>("/RealMatrixData",
                      //rmatrix_in);
    //assert(status >= 0);
    //assert(rmatrix_in(0, 0) == rmatrix_out(0, 0));

    std::vector<int> ivec_in;
    status = binary_file.read_data<int, 1>("/IntVectorData", ivec_in);
    assert(status >= 0);

    assert( ivec_in.size()   == ivec_out.size() );
    assert( ivec_in[isize-1] == ivec_out[isize-1] );
    assert( ivec_in[0]       == ivec_out[0] );
  }

  //assert(rval_in == rval_out);

  return status;
}
