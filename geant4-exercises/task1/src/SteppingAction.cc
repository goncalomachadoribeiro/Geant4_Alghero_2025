#include "SteppingAction.hh"
#include "RunAction.hh"

#include <G4Step.hh>
#include <G4Geantino.hh>

SteppingAction::SteppingAction(RunAction* runAction)
    : fRunAction(runAction)
{;}

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
  // Task 4a.2: Get the volume where the step starts and stops
  G4VPhysicalVolume* preVolume = nullptr;
  G4VPhysicalVolume* postVolume = nullptr;

  // Take care, because these volumes might not be available: be sure that the pointers  
  // "preVolume" and "postVolume" are non-NULL, otherwise any volume->Get... would 
  // cause a crash
  if (!preVolume || !postVolume)
    return; 

  // Task 4a.2 
  // Implement the proper conditions: boundary crossing and geantino. If the 
  // conditions are met, you want to update the counter by calling CountGeantinoCrossing()
  // from the pointer fRunAction
  // The logic is
  //
  // if (boundary crossing) 
  //  {
  //     if (particle is a geantino)
  //       Do something
  //  }
  //

}
