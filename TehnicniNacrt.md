
---

# Vsebina #
  1. Uvod
  1. Orodja, knjižnjice
  1. Glavne procedure
  1. Level format
  1. Gameplay
  1. Resource Managment
  1. Sound Manager

---


# 1. Uvod #
Tole je dokument, ki se nanaša na tehnični vidik igre oz. pogona; vsebuje imena uporabljenih knjižnjic, orodij in same bolj detajlne opise posameznih delov igre. Naj ne gre preveč v podrobnosti, vsaka sekcija mora biti opisana tako, da vsi razumejo(če pa kdo kej ne razume, naj napiše komentar spodaj!!!!)

Pa še to: jaz sem zato, da podobno kot zootfly, imamo nekakšen bolj 'open-policy', torej da kar kdo napiše so, dokler ni splošno sprejeto, zgolj predlogi. Če komu kaj ni kul, naj napiše, pa se prediskutirajo alternative.


# 2. Orodja, knjižnjice #

Kot prvo naj omenim, da bo ta dokument doživel velik update v ponedeljek ali torek, čez vikend se bom mogu posvetit jobu, ker mi je šefe naložil neko delo z katerim se mu zelo mudi :D

Zaenkrat pa tole:

**Uporabljeni jeziki:**
  * C++ za engine
  * Java za level editor

**Knjižnjice**
  * OpenGL za grafični pogon
  * GLFW kot platform-independent vmesnik za OpenGL, input in timer
  * OpenAL za zvok (ma kdo boljše ideje? jaz openal nekaj malega poznam in se mi zdi kul)
  * še kaj? jernej(skrabec) rabiš ti kakšno knjižnjico za paketke? ce ja, dopisi!

**Orodja**
  * zaenkrat se zdi dobra ideja IDE NetBeans (je free, tak da zdownloadajte in sprobajte), tako za javo kot C++

**Dodatne info:**
  * input - vhodne naprave(miška, tipkovnica, ...)
  * NetBeans IDE: http://download.netbeans.org/netbeans/6.1/final/start.html?bundles/netbeans-6.1-cpp-linux.sh&platform=linux&lang=en&option=cpp



**Nekaj povezav za OpenGL**
  * http://www.ultimategameprogramming.com/
  * http://zavie.free.fr/opengl/index.html.en
  * http://www.3dgamedesign.org/opengl3.htm
  * http://www.spacesimulator.net/tutorials.html
  * http://nehe.gamedev.net/


**GLFW referenca in user guide(zelo uporabno!;))**
  * http://glfw.sourceforge.net/GLFWUsersGuide26.pdf
  * http://glfw.sourceforge.net/GLFWReference26.pdf


# 3. Glavne procedure #

_Nanaša se na game.h objekt_

**initGame()**

Metoda še ni spisana, najprej bo klicala metodo za inicializacijo rendererja, potem se pa nastavijo še dodatni parametri, specifični igri oz. nastavijo začetne vrednosti.
Če gre tu kaj narobe, se izpiše sporočilo o napaki in igra prekine.


**mainLoop()**

Zanka ki teče, dokler se igra izvaja; prekine se le na uporabnikovo željo ali ob dogodku gameOver.
Zaenkrat je delno implementirana.


**processInput()**

  * bo dodana kmalu v game.h razred
  * bo implementirana na podlagi GLFW funkcij za hendlanje inputa
  * void glfwSetKeyCallback( GLFWkeyfun cbfun )

Zgledalo bo takole:
V zanki se izrisuje scena; ce pride do input callbacka se procesira prekinitev za input.
Funkcija preveri, ce je bil pritisnjen kateri od gumbov gor, dol, levo desno, s pomocjo parametra key, ki pove katera tipka je bila pritisnjena/spuscena, in parameter action, ki pove, ali je tipka bila pritisnjena ali spuscena.

Vrne pa vrednost, ki pove, za katero smer se procesira premik - lahko je to nek integer, ali pa enumeracija(enum smer {gor, dol, levo, desno};).
Ali pa informacijo, da se ni zgodilo nic in da se naj stvari meljejo naprej.

# 4. Level format #

Nanasa se na:
> - level.h
> - level.cpp

> - level editor

Objekti, ki jih je treba izpeljati iz PLevelOBject in bodo prisotni na stopnji:

Tile naj bodo implementirani v level.h:
  * PFloor
  * PSolidWall
  * PUnsolidWall
  * PTeleport
  * PBridge
  * PVoid
  * PCube
  * PCubeHolder
  * POnewayFloor
  * POnewayCube
  * PBomb
  * mogoce sem se kaj pozabil

V player.h:
  * PPlayer

V datoteki so ti elementi predstavljeni z id-ji; funkcije za preslikavo iz datoteke v strukturo in obratno na podlagi id-ja ustvarijo objekt ali na podlagi objekta ustvarijo id.
Sta pa 2 tipa podatkov, prvi id doloca tip elementa, drugi id doloca, kaj je nanj "priklenjeno" (attached). Zato sta v datoteki 2 matriki, ki dolocata kateri elementi so na stopnji in kaj je attached nanje.
Jernej, objavi ze sliko!!!!
Npr, ce predpostavljam, da je st. 1 tla, 2 je zid(prva matrika) in za drugo matriko je 1 igralec in 2 kocka, potem branje izgleda takole(psevdo):

```
while(niFertik())
{
 x = preberiPodatekIzMatrike1();
 if(x == 1)
     stopnja[i++][j++] = new PTla();
 else if(x == 2)
     stopnja[i++][j++] = new PZid();
 ....
}
```

Druga matrika:
```
while(niFertik())
{
 x = preberiPodatekIzMatrike2();
 PObject *novi = NULL;
 if(x == 1)
     novi = new PPlayer();
 else if(x == 2)
     novi = new PCube();
 ....

 stopnja[i++][j++]->attachNode(novi);
}
```

**prva matrika:**

  * Tla -- 0 (PFloor) ...F
  * Neprebojni zid -- 1 (PSolidWall) ...SW
  * Most -- 2 (PBridge) ...B
  * Nic/Prepad -- 3 (PVoid) ...VOID
  * Prostor za kocko 4 (PCubeHolder) ...CH
  * enosmerna tla (POneWayFloor) LEVO 5
  * enosmerna tla (POneWayFloor) DESNO 6
  * enosmerna tla (POneWayFloor) GOR 7
  * enosmerna tla (POneWayFloor) DOL 8
  * teleport in njegov id (PTeleport) >= 9

**druga matrika:**

  * Nic(el. nima otroka, npr. zid) -- 0
  * Igralec -- 1 (PPlayer) ...PLYR
  * Kocka -- 2 (PCube) ...C
  * Enosmerna kocka levo -- 3 (POnewayCube) ...OWC
  * Enosmerna kocka desno -- 4 (POnewayCube) ...OWC
  * Enosmerna kocka gor -- 5 (POnewayCube) ...OWC
  * Enosmerna kocka dol -- 6 (POnewayCube) ...OWC
  * Bomba -- 7 (PBomb) ...B
  * Prebojni zid -- 8 (PUnsolidWall) ...USW

  * Detonirana bomba -- 9 (PDetonatedBomb)

Opozotilo: PDetonatedBomb ni pomembna za level editor, tako da, skrabec, ti si lahko predstavljas da tega ni.
PDetonatedBomb je pomembna samo za gameplay in se lahko na stopnji pojavi le med igro, ko igralec odvrze nekam bombo. Na zacetku ne more obstajati.


Ce kdo med programiranjem ugotovi, da z temi id-ji kaj ne stima, naj prosim popravi wiki, in nekam na grupo napise, da nekaj ne stima in zakaj ne stima!
Naceloma spreminjanje tega ni zazeljeno; ce se bo spreminjalo, naj bo razlog res dober!

Spodobi se in pravicno je, da se v kodi uporabljajo naslednji makri(da bo lazje berljivo):

```
// MATRIKA 1
#define FLOOR 0 
#define S_WALL 1 //  (PSolidWall)
#define BRIDGE 2 // (PBridge)
#define VOID 3 // (PVoid) 
#define CUBE_PLACE 4
#define OW_FLOOR_L 5 // (POneWayFloor)
#define OW_FLOOR_R 6 // (POneWayFloor)
#define OW_FLOOR_U 7 // (POneWayFloor)
#define OW_FLOOR_D 8 // (POneWayFloor)
#define TELEPORT 9 // (PTeleport)


// MATRIKA 2
#define NO_CHILD 0
#define PLAYER 1 // (PPlayer)
#define CUBE 2 // (PCube)
#define OW_CUBE_L 3 // (POnewayCube)
#define OW_CUBE_R 4 // (POnewayCube)
#define OW_CUBE_U 5 // (POnewayCube)
#define OW_CUBE_D 6 // (POnewayCube)
#define BOMB 7 // (PBomb)
#define U_WALL 8 // (PUnsolidWall)


#define FLOOR_TEX 0
#define S_WALL_TEX 1 
#define BRIDGE_TEX 2 
#define CUBE_PLACE_TEX 3
#define OW_FLOOR_TEX 4
#define TELEPORT_TEX 5
#define PLAYER_TEX 6
#define CUBE_TEX 7
#define OW_CUBE_TEX 8
#define BOMB_TEX 9
#define U_WALL_TEX 10
```

**Testni level**

Naredil sem nek tesni level v beleznici, ki prikazuje kaksen je format levela:
```
12 7
1 1 1 1 3 3 3 1 1 1 1 1
1 2 2 1 1 3 1 0 0 0 11 1
1 0 0 7 0 1 0 0 0 0 0 1
1 0 0 7 0 6 0 0 0 0 0 1
1 9 0 0 0 0 0 0 2 2 1 1
1 0 4 4 4 4 0 0 5 5 10 1
1 1 1 1 1 1 1 1 1 1 1 1
+
0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0
0 7 4 0 0 0 0 2 5 0 0 0
0 7 0 0 0 2 0 0 0 3 8 0
0 0 6 6 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 1 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0
+
3
9 10
10 11
11 9
```

Najprej to: presledki med stevilkami so obvezni!
Torej matrika

222

222

222

NI ok!
Mora bit

2 2 2

2 2 2

2 2 2

Ker drugace ne bomo mogl locit med zaporedima celicama z vred. 1 in 2 in st. 12!

Prva vrstica pove dimenzijo stopnje: 12x7

Naslednjih 7 vrstic predstavlja matriko st. 1.

Med matriko 1 in 2 je vmes znak +.

Sledi 7 vrstic matrike 2, in za njo spet + , ki je locilo med matriko 2 in teleport matriko.

Po + sledi st. 2, ki pomeni teleport matriko velikosti 2 (2x2)
Sledi info, ki pove, kako so si teleporti v relaciji:

> -- otrok od teleporta z id 11 je teleport z id 12

> -- otrok od teleporta z id 12 je teleport z id 11

Za taksen format bom jaz zdaj pisal funkcije za lovdanje stopenj; ce kdo najde kaksen "error", naj cimprej pove! Da ne bomo programirali za not-ok format stopnje.

Ce komu ni kaj jasno, naj vprasa! (ce sploh kdo to bere :D)

# 5. Gameplay #

Gameplay se zacne pri inputu; tipicna main-game zanka izgleda namrec takole:

**gameCycle()**
  * preveri, ce je so spremebe na vhodnih napravah(oz. ce je igralec naredil spremembo)

  * v skladu z spremembami procesiraj gameplay(fiziko, AI, ...)

  * narisi sceno

Zelo grobo povedano.
Zato je nastal novi razred, imenovan **PInputSystem()**; definiran je v **input.h** in implementiran v **input.cpp**. Glavna metoda je **process()**, ki preverja spremembe na smernih tipkah in v skladu z spremembami prozi akcije, torej premika igralca levo, desno, gor, dol.
Ker so funkcije za premikanje objektov po igralnem polju oz. igralni matriki, vsebuje ta razred kazalec na stopnjo ` (PLevel *level) `.
Ko input sistem "ulovi" pritisk tipko, sprozi ustrezno akcijo; klice namrec metodo razreda **level.h** imenovano **moveObject()**, ki jemlje za parameter enumeracijo **PDirection**(ki je lako **left, right, up, down**).
Ta funkcija, **moveObject()**, je silno preprosta; vse, kar naredi, je to, da glede na parameter PDirection, torej smer premika, "poklice" funkcijo **checkAndApply()**(prosim za predloge za bolj smiselno ime!:D), poklice pa jo z ustreznimi parameteri za indekse objekta na polju; npr. ce se premikamo levo, klicemo z indexi(i , j-1), desno pa (i , j+1).
Ta funkcija, **checkAndApply()** naredi(oz bo naredila, v casu pisanja ni niti 10% implementirana, homever, sposobna je enostavnega premikanja igralca po polju) "magic stuff" oz. tukaj se melje vecina gameplaya in tudi ta funkcija je/bo zelo enostavna.
Po domace povedano, ta funkcija mora preveriti, ce je premik na zeljeno polje mogoc(check) in ce je, premik izvesti(Apply:D).

Tu nam priskoci na pomoc funkcija vsakega objekta na stopnji, **isPlayerMovePossible()** (verjetno je tudi to ime precej butasto, saj bo ista funkcija nabrz uporabljena tudi za cekiranje ce je mogoce premakniti skatlo, feel free to rename). Funkcija ni tipa bool, saj nista mogoci le 2 stanji, torej je premik mogoc ali ne, ampak precej vec!
Na primer, funkcija vrne 0 ce premik absolutno ni mogoc(na polju je npr. zid), 1, ce je naceloma mogoc, ampak je treba pregledati se vsebino(npr. tla; ce ni gor nic drugega, je premik takoj mogoc), vrednost 3 pa a teleport(tabela vrnjenih vred. in njihov pomen bo zbrana spodaj).
Ko gledamo vsebino, ce ni vsebine ni problema in izvedemo premik. Ce ja je na polju tla npr. kocka, naredimo naslednje:

  * preverimo, ce je kocko mogoce premaknit na eno polje dlje v smeri v katero se premikamo; ce je, nam moveObject() vrne true in tja zdaj lahko premaknemo igralca
  * v nasprotnem primeru premik ni mogoc

Ce kdo to bere, mu je najbrz jasno, da je bil ravnokar opisan obicni premik kocke!
Zdaj pa kar je pravzaprav pomembno, sta tabeli vrnjenih vrednosti in rekacij.
Ti dve tabeli bosta tekom razvoja seveda rasli!

Vrednosti, ki jih vrne element na matriki:
| **vrnjena vrednost** | **reakcija** |
|:---------------------|:-------------|
| 0                    | absolutno nemogoc premik |
| 1                    | absolutno mogoc premik |
| 2                    | pogojno mogoc - cekiraj otroka |
| 3                    | teleport - teleportiraj element!  |
| 4                    | bomba - odstrani bombo, povecaj stevec bomb! |
| 5                    | enosmrena povrsina, pogojno mogoc premik - glej se smer! |
| 6                    | cubeHolder   |


Vrednosti, ki jih vrne otrok elementa na matriki
| **vrnjena vrednost** | **reakcija** |
|:---------------------|:-------------|
| 0                    | absolutno nemogoc premik |
| 1                    | absolutno mogoc premik |
| 2                    | kocka - poskusi premaknit! |




# 6. Resource Managment #

Torej, skrajni čas je, da se razpišem o resource managmentu za xSoko, ker je ta del pomemben pri implementaciji audio podsistema.
Trenutno xSoko potrebuje le resource v obliki textur(to naj bi se z audio sistemom razširilo), zato bom delovanje opisal na podlagi upravljanja textur.

## 6.1 PTexture razred ##

PTexture razred je načeloma enostavna zadeva, še enostavnejše pa je delo z njo.

**Pomembni člani**
  * filename (string)  --- pot do slikovne datoteke v zipu
  * texture (PTextureImage)  --- struktura, ki vsebuje kazalec na vsebino slike, višino, širini in id texture

**Pomembne metode**
  * loadTGA (na podlagi poti zloada TGA sliko v pomnilnik)
  * generateTexture**, makeTgaTexture (zgenerira texturo)
  * getTexId (vrne id texture, ki je unikaten za vsako texturo)**


Delo z PTexture:
```
// tako ustvarimo dinamičen objekt za našo teksturo
PTexture *floor = new PTexture("floor.tga");

// z to metodo naenkrat naložimo sliko v pomnilnik in zgeneriramo texturo; struktura dobi unikatni id
floor->makeTGATexture(true);

/********* kako določimo, katero texturo uporabimo pri risanju? **************/
// odgovor se skriva v id-ju.
// recimo, da imamo metodo drawCube(), ki zna izrisati navadno kocko; če ji ne bomo določili barve ali texture posebej, bo bela
// lahko pa ji določimo texturo z funkcijo void glBindTexture(	GLenum target, GLuint texture);
// target naj bo GL_TEXTURE_2D,  texture pa je id texture!
// primer:

glBindTexture(GL_TEXTURE_2D, floor->getTexId()); // določimo texturo floor prek njenega id
drawCube(); // izrišemo kocko; nanjo je "prilepljenja" textura floor

// pa recimo, da želimo izrisati še eno kocko z texturo wall(recimo, da jo imamo)
// to naredimo tako:
glBindTexture(GL_TEXTURE_2D, wall->getTexId()); // pozor! predpostavljam, da smo naredili tex. wall, kot prej floor
drawCube(); // izrišemo kocko; nanjo je "prilepljenja" textura wall
```

Tako torej delamo z PTexture; smisel managerja pa je avtomatiziranje dela z PTexture.
Zato najprej naredimo še razred PTextureResource, ki delo z texturami še poenostavi.

## 6.2 PTextureResource ##

Namen: razred naj preko metode load() postori vse. Metoda load:

```
        bool PTextureResource::load()
        {
            // create new object for texture
            this->texture = new PTexture(this->filename); // create object
            //  this->texture->setPath(filename);
            if(!this->texture->makeTgaTexture(true))  // create texture(generate)
            {
                cout<<"Error loading "<<this->filename<<endl;  // failed
                delete texture;  // delete object from memory
                return false;
            }
            
            return true; // ok :)
        }
```

Kot vidite, naredi dinamični objekt, nastavi pot do texture(ki je tudi član tega razreda), naredi TGA texturo, če pride do problema, jo pobriše in vrne false.
Delo z tem razredom je še enostavnejše:
```
PTextureResource wall = new PTextureResource("wall.tga");
wall->load();
...
wall->getId();
drawNeki();
...
```

Zdaj potrebujemo le še razred, ki vsebuje kazalce do vseh mogočih in nemogočih resourcev in metode ki čimbolj avtomatizirajo delo z resurci.
Ta razred je PResourceManager.

## 6.3 PResourceManager ##

Kot že omenjeno, iz tega razreda mora biti dosopen vsak resource.
Lahko damo kazalec na resource v razred ročno, npr.

```
public:
  PTextureResource *wall; // individualna textura
```


ali kup textur spravimo v tabelo in delamo le z offsetom.

```
  PTextureResource *textures[];  // tabela textur
```

Do kazalcev dostopam z metodami, ki sem jih spisal za dostop do textur:
```
bool loadTextureResource(PTextureResource **res, string file);
bool loadTextureResource(int offset, string file);

unsigned getTextureTesourceId(int offset);
```

Pa recimo, da želim narediti objekt za steno. Mogoča sta 2 načina.

1. Individualni
```
PResourceManager resources;

resources.loadTextureResource(&wall, "wall.tga");
...
resources.wall->getId(); // dostop
...
```

2. Preko offseta; kazalec je v tabeli
```
resources.loadTextureResource(0, "wall.tga"); // pozor! ne smemo povoziti obstoječega indeksa

...
resources.getTextureResourceId(0); // dostop: preko offseta v tabeli
...
```


Za konec:
To ni nek super duper resource hendling, je tak osnovni in za to igro zadostuje.
Moj način upravljanja z resourcni ni najbolj človeku prijazen, tvoje metode so lahko bolj kul, vsekakor pa je potrebno, da narediš nek interface za dostop do zvočnih resourcev.
Jaz imam texture za objekte za levele v tabeli: (vem število)

```
...
        class PResourceManager
        {
        private:
            PTextureResource *textures[ELEMENTS_TEXTURES];
...
```

Pozor! Kazalci so (morajo!) biti po defaultu na NULL!!!!
Ko loadam stopnjo, zloadam texturo, če je potrebno:

```
...
#define FLOOR_TEX 0
#define S_WALL_TEX 1 
#define BRIDGE_TEX 2 
#define CUBE_PLACE_TEX 3
#define OW_FLOOR_TEX 4
#define TELEPORT_TEX 5
#define PLAYER_TEX 6
#define CUBE_TEX 7
#define OW_CUBE_TEX 8
#define BOMB_TEX 9
#define U_WALL_TEX 10
....
...
...
                              switch(num)  // if it is, we create suitable object
                              {
                                  case FLOOR:
                                      data[i][j] = new PFloor(this->gameCore);
                                      
                                      if((resourceHandle->getTextureResource(FLOOR_TEX))==NULL)  // texture isn't in memory yet?
                                            resourceHandle->loadTextureResource(FLOOR_TEX, "floor.tga");  // load it!
                                      
                                      break;
```

Dostop do texture:
```
        void PFloor::draw()
        {
            glColor3f(0.5, 0.5, 0.4);
            glBindTexture(GL_TEXTURE_2D, this->core->getResources()->getTextureTesourceId(FLOOR_TEX));
            this->core->getRenderer()->drawFloor(0.0, 0.0, 1.0);
        }
```

Podobno bi rad naložil prek ResourceManagerja tudi zvok in enostavno dostopal do njega.

# 7. Sound Manager #

Glavni namen Sound Managerja je seveda upravljanje z zvokom. Na začetku igre se ustvari objekt tipa _**SoundManager**_ znotraj objekta _**PGame**_. V _SoundManager_-ju imamo dva dinamična seznama _**effects**_ (zvočni efekti) in _**musics**_ (background glasba) v katerih so shranjeni vsi zvočni podatki. Najprej je potrebno naložit efekt ali glasbo v enega izmed teh seznamov in šele nato jih lahko uporabljamo (logično). Podrobnosti o tem kasneje, potrebno še je omenit, da so vsi zvočni podatki **singeltone** (glede na pot do datoteke). To pomeni, da če programer dvakrat naloži isto glasbo (ali zvočni efekt) znotraj projekta (ista pot do datoteke) Sound Manager ne porabi dvakrat toliko pomnilnika. Problem pa nastane, če je pot različna vsebina glasbe pa ista. Potem pač uporabi malo več pomnilnika, ampak če bomo vso glasbo shranjevali znotraj mape "data/sounds" se ne bodo dogajala take bedarije. Programer nato na poljubnem mestu v kodi, kjer pač želi uporabiti zvok, pridobi istanco objkta _SoundManager_ na naslednji način (seveda, če ni znotraj objekta _PGame_):
```
SoundManager *sm = PGame::getInstance().getSoundManagerInstance();
```
Sedaj lahko normalno uporablja vse metode _SoundManager_-ja, ki so podrobno opisane spodaj:
|**Metoda**|**Opis**|
|:---------|:-------|
|`SoundManager()`|navadni konstruktor - inicializacija začetnih podatkov|
|`SoundManager(const SoundManager& orig)`|kopirni konstruktor|
|`virtual ~SoundManager()`|destruktor - avtomatično zbriše še vse zvočne podatke, ki jih programer ni |
|`void loadEffect(string name, string path)`|naloži zvočni efekt v seznam; vsak zvočni efekt seveda rabi enolični identifikator (ime) in pot do datoteke |
|`void unloadEffect(string name)`|zbriše zvočni efekt iz pomnilnika - glede na ime efekta|
|`void playEffect(string name)`|predvaja efekt - glede na ime efekta|
|`void loadMusic(string name, string path)`|naloži glasbo - ista finta kot pri zvočnih efektih - podati je potrebno neko ime in pot |
|`void unloadMusic(string name)`|zbriše glasbo iz pomnilnika - glede na ime|
|`void playMusic(string name)`|predvaja glasbo - glede na ime|
|`void playMusic()`|če ni bila predvajana še nobene glasba začne na začetku seznama, drugače pa predvaja zadnje predvajano glasbo|
|`void stopMusic()`|neha z predvajanjem glasbe|
|`bool getMusicStatus()`|vrne status predvajanja glasbe - true: trenutno se nekaj predvaja, false: ni glasbe|
|`void playNextMusic()`|predvaja naslednjo glasbo v seznamu|
|`void playPreviousMusic()`|predvaja prejšnjo glasbo v seznamu|



---


p.s pisanje dokumentacije sux!


