// Copyright (c) 1998  INRIA Sophia-Antipolis (France).
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
//
// Author(s)     : Manuel Caroli

#include "types.h"

#include<CGAL/Delaunay_triangulation_3.h>
typedef CGAL::Delaunay_triangulation_3<K> Triang;

int main(int argc, char* argv[]) {
  Triang T;
  return bench_triang<Triang>(argc,argv,T,false);
}
 