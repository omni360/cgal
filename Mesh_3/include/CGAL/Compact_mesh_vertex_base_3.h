// Copyright (c) 2009 INRIA Sophia-Antipolis (France).
// Copyright (c) 2011 GeometryFactory Sarl (France)
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
// $URL: https://scm.gforge.inria.fr/svn/cgal/branches/features/Mesh_3-experimental-GF/Mesh_3/include/CGAL/Compact_mesh_vertex_base_3.h $
// $Id: Compact_mesh_vertex_base_3.h 69674 2012-06-18 09:34:06Z jtournoi $
//
//
// Author(s)     : Stéphane Tayeb, Andreas Fabri
//
//******************************************************************************
// File Description :
//
//
//******************************************************************************


#ifndef CGAL_COMPACT_MESH_VERTEX_BASE_3_H
#define CGAL_COMPACT_MESH_VERTEX_BASE_3_H

#include <CGAL/Triangulation_vertex_base_3.h>
#include <CGAL/Mesh_3/Has_features.h>
#include <CGAL/internal/Mesh_3/get_index.h>
#include <CGAL/Mesh_3/io_signature.h>

namespace CGAL {

// Class Mesh_vertex_base_3
// Vertex base class used in 3D meshing process.
// Adds information to Vb about the localization of the vertex in regards
// to the 3D input complex.
template<class GT,
         class MT,
         class Vb = Triangulation_vertex_base_3<GT> >
class Compact_mesh_vertex_base_3
: public Vb
{
public:
  typedef Vb Cmvb3_base;
  typedef typename Vb::Vertex_handle  Vertex_handle;

  // To get correct vertex type in TDS
  template < class TDS3 >
  struct Rebind_TDS {
    typedef typename Vb::template Rebind_TDS<TDS3>::Other Vb3;
    typedef Compact_mesh_vertex_base_3 <GT, MT, Vb3> Other;
  };

  // Types
  typedef typename MT::Index                      Index;
  typedef typename GT::FT                         FT;

  // Constructor
  Compact_mesh_vertex_base_3()
    : Vb()
    , number_of_incident_facets_(0)
    , number_of_components_(0)
    , index_()
    , meshing_info_(0)
    , dimension_(-1)
    , cache_validity(false)
#ifdef CGAL_INTRUSIVE_LIST
    , next_intrusive_()
    , previous_intrusive_()
#endif //CGAL_INTRUSIVE_LIST
  {}

  // Default copy constructor and assignment operator are ok

  // Returns the dimension of the lowest dimensional face of the input 3D
  // complex that contains the vertex
  int in_dimension() const {
    if(dimension_ < -1) return -2-dimension_;
    else return dimension_; 
  }

  // Sets the dimension of the lowest dimensional face of the input 3D complex
  // that contains the vertex
  void set_dimension(const int dimension) { dimension_ = dimension; }

  // Tells if the vertex is marked as a special protecting ball
  bool is_special() const { return dimension_ < -1; }

  // Marks or unmarks the vertex as a special protecting ball
  void set_special(bool special = true) {
    if(special != (dimension_ < -1) )
      dimension_ = -2-dimension_;
  }

  // Returns the index of the lowest dimensional face of the input 3D complex
  // that contains the vertex
  Index index() const { return index_; }

  // Sets the index of the lowest dimensional face of the input 3D complex
  // that contains the vertex
  void set_index(const Index& index) { index_ = index; }

  // Accessors to meshing_info private data
  const FT& meshing_info() const { return meshing_info_; }
  void set_meshing_info(const FT& value) { meshing_info_ = value; }

#ifdef CGAL_INTRUSIVE_LIST
  Vertex_handle next_intrusive() const { return next_intrusive_; }
  void set_next_intrusive(Vertex_handle v)
  { 
    next_intrusive_ = v;
  }

  Vertex_handle previous_intrusive() const { return previous_intrusive_; }
  void set_previous_intrusive(Vertex_handle v)
  {
    previous_intrusive_ = v; 
  }
#endif

  bool is_c2t3_cache_valid() const {
    return cache_validity;
  }

  void invalidate_c2t3_cache()
  {
    cache_validity = false;
  }

  void set_c2t3_cache(const int i, const int j)
  {
    number_of_incident_facets_ = i;
    number_of_components_ = j;
    cache_validity = true;
  }

  int cached_number_of_incident_facets() const
  {
    return number_of_incident_facets_;
  }
    
  int cached_number_of_components() const
  {
    return number_of_components_;
  }

  static
  std::string io_signature()
  {
    return 
      Get_io_signature<Vb>()() + "+" +
      Get_io_signature<int>()() + "+" +
      Get_io_signature<Index>()();
  }
private:

  int number_of_incident_facets_;
  int number_of_components_; // number of components in the adjacency
  // graph of incident facets (in complex)


  // Index of the lowest dimensional face of the input 3D complex
  // that contains me
  Index index_;
  // Stores info needed by optimizers
  FT meshing_info_;

  // Dimension of the lowest dimensional face of the input 3D complex
  // that contains me. Negative values are a marker for special vertices.
  short dimension_;
  bool cache_validity;
#ifdef CGAL_INTRUSIVE_LIST
  Vertex_handle next_intrusive_;
  Vertex_handle previous_intrusive_;
#endif
};  // end class Compact_mesh_vertex_base_3

namespace internal {
namespace Mesh_3 {
} // end namespace internal::Mesh_3
} // end namespace internal

template<class GT,
         class MT,
         class Vb>
inline
std::istream&
operator>>(std::istream &is, Compact_mesh_vertex_base_3<GT,MT,Vb>& v)
{
  typedef Compact_mesh_vertex_base_3<GT,MT,Vb> Vertex;
  typedef typename Vertex::Cmvb3_base Cmvb3_base;
  is >> static_cast<Cmvb3_base&>(v);
  int dimension;
  if(is_ascii(is)) {
    is >> dimension;

  } else {
    CGAL::read(is, dimension);
  }
  CGAL_assertion(dimension >= 0);
  CGAL_assertion(dimension < 4);
  typename Vertex::Index index = 
    internal::Mesh_3::Read_mesh_domain_index<MT>()(dimension, is);
  v.set_dimension(dimension);
  v.set_index(index);
  return is;
}

template<class GT,
         class MT,
         class Vb>
inline
std::ostream&
operator<<(std::ostream &os, const Compact_mesh_vertex_base_3<GT,MT,Vb>& v)
{
  typedef Compact_mesh_vertex_base_3<GT,MT,Vb> Vertex;
  typedef typename Vertex::Cmvb3_base Cmvb3_base;
  os << static_cast<const Cmvb3_base&>(v);
  if(is_ascii(os)) {
    os << " " << v.in_dimension()
       << " ";
  } else {
    CGAL::write(os, v.in_dimension());
  }
  internal::Mesh_3::Write_mesh_domain_index<MT>()(os, 
                                                  v.in_dimension(),
                                                  v.index());
  return os;
}

}  // end namespace CGAL



#endif // CGAL_COMPACT_MESH_VERTEX_BASE_3_H
