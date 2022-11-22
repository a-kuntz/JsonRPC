# Issues

//TODO: Prioritize issus and connect with user storys

1.  `setBodyPart(BodyPart bpart): bool`
    * Sets the body part
    * ?You have to implement an enum which represents the BodyParts?
    * The parameters should be set to the datafield
2.  `setPatientData(PatientData pdata): bool`
    * Sets the patient data
    * ?You have to implement a struct which represents the PatientData?
    * The parameters should be set to the datafield
3.  `adjustBeam(flost x, float y): bool`
    * Adjusts the size of the beam
    * The parameters have to be set to the datafield
4.  `getScanConfig(): xray::Config`
    * Returns the configuation of the set parameters
    * The information about the Patient, the Bodypart and the beam should be collected and    returned
5.  `getDosage(): std::float`
    * Returns the dosage emitted to the patient
    * The dosage is calculated by the following formula: dos=(current + voltage)/2
6.  `setExaminer(int id): bool`
    * Sets the ID of the performing Examiner
    * The parameter should be set to the datafield
7.  `setAnomalies(std:: string): bool`
    * Sets the complications occured during the exam
    * The parameter should be set to the datafield
8.  `getActorConfig(): xray::Config`
    * Returns the configuration of the set parameters
    * The information about the examinerId and the aanomalies should be collected and returned
9.  `setDate(DateTime date): bool`
    * Sets the date
    * ?You have to implement a struct which represents the DateTime?
    * The parameter should be set to the datafield
9.  `setTime(Time time): bool`
    * Sets the time
    * ?You have to implement a struct which represents the Time?
    * The parameter should be set to the datafield
10. `getSystemStatus(): std::string`
    * Returns the System status
    * The information about the time, date and serverId should be collected and returned

## User Story

//TODO: Add content and explenation

1. Add patient data into picture

In the past, there has often been confusion between the X-ray scanns of different patients. The hospitals tryed to prevent that Issue by labeling the pictures afterward. Usually that meant that a hospital employee printed out the picture and sticked a patient data sticker on it. In the new system this sould not be necessary anymore. The system should work digital only. Because of safty reasons the label should be added as soon as possible to the picture.

1. Diferent pictures for diffferen combinations of parameter

The delivery of the X-ray tube and camara is delayed because of supply chain issues. Nevertheless the marketing department of your customer decided to present a dummy of the system at a fair. For this purpose the X-Ray should behave like the complet system. Therefore, the X-ray should returne a dummy picture. In reallity this picture would depend on the given parameters. The dummy picture should behave the same way.

1. Automatisierte Diagnose routine
    * Nach jedem startup
    * Prüfe registrierte Methoden

## Issues #2

1. `getScan(BodyPart bpart, PatientData pdata, float x, float y): std::string`
   * Calls the functions implemented in the first Iteration (Class: XRayScan)
   * returns the results of the getStatus-function
2. `getTube(double voltage, double current): std::string`
   * Calls the functions in the class XRayTube 
   * returns the results of the getStatus-function
3. `getActor(int examinerId, std::string anomalies): std::string`
   * Calls the functions implemented in the first Iteration (Class: Actor)
   * returns the results of the getStatus-function
4. `getSettings(DateTime date, Time time): std::string`
   * Calls the functions implemented in the first Iteration (Class: Settings)
   * returns the results of the getSystemStatus-function
  
After refactoring, the server should look like this.

```plantuml
@startuml
title "Second Iteration:"
package "Server"{
class ServerInterface{
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
ServerInterface *-- "1" XRayTube
ServerInterface *-- "1" Actor
ServerInterface *-- "0..1" XRayScan
ServerInterface *-- "1" Settings
}
@enduml
```

