 # VDV301tester

This is a program used to test devices compatible with VDV301 1.0, VDV301 2.2CZ1.0 and VDV301 2.2CZ1.0, written in Qt Framework.

# Features
- XML ROPID timetable import
        - selecting of a trip by line/trip or line/vehicleRun
- map plot of route
- voice announcements
- configuration with settings file
- changing languages in menu (English/Czech)
- touch optimised ui (for resolution 800x480px)
- VDV301
        - deviceManagementService
                - change V1.0 device ID
                - get DeviceStatus
                - get DeviceInformation

        - CustomerInformationService
                - AllData
                - CurrentDisplayContent
        - publish and subscribe request
        - service deiscovery using DNS-SD (Bonjour)

        - automated subscription and loss of subscription test (development abandoned for now)
- VDV300
        - manually activated sending telegrams according to IPIS (czech modification of IBIS)

# Planned features

- Asynchronous serial port IBIS sending
- VDV301
        - Time service
        - Location service
        - CustomerInformationService
                -       GlobalDisplayContent
        - DeviceManagementService
                - firmware update in devices
        - full translation of sourcode to English
# Known bugs
- IbisSender
        - viapoints over certain length will not display on BS210
        
# Voice annoucements
MP3 files are not provided with the program.

Stop names have to be stored in hlaseni/zastavky folder, using CIS od OIS number.

Special sounds are stored in hlaseni/special

| content                 | filename |
|-------------------------|----------|
| jingle                  | H000.mp3 |
| next stop               | H001.mp3 |
| request stop            | H002.mp3 |
| last stop               | H113.mp3 |
| please, get off         | H114.mp3 |
| attention, please       | H178.mp3 |
| fare zone change        | H170.mp3 |
| transfer to train lines | H184.mp3 |
| transfer to Metro       | H103.mp3 |
| transfer to ferry       | H274.mp3 |
| A                       | H104.mp3 |
| B                       | H105.mp3 |
| C                       | H106.mp3 |
| A and B                 | H107.mp3 |
| A and C                 | H108.mp3 |
| B and C                 | H109.mp3 |







## Requirements:
### Windows
        Bonjour
        QtHttpServer (Qt Maintenance Tool can be used)
        OpenSSL (only for HTTPS Golemio access)
### Linux
        Avahi
        QtHttpServer  (https://github.com/qt/qthttpserver/tree/5.15) (qmake, make, make install)
        OpenSSL? (Golemio is not tested on Linux yet)


### Tested Qt versions:
- 5.15.2
        - available in 32bit and 64bit versions
- 6.5.0
        - available in 64bit version only
        - improved spacing of voice announcement segments

## After compiling
- Copy all programs from folder *copy_to_program_directory* to the build directory
- Copy *data.sqlite* from folder *XmlRopidImportStream* to build directory
## Loading of new XML data

 - Options -> Truncate, 
 - XML Path -> select file, 
 - Load XML  

## Program Settings
### Golemio Connections

Golemio API key has to be set in settings.ini

For HTTPS access to Golemio, OpenSSL needs to be installed with Qt Maintenance tool.

### Change language
Language can be changed in language parameter in settings.ini file or on the settings tab in the program.
Two options are available: 

Czech
```
language="cs"
```

English
```
language="en"
```
Some of the variable and function names are still in Czech. The translation to English is still in progress.

## Installation from source code
### Download
`git clone https://github.com/frutabruta/VDV301tester.git --recurse-submodules`

### OpenSSL install:
https://stackoverflow.com/a/68629557

### QtHttpServer:
```
git clone https://github.com/qt/qthttpserver/
cd qthttpserver
git submodule update --init --recursive
```

```
qmake
mingw32-make
mingw32-make install
```




## Changelog
- 20240607_1817
        - submodule VDV301DataStructures moved to other submodules which require it
        - IbisSender
                - VDV301DataStructures includions moved to pisPid and IpisTelegramCompose
        - MapaVykresleni
                - changed to MapyApiStops
        - VDV301publisher
                - added examples
                - VDV301DataStructures included
        - VDV301subscriber
                - added examples
        - VDV301DataStructures path changed to one included in VDV301publisher:
                - VoiceAnnouncer
                - Golemio
                - konfigurace
                - SqlRopidXmlQueries
                - XmlMpvParser

- 20240514_1556
        - VDV301publisher
                - 5.15 compatibility fix
        - VDV301publisher
                - 5.15 compatibility fix

        - VoiceAnnouncer
                - moved into separate folder
                - new parent class QueueSoundPlayer


- 20240514_1039
        - VoiceAnnouncer
                - added option to split this and next stop announcements (announcement type)
- 20240513_1725
        - IbisSender
                - IpisTelegramCompose 
                        - address of the device as variable
                        - added delay between commands 
        - settings.ini
                -added option IBIS/enable=true
- 20240510_0038
        - splitting IbisOvladani into several classes
        - settings.ini
                - added IBIS com port setting
        - IBIS serial port stop and start added to Change port button
        - added program icon
        - VDV301publisher
                -  fix of < escaping using CDATA
- 20240422_1414
        - VDV301subscriber
                - using XmlParserSubscriber
                - select ip from list
        - XmlRopidImportStream
                - allow to import multiple lines with one license number 
        - settings.ini
        - devMgmtSubscriber still highly experimental
        - devMgmtSubscriber2 looks for version 2.2 publishers

- 20240215_1538
        - set ID of selected device in detected devices table
        - Vdv301subscriber
                - new version supporting setDeviceID
        - button to setDeviceId activated
- 20240214_1029
        - rename of mainwindow.ui elements to English
                - applies to slot names

- 20240208_1959
        - MainWindow
                - functions reorder
- 20240208_1900
        - MainWindow
                - most of functions and variable names translated to English
        - SqlRopidXmlDotazy
                - renamed to SqlRopidXmlQueries
        - Hlasic
                - renamed to VoiceAnnouncer

- 20240208_1553
        - VDV301DataStructures
                - Vdv301Trip added
        - VDV301publisher
                - currentDisplayContent 2.3 fix

- 20240204_1145
        - nastaveni.ini renamed to settings.ini
        - folders renamed to English
        - show device status in device detection
        - new approach for showing LED displays in 2.3 version (using DisplayContent)
        - VDV301publisher
                - 2.3 out of service fix
        - VDV301subscriber
                - experimental implementation of deviceManagementService v2.2 subscriber
        - VDV301DataStructures
                - vehicleState submode default value fix
        - MainWindow
                - build number now does not get lost in English translation
                - new functions
                        - MainWindow::retranslateUi (prepar)
                        - MainWindow::ledLabelInitialize2_3

        - LabelVykreslovani
                - new functions 
                        - LabelVykreslovani::ledDisplaySetDisplayContent
                        - LabelVykreslovani::ledWriteToDisplay
                - new class
                        - LedLabelDisplay
        - XmlParser
                - new function
                        - XmlParser::parseAllData2_3
                        - XmlParser::domTripInformationToVdv301Trip
                        - XmlParser::domStopListToVdv301TripStopList
                        - XmlParser::tripDoSeznamuZastavek2_3
- 20240123
        - SqlRopidXmlDotazy
                - transferMetroC fix
- 20240109_1404
        - fixed setting golemio API key in configuration tab

- 20240105_1123
        - VDV301publisher 
                - unsubscribe response fix
        - VDV301subscriber
                - unsubscribe response fix
                - HTTP status check
        - language selector in Settings now works

- 20231214_1750
        - VDV301publisher 
                - unsubscribe functionality
        - VDV301subscriber
                - unsubscribe functionality

- 20231206_2100
        - ui
                - smaller padding in tabWidget_hlavni
                - removed one excessive Connections checkbox

- 20231206_2031
        - ui
                - selection of trip from QTableView
                - added new tabs in Options menu
                - Connections checkbox moved to Options              
        - XmlRopidImportStream
                - new truncate functions
                - new columns added
        - timerTrvaniZmenyPasma is not a pointer now  

- 20231124_1706
        - added SQL VACUUM after tables truncate
- 20231124_1453
        - translations fix
        - new buttons to manually add 2.3 subscriber
        - manual mode subscriber lists layout change
        - default language changed to English
        - removed non-functional STOP requested checkbox from Vehicle run screen
        - VDV301subscriber
                - set port number fix
        - readme.md description fixes


- 20231107_2339
        - VDV301publisher
                - 2.4 functions renamed to 2.3
        - VDV301subscriber
                - 2.4 functions renamed to 2.3
                - service name change fix (unsuccessful subscription)
        - default configuration (nastaveni.ini)
                - 2.4 CIS renamed to 2.3

- 20231103_1633
        - VDV301publisher
                - 2.4 farezone compliance
        - stop requested checkbox in Ride mode

- 20231101_1601
        - VDV301publisher
                - 1.0 Connections fix
- 20231030_1931
        - detection of subscriber ID fixed
        - changed english UI translation to comply with VDV301 (connection, trip, vehicle run) 
        - VDV301publisher
                - fix of wrong xml file generating (XML pass by reference error)
        - VDV301subscriber
                - fix of empty service name in DevMgmtSubscriber
        - DeviceManagementService publisher reenabled      

- 20231030_1401
        - English version of libraries
                - VDV301publisher
                - VDV301subscriber
                - VDV301DataStructures               

- 20231025_1111
        - XmlRopidImportStream
                - import now doesn't stop when unknown tag occurs
        - last version of sourcecode in czech

- 20230907_1845
        - VDV301 publisher
                - metro icon transfer
        - VDV301struktury
                - regionalRail fix
        - golemio.cpp
                - debug messages removal
        - V2.4 subscribers table   

- 20230831_1130
        - VDV301publisher VDV301 2.4
                - in-line color formatting of line number
                - removal of lineProperty

- 20230830_1341
        - new verion of VDV301publisher (2.4 viaPoint fix)
        - new version of VDV301subscriber (subscriber version)
        - new version of XmlRopidImportStream
                - import of APC data
                - timetables import in new class xmlimportjr.cpp
        - devMgmtSubscriber renamed to deviceManagementServiceSubscriber
        - MapaVykresleni (mapdrawing module) moved to a submodule

- 20230622_1447
        - VDV301publisher
                -DisplayContentClass
        - changelog.txt merged to readme.md
        - hlasic
                -compability with Qt 5.15 and Qt 6.5        

## Old Changelog (in Czech)

- 20230614_1001
        - VDV301 2.4
                - generování různých DisplayContent pro LCD, Front, Side, Rear panely
- 20230608_1055
        - oprava mapy
        - oprava přiložené databáze 
- 20230607_2028
        - verze se dá zkopírovat
        - verze mapy s příznaky
        - nová verze VDV301publisher
               - nový signál SluzbaPublikovana
        - nová verze VDV301subscriber
                - nastavení portu
        - postupné spouštění verzí CustomerInformationService
        - přesunutí konfiguračních souborů ve zdrojových souborech do samotatné složky


- 2023_05_22
        - úprava mapy (popis spoje)
        - nová verze DB
        - nová verze struktura
        - oprava XML dotazů  pro eliminaci duplicitních spojů

- 2023_05_02
        - vykreslení radiusu zastávky

- 2023_04_25
        - změna datového typu souřadnic na double
        - oprava dotazu pro natažení souřadnic
        - odmazaní funkčí pro vykreslení mapy využívající přímý zápis HTML

- 2023_04_24
        - možnost zobrazit trasu linky
        - import GPS souřadnic

- 2023_02_16_1152
        - možnost změnit port u služeb

- 2023_02_08_1239
        - oprava DB
        - aktualizace XmlImportStream

- 2023_01_24_1850 18:50
        - změna jazyka přes nastaveni.ini

- 2023_01_24
        - konfigurace přes nastaveni.ini