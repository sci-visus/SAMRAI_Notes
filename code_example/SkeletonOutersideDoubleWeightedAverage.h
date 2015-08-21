/*************************************************************************
 *
 * This file is part of the SAMRAI distribution.  For full copyright
 * information, see COPYRIGHT and COPYING.LESSER.
 *
 * Copyright:     (c) 1997-2014 Lawrence Livermore National Security, LLC
 * Description:   Weighted averaging operator for outerside double data on
 *                a Skeleton mesh.
 *
 ************************************************************************/

#ifndef included_SkeletonOutersideDoubleWeightedAverageXD
#define included_SkeletonOutersideDoubleWeightedAverageXD

#include "SAMRAI/SAMRAI_config.h"
#include "SAMRAI/hier/Box.h"
#include "SAMRAI/hier/IntVector.h"
#include "SAMRAI/hier/Patch.h"
#ifndef included_String
#include <string>
#define included_String
#endif
#include "SAMRAI/hier/CoarsenOperator.h"

#include "boost/shared_ptr.hpp"

using namespace std;
using namespace SAMRAI;

/**
 * Class SkeletonOutersideDoubleWeightedAverage implements conservative
 * side-weighted averaging for outerside double patch data defined over
 * a Skeleton mesh.  It is derived from the hier::CoarsenOperator base class.
 * The numerical operations for theaveraging use FORTRAN numerical routines.
 *
 * @see hier::CoarsenOperator
 */

class SkeletonOutersideDoubleWeightedAverage:
   public hier::CoarsenOperator
{
public:
   /**
    * Uninteresting default constructor.
    */
   SkeletonOutersideDoubleWeightedAverage(
      const tbox::Dimension& dim);

   /**
    * Uninteresting virtual destructor.
    */
   virtual ~SkeletonOutersideDoubleWeightedAverage();

   /**
    * The priority of outerside double weighted averaging is 0.
    * It will be performed before any user-defined coarsen operations.
    */
   int
   getOperatorPriority() const;

   /**
    * The stencil width of the weighted averaging operator is the vector of
    * zeros.  That is, its stencil does not extend outside the fine box.
    */
   hier::IntVector
   getStencilWidth(
      const tbox::Dimension& dim) const;

   /**
    * Coarsen the source component on the fine patch to the destination
    * component on the coarse patch using the outerside double weighted
    * averaging operator.  Coarsening is performed on the intersection of
    * the destination patch and the coarse box.  It is assumed that the
    * fine patch contains sufficient data for the stencil width of the
    * coarsening operator.
    */
   void
   coarsen(
      hier::Patch& coarse,
      const hier::Patch& fine,
      const int dst_component,
      const int src_component,
      const hier::Box& coarse_box,
      const hier::IntVector& ratio) const;

   /**
    * Set the dx, the distance between mesh nodes.
    */
   void
   setDx(
      const int level_number,
      const double* dx);

private:
   /**
    * Return the dx
    */
   void
   getDx(
      const int level_number,
      double* dx) const;

   const tbox::Dimension d_dim;
   std::vector<std::vector<double> > d_dx;

};

#endif
