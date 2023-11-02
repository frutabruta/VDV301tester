 VDV301tester

This is a program used to test devices compatible with VDV301 1.0 and VDV301 2.2CZ1.0.

Can be compiled with QT5.15.2
## Requirements:
### Windows
        Bonjour
        QtHttpServer (Qt Maintenance Tool can be used)
        OpenSSL (only for HTTPS Golemio access)
### Linux
        Avahi
        QtHttpServer  (https://github.com/qt/qthttpserver/tree/5.15) (qmake, make, make install)
        OpenSSL? (Golemio is not tested on Linux yet))

The program is now only available in Czech.

## Loading of new XML data:
 (Nast.->vymazat data z DB, Vyber cestu XML, nactiXML  )

 Golemio API key has to be set in nastaveni.ini

For HTTPS access to Golemio, OpenSSL needs to be installed with .

## Download
`git clone https://github.com/frutabruta/VDV301tester.git --recurse-submodules`

## OpenSSL install:
https://stackoverflow.com/a/68629557

## QtHttpServer:
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