#include <cstdio>
#include <cstdlib>
#include <string>
#include "SAMRAI/hier/VariableDatabase.h"
#include "SAMRAI/hier/PatchLevel.h"
#include "SAMRAI/hier/PatchData.h"
#include "SAMRAI/hier/BoundaryBox.h"
#include "SAMRAI/pdat/CellData.h"

using namespace SAMRAI;

void mergeTreeCompute(boost::shared_ptr< hier::PatchLevel > patch_level,
                      const std::string &variable_name, 
                      const std::string &context_name);
