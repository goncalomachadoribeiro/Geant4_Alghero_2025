#include "EventAction.hh"

#include <G4SDManager.hh>
#include <G4THitsMap.hh>
#include <G4SystemOfUnits.hh>
#include <G4Event.hh>

#include "Analysis.hh"

using namespace std;

void EventAction::EndOfEventAction(const G4Event* event)
{
    G4SDManager* sdm = G4SDManager::GetSDMpointer();
    G4AnalysisManager* analysis = G4AnalysisManager::Instance();

    // Task 4c.2: Get the hit collections
    G4HCofThisEvent* hcofEvent = nullptr;

    // If there is no hit collection, there is nothing to be done
    if(!hcofEvent) return;

    /* The variable fNaIId is initialized to -1 (see EventAction.hh) so this block 
     of code is executed only at the end of the first event. After the first execution 
     fNaIId gets a non-negative value and this block is skipped for all subsequent 
     events.*/
    if (fNaIId < 0)
    {
      /* Task 4c.2: Retrieve fNaIId from sdm: the name of the hit collection to retrieve is
       is built from the strings passed to as inputs to G4MultiFunctionalDetector()
       and to G4PSEnergyDeposit(). It could be "NaI/energy" or something else.
      */
      // fNaIId = sdm->Get... 
      G4cout << "EventAction: NaI energy scorer ID: " << fNaIId << G4endl;
    }

    G4int histogramId = 1;     // Note: We know this but in principle, we should ask

    if (fNaIId >= 0)
    {
      // Task 4c.2: Get and cast hit collection with energy in the NaI detector
      G4THitsMap<G4double>* hitMapA = nullptr;

      //The block below is not executed, until the hit collection is retrieved
      //correctly
      if (hitMapA)
      {
	//Now we are looping over the hit collection
	for (auto pair : *(hitMapA->GetMap()))
          {
	    //The first element of the map is the copyNb --> always zero in this case!
	    G4int copynb = pair.first;

	    //The second element is the interesting information: energy!
	    G4double energy = *(pair.second);
	  
	    //Use a printout to check that everything is all-right
	    //G4cout << event->GetEventID() << " " << copynb << " " << energy/keV << 
	    //G4endl;
	    
	    // Task 4c.3. Store the position to the histogram      
          }
      }
    }
}
