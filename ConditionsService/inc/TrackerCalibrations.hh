#ifndef ConditionsService_TrackerCalibrations_hh
#define ConditionsService_TrackerCalibrations_hh
//
// Parameters for tracker calibrations.
//
// $Id: TrackerCalibrations.hh,v 1.4 2011/12/02 11:52:32 brownd Exp $
// $Author: brownd $
// $Date: 2011/12/02 11:52:32 $
//
// Original author Vadim Rusu
//

// C++ includes.
#include <iostream>

// Mu2e includes.
#include "ConditionsService/inc/ConditionsEntity.hh"
#include "TrackerGeom/inc/StrawIndex.hh"
#include "CLHEP/Vector/ThreeVector.h"

namespace mu2e
{
  class SimpleConfig;
  class StrawHit;


  struct TrackerCalibrations: public ConditionsEntity{


    TrackerCalibrations ( SimpleConfig const& config );

    // Accept compiler generated:
    // copy c'tor, d'tor and assignment operator.

    const double TimeDivisionResolution(StrawIndex strawIndex, double znorm) const;
    const double SignalVelocity(StrawIndex strawIndex) const;

    //this shoule be called by the patt rec
    const double TimeDiffToDistance(StrawIndex strawIndex, double deltaT) const;
    
    // information about a hit's position and time.  This uses time difference to compute
    // the position along the wire
    void StrawHitInfo(StrawHit const& strawhit,
      CLHEP::Hep3Vector& pos, double& time,double& tdres, double& timeres) const;

  private:

    // We want to discourage multi-phase construction.
    TrackerCalibrations ();

    // time-division base resolution and length-dependent quadratic term
    double _resopar0;
    double _resopar1;


  };

  // Shift left (printing) operator.
  inline std::ostream& operator<<(std::ostream& ost,
                                  const TrackerCalibrations& daqpar ){
    ost << "( "
        << " )";

    return ost;
  }
}

#endif /* ConditionsService_TrackerCalibrations_hh */
