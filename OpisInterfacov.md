# OPISI INTERFACOV #

== ZipFile == **OBSOLETE**

public metode:

`int openZip(const char*);`

Odpre zip datoteko z podanim imenom


`void closeZip();`

Zapre trenutno odprto zip datoteko

`int openFile(const char*);`

Odpre datoteko z podanim imenom v trenutno odprti zip datoteki

`void closeFile();`

Zapre trenutno odprto datoteko v trenutno odprti zip datoteki

`int readFile(void*,unsigned);`

Prebere podano stevilo bytov v podan medpomnilnik (buffer)

`bool isFileOpened();`

Vrne true oz. false, glede na to, ali je kakšna datoteka trenutno odprta v trenutno odprti zip datoteki.

`int getFileSize();`

Vrne velikost trenutno odprte datoteke.

**Delo z zip datotekami:**
Najprej odpremo zip datoteko preko konstruktorja ali metode openZip(). Nato odpremo datoteko znotraj zip datoteke. Podatke iz datoteke preberemo s pomočjo metode readFile(), velikost datoteke pa lahko dobimo preko metode getFileSize(). Po končani obdelavi datoteko zapremo s pomočjo closeFile(), po končanem branju zip datoteke, pa le to zapremo z closeZip().

**OPOMBA:**
Z enim objektom lahko imamo naenkrat samo eno odprto zip datoteko in samo eno odprto datoteko znotraj odprte zip datoteke. Če želimo odpreti drugo datoteko oz. drugo zip datoteko, moramo najprej trenutno odprto datoteko/zip datoteko zapreti (v pravem vrstnem redu). Če bi kdo potreboval več odprtih datotek naenkrat, naj se mi pritoži.

## zifstream ##

zifstream(string zipfile, string file)
odpre najprej zip datoteko, nato pa še datoteko v zipu

uporablja se popolnoma isto kot ifstream objekt, edina razlika je v konstruktorju.

**OPOMBA:**
verjetno ne delajo vse funkcije, saj je vezni objekt med zlib in istream le skelet, v katerem so implementirane le funkcije, ki so potrebne za osnovno delovanje.