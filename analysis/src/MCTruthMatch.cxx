/*
 * @file MCTruthMatch.cxx
 * @author PF
 * @author Cam
 * @author Stany 
 * @date April 3, 2020
 * @brief 
 *
 */

#include <MCTruthMatch.h>


MCTruthMatch::MCTruthMatch(TRefArray* ele_trk_hits, int momToMatchPDG)
  : ele_trk_hits_(ele_trk_hits),
    mom_to_match_pdg_(momToMatchPDG) { }

MCTruthMatch::~MCTruthMatch() { }

std::pair< int, int > MCTruthMatch::getMaxHitsOnTrkMCPair()
{
  //Build map of hits and the associated MC Particle IDs for later
  for(int i = 0; i < hits_->size(); i++)
  {
    TrackerHit* hit = hits_->at(i);
    trueHitIDs[hit->getID()] = hit->getMCPartIDs();
  }

  //Store number of hits-on-track for each MC particle
  std::map < int, int > nHitsPerMCPart;
  for(int i = 0; i < ele_trk_hits_->GetEntries(); i++)
  {
    TrackerHit* eleHit = (TrackerHit*)ele_trk_hits_->At(i);
    for(int idI = 0; idI < trueHitIDs[eleHit->getID()].size(); idI++ )
    {
      int partID = trueHitIDs[eleHit->getID()].at(idI);
      if ( nHitsPerMCPart.find(partID) == nHitsPerMCPart.end() )
      {
	// not found
	nHitsPerMCPart[partID] = 1;
      } else {
	// found
	nHitsPerMCPart[partID]++;
      }
    }
  }
  
  //Determine the MC Particle with the most hits on the track
  int maxNHits = 0;
  int maxID = 0;
  for (std::map<int,int>::iterator it=nHitsPerMCPart.begin(); it!=nHitsPerMCPart.end(); ++it)
  {
    if(it->second > maxNHits)
    {
      maxNHits = it->second;
      maxID    = it->first;
    }
  }
  maxIDHitPair = std::make_pair(maxID,maxNHits);
  return maxIDHitPair;
}

bool MCTruthMatch::isRadEle()
{
  int isRadEle = 0;
  for(int i=0; i < mcParts_->size(); i++)
  {
    int momPDG = mcParts_->at(i)->getMomPDG();
    std::cout << "max ID: " << maxIDHitPair.first << std::endl;
    std::cout << "max hit: " << maxIDHitPair.second << std::endl;
    if(mcParts_->at(i)->getID() != maxIDHitPair.first) continue;
    if(momPDG == mom_to_match_pdg_) isRadEle = 1;
  }
  if(isRadEle == 1)
  { 
    return true;
  } else {
    return false;
  }
}
bool MCTruthMatch::isRecEle()
{
  int isRecEle = 0;
  for(int i=0; i < mcParts_->size(); i++)
  {
    int momPDG = mcParts_->at(i)->getMomPDG();
    if(mcParts_->at(i)->getID() != maxIDHitPair.first) continue;
    if(momPDG == 623) isRecEle = 1;
  }
  if(isRecEle == 1)
  { 
    return true;
  } else {
    return false;
  }
}


TVector3 MCTruthMatch::getTrueEleP()
{
  for(int i=0; i < mcParts_->size(); i++)
  {
    int momPDG = mcParts_->at(i)->getMomPDG();
    if(mcParts_->at(i)->getPDG() == 11 && momPDG == mom_to_match_pdg_) 
    {
      std::vector<double> lP = mcParts_->at(i)->getMomentum();
      tmpTrueEleP.SetXYZ(lP[0],lP[1],lP[2]);
    }
    if(mcParts_->at(i)->getID() != maxIDHitPair.first) continue;
  }
  
  return tmpTrueEleP;
}
