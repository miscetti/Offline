#ifndef ProtoStrawCluster_hh
#define ProtoStrawCluster_hh
//
// A crude step along the way to forming real clusters.
//
// $Id: ProtoStrawCluster.hh,v 1.3 2010/03/23 20:28:02 kutschke Exp $
// $Author: kutschke $
// $Date: 2010/03/23 20:28:02 $
//
//
#include <vector>

#include "TrackerGeom/inc/SectorId.hh"

namespace mu2e {

  struct ProtoStrawCluster{

    SectorId id;
    std::vector<int32_t> hitIndices;

    ProtoStrawCluster( SectorId const& sectorId, int index);
    
    void add( int idx){
      hitIndices.push_back(idx);
    }

    int size() const{ return hitIndices.size(); }

    //int operator[]( int i) const { return hitIndices[i]; }

    int at( int i) const { return hitIndices.at(i); }
    
  };

}

#endif
