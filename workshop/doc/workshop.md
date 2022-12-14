# Workshop

The main goals of the workshop are to:

- develop software as part of a small team
- emulate a real software development workflow
- fix and extend existing codebase
- focus on software development process


## Scope

You are a Software Engineer at ITK.
The customer "HKO X-ray" has commissioned ITK to develop the software for their new X-ray machine. For this purpose, they have provided the development team with a prototype, which is located here in the test center. The project has been moved from another company to ITK so there is an existing codebase which need to be fixed and extended.

## System Overview

The X-ray machine consists of two hardware components:
    1. Terminal (Client)
    2. X-ray (Server)

![firstServer](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/a-kuntz/JsonRPC/branch/feature/workshop/workshop/doc/plantuml/firstServer.txt)

In this configuration the X-ray acts as a server and the terminal as a client.
The server provides various functions, which can be called by the client. The operator only interacts with the client.

The communication between server and client runs via the JSON-RPC-protocol.
This sends JSON files back and forth between the server and the client.

As a request, the client sends a JSON object to the server, in which the function to be called is specified.

As a Response, the server also returns a JSON object. This contains the result of the called function.

![ServerClientCommunicationUsingJSON](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/a-kuntz/JsonRPC/branch/feature/workshop/workshop/doc/plantuml/server_client_communication.txt)

Currently the system supports four functions. The functions `takePicture`, `setTubeVoltage`, `setTubeCurrent` and `getTubeConfig`. The following class diagram shows the server's current public interface:

![ClassDiagrammServer](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/a-kuntz/JsonRPC/branch/feature/workshop/workshop/doc/plantuml/class_diagramm_server.txt)

## Sample client server session

To start the server execute the following command in a terminal and indicate the port number the server will be listening on:

```shell
./build/app/xrayserver 4242
```

On a second terminal you can now send commands from the client to the server using command line arguments:

```shell
./build/app/xrayclient localhost 4242 setTubeCurrent 12.3
./build/app/xrayclient localhost 4242 setTubeVoltage 42.1
./build/app/xrayclient localhost 4242 takePicture {}
```

If everything works properly the output should look like this:

```shell
$./build/app/ayclient localhost 4242 tubeCurrent 12.3
true
$./build/app/ayclient localhost 4242 tubeVoltage 42.1
true
$./build/app/ayclient localhost 4242 takePicture {}
Picture taken!
```

## Tasks

1. Setup environment (15min)
1. Clone and build repository (15min)
1. Get used to the project: run client, server and module test
1. Find and fix your first bug (15min)
1. Implement new functionality. To this end:
    1. Hold a team meeting and review issues (15min)
    1. Organize two teams
    1. Implement and test one issue per team (45min)
    1. (Push and merge all features)
    1. Organize a team meeting to plan how to implement the user story (15-30min)
    1. Implement user stories (45-60min)

## Setup environment

To setup your Ubuntu 20.04 machine for building the library execute the following command

```shell
wget -qO - https://raw.githubusercontent.com/a-kuntz/JsonRPC/master/scripts/bootstrap-ubuntu-20-04.sh | bash
```

## Clone and build repository

Clone working copy

```shell
git clone -b branch/feature/workshop https://github.com/a-kuntz/JsonRPC.git
```

To build the library and run all examples simply run `./build.sh` inside your working copy

```shell
cd JsonRPC
./build.sh
```

## Get used to the project

The build process automatically runs the included tests. You will see that one test fails. Before trying to find and fix the bug, you may want to browse through the code. With the commands above you can also try out the program and function manually.

## Find and fix your first bug

As you already know, there is a bug in the project. Try to find it and fix it. Take a look at the test output. Try to run the public functions manually. To rebuild the whole project and run the tests, type:

```shell
cd build
make all test
```

## Implement new functionality

In the GitHub repo you will find a list of issues. Every issue represents a new feature which should be implemented. Please plan your work together before starting to implement the features. Maybe a team meeting is helpful for this. Please organize in a group of two to implement one issue. Please note that every new feature should be well tested using unit tests. After all features have been implemented, the server should look like this:

![ClassDiagrammImplementedIssues](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/a-kuntz/JsonRPC/branch/feature/workshop/workshop/doc/plantuml/class_diagramm_implemented_issues.txt)

## Implement user story

The sales team had made the following notes during a meeting with the customer. Review the notes in a team meeting and make a plan on how to implement the described features. Afterward, implement and test the new features.

Since the X-ray is a medicine product, it needs to make sure that it works correctly. Therefore, a check routine must be performed every time the client is started. The following points are part of the evaluation:

* The server should provide its version using the format major.minor.patch. (See semantic versioning.)
* The client should verify its compatibility with the server's version.
* The server needs one minute to start the x-ray tube. This behaviour needs to be simulated by the server.
* The client should make sure that the server is ready to respond.

## Helpful resources

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
