# Workshop

The main goals of the workshop are:

- hands on software development workflow
- continue excisting codbase
- work in small groups
- focus on software development process
- software development is teamwork


## Scope

You are a Software Engineer at ITK.
The Customer "HKO X-ray" has commisioned ITK to develop the software for their new X-ray machine. For this purpose, they have provided the development team with a prototype, which is located here in the test center. The project has been moved from another cpompany to ITK so there is an existig codebase which need to be fixed and extended.

## System Overview

The X-ray machine consists of two hardware components:
    1. Terminal (Client)
    2. X-ray (Server)

![firstServer](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/a-kuntz/JsonRPC/branch/feature/workshop/workshop/doc/plantuml/firstServer.txt)

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

In this configuration the X-ray acts as a server and the terminal as a client.
The server provides various functions, which can be called by the client. The operator only interacts with the client.

The communication between server and client runs via the JSON-RPC-protocoll.
This sends JSON files back and forth between the server and the client.
As a Request, the client sends a JSON object to the server, in which the function to be called is specified.

As a Response, the server also returns a JSON object. This contains the result of the called function.

```plantuml
@startuml
title Server client communication using JSON
actor User
User -> Client: setTubeVoltage 20.5
Client -> Server: {method: setTubeVoltage,params: [20.5]}
Server --> Client: {result: true}
Client --> User: Voltage has been set succesfully!
User -> Client: setTubeCurrent 10.5
Client -> Server: {method: setTubeCurrent,params: [10.5]}
Server --> Client: {result: true}
Client --> User: Current has been set succesfully!
@enduml
```

Currently the system supports four functions. The functions `takePicture`, `setTubeVoltage`, `setTubeCurrent` and `getTubeConfig`. The following class diagram shows the current structure of the server:

```plantuml
@startuml
title "Server:"
class XRayServer{
    +setTubeCurrent(double current): bool
    +setTubeVoltage(double voltage): bool
    +takePicture(): char[]
    +getTubeConfig(): xray::Config
}
@enduml
```

## Sample client server session

To run the server start the server at the terminal with a port number:

```shell
xrayserver 4242 
```

On a second terminal you can now send commands from the client to the server using command line arguments:

```shell
xrayclient localhost 4242 setTubeCurrent 12.3
xrayclient localhost 4242 setTubeVoltage 42.1
xrayclient localhost 4242 takePicture {}
```

If everything works properly the output should look like this:

```shell
$xrayclient localhost 4242 tubeCurrent 12.3
true
$xrayclient localhost 4242 tubeVoltage 42.1
true
$xrayclient localhost 4242 takePicture {}
This is a picture ;)
```

## Tasks

1. Setup enviroment (15min)
1. Clone and build repository (15min)
1. Get used to the project: Run client, server and module test
1. Find and fix your first bug (15min)
1. Your software development experience: Implement new functionality
    1. Hold a team meeting and review issues (15min)
    1. Organize in teams of two
    1. Every team should implement and test one issue (45min)
    1. (Push and merge all features)
    1. Team meeting to palan how to implement the user story (15-30min)
    1. implement user storys (45-60min)

## Setup enviroment

To setup your Ubuntu 20.04 machine for building the library execute the following command

```shell
wget -qO - https://raw.githubusercontent.com/a-kuntz/JsonRPC/master/scripts/bootstrap-ubuntu-20-04.sh | sh
```

## Clone and build repository

Clone working copy

```shell
git clone https://github.com/a-kuntz/JsonRPC.git
```

To build the library and run all examples simply run `./build.sh` inside your working copy

```shell
cd JsonRPC
./build.sh
```

## Get used to the project

The build process automaticly runs the included tests. You will see that one test fails. Before you going to find and fix the bug you may want to browse through the code. With the commands above you can also try out the programm and function manually.

## Find and fix your first bug

As you already know there is a bug in the project. Find it and fix it. Therefore you may take a look at the test output. You also can run the single functions manually. You can run the tests without building the whole project by using the following commands:

```shell
cd build
make all test
```

## Implement new functionality

In the GitHub Repo you will find a list of issues. Every issue represents a new feature which should be implemented. Please plan your work together before starting to implement the features. Maybe a team meeting is helpful for this. Please organize in a group of two to implement one issue. Please note that every new feature should be tested sufficent with unit tests. After all features have been implemented the server should look like this:

```plantuml
@startuml
title "Implemented Issues:"
package "Server" {
    interface "Functions" { 
        -BodyPart bpart
        -PatientData pdata
        -float x
        -float y
        ..
        -Config config 
        ..
        -int examinerId
        -std::string anomalies
        ..
        -int ServerID
        -DateTime date
        -Time time
        ==
        +setBodyPart(BodyPart bpart): bool
        +setPatientData(PatientData pdata): bool
        +adjustBeam(float x, float y): bool
        +getScanConfig(): xray:Config 

        +setTubeCurrent(double current): bool
        +setTubeVoltage(double voltage): bool 
        +takePicture(): char[]
        +getTubeConfig(): xray::Config
        +getDosage(): std::float
        
        +setExaminer(int id): bool
        +setAnomalies(std:string): bool
        +getActorConfig(): xray::Config
  
        +setDate(DateTime date): bool
        +setTime(Time time): bool 
        +getSystemStatus(): std::string
    }
    together {
        struct PatientData {
            -std::string name
            -int age
            -int id
        }
        enum BodyPart {
            thorax
            hand
            spine
            knee
            foot
        }
        struct Config {
            -double voltage
            -double current
        }
        
    }
    together {
        struct Time{
            -int hour
            -int minute
        }
        struct DateTime{
            -int year
            -int month
            -int day
        }
    }
    
    PatientData -[hidden]-> Time 
}
@enduml  

```

## Implement user story

The sales team had made the following notes during a meeting with the cutomer. Review the notes in a team meeting and make a plan on how to implement the described features. Afterward implement and test the new features.

Since the X-ray is a medicine product it needs to make shure that it works correctly. Therefore a check routine should be perforemd every time the client is started. The following points are part of the evaluation:

* The server should provide a semantic versioning (major.minor.patch)
* The client should verify its compatibility with the server version.
* The server needs one minute to start the x-ray tube. This behaviour needs to be simulated by the server.
* The client should make shure that the server is ready to responde

## Helpful ressources

C++:
* [hackingcpp](https://hackingcpp.com)
* [cppreference](https://en.cppreference.com/w/)
* [cheat sheet](https://github.com/mortennobel/cpp-cheatsheet)

Linux:
* [bash cheet sheet](https://www2.icp.uni-stuttgart.de/~icp/mediawiki/images/b/bd/Sim_Meth_I_T0_cheat_sheet_10_11.pdf)

JSON:
* [JSON quick reference](https://quickref.me/json)

Semantic Versioning:
* [semantic versioning](https://semver.org/lang/de/)
