#ifndef RUNACTION_HH
#define RUNACTION_HH

#include <G4UserRunAction.hh>
#include <G4Run.hh>
#include <G4ParticleDefinition.hh>
#include <G4Accumulable.hh>

class RunAction : public G4UserRunAction
{
public:
  //! constructor
  RunAction();

  //! destructor
  ~RunAction();

  //! Main interface
  void BeginOfRunAction(const G4Run*);
  void EndOfRunAction(const G4Run*);

  void AddSecondary(const G4ParticleDefinition*, G4double energy);
  //increment the geantino counter!
  void CountGeantinoCrossing();

private:
  //Those accumulable are just "counters", which accumulate quantities 
  //over the events. The G4Accumulable is thread-safe, so it is able 
  //to handle inputs coming from different threads. If we were to run 
  //in a pure sequential mode, we could have used just G4int and 
  //G4double
  G4Accumulable<G4int>    fNGammas;
  G4Accumulable<G4int>    fNElectrons;
  G4Accumulable<G4int> fNGeantinos;
  G4Accumulable<G4double> fAverageGammaEnergy;
  G4Accumulable<G4double> fAverageElectronEnergy;
 

};

#endif
