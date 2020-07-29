#ifndef CaloConditions_CaloDAQConditionsMaker_hh
#define CaloConditions_CaloDAQConditionsMaker_hh

//
// construct a CaloDAQConditions conditions entity
// from fcl or database
//

#include "CaloConditions/inc/CaloDAQConditions.hh"
#include "CaloConditions/inc/CaloDAQConditionsConfig.hh"
#include "DbTables/inc/DIRACtoCalo.hh"
#include "DbTables/inc/CalotoDIRAC.hh"


namespace mu2e {

  class CaloDAQConditionsMaker {
  public:
    CaloDAQConditionsMaker(CaloDAQConditionsConfig const& config):_config(config) {}
    CaloDAQConditions::ptr_t fromFcl();
    CaloDAQConditions::ptr_t fromDb(DIRACtoCalo::cptr_t tdtc,
				    CalotoDIRAC::cptr_t tctd );
  
  private:

    // this object needs to be thread safe, 
    // _config should only be initialized once
    const CaloDAQConditionsConfig _config;

  };
}


#endif

