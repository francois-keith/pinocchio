//
// Copyright (c) 2019 INRIA
//

#include "pinocchio/math/tensor.hpp"
#include "pinocchio/multibody/model.hpp"

#include <boost/test/unit_test.hpp>
#include <boost/utility/binary.hpp>

#include <iostream>

BOOST_AUTO_TEST_SUITE(BOOST_TEST_MODULE)

BOOST_AUTO_TEST_CASE(test_emulate_tensors)
{
  typedef pinocchio::Tensor<double,3> Tensor;
  
  const Eigen::DenseIndex x_dim = 6, y_dim = 20, z_dim = 20;
  Tensor tensor1(x_dim,y_dim,z_dim);
  
  BOOST_CHECK(tensor1.size() == x_dim * y_dim * z_dim);
  BOOST_CHECK(tensor1.dimension(0) == x_dim);
  BOOST_CHECK(tensor1.dimension(1) == y_dim);
  BOOST_CHECK(tensor1.dimension(2) == z_dim);
  
  double * data = tensor1.data();
  for(Eigen::DenseIndex k = 0; k < tensor1.size(); ++k)
    data[k] = k;
  
  for(Eigen::DenseIndex k = 0; k < z_dim; ++k)
  {
    for(Eigen::DenseIndex j = 0; j < y_dim; ++j)
    {
      for(Eigen::DenseIndex i = 0; i < x_dim; ++i)
      {
        BOOST_CHECK(tensor1(i,j,k) == i + j*x_dim + k*(x_dim*y_dim));
      }
    }
  }
}

BOOST_AUTO_TEST_SUITE_END()
