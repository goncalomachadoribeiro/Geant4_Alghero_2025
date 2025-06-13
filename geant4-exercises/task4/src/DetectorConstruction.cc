#include "DetectorConstruction.hh"

#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4NistManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4VisAttributes.hh>
#include <G4Box.hh>
#include <G4Sphere.hh>
#include <G4Tubs.hh>
#include <G4SDManager.hh>
// Task 4c: do not forget the #include's! 

using namespace std;
using namespace CLHEP;

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4NistManager* nist = G4NistManager::Instance();
    G4double worldSizeX = 0.5* m;
    G4double worldSizeY = worldSizeX;
    G4double worldSizeZ = worldSizeX;

    // We have created the world volume for you
    // As with all volumes, it requires three steps:
    // 1) Solid
    G4VSolid* worldBox = new G4Box("world", worldSizeX / 2, worldSizeY / 2, 
				   worldSizeZ / 2);
    // 2) Logical volume
    G4LogicalVolume* worldLog = new G4LogicalVolume(worldBox, 
						    nist->FindOrBuildMaterial("G4_AIR"), "world");
    //Task 1b.4: Set the world volume to be invisible
    worldLog->SetVisAttributes(G4VisAttributes::GetInvisible());

    // 3) Physical volume
    G4VPhysicalVolume* worldPhys = new G4PVPlacement(nullptr, {}, worldLog, "world", nullptr, false, 0);

    /*
      NOW START TO BUILD THE Cu SAMPLE TO BE SCREENED
      It is placed in (0,0,0) and it is a sphere of r = 1 cm
    */
    //Task 1a.2 See how material Copper is defined from the NIST database
    G4Material* matCu = nist->FindOrBuildMaterial("G4_Cu"); 
    //1) solid
    G4double rSphere = 1.0* cm;
    // Task 1b.1 Create the sphere (solid): uncomment and complete
    G4Sphere* sampleSolid = new G4Sphere("sampleSolid",0.,rSphere,0,twopi,0,pi);
   
    //2) logical volume and visualization attributes
    // Task 1b.2 Create the logicalvolume: uncomment and complete
    G4LogicalVolume* sampleLog = new G4LogicalVolume(sampleSolid, matCu,"sample");
    G4VisAttributes* red = new G4VisAttributes(G4Colour::Red());
    red->SetVisibility(true);
    red->SetForceSolid(true);
    sampleLog->SetVisAttributes(red);
    //3) physical volume
    // Task 1b.3 Create the physical volume: uncomment and complete
    G4VPhysicalVolume* samplePhys = new G4PVPlacement(nullptr, {}, sampleLog,"sample",worldLog,false,0); 

    /*
      NOW NOW START TO BUILD THE NaI DETECTOR WITHIN ITS Al CASING
      Detector:  3inch diameter, 3 inch z
      Casing: 0.3 cm thick
      The FACE of the casing is 5 cm far from the center of the sample
    */
    const G4double inch = 2.54*cm;
    //Task 1a.2 Define material Al, from the NIST database
    G4Material* matAl = nist->FindOrBuildMaterial("G4_Al");
  
    //Task 1a.1: create element Iodine and then use Na and I to make 
    // sodium iodide!
    G4Element* Na = nist->FindOrBuildElement("Na"); 
    G4Element*  I = nist->FindOrBuildElement("I");

    // Declare the material with its density and number of components
    G4Material* matNaI = new G4Material("NaI", //its name
					3.67*g/cm3, //its density
					2); //number of components
    matNaI->AddElement(Na,1);
    matNaI->AddElement(I,1);

    //External casing, made of Al
    G4double NaIDiameter = 3.*inch;
    G4double NaIHeight = 3.*inch;
    G4double casingTh = 0.3*cm;
    //Calculate!
    G4double casingDiameter = NaIDiameter + 2.*casingTh;
    G4double casingHeight = NaIHeight + 2.*casingTh;

    //Casing!
    G4Tubs* casingSolid = new G4Tubs("CasingSolid",0.,casingDiameter/2.,
			      casingHeight/2.,0,twopi);
    G4LogicalVolume* casingLog = new G4LogicalVolume(casingSolid, matAl,"casing");
    G4VisAttributes* gray = new G4VisAttributes(G4Colour::Gray());
    gray->SetVisibility(true);
    casingLog->SetVisAttributes(gray);
    // Task 1b.4: uncomment and complete this block, to place the casing properly!
    //Physical volume: casing is a daughter of the world volume
    G4double sampleToFaceDistance = 5.0*cm;
    G4ThreeVector casingCenter(0,0,sampleToFaceDistance+casingHeight/2.);
    G4VPhysicalVolume* casingPhys = new G4PVPlacement(nullptr, casingCenter, casingLog,
						      "casing",worldLog,false,0); 
    
    //     
    // ***** NaI crystal *****
    //
    // Task 1b.5: uncomment and complete this block, to create and place the NaI detector!
    G4Tubs* naiSolid = new G4Tubs("NaISolid",0,NaIDiameter/2.,
				NaIHeight/2.,0,twopi);
    G4LogicalVolume* naiLog = new G4LogicalVolume(naiSolid,matNaI,"NaILV");
    G4VisAttributes* yellow = new G4VisAttributes(G4Colour::Yellow());
    yellow->SetVisibility(true);
    naiLog->SetVisAttributes(yellow);
    //Pay attention! Daughter of the casing and placed in the center of the casing
    G4VPhysicalVolume* naiPhys = new G4PVPlacement(nullptr,{}, naiLog,
						   "NaI",casingLog,false,0); 

    // Task 1a.0: Show the material table
    G4cout << "The material table is: " << G4endl << 
      *(G4Material::GetMaterialTable()) << G4endl;

    // The Construct() method has to return the final (physical) world volume:
    return worldPhys;
}

/*
  This function is a virtual method of G4VUserDetectorConstruction, but 
  - unlike Construct() - it is not purely virtual: you can decide to implement it
  or not. This is the place where to define fields and sensitive detectors
*/

//Uncomment the whole block below for Task 4c
/*
void DetectorConstruction::ConstructSDandField()
{  
    G4SDManager* sdManager = G4SDManager::GetSDMpointer();
    sdManager->SetVerboseLevel(2);  

    // Task 4c.1: Create one instance of G4MultiFunctionalDetector, for the NaI detector
    // G4MultiFunctionalDetector* naiDetector = ...

    // Task 4c.1: Create a primitive scorer for the dose and assign it to the multifunctional detector
    // G4VPrimitiveScorer* naiScorer = ...

    // Task 4c.1 Assign multi-functional detector to the logical volume and register it to 
    //   the SDmanager
    // SetSensitiveDetector("....",....);
    // sdManager->AddNewDetector(...);

}

*/



