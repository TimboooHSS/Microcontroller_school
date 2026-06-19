# Projectverslag: Arduino Memory Spel

Dit is het verslag van mijn Arduino-project voor het praktijkexamen. In dit document leg ik uit wat ik heb gemaakt, welke onderdelen ik heb gebruikt en hoe het project is verlopen.

---

## 1. Algemene Informatie

*   **Naam:** Tim van Loo
*   **Vak:** Programmeren van microcontrollers

---

## 2. Wat ga ik maken?
Ik maak een Simon Says memory spel met een Arduino microcontroller.

### 2.1 Uitleg van het spel
Het spel is een geheugenspel waarbij de Arduino een willekeurige volgorde van lampjes (LEDs) laat zien en bijbehorende geluidjes afspeelt via een buzzer. De speler moet deze volgorde precies naspelen door op de juiste knoppen te drukken. 

Het spel werkt als volgt:
1. Het spel begint en op het schermpje (OLED display) verschijnt de tekst "READY?".
2. De Arduino kiest willekeurig een lampje, laat dit branden en laat een toon horen. Dit lampje wordt toegevoegd aan een reeks.
3. De Arduino laat de hele reeks achter elkaar zien en horen die de speler moet onthouden.
4. De speler moet nu op de knoppen drukken in precies dezelfde volgorde.
5. Als de speler het goed doet, gaat het spel naar de volgende ronde en komt er een nieuw lampje bij in de reeks.
6. Als de speler een fout maakt, stopt het spel direct. Het scherm laat "WRONG!" zien en de buzzer maakt een foutgeluid. Daarna begint het spel opnieuw met de tekst "TRY AGAIN".
7. Als de speler 10 rondes achter elkaar goed heeft nagespeeld, wint de speler. Het scherm toont "YOU WIN!" en er klinkt een overwinningsmelodie.

### 2.2 Wat moet het spel kunnen? (Eisen)
*   Het spel moet willekeurig een van de drie LEDs laten branden en een bijbehorende toon afspelen.
*   De speler moet de volgorde kunnen invoeren met drie drukknoppen.
*   Er moet een OLED-schermpje zijn waarop de huidige ronde (bijvoorbeeld "Round 1") en de spelstatus (zoals "READY?", "WRONG!", "YOU WIN!" of "TRY AGAIN") te zien is.
*   Het spel moet maximaal 10 rondes duren. Bij het behalen van de 10e ronde wint de speler het spel.
*   Bij een foutieve knopinvoer moet het spel direct stoppen en teruggaan naar ronde 1.

---

## 3. Gebruikte Onderdelen (Hardware)
| **Microcontroller** Arduino Uno | [1] | 
| **Display** (bijv. OLED SH1106 scherm) | [1] |
| **Knoppen** | [4] | 
| **LEDs** | [3] | 
| **Buzzer** Buzzertje | [1] |
| **Weerstanden**  220 Ohm | [3] | Nodig om je lampjes niet kapot te branden
| **Breadboard & Kabeltjes** | [1] | 

---

## 4. Software en Programmeren
*Hier beschrijf ik welke software en code-bibliotheken (libraries) ik heb gebruikt.*

*   **Programma:** Arduino IDE (om de code te schrijven en te uploaden)
*   **Libraries (Bibliotheken):**
    *   [Bijv. Adafruit_SH1106G (voor het aansturen van het scherm)]
    *   [Bijv. Adafruit_GFX (voor het tekenen van tekst op het scherm)]

---

## 5. Planning (Eerste twee weken van Juni)
*Hieronder staat de planning die ik heb gevolgd in de eerste twee weken van juni 2026. Dit laat zien wat ik per dag heb gedaan en wat er wel of niet lukte.*
**Hier ben ik eerlijk over. De planning volgen is niet gelukt. Ik heb het gemaakt maar ben vrij willekeurig bezig gegaan**

### Week 1 (1 t/m 7 juni 2026)

| **Ma 1 juni** | Eisen bekijken en bedenken wat ik ga maken. | Eisen bekeken. Gekozen om een Simon Says memory spel te maken met LEDs en geluid. |
| **Di 2 juni** | Onderdelen bij elkaar zoeken in het lokaal. | Alle onderdelen gevonden. Het schermpje had andere pinnetjes dan op het internet stond, dus de datasheet erbij gepakt voor de juiste poorten. |
| **Wo 3 juni** | Arduino IDE installeren en de microcontroller aansluiten op de pc. | IDE geïnstalleerd. De pc herkende de Arduino eerst niet. Dit bleek te liggen aan de USB-driver van het goedkope Arduino-bordje. Driver geïnstalleerd en toen werkte het. |
| **Do 4 juni** | Tekenen van het aansluitschema op papier. | Schema getekend. Gekozen om de knoppen met `INPUT_PULLUP` aan te sluiten om minder losse weerstanden nodig te hebben. |
| **Vr 5 juni** | LEDs, knoppen en de buzzer op het breadboard prikken. | Alles opgebouwd. Simpele testcode geschreven. Eén knopje bleek kapot te zijn en deed niks. Dit knopje vervangen door een andere. |
| **Za 6 juni** | Weekend. | - |
| **Zo 7 juni** | Het OLED schermpje aansluiten en testen of het werkt. | Scherm aangesloten. Het scherm bleef eerst helemaal zwart. Het I2C-adres in de code bleek niet te kloppen. Aangepast van 0x3D naar 0x3C en toen werkte het. |

### Week 2 (8 t/m 14 juni 2026)

| **Ma 8 juni** | Basiscode schrijven voor de LEDs en buzzer. | Code geschreven om de LEDs te laten knipperen en de buzzer tonen te laten maken. De tonen van de buzzer wat zachter gezet zodat het minder irritant klinkt. |
| **Di 9 juni** | Spel-volgorde maken (willekeurige LEDs laten branden). | Code geschreven voor de willekeurige volgorde. Probleem: bij het opstarten was de volgorde steeds precies hetzelfde. Opgelost door `randomSeed(analogRead(0))` te gebruiken. |
| **Wo 10 juni** | Code schrijven om de knoppen uit te lezen. | Code geschreven. Probleem: als ik één keer op een knop drukte, dacht de Arduino soms dat ik twee keer drukte (denderen van de knop). Opgelost door een kleine delay in de code te zetten na het indrukken. |
| **Do 11 juni** | Teksten zoals de ronde en win/verlies op het scherm programmeren. | Teksten geprogrammeerd. Het scherm reageerde eerst wat traag. De code wat korter gemaakt om geheugen te besparen. |
| **Vr 12 juni** | Het hele spel voor de eerste keer testen en fouten zoeken. | Eerste grote test gedaan. Het spel werkte, maar de lampjes knipperden veel te snel achter elkaar waardoor je het niet kon onthouden. Delays in de code langer gemaakt. |
| **Za 13 juni** | Testen of alles goed blijft werken na vaker spelen. | Getest. Soms bleef de buzzer piepen als je heel snel op de knoppen drukte. Dit opgelost door de code zo aan te passen dat de buzzer na elke knopdruk direct stopt. |
| **Zo 14 juni** | Verslag gemaakt aan het einde van de week. ** Dit is ook niet gelukt en heb ik nog dingen moeten aanpassen op de laatste dag ** 

---

## 6. Aansluitschema

Bekijk de foto van het schema.

---

## 7. Het spel testen
*Hieronder staat wat ik heb getest om te kijken of alles goed werkt.*

| **Opstarten** | Scherm toont "READY?" | Scherm werkte, maar de lampjes bleven uit bij de start. (Opgelost) |
| **Ronde starten** | Spel laat zien welke ronde het is en laat 1 lampje branden met geluid. | Dit werkte meteen goed. 
| **Goede knop indrukken** | Spel gaat naar de volgende ronde en voegt een lampje toe. | Dit werkte goed. 
| **Foute knop indrukken** | Spel stopt, zegt "WRONG!", speelt een foutgeluid en start opnieuw. | Spel stopte wel, maar er bleef oude tekst op het scherm staan. (Code later aangepast)  (Nu opgelost) |
| **Spel winnen (10 rondes)** | Scherm zegt "YOU WIN!" en speelt een overwinningsmuziekje. | Muziekje speelde af, maar de tekst kwam nooit op het schermpje. (Code later aangepast) | (Nu opgelost) |
| **Meerdere knoppen tegelijk indrukken** | Spel mag niet crashen of vastlopen. | Spel pakt gewoon de eerste knop die hij registreert en loopt niet vast.

---

## 8. Problemen en Oplossingen
*Tijdens het maken liep ik tegen een paar problemen aan. Hieronder leg ik uit hoe ik die heb opgelost.*

1.  **Lampjes bleven uit bij de start**
    *   Wat was er mis: De lampjes bleven uit omdat ik ze niet op de juiste positie had aangesloten.
    *   Oplossing: De kabeltjes controleren en ze op de juiste plek insteken.
2.  **Dubbele knopregistratie:**
    *   *Wat was er mis: De knopjes denderden (bouncen). De Arduino las heel snel achter elkaar dat de knop open en dicht ging.
    *   *Oplossing:* Een kleine delay ingebouwd nadat een knop is ingedrukt, zodat hij even wacht met opnieuw uitlezen.
3.  **Spel toonde steeds dezelfde volgorde:**
    *   *Wat was er mis: De willekeurige generator begon telkens bij dezelfde waarde bij het opstarten.
    *   *Oplossing:* `randomSeed(analogRead(0))` toegevoegd in de setup. Omdat pin A0 niet is aangesloten, leest hij ruis en is het spel elke keer anders.
4.  **Schema volgen was een aardig groot probleem. Ik wil mij hier de volgende keer beter op voorbereiden en zorgen dat ik daadwerkelijk genoeg energie heb om het schema goed af te werken.**
    *   Oplossing::* Gelukkig is dit geen probleem met de volgende keuzedelen omdat ik dan niet met veel examens zit. Deze keer was het erg lastig omdat ik ook dingen moest voorbereiden voor alle AVO examens. Hierdoor had ik minder tijd.

---

## 9. Wat kan de volgende keer beter? (Verbeterpunten)
*   Het spel is nu gebouwd op een breadboard met losse kabeltjes. De volgende keer zou ik de onderdelen op een printplaat willen solderen zodat het steviger is en niet losraakt. Of tenminste iets 3d printen zodat het steviger in mekaar zit.
*   De knoppen worden nu uitgelezen met een simpele loop. Dit kan beter met 'interrupts', zodat de Arduino de knoppen direct registreert, zelfs als de code bezig is met een delay. Hier ben ik veel te laat achter gekomen en dit weet ik nu voor de toekomst.
*   Volgende keer wil ik meer lampjes toevoegen en het daardoor veel moeilijker maken voor de speler!
