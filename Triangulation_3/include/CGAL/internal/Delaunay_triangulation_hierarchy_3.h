// Copyright (c) 2009   INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL$
// $Id$
//
// Author(s)     : Sylvain Pion

#ifndef CGAL_INTERNAL_DELAUNAY_TRIANGULATION_HIERARCHY_3_H
#define CGAL_INTERNAL_DELAUNAY_TRIANGULATION_HIERARCHY_3_H

#if !defined CGAL_DELAUNAY_TRIANGULATION_3_H
#  error  "Other header files need to be included first..."
#endif

#include <CGAL/Triangulation_hierarchy_3.h>

namespace CGAL {

// Specializations of Delaunay_triangulation_3 for Fast_location,
// as 2nd as well as 3rd positions (deduced parameter).

#define CGAL_TDS_3 \
typename Default::Get<Tds, Triangulation_data_structure_3 <\
	                   Triangulation_vertex_base_3<Gt>,\
	                   Triangulation_cell_base_3<Gt> > >::type

template < class Gt, class Tds >
class Delaunay_triangulation_3<Gt, Tds, Fast_location>
  : public Triangulation_hierarchy_3<Delaunay_triangulation_3<Gt,
      CGAL_TDS_3::template Rebind_vertex<Triangulation_hierarchy_vertex_base_3<CGAL_TDS_3::Vertex> >::Other> >
{
    typedef Triangulation_hierarchy_3<Delaunay_triangulation_3<Gt,
      CGAL_TDS_3::template Rebind_vertex<Triangulation_hierarchy_vertex_base_3<CGAL_TDS_3::Vertex> >::Other> >  Base;

public:

    Delaunay_triangulation_3(const Gt& traits = Gt())
      : Base(traits) {}

    template < typename InputIterator >
    Delaunay_triangulation_3(InputIterator first, InputIterator last,
                             const Gt& traits = Gt())
      : Base(first, last, traits) {}
};

#undef CGAL_TDS_3

template < class Gt, class Tds >
class Delaunay_triangulation_3<Gt, Tds, Compact_location>
  : public Delaunay_triangulation_3<Gt, Tds>
{
    typedef Delaunay_triangulation_3<Gt, Tds> Base;

public:

    Delaunay_triangulation_3(const Gt& traits = Gt())
      : Base(traits) {}

    template < typename InputIterator >
    Delaunay_triangulation_3(InputIterator first, InputIterator last,
                             const Gt& traits = Gt())
      : Base(first, last, traits) {}
};

// 2 cases for Location_policy<> in 2nd position.

template < class Gt >
class Delaunay_triangulation_3<Gt, Fast_location>
  : public Triangulation_hierarchy_3<Delaunay_triangulation_3<Gt,
             Triangulation_data_structure_3< Triangulation_hierarchy_vertex_base_3<Triangulation_vertex_base_3<Gt> >,
	                                     Triangulation_cell_base_3<Gt> > > >
{
    typedef Triangulation_hierarchy_3<Delaunay_triangulation_3<Gt,
             Triangulation_data_structure_3< Triangulation_hierarchy_vertex_base_3<Triangulation_vertex_base_3<Gt> >,
	                                     Triangulation_cell_base_3<Gt> > > >  Base;

public:

    Delaunay_triangulation_3(const Gt& traits = Gt())
      : Base(traits) {}

    template < typename InputIterator >
    Delaunay_triangulation_3(InputIterator first, InputIterator last,
                             const Gt& traits = Gt())
      : Base(first, last, traits) {}
};

template < class Gt >
class Delaunay_triangulation_3<Gt, Compact_location>
  : public Delaunay_triangulation_3<Gt>
{
    typedef Delaunay_triangulation_3<Gt> Base;

public:

    Delaunay_triangulation_3(const Gt& traits = Gt())
      : Base(traits) {}

    template < typename InputIterator >
    Delaunay_triangulation_3(InputIterator first, InputIterator last,
                             const Gt& traits = Gt())
      : Base(first, last, traits) {}
};

} // namespace CGAL

#endif // CGAL_INTERNAL_DELAUNAY_TRIANGULATION_HIERARCHY_3_H