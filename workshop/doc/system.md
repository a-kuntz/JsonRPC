# Issues

1. `setBodyPart(BodyPart bpart)`
    * Sets the body part
    * ?You have to implement an enum which represents the BodyParts?
    * The parameters have to be set to the datafield
2. `setPatientData(std::string name, int age, int id)`
    * Sets the patient data
    * ?You have to implement a struct which represents the PatientData?
    * The parameters have to be set to the datafield
3. `adjustBeam(flost x, float y)`
    * Adjusts the size of the beam
    * The parameters have to be set to the datafield
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
8.  `Actor::getStatus(): std::string`
    * Returns the status of the set parameters
    * The information about the examinerId and the aanomalies should be collected and returned
9.  `setDate(DateTime date)`
    * Sets the date
    * The parameter have to be set to the datafield
    * ?You have to implement a struct which represents the DateTime?
10. `setTime(Time time)`
    * Sets the time
    * ?You have to implement a struct which represents the Time?
11. `getSystemStatus(): std::string`
    * Returns the System status
    * The information about the time, date and serverId should be collected and returned

After you have implemented all features the server should look like this:

```plantuml
@startuml
title "First Iteration:"
package "Server" {
    package "XRayScan"{
        class XRayScan{
            -BodyPart bpart
            -PatientData pdata
            -int x
            -int y
            +setBodyPart(BodyPart bpart)
            +setPatientData(PatientData pdata)
            +adjustBeam(float x, float y)
            +getStatus(): std::string 
            }
        enum BodyPart {
            thorax
            hand
            spine
            knee
            foot
        }
        struct PatientData {
            -std::string name
            -int age
            -int id
            }
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
        +getStatus(): std::string
    }
    package "Settings"{
        class Settings{
        + {static} int ServerID
        -DateTime date
        -Time time
        +setDate(DateTime date)
        +setTime(Time time)
        +getSystemStatus(): std::string
        }

        struct DateTime{
            int year
            int month
            int day
        }

        struct Time{
            int hour
            int minute
            }
    }

}


@enduml
```

For the next iteration, the server should get an interface, which will be called instead of calling the function directly. The operator of the client should call the interface function for the desired operation and the interface function will handle the data distribution to the base functions.
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
