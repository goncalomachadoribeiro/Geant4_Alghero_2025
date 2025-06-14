#include "RunAction.hh"
#include <G4Gamma.hh>
#include <G4Electron.hh>
#include <G4AccumulableManager.hh>
#include <G4SystemOfUnits.hh>

// Task 4c.3: Include the necessary Analysis.hh

RunAction::RunAction() :
  G4UserRunAction(),
  fNGammas("NGammas", 0),
  fNElectrons("NElectrons", 0),
  fNGeantinos("NGeantinos",0),
  fAverageGammaEnergy("AvgGammaEnergy",0.),
  fAverageElectronEnergy("AvgElectronEnergy",0.)
{
  // Register created accumulables
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->RegisterAccumulable(fNGammas);
  accumulableManager->RegisterAccumulable(fNElectrons);
  accumulableManager->RegisterAccumulable(fNGeantinos);
  accumulableManager->RegisterAccumulable(fAverageGammaEnergy);
  accumulableManager->RegisterAccumulable(fAverageElectronEnergy);

  // Task 4c.3: Uncomment the following 4 lines to enable analysis.
  //G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  //analysisManager->SetVerboseLevel(1);
  //analysisManager->SetFirstHistoId(1);

  // Create histogram to be used in 4c
  // ...

  // Task 4c.3: Open file task (extension will be added automatically)
  //analysisManager->OpenFile("task");
}

//==============================================================================

RunAction::~RunAction()
{
  // Task 4c.3: Write the analysis objects by uncommmenting the 
  // following lines. 
  //G4AnalysisManager* man = G4AnalysisManager::Instance();
  //man->Write();
}

//==============================================================================

void RunAction::BeginOfRunAction(const G4Run*)
{
  // Reset all accumulables to their initial values
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();
}

//==============================================================================

void RunAction::EndOfRunAction(const G4Run* run)
{
  //retrieve the number of events produced in the run
  G4int nofEvents = run->GetNumberOfEvent();

  //do nothing, if no events were processed
  if (nofEvents == 0) return;

  // Merge accumulables
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Merge();

  if (IsMaster())
  {
    G4cout
     << "\n--------------------End of Global Run-----------------------"
     << " \n The run was " << nofEvents << " events " << G4endl;
    if (fNGammas.GetValue())
      G4cout << " * Produced " << fNGammas.GetValue()/((G4double)nofEvents) <<
	" secondary gammas/event. Average energy: "
	     << fAverageGammaEnergy.GetValue()/keV/fNGammas.GetValue() << " keV" << G4endl;
    else
      G4cout << " * No secondary gammas produced" << G4endl;
    if (fNElectrons.GetValue())
      G4cout << " * Produced " << fNElectrons.GetValue()/((G4double)nofEvents)  <<
	" secondary electrons/event. Average energy: "
	     << fAverageElectronEnergy.GetValue()/keV/fNElectrons.GetValue() << " keV" << G4endl;
    else
      G4cout << " * No secondary electrons produced" << G4endl;
    if (fNGeantinos.GetValue())
      G4cout << " * " << fNGeantinos.GetValue() << " geantinos counted --> solid angle fraction = " << 
	fNGeantinos.GetValue()/((G4double)nofEvents)  << G4endl;
    
  }
}

//==============================================================================

void RunAction::AddSecondary(const G4ParticleDefinition* particle,
			     G4double energy)
{
  if (particle == G4Gamma::Definition())
    {
      fNGammas += 1;
      fAverageGammaEnergy += energy;
    }
  else if (particle == G4Electron::Definition())
    {
      fNElectrons += 1;
      fAverageElectronEnergy += energy;
    }
  return;
}

//==============================================================================

void RunAction::CountGeantinoCrossing()
{
  ; //increment counter!
}

