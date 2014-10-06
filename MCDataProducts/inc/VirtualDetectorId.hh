#ifndef MCDataProducts_VirtualDetectorId_hh
#define MCDataProducts_VirtualDetectorId_hh
//
// An enum-matched-to-names class for virtual detector Id's.
//
// $Id: VirtualDetectorId.hh,v 1.21 2014/06/09 23:14:33 genser Exp $
// $Author: genser $
// $Date: 2014/06/09 23:14:33 $
//
// Original author Rob Kutschke
//
// Notes:
// 1) The enum_type must be in the class to avoid clashes with
//    similar classes that are modelled on this.  In particular
//    unknown and lastEnum will clash.
//
// 2) I do want both the name() operator and the << operator.
//    If only <<, then users will need to make temp ostringsteams
//    if they want to do their own formatting.
//
// 3) Root always stores enum types as 32 bit ints, regardless of
//    native word length on a machine.
//

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

namespace mu2e {

  class VirtualDetectorId {

  public:

    // Need to keep the enum and the following MACRO in sync.
    enum enum_type {
      unknown,                                                // 0:       If you see this, the object was not properly initialized.
      Coll1_In,       Coll1_Out,                              // 1,2:     Surround the collimator in TS1
      Coll31_In,      Coll31_Out, Coll32_In, Coll32_Out,      // 3,4,5,6: Surround the two pieces of the collimator in TS3
      Coll5_In,       Coll5_Out,                              // 7,8:     Surround the collimator in TS5
      ST_In,          ST_Out,                                 // 9,10:    Surround the stopping target foils.
      TT_Mid,         TT_MidInner,                            // 11, 12:  Middle of the tracker
      TT_FrontHollow, TT_FrontPA,                             // 13, 14:  Front face of the tracker.
      TT_Back,                                                // 15       Back (downstream) face of the tracker.
      EMFC1Entrance,  EMFC1Exit, EMFC2Entrance,  EMFC2Exit,   // 16-19:   ExtMonFNAL collimator entrance and exit planes
      PS_FrontExit,                                           // 20:      Front exit (to beam dump) on PS
      EMIEntrance1,                                           // 21:      In front of ExtMonUCI front removable concreate shielding
      TT_OutSurf, TT_InSurf,                                  // 22-23:   external and internal surface of the TTracker envelope
      EMIEntrance2,                                           // 24:      Between ExtMonUCI front removable shielding and front shielding
      EMIC0Entrance,  EMIC0Exit, EMIC1Entrance,  EMIC1Exit,   // 25-28:   In ExtMonUCI
      EMIC2Entrance,  EMIC2Exit, EMIC3Entrance,  EMIC3Exit,   // 29-32:   4 collimator entrance and exit planes
      ExtMonCommonPlane,                                      //    33:   An XY plane between the PS and anything ExtMon
      ProtonBeamDumpCoreFace,                                 //    34
      EMFDetectorUpEntrance, EMFDetectorUpExit,               // 35,36
      Coll5_OutSurf,                                          // 37       Surround the outer cyl. surface of collimator in TS5
      EMFDetectorDnEntrance, EMFDetectorDnExit,               // 38,39
      EMFBoxFront, EMFBoxSW, EMFBoxBottom,                    // 40, 41, 42
      EMFBoxBack, EMFBoxNE, EMFBoxTop,                        // 43, 44, 45
      IT_VD_EndCap_Front,  IT_VD_EndCap_Back,                 // 46, 47:  Front and Back parts of the tracker
      IT_VD_InSurf,                                           // 48:      external and internal surface of the ITracker envelope
      //the following virtual detectors are related to the vane calorimeter:
      //the first number after EMC_ is the vane id, according to the convention used in the calorimeter geom
      //Front indicates the vane planes which are in the x-y plane: 
      // (-) FrontIn is the one nearest to the Tracker, FrontOut is the one nearest to the beam-stop
      //Edge indicates the vane planes in the y-z plane:
      //(-) EdgeIn is the one nearest to the beam line, EdgeOut is the one far away
      //Surf indicates the vane planes in the x-z plane
      //(-) SurfIn is the one in the opposite side of the vane RO, SurfOut is the one in the vane RO plane
      EMC_0_FrontIn, EMC_0_FrontOut, EMC_1_FrontIn, EMC_1_FrontOut, // 49, 50, 51, 52
      EMC_2_FrontIn, EMC_2_FrontOut, EMC_3_FrontIn, EMC_3_FrontOut,// 53, 54, 55, 56
      EMC_0_EdgeIn, EMC_0_EdgeOut, EMC_1_EdgeIn, EMC_1_EdgeOut, // 57, 58, 59, 60
      EMC_2_EdgeIn, EMC_2_EdgeOut, EMC_3_EdgeIn, EMC_3_EdgeOut, // 61, 62, 63, 64 
      EMC_0_SurfIn, EMC_0_SurfOut, EMC_1_SurfIn, EMC_1_SurfOut, // 65, 66, 67, 68
      EMC_2_SurfIn, EMC_2_SurfOut, EMC_3_SurfIn, EMC_3_SurfOut, // 69, 70, 71, 72
      EMC_Disk_0_SurfIn, EMC_Disk_0_SurfOut, EMC_Disk_1_SurfIn, EMC_Disk_1_SurfOut,// 73, 74, 75, 76
      EMC_Disk_0_EdgeIn, EMC_Disk_0_EdgeOut, EMC_Disk_1_EdgeIn, EMC_Disk_1_EdgeOut,// 77, 78, 79,80
      DSNeutronShieldExit, // 81
      PSTargetSurf, // 82
      PT_Front, PT_Back,                         // 83, 84:  Forward and backward side of the production targets
      STMUpstream,                  // 85:  I'm not sure who named this STM, because it's not in the MSTM area (FIXME)
      MSTM_WallUpStr, MSTM_Coll1DnStr, MSTM_ShutterDnStr, MSTM_Coll2DnStr, MSTM_Coll3DnStr,  // 86, 87, 88, 89, 90:  All inside MSTM area
      lastEnum
    };

    // Keep this in sync with the enum. Used in VirtualDetectorId.cc
#define VIRTUALDETECTORID_NAMES						\
    "unknown",								\
      "Coll1_In",       "Coll1_Out",					\
      "Coll31_In",      "Coll31_Out",  "Coll32_In", "Coll32_Out",	\
      "Coll5_In",       "Coll5_Out",					\
      "ST_In",          "ST_Out",					\
      "TT_Mid",         "TT_MidInner",					\
      "TT_FrontHollow", "TT_FrontPA",					\
      "TT_Back",							\
      "EMFC1Entrance", "EMFC1Exit", "EMFC2Entrance", "EMFC2Exit",	\
      "PS_FrontExit",							\
      "EMIEntrance1",							\
      "TT_OutSurf", "TT_InSurf",					\
      "EMIEntrance2",							\
      "EMIC0Entrance", "EMIC0Exit", "EMIC1Entrance", "EMIC1Exit",	\
      "EMIC2Entrance", "EMIC2Exit", "EMIC3Entrance", "EMIC3Exit",	\
      "ExtMonCommonPlane",						\
      "ProtonBeamDumpCoreFace",						\
      "EMFDetectorUpEntrance", "EMFDetectorUpExit",			\
      "Coll5_OutSurf",							\
      "EMFDetectorDnEntrance", "EMFDetectorDnExit",			\
      "EMFBoxFront", "EMFBoxSW", "EMFBoxBottom",			\
      "EMFBoxBack", "EMFBoxNE", "EMFBoxTop",				\
      "IT_VD_EndCap_Front",     "IT_VD_EndCap_Back",			\
      "IT_VD_InSurf",							\
      "EMC_0_FrontIn", "EMC_0_FrontOut", "EMC_1_FrontIn", "EMC_1_FrontOut", \
      "EMC_2_FrontIn", "EMC_2_FrontOut", "EMC_3_FrontIn", "EMC_3_FrontOut", \
      "EMC_0_EdgeIn", "EMC_0_EdgeOut", "EMC_1_EdgeIn", "EMC_1_EdgeOut", \
      "EMC_2_EdgeIn", "EMC_2_EdgeOut", "EMC_3_EdgeIn", "EMC_3_EdgeOut", \
      "EMC_0_SurfIn", "EMC_0_SurfOut", "EMC_1_SurfIn", "EMC_1_SurfOut", \
      "EMC_2_SurfIn", "EMC_2_SurfOut", "EMC_3_SurfIn", "EMC_3_SurfOut", \
      "EMC_Disk_0_SurfIn", "EMC_Disk_0_SurfOut","EMC_Disk_1_SurfIn", "EMC_Disk_1_SurfOut", \
      "EMC_Disk_0_EdgeIn", "EMC_Disk_0_EdgeOut","EMC_Disk_1_EdgeIn", "EMC_Disk_1_EdgeOut", \
      "DSNeutronShieldExit", \
      "PSTargetSurf", \
      "PT_Front", "PT_Back","STMUpstream", \
      "MSTM_WallUpStr", "MSTM_Coll1DnStr", "MSTM_ShutterDnStr", "MSTM_Coll2DnStr", "MSTM_Coll3DnStr"

  public:

    // The most important c'tor and accessor methods are first.
    explicit VirtualDetectorId( enum_type id):
      _id(id)
    {}

    enum_type id() const { return _id;}

    // Member function version of the name function.
    std::string const& name() const {
      return name(_id);
    }

    // The enum values come in pairs.  Provide tests for membership in a pair.
    bool isColl1() const {
      return ( _id == Coll1_In || _id == Coll1_Out );
    }

    bool isColl3() const {
      return ( _id == Coll31_In || _id == Coll31_Out  ||
               _id == Coll32_In || _id == Coll32_Out );
    }

    bool isColl5() const {
      return ( _id == Coll5_In || _id == Coll5_Out );
    }

    bool isStoppingTarget() const {
      return ( _id == ST_In || _id == ST_Out );
    }

    bool isTrackerMid() const {
      return ( _id == TT_Mid || _id == TT_MidInner || _id == IT_VD_InSurf );
    }

    bool isTrackerFront() const {
      return ( _id == TT_FrontHollow || _id == TT_FrontPA || _id == IT_VD_EndCap_Front );
    }

    bool isTrackerBack() const {
      return ( _id == TT_Back || _id == IT_VD_EndCap_Back );
    }

    bool isVaneCalorimeter0() const{
      return (_id == EMC_0_FrontIn || _id == EMC_0_FrontOut || _id == EMC_0_EdgeIn || 
	      _id == EMC_0_EdgeOut || _id == EMC_0_SurfIn   || _id == EMC_0_SurfOut);
    }
    bool isVaneCalorimeter1() const{
      return (_id == EMC_1_FrontIn || _id == EMC_1_FrontOut || _id == EMC_1_EdgeIn || 
	      _id == EMC_1_EdgeOut || _id == EMC_1_SurfIn   || _id == EMC_1_SurfOut );
    }
    bool isVaneCalorimeter2() const{
      return ( _id == EMC_2_FrontIn || _id == EMC_2_FrontOut || _id == EMC_2_EdgeIn || 
	       _id == EMC_2_EdgeOut || _id == EMC_2_SurfIn   || _id == EMC_2_SurfOut);
    }
    bool isVaneCalorimeter3() const{
      return ( _id == EMC_3_FrontIn || _id == EMC_3_FrontOut || _id == EMC_3_EdgeIn || 
	       _id == EMC_3_EdgeOut || _id == EMC_3_SurfIn   || _id == EMC_3_SurfOut);
    }
    
    bool isDiskCalorimeter0() const{
      return (_id == EMC_Disk_0_SurfIn || _id == EMC_Disk_0_SurfOut || _id == EMC_Disk_0_EdgeIn || _id == EMC_Disk_0_EdgeOut);
    }
    
    bool isDiskCalorimeter1() const{
      return ( _id == EMC_Disk_1_SurfIn || _id == EMC_Disk_1_SurfOut || _id == EMC_Disk_1_EdgeIn || _id == EMC_Disk_1_EdgeOut);
    }

    bool isPSTargetSurf() const{
      return (_id == PSTargetSurf);
    }
    
    // ROOT requires a default c'tor.
    VirtualDetectorId():
      _id(unknown){
    }

    // Need this to interface with legacy code; prefer to remove it if possible.
    explicit VirtualDetectorId( int id):
      _id(static_cast<enum_type>(id)){
      isValidorThrow(_id);
    }

    virtual ~VirtualDetectorId(){}

    // This operator implements:
    //   VirtualDetectorId a;
    //   enum_type b;
    // a = b;
    VirtualDetectorId& operator=(VirtualDetectorId::enum_type const& c){
      _id = c;
      return *this;
    }

    // This operator implements:
    //   VirtualDetectorId a;
    //   enum_type b = a;
    operator VirtualDetectorId::enum_type ()const{
      return _id;
    }

    // Comparison operators
    bool operator==(const VirtualDetectorId g) const{
      return ( _id == g._id );
    }

    bool operator==(const VirtualDetectorId::enum_type g) const{
      return ( _id == g );
    }

    // Static version of the name method.
    static std::string const& name( enum_type id );

    // Get a vector of all known names.
    static std::vector<std::string> const& names();

    // Check validity of an Id.
    static bool isValid( enum_type id){
      if ( id <   unknown ) return false;
      if ( id >= lastEnum ) return false;
      return true;
    }

    // Check validity and throw if invalid.
    static bool isValidorThrow( enum_type id);

    // Print all known values and their names.
    static void printAll( std::ostream& ost = std::cout);

    // Member function version of static functions.
    bool isValid() const{
      return isValid(_id);
    }

  private:

    // The one and only per-instance member datum.
    enum_type _id;

  };

  // Shift left (printing) operator.
  inline std::ostream& operator<<(std::ostream& ost,
                                  const VirtualDetectorId& id ){
    ost << "( "
        << id.id() << ": "
        << id.name()
        << " )";
    return ost;
  }

}

#endif /* MCDataProducts_VirtualDetectorId_hh */
