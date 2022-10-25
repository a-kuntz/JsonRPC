# Workshop Software Structure

The Software of the X-Ray has two seperated parts as you can see at the following diagramm:
@startuml
!include https://raw.githubusercontent.com/plantuml-stdlib/C4-PlantUML/master/C4_Container.puml
title "Project Structure:"
Person(user, "User")
Container(server, "X-Ray", "Server")
Container(client, "Terminal", "Client")
BiRel_R(server, client, "Comunicate", "JSON")
BiRel_R(client, user, "interacts")
@enduml
!system.png
The X-Ray provides certain services, which are requested from the Client Software. 
The communication between Server and Client works with JSON. The user only interacts with the client software.

The X-Ray contains the following Classes:
@startuml
title "Server:"
enum Body{
    HEAD, R_ARM, L_ARM, STOMAGE, R_LEG, L_LEG
}
class Server{
    +getCamera(): *Camera
    +getActor(): *Actor
    +getSettings(): *Settings
}
class XRayScan{
    -Body bodypart
    -float wight
    -float hight
    -float power
    +setBodyPart(Body bodypart)
    +setPatientData(float weight, float hight)
    +setEnergy(float power)
    +takePicture(): char[]
}
class Camera{
    +takePicture(floar power): char[]
    +setPictureSetting(float contrast, float sharpening)
}
class Actor{
    +setParameter(Body bodypart, float wight, float hight): bool
}
Server *-- "1" Camera
Server *-- "1" Actor
Server *-- "0..1" XRayScan
class Settings{
    +int minutes
    +int hours
    +int day
    +int month
    +int year
    -float contrast
    -float sharpening
    +setTime(int minutes, int houers)
    +setDate(int day, int month, int year)
    +getTime(): char[]
    +getDate(): char[]
    +setContrast(float contrast)
    +setSharpening(float sharpening)
    +confirm(): bool


}
Server *-- "1" Settings
@enduml

You will only change the server.

The server has the following routines:
@startuml
title "The states of the server:"
[*] --> init
init --> SetData : JSON(setBodypart) | JSON(setPatientData) | JSON(setEnergy)
state SetData{
    [*]->BodypartSet : JSON(setBodypart)
    BodypartSet->[*]
    --
    [*]->PatientDataSet : JSON(setPatientData)
    PatientDataSet->[*]
    --
    [*]->EnergySet : JSON(setEnergy)
    EnergySet->[*]
}
SetData --> TakePicture : JSON(takePicture)
TakePicture --> init
SetData->init : abort()
init -> SettingInit :JSON(settings)
SettingInit -> Setting
state Setting{
    [*] -> SetTime : JSON(setTime)
    SetTime-> SetDate : JSON(setDate)
    SetDate -> [*]
    --
    [*] -> SetContrast : JSON(setContrast)
    SetContrast -> SetSharpening : JSON(setSharperning) 
    SetSharpening ->[*]
}
Setting -> SettingInit
SettingInit -> init : JSON(confirm)
SettingInit -> init : abort()
Setting -> init : abort()
@enduml