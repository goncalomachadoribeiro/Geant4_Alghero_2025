#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
//! Optional user classes
// Task 3a.1: uncomment the UserAction's headers
// #include "RunAction.hh"
// #include "StackingAction.hh"

// Task 4a.2: Include the header for SteppingAction
//..
// Task 4c.2: Include the header for EventAction
//...

void ActionInitialization::Build() const
{
    SetUserAction(new PrimaryGeneratorAction());
    /* These two classes are used only in task3-4. Please
       keep them commented in tasks1-2 */

    // Task 3a.1: Uncomment the SetUserActions
    //RunAction* theRunAction = new RunAction();
    //SetUserAction(theRunAction);
    //SetUserAction(new StackingAction(theRunAction));

    // Task 4a.2: Add a properly initialized instance of SteppingAction
    // Notice: the constructor of SteppingAction takes a pointer to
    //  RunAction as an argument
    // ...

    // Task 4c.2: Add a properly initialized instance of EventAction
    // Notice: the constructor of EventAction takes no arguments.
    // ...
}

void ActionInitialization::BuildForMaster() const
{
  // Task 3a.1: Uncomment the following line
  //SetUserAction(new RunAction());
}
