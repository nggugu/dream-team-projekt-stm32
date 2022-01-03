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
  
## Korisni linkovi
I2C komunikacija na STM32: https://www.youtube.com/watch?v=cvmQNTVJrzs <br>
Pisanje drivera: https://www.youtube.com/watch?v=_JQAve05o_0 <br>
Općenito dosta dobar kanal za STM32, PCB, embedded i ostalo: https://www.youtube.com/c/PhilS94/featured
