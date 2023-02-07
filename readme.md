# VDV301tester

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