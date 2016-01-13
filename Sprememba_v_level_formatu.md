Del starega wiki-ja, ki je spremenjen:

---

ID-ji elementov v datoteki:

**prva matrika:**
  * Tla -- **0** _(PFloor)_   ...F
  * Enosmerna tla -- **1** _(POneWayFloor)_  ...OWF
  * Neprebojni zid -- **2** _(PSolidWall)_   ...SW
  * Prebojni zid -- **3** _(PUnsolidWall)_   ...USW
  * PTeleport -- **4** _(PTeleport)_   ...T
  * Most -- **5** _(PBridge)_   ...B
  * Nic/Prepad -- **6** _(PVoid)_  ...VOID
  * Prostor za kocko **7** _(PCubeHolder)_   ...CH

**druga matrika:**
  * Nic(el. nima otroka, npr. zid) -- **0**
  * Igralec -- **1** (PPlayer)_...PLYR
  * Kocka -- **2** (PCube)_    ...C
  * Enosmerna kocka levo -- **3** _(POnewayCube)_   ...OWC
  * Enosmerna kocka desno -- **4** _(POnewayCube)_  ...OWC
  * Enosmerna kocka gor -- **5** _(POnewayCube)_    ...OWC
  * Enosmerna kocka dol -- **6** _(POnewayCube)_    ...OWC
  * Bomba -- **7** _(PBomb)_    ...B
  * ID za smer enosmerne kocke -- **8-levo, 9-desno, 10-gor, 11-dol**
  * ID starsevskega teleporta -- **> 11**

Ce kdo med programiranjem ugotovi, da z temi id-ji kaj ne stima, naj prosim popravi wiki, in nekam na grupo napise, da nekaj ne stima in zakaj ne stima!
Naceloma spreminjanje tega ni zazeljeno; ce se bo spreminjalo, naj bo razlog res dober!

Spodobi se in pravicno je, da se v kodi uporabljajo naslednji makri(da bo lazje berljivo):

```
// MATRIKA 1
#define FLOOR 0 
#define OW_FLOOR 1 // (POneWayFloor)
#define S_WALL 2 //  (PSolidWall)
#define U_WALL 3 // (PUnsolidWall)
#define TELEPORT 4 // (PTeleport)
#define BRIDGE 5 // (PBridge)
#define VOID 6 // (PVoid) 
#define CUBE_PLACE 7

// MATRIKA 2
#define NO_CHILD 0
#define PLAYER 1 // (PPlayer)
#define CUBE 2 // (PCube)
#define OW_CUBE_L 3 // (POnewayCube)
#define OW_C_CUBE_R 4 // (POnewayCube)
#define OW_CUBE_U 5 // (POnewayCube)
#define OW_CUBE_D 6 // (POnewayCube)
#define BOMB 7 // (PBomb)

// ID za smer enosmerne kocke  
#define LEFT 8
#define RIGHT 9
#define UP 10 
#define DOWN 11
```

**Testni level**

Naredil sem nek tesni level v beleznici, ki prikazuje kaksen je format levela:
```
12 7
2 2 2 2 2 2 2 2 2 2 2 2
2 0 0 0 0 0 0 0 0 0 0 2
2 0 0 0 0 0 0 0 0 0 0 2
2 0 0 0 6 6 6 0 0 0 0 2
2 4 0 0 0 0 0 0 0 0 0 2
2 0 0 7 7 0 0 0 0 0 4 2
2 2 2 2 2 2 2 2 2 2 2 2
+
0 0 0 0 0 0 0 0 0 0 0 0
0 0 1 0 0 0 0 2 2 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0
0 11 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 12 0
0 0 0 0 0 0 0 0 0 0 0 0
+
2
11 12
12 11
```

---


Ta del je obsolete in je zamenjan z:


---

prva matrika:

  * Tla -- 0 (PFloor) ...F
  * Neprebojni zid -- 1 (PSolidWall) ...SW
  * Prebojni zid -- 2 (PUnsolidWall) ...USW
  * Most -- 3 (PBridge) ...B
  * Nic/Prepad -- 4 (PVoid) ...VOID
  * Prostor za kocko 5 (PCubeHolder) ...CH
  * enosmerna tla (POneWayFloor) LEVO 6
  * enosmerna tla (POneWayFloor) DESNO 7
  * enosmerna tla (POneWayFloor) GOR 8
  * enosmerna tla (POneWayFloor) DOL 9
  * teleport in njegov id (PTeleport) >= 10

druga matrika:

  * Nic(el. nima otroka, npr. zid) -- 0
  * Igralec -- 1 (PPlayer) ...PLYR
  * Kocka -- 2 (PCube) ...C
  * Enosmerna kocka levo -- 3 (POnewayCube) ...OWC
  * Enosmerna kocka desno -- 4 (POnewayCube) ...OWC
  * Enosmerna kocka gor -- 5 (POnewayCube) ...OWC
  * Enosmerna kocka dol -- 6 (POnewayCube) ...OWC
  * Bomba -- 7 (PBomb) ...B

Ce kdo med programiranjem ugotovi, da z temi id-ji kaj ne stima, naj prosim popravi wiki, in nekam na grupo napise, da nekaj ne stima in zakaj ne stima! Naceloma spreminjanje tega ni zazeljeno; ce se bo spreminjalo, naj bo razlog res dober!

Spodobi se in pravicno je, da se v kodi uporabljajo naslednji makri(da bo lazje berljivo):

```
// MATRIKA 1
#define FLOOR 0 
#define S_WALL 1 //  (PSolidWall)
#define U_WALL 2 // (PUnsolidWall)
#define BRIDGE 3 // (PBridge)
#define VOID 4 // (PVoid) 
#define CUBE_PLACE 5
#define OW_FLOOR_TEX 4
#define OW_FLOOR_L 6 // (POneWayFloor)
#define OW_FLOOR_R 7 // (POneWayFloor)
#define OW_FLOOR_U 8 // (POneWayFloor)
#define OW_FLOOR_D 9 // (POneWayFloor)
#define TELEPORT 10 // (PTeleport)
#define TELEPORT_TEX 6

// MATRIKA 2
#define NO_CHILD 0
#define PLAYER 1 // (PPlayer)
#define PLAYER_TEX 7
#define CUBE 2 // (PCube)
#define CUBE_TEX 8
#define OW_CUBE_L 3 // (POnewayCube)
#define OW_CUBE_R 4 // (POnewayCube)
#define OW_CUBE_U 5 // (POnewayCube)
#define OW_CUBE_D 6 // (POnewayCube)
#define OW_CUBE_TEX 9
#define BOMB 7 // (PBomb)
```

Testni level

Naredil sem nek tesni level v beleznici, ki prikazuje kaksen je format levela:

```
12 7
1 1 1 1 4 4 4 1 1 1 1 1
1 3 3 1 1 4 1 0 0 0 0 1
1 0 0 0 0 1 0 0 0 0 0 1
1 0 0 0 0 0 0 0 0 0 0 1
1 10 0 0 0 0 0 0 3 3 1 1
1 0 5 5 5 5 0 0 6 6 11 1
1 1 1 1 1 1 1 1 1 1 1 1
+
0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0
0 0 4 0 0 0 0 2 5 0 0 0
0 0 0 0 0 2 0 0 0 3 0 0
0 0 6 6 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 1 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0
+
2
10 11
11 10
```

---



**Razlog za spremembe**

Prej je bilo tako, da pri, npr. teleportu, je bilo v prvi matriki dano, kateri element je, v drugi pa metapodatek. Torej, ce se shrani state igre, in je igralec tisti cas na teleportu, se shrani v datoteko le pozicija igralca, ne pa tudi metapodatek, ker je v drugi matriki prostor le za eno stevliko.
Podovna situacija je pri enosmernih tleh.


**Opis spremembe**

Teleport se v celoti prebere v prvi matriki; stevilka 10 ali vec pove, da gre za teleport in id teleporta. Dodana so tudi mesta za enosmetna tla. Metapodatek o usmerjenosti tal in o id-jih teleporta so letele iz druge matrike; spremenili so se id-ji oz. vrstni red idjev prve matrike.