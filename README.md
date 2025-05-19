# Tamagotchi 
## Architetture dei sistemi di elaborazione
Il repository contiene i progetti extra points del corso Architetture dei sistemi di elaborazione al Politecnico di Torino per l'anno 2022/2023.

Il progetto consiste nello sviluppo di un gioco Tamagotchi semplificato sulla scheda LandTiger LPC1768, utilizzando linguaggi C e assembly ARM, all’interno dell’ambiente di sviluppo Keil µVision 5. Il gioco è una simulazione di un animaletto virtuale, con cui l’utente può interagire tramite le periferiche hardware della scheda, schermo, touch screen sensor, speaker, joystick, pulsanti, led, e timer.

### 🎮 **Funzionalità del gioco**

#### 1. **Visualizzazione e animazione iniziale**

* Sullo **schermo LCD** viene disegnato il Tamagotchi con una **forma personalizzata** (un panda).
* È prevista una **semplice animazione** che si aggiorna **ogni secondo** (occhi che lampeggiano).

---

#### 2. **Stato del Tamagotchi (Status Bar in alto)**

Sempre visibile in alto, mostra:

* **Età**: in formato ore\:minuti\:secondi (counter aggiornato ogni secondo).
* **Felicità (Happiness)**: scala a barre (da 0 a 5).
* **Sazietà (Satiety)**: scala a barre (da 0 a 5).

> ⚠️ **Happiness** e **Satiety** si **degradano ogni 5 secondi** (scende di 1 "bar").

---

#### 3. **Menu del cibo (Food Menu in basso)**

Sempre visibile in basso. Contiene 2 opzioni:

* **Meal** → aumenta la Satiety
* **Snack** → aumenta la Happiness

Navigazione con **joystick**:

* **LEFT/RIGHT** per muoversi tra le voci
* **SELECT** per selezionare

#### 🍽️ **Animazione di alimentazione**

Quando si sceglie un cibo:

* Compare un **simbolo** del cibo
* Il Tamagotchi si **muove verso il cibo**, lo "mangia" per almeno 1 secondo
* Durante questo tempo, il menu è **disabilitato**
* Dopo l’animazione:

  * Snack → +1 Happiness
  * Meal → +1 Satiety

---

#### 4. **Logica di abbandono (Runaway Sequence)**

Se **Happiness o Satiety arrivano a 0**, il Tamagotchi **scappa via**:

* Viene attivata una **breve animazione di uscita** dallo schermo
* Lo schermo mostra un **messaggio o icona** di abbandono
* Il **timer dell’età si ferma**
* Il menu del cibo viene **sostituito con un pulsante di Reset**

---

#### 5. **Reset del gioco**

Dopo che il Tamagotchi è fuggito:

* L’utente può premere **SELECT (joystick)** per fare reset
* Si genera un **nuovo Tamagotchi**, con:

  * Happiness e Satiety al massimo
  * Timer dell’età azzerato (00:00:00)
  * Animazione iniziale ripristinata

---

### 🧠 **Logica interna**

Il progetto è un **sistema a stati**:

* Stato attivo: il Tamagotchi è presente e interagisce
* Stato di alimentazione: animazione di eating in corso
* Stato abbandonato: Tamagotchi è fuggito
* Stato reset: attesa di reset

Usa:

* **Timer hardware/software** per:

  * aggiornare l’età
  * aggiornare l’animazione
  * decrementare Happiness/Satiety
* **Interrupts** per joystick, pulsanti
* **Display driver** per disegnare grafica e testo
* **Possibile uso di suoni** via PWM per lo speaker

Valutazione: 4/4.
