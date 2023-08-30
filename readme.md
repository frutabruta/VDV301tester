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


- 22. 5. 2023
        - úprava mapy (popis spoje)
        - nová verze DB
        - nová verze struktura
        - oprava XML dotazů  pro eliminaci duplicitních spojů

- 2. 5. 2023
        - vykreslení radiusu zastávky

- 25. 4. 2023
        - změna datového typu souřadnic na double
        - oprava dotazu pro natažení souřadnic
        - odmazaní funkčí pro vykreslení mapy využívající přímý zápis HTML

- 24. 4. 2023
        - možnost zobrazit trasu linky
        - import GPS souřadnic

- 16. 2. 2023 11:52
        - možnost změnit port u služeb

- 8. 2. 2023 12:39
        - oprava DB
        - aktualizace XmlImportStream

- 24. 1. 2023 18:50

        - změna jazyka přes nastaveni.ini

- 24. 1. 2023:
        - konfigurace přes nastaveni.ini