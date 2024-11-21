// Copyright 2024 R(obots) V(ision) and P(erception) group
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

// pybind11
#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/eigen.h>
#include <pybind11/functional.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

// std stuff
#include <Eigen/Core>
#include <memory>
#include <vector>

#include "eigen_stl_bindings.h"
#include "odometry/pipeline.h"

PYBIND11_MAKE_OPAQUE(std::vector<Eigen::Vector3d>);

namespace py11 = pybind11;
using namespace py11::literals;

PYBIND11_MODULE(pypeline, m) {
  auto vector3dvector = pybind_eigen_vector_of_vector<Eigen::Vector3d>(
      m, "VectorEigen3d", "std::vector<Eigen::Vector3d>",
      py11::py_array_to_vectors_double<Eigen::Vector3d>);

  auto pipeline =
      py11::class_<Pipeline>(m, "Pipeline")
          .def(py11::init<double, bool, double, double, double, double, double,
                          int, int, bool>(),
               py11::arg("sensor_hz"), py11::arg("deskew"), py11::arg("b_max"),
               py11::arg("rho_ker"), py11::arg("p_th"), py11::arg("b_min"),
               py11::arg("b_ratio"), py11::arg("num_keyframes"),
               py11::arg("num_threads"), py11::arg("realtime"))
          .def("currentPose", &Pipeline::currentPose)
          .def("trajectory", &Pipeline::trajectory)
          .def("keyframePose", &Pipeline::keyframePose)
          .def("isInitialized", &Pipeline::isInitialized)
          .def("isMapUpdated", &Pipeline::isMapUpdated)
          .def("currentID", &Pipeline::currentID)
          .def("keyframeID", &Pipeline::keyframeID)
          .def("modelLeaves", &Pipeline::modelLeaves)
          .def("currentLeaves", &Pipeline::currentLeaves)
          .def("compute", &Pipeline::compute);
}