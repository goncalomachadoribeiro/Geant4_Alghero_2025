#include <vector>

#include <G4RunManagerFactory.hh>
#include <G4VisExecutive.hh>
#include <G4UIExecutive.hh>
#include <G4String.hh>
#include <G4UImanager.hh>

#include "ActionInitialization.hh"

// Task 1: See that we need to include the proper header
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"

// Task 4b.1: Include the proper header to enable scoring manage

// Task 4c.3: Include the proper header for the Analysis

using namespace std;

/// Main function that enables to:
/// - run one macro (put it as command-line argument)
/// - start interactive UI mode (no arguments)

int main(int argc, char** argv)
{
  G4cout << "Application starting..." << G4endl;
 
  // Create the run manager (let the RunManagerFactory decide if MT, 
  // sequential or other). The flags from G4RunManagerType are:  
  // Default (default), Serial, MT, Tasking, TBB
  auto* runManager  = 
    G4RunManagerFactory::CreateRunManager(G4RunManagerType::Serial);
  runManager->SetVerboseLevel(1);

  // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive* ui = nullptr;
  if ( argc == 1 ) { ui = new G4UIExecutive(argc, argv); }

  G4VisManager* visManager = new G4VisExecutive();
  visManager->Initialize();

  //Set mandatory user actions
  runManager->SetUserInitialization(new PhysicsList());
  runManager->SetUserInitialization(new DetectorConstruction());
  runManager->SetUserInitialization(new ActionInitialization());

  // Task 4b.1: You need to access the scoring manager here
  // ...

  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  //Open interactive session
  if (argc==1) // This is an interactive session!
    {
      G4cout << "Creating interactive UI session ...";
      //If a graphical user interface is available, launch automatically the macro 
      //macros/ui.mac
      if (ui->IsGUI())
	{
	  G4cout << "Executing the macro macros/ui.mac..." << G4endl;
	  UImanager->ApplyCommand("/control/execute macros/ui.mac");
	}
      //If a non-graphical UI is available (i.e. terminal-like), just initialize 
      //the run
      else	
	UImanager->ApplyCommand("/run/initialize");
	
      ui->SessionStart();
      delete ui;
    }
  else if (argc==2) //one argument is passed after the executable
    {
      //If not interactive, run the macro passed via command line
      G4String command = "/control/execute " + G4String(argv[1]);
      G4cout << "Executing the macro " << G4String(argv[1]) << G4endl;
      UImanager->ApplyCommand(command);
    }
  else //too many arguments!
    {
      G4cout << "** Too many arguments given in the command line! \n Exit! ** " << G4endl;
      return 1;
    }

  delete runManager;

  // Task 4c.3: Close the analysis output by uncommmenting the following lines
  //G4AnalysisManager* man = G4AnalysisManager::Instance();
  //man->CloseFile();

  G4cout << "Application successfully ended.\nBye :-)" << G4endl;

  return 0;
}
