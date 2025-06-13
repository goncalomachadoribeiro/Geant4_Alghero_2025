#include "PrimaryGeneratorAction.hh"

#include <G4ParticleTable.hh>
#include <G4Event.hh>
#include <G4SystemOfUnits.hh>
#include <G4ParticleGun.hh>
#include <Randomize.hh>
#include <G4Gamma.hh>
// Task 2b.1 Include the proper header file for G4GeneralParticleSource
#include <G4GeneralParticleSource.hh>

using namespace std;

//! Notice: whatever setting is given in this method (constructor) is given only
//! once, at the instantiation time, and can be overridden, either by macro commands
//! or by the method GeneratePrimaries() below
PrimaryGeneratorAction::PrimaryGeneratorAction()
{
    // Task 2b.1: Comment out the particle gun creation and instatiate a GPS instead
    // fGun = new G4ParticleGun();
    fGPS = new G4GeneralParticleSource();

    // Task 2a.1: Set the basic properties for the particles to be produced
    auto particle = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
    // Alternative: 
    // auto particle = G4Gamma::Definition();    

    // Task 2a.1 complete particle name, energy and momentum
    /* 
       fGun->SetParticleDefinition(particle);
       fGun->SetParticleEnergy(662. * MeV); 
       fGun->SetParticleMomentumDirection(G4ThreeVector(0, 0., 1.));  // along z
    */

    // Task 2b.1: Set the same properties for the GPS (removing previous lines)
    fGPS->SetParticleDefinition(particle);
    fGPS->GetCurrentSource()->GetEneDist()->SetMonoEnergy(662.* keV);
    fGPS->GetCurrentSource()->GetAngDist()->SetAngDistType("iso");
    //fGPS->GetCurrentSource()->GetAngDist()->SetParticleMomentumDirection(G4ThreeVector(0, 0., 1.));    

    // Task 2b.2: You can remove or keep the previous lines in the later stages
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    // Task 2b.2: Delete the GPS instead of the gun
    // delete fGun;
    delete fGPS;
}

//! Notice: whatever setting is given in this method is given at the beginning of 
//! each event, so it overrides any other setting, e.g. from the constructor or 
//! from UI commands. This is the right place for parameters which change 
//! event-by-event
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  /*
  // Task 2a.2: Include the direction randomization
  // Sample cos(theta) and phi
  G4double phi = G4UniformRand()*CLHEP::twopi;
  G4double cosTheta = G4UniformRand()*2.-1;

  // Task 2a.2 Calculate sin(theta) and the direction cosines
  G4double sinTheta = std::sqrt(1. - cosTheta*cosTheta);
  G4ThreeVector direction(sinTheta*std::sin(phi),sinTheta*std::cos(phi),cosTheta);

  // Task 2a.2 Pass the direction to the particle gun!
  fGun->SetParticleDirection(direction);
  */

  // Task 2b.1: Comment out all previous commands in this method (there is no fGun!)

  // Task 2b.1: The method for vertex creation remains the same,.just change the object to your GPS
  // fGun->GeneratePrimaryVertex(anEvent);
  fGPS->GeneratePrimaryVertex(anEvent);
}
