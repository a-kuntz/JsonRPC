# Workshop 

## Scope

Softwareentwickler bei ITK im Team "X-Ray"
Der Kunde "HKO X-Ray" hat ITK beauftragt die Software für sein neues Röntgengerät zu entwickeln. Dafür hat er dem Entwicklerteam einen Prototypen zur Verfügung gestellt, welcher hier im Testcenter steht.

## Systemübersicht

Das Röntgenerät besteht aus zwei Hardware-Komponenten:
    1. Steuerterminal (Client)
    2. X-Ray (Server)

In diesem Aufbau fungiert das X-Ray als Server und das Steuerterminal als Client
Der Server stellt verschiedene Funktionen zur Verfügung, die vom Client aufgerufen werden. Der Bediener interagiert nur mit dem Client.

Die Kommunikation zwischen Server und Client läuft über das JSON-RPC-Protokoll. 
Dabei werden zwischen Server und Client JSON-Dateien hin und her gesendet.
Der Client schickt als Anfrage ein JSON-Objekt an den Server. => Request
In dem Objekt wird die Funktion spezifiziert, die aufgerufen werden soll

Als Antwort sendet der Server ebenfalls ein JSON-Objekt zurück => Response
Darin enthalten ist das Ergebnis der aufgerufenen Funktion.

//TODO: JSON Beschreibungsbild einfügen 

//TODO: Systemübersicht einfügen

//TODO: Klassendiagramm einfügen

//TODO: Komponentensicht (mit einzelnen states und Funktionen) einfügen


## Aufgabe
Aufteilung der Gruppe in zwei Teams.
Jedes Team arbeitet separat an einer eigenen Aufgabe.

-> gewünscht: Aufgabenverteilung im Team: Development, Testing

Aufgabe Team 1 (setData):
-> soll im setData-Zustand eine weitere Funktion implementieren und testen

Aufgabe Team 2 (settings):
-> soll im settings-Zustand eine weitere Funktion implementieren und testen

Am Ende der Entwicklung des neuen Features werden die Ergebnise präsentiert. Danach werden beide Features zusammengeführt und in das Hauptprojekt integriert.

## Themen zum Abklären
1. Sprache (eng/deu)
2. Prozess vorgeben?
    -> Wasserfall, Scrum
    -> Aufbau des Workshops anhand eines Modells
    -> regelmäßige Status-Updates? in kleinen Sprint mehrere kleine Features implementieren?
3. zeitliche Rahmebedingungen
4. Detailgrad der Aufgabenstellung (Requirementsdokument)
5. Cheat Sheet C++/JSON/CMake
6. Confluence Seite?

=> beide Teams sollen am ende von ihrem Programmteil etwas zurückbekommen (setData -> Picture; settings -> ???)