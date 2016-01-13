# Dokumentacija - xSoko #
_verzija 0.4_

---

**Vsebina**
  1. Opis
  1. Cilj sokobana
  1. Gameplay
  1. Igralno polje
  1. Iterakcija človek-igra
  1. Level editor (urejevalnik stopenj)
  1. Cilji za verzijo 0.5
  1. Sprejeti inovativni dodatki in njihova namembnost
  1. Točkovanje
  1. Uradna kampanija

---


**Pojmi**:
zaradi nekonsistentnosti izrazov v dokumentaciji je potrebno definirati uporabljene pojme
  * **sokoban, možicelj**: glavni lik; uporavlja ga uporabnik; možicelj lahko premika določene elemente gor in dol po igralni plošči
  * **škatla**: objekt, ki ga možicelj (sokobanček) lahko premika gor in dol
  * **zid**: statični objekt, katerega možicelj ne more premikati; prav tako ga ne more prečkat noben drug objekt
  * **teleport**: objekt skozi katerega se možicelj premakne (preslika,...) na drugo pozicijo v igralni plošči
  * **ciljni prostor**: objekt (ali mesto) na katerega možiclj mora premaknit škatlo
  * **tla**: objekt kateri lahko vsebuje (nosi) druge objekte nad sabo: škatla, možicelj
  * **bomba**: (destruktitev) objekt, ki lahko uničuje (določene) ostale objekte: leseni zid
  * **leseni zid**: za ta objekt velja enako, kot za navadni zid; ima dodatno lastnost, da se ga lahko uniči (razstreli) z bombo

---


**0. Časovni okvir**

Projekt brez časovnega roka je nedokonačan projekt, zato je naš cilj izdat končno verzijo igre do **1.10.2008 00:00**.
Časovni rok za izdelavo koncepta igre in dokumentacije je **29.6.2008 00:00**

**1. Opis**

Predelava klasičnega sokobana z nekaj dodatki.


**2. Cilj sokobana**

Škatle so nameščene po stopnji. Cilj igre je, da jih možicelj potisne v ciljni prostor. Škatlo lahko igralec pomika gor, dol, levo desno.
Vec informacij o klasičnem sokobanu na [wikipediji](http://en.wikipedia.org/wiki/Sokoban); [primer](http://www.geocities.com/ygp_bg/sokoban.html) sokobana (za windows)


**3. Gameplay**

Uporabnik s pomočjo smernih tipk pomika možiclja gor, dol, levo, desno. Možicelj lahko potiska škatle; premakne jih lahko kamorkoli na (praznih) tleh. To seveda stori tako, da se postavi 1 polje stran od škatle in "potisne" škatlo v izbrano smer (klasični sokoban).
Možicelj lahko gre tudi skozi teleport (škatla ne sme skozi teleport). Lahko razstreli določene elemente (leseni zid), če ima bombo. Bombo pa lahko ali pobere ali pa mu je katera dodeljena na začetku stopnje. Škatle, zida, tla ni mogoče razstreliti

Cilj uporabnika je, da "obrne" vse stopnje, pri čemer lahko trenutno stanje shrani. To lahko stori na **dva** načina. Ob kliku na ESC (zapušča igro) se ga vpraša ali hoče shranit igro. Drugi način pa je, da med igranjem pritisne CTRL+S in se mu prikaže dialog za shranjevanje igre.
Uporabnik drži tudi nek "highscore" oz. točke, ki jih je nabral do trenutne stopnje; ta higscore je pa odvisen od časa, ki ga igralec porabi za stopnjo in od števila potez.

**4. Igralno polje**

Igralno polje je sestavljeno iz dvodimenzionalne matrike velikosti m×n (predlog za dejansko velikost: **30x30**). Osnovni element, ki sestavljajo matriko se naj imenujeje 'kocka'.
Kocka je prazen element (ne vsebuje ničesar nad sabo, niti tla). Na kocke potem projeciramo osnovne gradnike: tla, zid, škatla, ciljno polje, možicelj (sokoban) + ostali inovativni dodatki.

**5. Interakcija človek-igra**

Uporabnik klikne na ikono 'xSoko'. Zažene se igra v celozaslonki način. Ko se zadeva uspešno naloži se ponudi igralcu osnovni menu.

  * _Nova igra_: uporabnika se vpraša ali hoče igrat uradno kampanijo ali hoče igrat ustvarjeno sobo; zažene se glavna zanka igre (1. level) in uporabnik začne opravjat svojo nalogo (igranje). Ob predčasnem izhodu iz igre (ESC) se igralcu ponudi shranjevanje igre (save game)
  * _Naloži igro_: uporabniku se ponudi možnost nalaganja shranjene igre
  * _Nastavitve_: ločljivost, barva igralca, tema tekstur
  * _Highscore_: lestvica najboljših
  * _Izhod_: konec igre

**6. Level editor (urejevalnik stopenj)**

Eden izmed (pomebnih) sestavnih delov projekta je tudi level editor. Končnemu uporabniku omogoča izdelavo svojih stopenj, ki jih kasneje lahko uvozi v igro. Gre za preprosto aplikacijo v kateri ima na voljo vse grafične gradnike (zid, škatla, možicelj, ciljno polje...) in jih lahko poljubno razporedi po mreži (velikost mreže ima maksimum, minimum).


**7. Cilji za verzijo 0.5** (**deadline: 20.8.2008**)
  * zidovi (vse kar paše k njim, se pravi da se ne prehaja skozi njih)
  * možicelj (premikanje, porivanje)
  * škatle (premikanje v eno smer kadar jih poriva možicelj)
  * cilja polja (vse kocke morajo priti v "štalco" nakar se izpiše "super, opravil si level 1...ti si car!")
  * 1. delujoč level! (oziroma vec, ker bo potrebno veliko testiranja)
  * osnovni level editor (ni nujno koncni)

**8. Sprejeti inovativni dodatki in njihova namembnost**

Glavna ideja našega projekta je inovativno razširiti klasični sokoban. In kot smo hitro ugotovili je potrebno o naših inovacijah razmišljati že zelo zgodaj, drugače lahko kasneje pride do (velikih) težav pri implementaciji.
  * _teleport_: teleportira (preslika, prestavi) igralca iz enega začetnega mesta (začetna luknja) proti končnemu mestu za teleport; možnih je več lukenj za teleport (max 5), v tem primeru pa se teleportira v naprej definiranem zaporedju
  * _bomba_: razbije (uniči, zbriše) leseni zid (lesena povšina)
  * _most_: objekt, ki se razbije (uniči) po prečkanju možiclja (primer: imamo dva 'otoka' vmes pa sta povezana z mostom; ko ga možicelj prečka se le ta podre); z ustrezno akcijo (vstop na kocko za aktivacijo mostu) se most lahko zgradi nazaj
  * _enosmerna tla_: premikanje čez to polje je mogoče samo v eno smer (pot premika je označena z puščico ali kako drugače)
  * _enosmerna škatla_: škatlo je mogoče potisniti samo v eno smer (smer potiska je nakazana z puščico na škatli ali kako drugače)

**9. Točkovanje**

tukaj se zapiše sistem točkovanja

**10. Uradna kampanija**

Naša naloga je ustvariti igro in ne samo osnutek igre (primer: izdelan pogon z eno narejeno stopnjo in konec). Zato moramo pripraviti tudi 'uradno kampanijo' (nimam ideje kako bi to poimenovali). Gre pa za 20 (končanih) stopenj, ki so del igre. To so default stopnje, ki so priložene igri. V prvih petih stopnjah se uporabijo koncepti klasičnega sokobana (za ogrevanje), v ostalih pa tudi naše inovativne ideje.