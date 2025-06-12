#include "PhysicsList.hh"

#include <G4EmStandardPhysics.hh>
#include <G4DecayPhysics.hh> 
#include <G4ProductionCutsTable.hh>
#include <G4SystemOfUnits.hh>

// Task 3b.1: Include header for G4EmLivermorePhysics
#include <G4EmLivermorePhysics.hh>

// Task 3b.2: Include header for G4EmExtraPhysics
//#include <G4...>

// Task 3b.3: Include headers for hadronic physics
// ...

PhysicsList::PhysicsList()
{
  // Standard EM physics 
  RegisterPhysics(new G4EmStandardPhysics());
  
  // Default Decay Physics
  RegisterPhysics(new G4DecayPhysics());
    
  //Task 3b.2 (add G4EmExtraPhysics)
  // ...

  // Task 3b.3: Add hadronic physics
  // ...
}


void PhysicsList::SetCuts()
{
  // The method SetCuts() is mandatory in the interface. Here, one just use 
  // the default SetCuts() provided by the base class.
  G4VUserPhysicsList::SetCuts();
  
  // Task 3c.1: Temporarily update the production cuts table energy range
  // G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(100*eV,100.*GeV);
  
  // In addition, dump the full list of cuts for the materials used in 
  // the setup
  DumpCutValuesTable();
}
