# Workshop

## System

The X-Ray system is built out of two parts. The user interacts with a client software, which is installed on a terminal. The X-Ray is connected to a server, which provides the interface for communicating with the client. This comunication uses the JsonRPC protocol.

```plantuml
@startuml firstServer
!include https://raw.githubusercontent.com/plantuml-stdlib/C4-PlantUML/master/C4_Container.puml
title "Project Structure:"
Person(user, "User")
Container(server, "X-Ray", "Server")
Container(client, "Terminal", "Client")
BiRel_R(server, client, "Comunicate", "JSON")
BiRel_R(client, user, "interacts")
@enduml
```

Currently the system supports one class with four functions. The functions `takePicture`, `setVoltage`, `getStatus` and the function `setIntensity`. The first 3 functions work just fine. Unfortunately, the tests for the function `setIntensity` fails. The following class diagram shows the current structure of the server:

```plantuml
@startuml
title "Server:"
class XRayTube{
    -double current
    -double voltage
    +takePicture(): char[]
    +setTubeCurrent(double current): bool
    +setTubeVoltage(double voltage): bool
    +getStatus(): std::string
}
@enduml
```

The class `XRayTube` represents components of the X-Ray. They are allready implemented and you should not change them.

TODO: Implement the features and tests. The XRayTube should return a picture. This could take all public members of XRayScan and Settings into account.
TODO: Cheat Sheet C++/JSON/CMake?
TODO: Add client view

## Issues

Your first task is to finde the bug in the `setIntensity` function and fix it.
After the bug is fixed, your task will be to implement the following features:

1. `setBodyPart(BodyPart bpart)`
    * Sets the body part
    * This interface function passes the value to the Actor
    * If the actor returns false you have to handel the failure
    * ?You have to implement an enum which represents the Body_Parts?
2. `setPatientData(std::string name, int age, int id)`
    * Sets the patient data
    * The parameters have to be set to the datafield
3. `adjustBeam(flost x, float y)`
    * Adjusts the beam
    * The parameters have to be passed to The Actor
    * If the Actor returns false you have to handel the failure
4. `XRayScan::getStatus(): std::string`
    * Returns the status of the set parameters
    * The information about the Patient, the Bodypart and the beam should be collected and    returned
5. `getDosage(): std::float`
    * Returns the dosage emitted to the patient
    * The dosage is calculated by the following formula: dos=(current + voltage)/2
6. `setExaminer(int id)`
    * Sets the ID of the performing Examiner
    * The parameter have to be set to the datafield
7. `setAnomalies(std:: string)`
    * Sets the complications occured during the exam
    * The parameter have to be set to the datafield
8. `setDate(DateTime date)`
    * Sets the date
    * The parameter have to be set to the datafield
    * ?You have to implement a struct which represents the DateTime?
9. `setTime(Time time)`
    * Sets the time
    * ?You have to implement a struct which represents the Time?
10. `getSystemStatus(): std::string`
    * Returns the System status
    * The information about the time, date and serverId should be collected and returned

TODO: Add more features
TODO: Specify the features
TODO: Add complexity?

After you have implemented all features the server should look like this:

```puml
@startuml
title "Complete Server:"
class XRayScan{
    -std::string name
    -int age
    -int id
    +setBodyPart(BodyPart bpart)
    +setPatientData(std::string name, int age, int id)
    +adjustBeam(float x, float y)
    +getStatus(): std::string 
}
class XRayTube{
    -double voltage
    -double current
    +takePicture(): char[]
    +setTubeCurrent(double current): bool
    +setTubeVoltage(double voltage): bool
    +getStatus(): std::string
    +getDosage(): std::float
}
class Actor{
    -int examinerId
    -std::string anomalies
    +setExaminer(int id)
    +setAnomalies(std:string)
}
class Settings{
    + {static} int ServerID
    -DateTime date
    -Time time
    +setDate(DateTime date)
    +setTime(Time time)
    +getSystemStatus(): std::string
}

@enduml
```

For the next iteration, the server should get an interface, which will be called instead of the function. The operator of the client should call the interface function for the desired operation and the interface function will handle the data distribution to the base functions.
After reworking, the server should look like this.

```puml
@startuml
title "Complete Server:"
class Server{
    + {static} int ServerID
    +getScan(): *XRayScan
    +getTube(): *XRayTube
    +getActor(): *Actor
    +getSettings(): *Settings
}
class XRayScan{
    -std::string name
    -int age
    -int id
    +setBodyPart(BodyPart bpart)
    +setPatientData(std::string name, int age, int id)
    +adjustBeam(float x, float y)
    +getStatus(): std::string
    }
class XRayTube{
    -double voltage
    -double current
    +takePicture(): char[]
    +setTubeCurrent(double current): bool
    +setTubeVoltage(double voltage): bool
    +getStatus(): std::string    
    +getDosage(): std::float
}
class Actor{
    -int examinerId
    -std::string anomalies
    +setExaminer(int id)
    +setAnomalies(std:string)
}
class Settings{
    -DateTime date
    -Time time
    +setDate(DateTime date)
    +setTime(Time time)
    +getSystemStatus(): std::string
}
Server *-- "1" XRayTube
Server *-- "1" Actor
Server *-- "0..1" XRayScan
Server *-- "1" Settings
@enduml
```
## Tasks

1. Setup enviroment
1. Clone and build repository
1. Run the server and get used to the project
1. Run the tests
1. Find and fix the bug in `setIntensity`
1. Hold a team meeting and review issues
1. Organize in teams of two
1. Every team should implement and test one issue
1. Push all features
1. Team meeting and merging of all features
1. eventually develop and implement own feature

TODO: Completet task list and add more details
