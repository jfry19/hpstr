/*
 * @file MCTruthMatch.h
 * @author Stany Sevova
 * @date April 3, 2020
 * @brief 
 *
 */

#ifndef __MC_TRUTH_MATCH_H__
#define __MC_TRUTH_MATCH_H__

//----------------//   
//   C++ StdLib   //
//----------------//   
#include <string>
#include <map>
#include <vector>
#include <iostream>

//----------//
//   ROOT   //
//----------//
#include <TFile.h>
#include <TVector3.h>
#include <TRefArray.h>

//------------//
//    HPSTR   //
//------------//
#include <MCParticle.h>
#include <TrackerHit.h>

class MCTruthMatch {
  
 public: 

  /** 
   * Constructor
   *  
   */
  MCTruthMatch(TRefArray* ele_trk_hits, int momToMatchPDG);
  
  /** Destructor */
  ~MCTruthMatch();
  

  std::pair<int,int> getMaxHitsOnTrkMCPair();
  
  bool isRadEle();

  bool isRecEle();
  
  TVector3 getTrueEleP();
  
 private:

  TRefArray* ele_trk_hits_;
  
  int mom_to_match_pdg_;
  
  std::map< int, std::vector<int> > trueHitIDs;

  std::pair <int, int> maxIDHitPair;

  TVector3 tmpTrueEleP;

  std::vector<TrackerHit*>  * hits_{};

  std::vector<MCParticle*>  * mcParts_{};
};

#endif // __MC_TRUTH_MATCH_H__
