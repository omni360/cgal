#ifndef CGAL_KERNEL_PREDICATE_OBJECTS_3_H
#define CGAL_KERNEL_PREDICATE_OBJECTS_3_H

#include <CGAL/Kernel/function_objects.h>

CGAL_BEGIN_NAMESPACE

template < class R >
class Kernel_predicate_objects_3
{
public:
typedef typename R::FT                         FT;
typedef typename R::RT                         RT;
typedef typename R::Point_3                    Point_3;
typedef typename R::Vector_3                   Vector_3;
typedef typename R::Direction_3                Direction_3;
typedef typename R::Line_3                     Line_3;
typedef typename R::Plane_3                    Plane_3;
typedef typename R::Ray_3                      Ray_3;
typedef typename R::Segment_3                  Segment_3;
typedef typename R::Triangle_3                 Triangle_3;
typedef typename R::Tetrahedron_3              Tetrahedron_3;
typedef typename R::Aff_transformation_3       Aff_transformation_3;

/* PLEASE FILL IN WITH STEFAN */
};

CGAL_END_NAMESPACE

// This macro is provided for convenience in defining the Kernel
// function objects inside a new representation class.
// See Cartesian_3.h and Cartesian.h

#define CGAL_UNPACK_KERNEL_PREDICATE_OBJECTS_3(PR) 

#endif // CGAL_KERNEL_PREDICATE_OBJECTS_3_H
