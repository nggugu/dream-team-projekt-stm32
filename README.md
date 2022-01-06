# Preddiplomski projekt, [Džapini anđeli](https://www.youtube.com/watch?v=dQw4w9WgXcQ) - STM32
Ovo je repozitorij za dio projekta koji se tiče STM32. <br>
Link na repozitorij za web stranicu: <i> Ovdje se unosi link </i>

## Upute za koristenje BME280 drivera
1. Deklarirati strukturu tipa `BME280`. U njoj će se nalaziti svi podatci sa senzora.
2. Inicijalizirati senzor pomoću funkcije `BME280_Initialise(BME280 *dev, I2C_HandleTypeDef *i2c_handle)`. Prvi argument je pokazivač na strukturu senzora, a drugi argument je adresa I<sup>2</sup>C handlera. U našem slučaju drugi argument mora biti `&hi2c3`, jer koristimo I2C3 periferiju.
3. Senzor će na početku odraditi mjerenje. Kada se mjerenje želi ponovno obaviti potrebno je prvo pozvati funkciju `BME280_PerformMeasurements(BME280 *dev)`.

Vrijednosti mjerenja su dostupne u strukturi senzora i nalaze se u varijablama:
* temp (temperatura zrak)
* press (tlak zraka)
* hum (vlažnost zraka)

<i> Napomena: funkcije `BME280_Initialise` i `BME280_PerformMeasurements` vraćaju broj pogrešaka koje su se dogodile tijekom komunikacije sa senzorom u formatu `uint8_t`. </i>

## Upute za korištenje senzora za vlagu tla
<b> Senzor još nije spreman za upotrebu. Treba ga kalibrirati. </b>

## Upute za korištenje ESP8266 WiFi drivera

### Spajanje ESP-01 modula
Slika rasporeda pinova na ESP-01 pločici može se naći [ovdje](https://www.makerlab-electronics.com/?attachment_id=11461). <br>
Pinove je potrebno spojiti na sljedeći način (u formatu ESP-01 pin <-> STM32 Discovery pin):<br>
RXD <-> PB6 (TX) <br>
VCC <-> 3V <br>
CHPD <-> 3V <br>
GND <-> GND <br>
TXD <-> PB7 (RX) <br>

### Korištenje drivera
1. Prije početka rada s WiFi-jem pozvati funkciju: `int8_t WIFI_Init(char *ssid, char *pwd)` Parametri funkcije su ime i lozinka mreže na koju se treba spojiti. Povratna vrijednost je 0 ako nije bilo grešaka i -1 ako je došlo do greške. <br>
<i><b>Napomena:</b> ESP nema mogućnost spajanja na eduroam mrežu s trenutnim firmware-om. Ako radite na faksu, najbolje je spojiti se na AP od mobitela.</i>

2. Za slanje podataka na server koristiti funkciju: `int8_t WIFI_SendRequestWithParams(char *hostname, char *path, double temp, double moisture, double humidity, double waterLevel)` Hostname servera je ekantica.herokuapp.com, bez sheme na početku (http:// ili https://). Path za slanje podataka je /data. Ostali parametri su vrijednosti očitanja senzora koje se žele poslati, a prilikom slanja zahtjeva zaokružuju se na dvije decimale. Funkcija na temelju odgovora servera vraća 0 ako nije potrebno uključiti pumpu, a 1 ako jest. Ako je došlo do pogreške, povratna vrijednost je -1.

<b>VAŽNO:</b> Budući da komunikacija s ESP-om funkcionira na principu slanja komande i zatim čekanja odgovora, moguće je da navedene funkcije zapnu u beskonačnoj petlji ako dođe do nepredviđene greške, npr. ako se dogodi prekid komunikacije s ESP-om ili je nemoguće parsirati HTTP odgovor servera. U planu je dodavanje timeout funkcionalnosti, ali dok to ne bude implementirano predlažem sljedeću metodu: kako bi se lakše uočilo da je došlo do zastoja, signalizirati uspješno izvršavanje funkcije, npr. paljenjem LED-ice ili ispisom na LCD nakon što je funkcija vratila vrijednost. Ako takav signal izostane, moguće je zaključiti da se dogodila beskonačna petlja.
  
## Korisni linkovi
I2C komunikacija na STM32: https://www.youtube.com/watch?v=cvmQNTVJrzs <br>
Pisanje drivera: https://www.youtube.com/watch?v=_JQAve05o_0 <br>
Općenito dosta dobar kanal za STM32, PCB, embedded i ostalo: https://www.youtube.com/c/PhilS94/featured
