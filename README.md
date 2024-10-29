## Puzzle Pieces Plugin

Current version: 0.0.2024.1

A bunch of modular Actors that can be combined to create numerous Puzzles.

#### CURRENT FEATURES
- A **Puzzle** is a combination of one Puzzle Manager, one or many Puzzle Trigger and one or many Puzzle Feedback, all related between them.
  - **PuzzleManager** *(APPActorManager)*: It handles the state of the Puzzle. It stores the PuzzleTriggers that take part in the Puzzle, and also listens to the Managers of previous Puzzles.
  - **PuzzleTrigger** *(APPActorTrigger)*: Basic mold for every Actor that can change the state of the Puzzle. It has an internal value that the owner PuzzleManager can read throught the interface method CheckState, and
that defines whether the step of the puzzle is correct or not.
    - **Button** *(APPActorTrigger_Button)*: Interact with this object through a basic InteractInterface. You can set up a MinValue and a MaxValue for this ActorTrigger, and also an ExpectedValue. If CurrentValue = ExpectedValue, this Actor will comunicate to every 
listening Manager (those binded to the OnTriggerHasCorrectValue delegate), that its value is correct. Also, when the value changes it is sent to the owned FeedbackActor through the interface method called SendValue.
  - **PuzzleFeedback** *(APPFeedbackActor)*: The visual interface of the PuzzleTrigger. Children of this class are actors that can react to a change through the implementation of the SendValue() and the NotActive() methods, 
both part of the TriggerToFeedback interface.
- The basic architecture between the 3 elements, so adding new PuzzleTriggers shouldn't be a problem.

#### TODO
- Add a valve-like functionality
- Add a Collision Box functionality
- Make a demo for a Third Person Character
- Add an optional widget interface (for creating pieces like codelocks)
