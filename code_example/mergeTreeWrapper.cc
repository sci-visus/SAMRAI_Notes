#include "mergeTreeWrapper.h"
                      

using namespace SAMRAI;


void mergeTreeCompute(boost::shared_ptr< hier::PatchLevel > patch_level,
                      const std::string &variable_name, 
                      const std::string &context_name) {

  std::cout << "Hello SAMRAI\n";
  const boost::shared_ptr<hier::Variable> variable = 
        hier::VariableDatabase::getDatabase()->getVariable(variable_name);
  const boost::shared_ptr<hier::VariableContext> context =
        hier::VariableDatabase::getDatabase()->getContext(context_name);
                  
  int id = hier::VariableDatabase::getDatabase()->
                 mapVariableAndContextToIndex(variable,context);
  
  std::cout << "variable : " << variable->getName() << " context : " << context->getIndex() 
            << " ID : " << id << "\n";

  std::cout << "Num patches: " << patch_level->getNumberOfPatches() << "\n";
  hier::PatchLevel::Iterator p_it = patch_level->begin();
  
  for (p_it = patch_level->begin(); p_it != patch_level->end(); p_it++) {
    
    std::cout << "num patch data:: " << p_it->numPatchData() << "\n";

    boost::shared_ptr<pdat::CellData<double> > d_vol(
            BOOST_CAST<pdat::CellData<double>, hier::PatchData>(
            p_it->getPatchData(variable, context)));

    std::cout << p_it->getBox() << " box id :: " << p_it->getBox().getBoxId() << "\n";
    //p_it->getPatchGeometry()->printClassData(std::cout);
    //const std::vector<std::vector<hier::BoundaryBox> > boudaries =  p_it->getPatchGeometry()->getPatchBoundaries();
    const std::vector<std::vector<hier::BoundaryBox> > boudaries =  p_it->getPatchGeometry()->getPatchBoundaries();
    const std::vector<hier::BoundaryBox> n_boundaries =  p_it->getPatchGeometry()->getFaceBoundaries();
    
    std::cout << "ghost box: "<< d_vol->getGhostBox() << "\n";
    std::cout << "ghost cell width: "<< d_vol->getGhostCellWidth() << "\n";

    //for (int i=0; i<n_boundaries.size(); i++)
      //std::cout << n_boundaries[i].getBox() << "\n";
  //tbox::pout << "vol: " << 
    //d_vol->print(p_it->getBox());
  //BOOST_CAST<pdat::CellData<double>, hier::PatchData>(p_data)->print(p_it->getBox());
  }

}
