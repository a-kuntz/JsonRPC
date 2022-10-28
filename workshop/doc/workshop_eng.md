# Workshop 

## Scope

You are a Software Engineer at ITK.
The Customer "HKO X-Ray" has commisioned ITK to develop the software for their new X-ray machine. For this Purpose, they have provided the development team with a prototype, which is located here in the test center.

## System Overview

The X-ray machine consists of two hardware components:
    1. Terminal (Client)
    2. X-Ray (Server)

In this configuration the X-Ray acts as a server and the terminal as a client.
The server provides various functions, which can be called by the client. The operator only interacts with the client. 

The communication between server and client runs via the JSON-RPC-protocoll.
This sends JSON files back and forth between the server and the client.
As a Request, the client sends a JSON object to the server, in which the function to be called is specified.

As a Response, the server also returns a JSON object.This contains the result of the called function.

//TODO: JSON Beschreibungsbild einfügen 

//TODO: Systemübersicht einfügen

//TODO: Klassendiagramm einfügen

//TODO: Komponentensicht (mit einzelnen states und Funktionen) einfügen


## Aufgabe
Splitting the group into two teams.
Each team works separately on its own task.

-> desired: Distribution of tasks: Development, Testing

Task Team 1 (setData):
-> implement and test a new feature in the setData-state

Task Team 2 (settings):
-> implement and test a new feature in the settings-state

At the end of the development process the results will presented to the project manager. Both features will be joined and merged into the main project. 
