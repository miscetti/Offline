//
// This module loops over the data products in the event
// and makes a set of standard validation histograms
// for instances of products it knows about
//
// Ray Culbertson
// 

#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Services/Optional/TFileService.h"
#include "Validation/inc/ValGenParticle.hh"
#include "Validation/inc/ValSimParticle.hh"
#include "Validation/inc/ValStepPointMC.hh"
#include "Validation/inc/ValCaloCrystalHit.hh"
#include "Validation/inc/ValCaloCluster.hh"
#include "Validation/inc/ValStrawHit.hh"
#include "Validation/inc/ValTrackSummary.hh"
#include "Validation/inc/ValTrackClusterMatch.hh"

namespace mu2e {

  class Validation : public art::EDAnalyzer {

  public:

    explicit Validation(fhicl::ParameterSet const& );
    void analyze  ( art::Event const&  event  ) override;
    void beginJob () override;
    void endJob () override;

  private:

    int _level;   // level=1 is a small number of histograms, 2 is more
    int _count;   // event count

    // ValXYZ are classes which contain a set of histograms for 
    // validation of product XYZ.  They are in vectors, since we usually
    // have several instances of a product and we make histograms 
    // for each instance.
    std::vector<std::shared_ptr<ValGenParticle>>       _genp;
    std::vector<std::shared_ptr<ValSimParticle>>       _simp;
    std::vector<std::shared_ptr<ValStepPointMC>>       _spmc;
    std::vector<std::shared_ptr<ValCaloCrystalHit>>    _calh;
    std::vector<std::shared_ptr<ValCaloCluster>>       _ccls;
    std::vector<std::shared_ptr<ValStrawHit>>          _stwh;
    std::vector<std::shared_ptr<ValTrackSummary>>      _trks;
    std::vector<std::shared_ptr<ValTrackClusterMatch>> _mtch;

    // Loop over the products of type T and 
    // call fill() on validation histogram class V to make histograms.
    // It will create the root file subdirectories and 
    // histograms on the first event
    template<class T, class V> int analyzeProduct(
	 std::vector<std::shared_ptr<V>>& list,
	  art::Event const& event);

    art::ServiceHandle<art::TFileService> _tfs;

  };

}

mu2e::Validation::Validation(fhicl::ParameterSet const& pset ):
  art::EDAnalyzer(pset),
  _level(0),_count(0){
  _level = pset.get<int>("validation_level");

}

void mu2e::Validation::beginJob(){

}

void mu2e::Validation::analyze(art::Event const& event){
  analyzeProduct<GenParticleCollection,ValGenParticle>        (_genp,event);
  analyzeProduct<SimParticleCollection,ValSimParticle>        (_simp,event);
  analyzeProduct<StepPointMCCollection,ValStepPointMC>        (_spmc,event);
  analyzeProduct<CaloCrystalHitCollection,ValCaloCrystalHit>  (_calh,event);
  analyzeProduct<CaloClusterCollection,ValCaloCluster>        (_ccls,event);
  analyzeProduct<StrawHitCollection,ValStrawHit>              (_stwh,event);
  analyzeProduct<TrackSummaryCollection,ValTrackSummary>      (_trks,event);
  analyzeProduct<TrackClusterMatchCollection,ValTrackClusterMatch>(_mtch,event);
}


void mu2e::Validation::endJob () {

  std::cout << "end Validation::endJob summary" << std::endl;

}

// make histograms for product type T by calling fill() on 
// histogram class V
template <class T, class V>
int mu2e::Validation::analyzeProduct(
    std::vector<std::shared_ptr<V>>& list,
    art::Event const& event) {

  // get all instances of products of type T
  std::vector<art::Handle< T >> vah;
  event.getManyByType(vah);

  std::string name;
  // loop over the list of instances of products of this type
  for (auto const & ah : vah) {
    const art::Provenance* prov = ah.provenance();

    // the name of the root file directory holding these histos
    // is the className_moduleName_InstanceName for the instance
    std::string inst = prov->productInstanceName();
    if(inst.size()==0) inst="noName";
    name = prov->friendlyClassName()+"_"+
      prov->moduleLabel()+"_"+ inst;
    if(name.find("mu2e::",0)==0) name.erase(0,6);

    // see if this instance of this product is already in our list 
    // of products being histogrammed.  If not, add it to the list
    std::shared_ptr< V > prd = nullptr;
    for (auto ptr : list ) {
      // if this instance of this product found in the list
      if(ptr->name().compare(name)==0)  prd = ptr;
    }
    // if not in the list, create a new set of histograms 
    // for this product
    if ( prd == nullptr ) {
      prd = std::make_shared<V>(name);
      // create root file subdirectory
      art::TFileDirectory tfdir = _tfs->mkdir(name);
      // create histograms
      prd->declare(tfdir);
      // add it to the list of products being histogrammed
      list.push_back( prd );
    }
    // histogram this event for this product instance
    prd->fill(*ah, event);
  }
  return 0;
}


DEFINE_ART_MODULE(mu2e::Validation)