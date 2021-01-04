//
// Copyright (c) 2016-2020 CNRS INRIA
//

#ifndef __pinocchio_python_frame_hpp__
#define __pinocchio_python_frame_hpp__

#include "pinocchio/multibody/fwd.hpp"
#include "pinocchio/multibody/frame.hpp"
#include "pinocchio/bindings/python/utils/copyable.hpp"
#include "pinocchio/bindings/python/utils/printable.hpp"

namespace pinocchio
{
  namespace python
  {
    namespace bp = boost::python;

    struct FramePythonVisitor
      : public boost::python::def_visitor< FramePythonVisitor >
    {
      template<class PyClass>
      void visit(PyClass& cl) const 
      {
        cl
          .def(bp::init<>(bp::arg("self"),"Default constructor"))
          .def(bp::init<const Frame &>(bp::args("self","other"),"Copy constructor"))
          .def(bp::init< const std::string&,const JointIndex, const FrameIndex, const SE3&,FrameType> ((bp::arg("name (string)"),bp::arg("index of parent joint"), bp::args("index of parent frame"), bp::arg("SE3 placement"), bp::arg("type (FrameType)")),
                "Initialize from name, parent joint id, parent frame id and placement wrt parent joint."))

          .def_readwrite("name", &Frame::name, "name  of the frame")
          .def_readwrite("parent", &Frame::parent, "id of the parent joint")
          .def_readwrite("previousFrame", &Frame::previousFrame, "id of the previous frame") 
          .def_readwrite("placement",
                         &Frame::placement,
                         "placement in the parent joint local frame")
          .def_readwrite("type", &Frame::type, "type of the frame")
          .def(bp::self == bp::self)
          ;
      }
      
      static void expose()
      {
        bp::enum_<FrameType>("FrameType")
            .value("OP_FRAME",OP_FRAME)
            .value("JOINT",JOINT)
            .value("FIXED_JOINT",FIXED_JOINT)
            .value("BODY",BODY)
            .value("SENSOR",SENSOR)
            .export_values()
            ;

        bp::class_<Frame>("Frame",
                          "A Plucker coordinate frame related to a parent joint inside a kinematic tree.\n\n",
                          bp::no_init
                         )
        .def(FramePythonVisitor())
        .def(CopyableVisitor<Frame>())
        .def(PrintableVisitor<Frame>())
        .def_pickle(Pickle())
        ;
      }

    private:
      struct Pickle : bp::pickle_suite
      {
        static bp::tuple getinitargs(const Frame & f)
        {
          return bp::make_tuple();
        }

        static bp::tuple getstate(const Frame & f)
        {
          return bp::make_tuple(f.name, f.parent, f.previousFrame, f.placement, (int)f.type);
        }

        static void setstate(Frame & f, bp::tuple tup)
        {
          f.name = bp::extract<std::string>(tup[0]); 
          f.parent = bp::extract<JointIndex>(tup[1]); 
          f.previousFrame = bp::extract<JointIndex>(tup[2]); 
          f.placement = bp::extract<SE3&>(tup[3]); 
          f.type = (FrameType)(int)bp::extract<int>(tup[4]); 
        }
      };
    };
    

  } // namespace python
} // namespace pinocchio

#endif // ifndef __pinocchio_python_frame_hpp__
