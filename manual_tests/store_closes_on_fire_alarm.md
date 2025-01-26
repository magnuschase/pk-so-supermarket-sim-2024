# Test 4

_Na sygnał o pożarze – sygnał wysyła strażak - klienci natychmiast opuszczają supermarket bez robienia zakupów, a następnie po wyjściu klientów zamykane są wszystkie kasy._

### Założenie

Działanie programu zostaje zakończone w wyniku podniesienia alarmu pożarowego przez strażaka. Program nie czeka na nic - klienci nie kończą zakupów, wszystko zostaje przerwane. Po zakończeniu programu nie pozostaje żaden proces zombie.

### Przebieg testu

Wywołanie `ps` przed rozpoczęciem działania programu:
<img width="1019" alt="Screenshot 2025-01-26 at 18 30 26" src="https://github.com/user-attachments/assets/4f2deb93-803d-4ad5-b9ea-9be021e66f02" />


Ustawiam następującą konfiguracje:

```
QUEUE_PER_CUSTOMER = 5
SHOPPING_TIME_MIN = 1
SHOPPING_TIME_MAX = 2
CUSTOMER_WAIT_MIN = 1
CUSTOMER_WAIT_MAX = 2
FIRE_WAIT_MIN = 0
FIRE_WAIT_MAX = 1
```

Wywołanie `ps` w trakcie działania programu (`CTRL+Z`, a następnie `fg`):
<img width="1023" alt="Screenshot 2025-01-26 at 18 30 58" src="https://github.com/user-attachments/assets/bf2f718a-f1a2-4234-938f-d8f14a162c29" />


Logi z przebiegu testu:

```
[18:30:40] pid:54151 >  Ding dong!  Customer entered.  Total customers: 1
[18:30:41] pid:54151 >  Cashier 1.  Customer queued.  Queue length: 1
[18:30:41] pid:54151 >  Ding dong!  Customer entered.  Total customers: 2
[18:30:42] pid:54151 >  Cashier 0.  Customer queued.  Queue length: 1
[18:30:42] pid:54151 >  Ding dong!  Customer entered.  Total customers: 3
[18:30:43] pid:54151 >  Ding dong!  Customer entered.  Total customers: 4
[18:30:43] pid:54151 >  Cashier 0.  Customer queued.  Queue length: 2
[18:31:10] pid:54151 >  Cashier 1.  Customer queued.  Queue length: 2
[18:31:10] pid:54151 >  Ding dong!  Customer left.  Total customers: 3
[18:31:10] pid:54151 >  Ding dong!  Customer left.  Total customers: 2
[18:31:10] pid:54151 >  Ding dong!  Customer left.  Total customers: 1
[18:31:10] pid:54151 >  Ding dong!  Customer entered.  Total customers: 2
[18:31:10] pid:54153 >  DANGER! DANGER!  Fire alarm triggered.
[18:31:11] pid:54087 >  Fire alarm received: Fire alarm!
```

Wywołanie `ps` po zakończeniu działania programu:
<img width="1032" alt="Screenshot 2025-01-26 at 18 31 30" src="https://github.com/user-attachments/assets/6b73904b-56b8-4acd-9cb9-7fd0e11aca14" />


## Wynik testu

Pozytywny! Trzecia kasa (Cashier 2) nie została zamknięta zanim wszyscy klienci w kolejce zostali obsłużeni, nawet gdy liczba klientów spadła poniżej wymaganego pułapu do tego, by pozostała ona otwarta. Została ona zamknięta dopiero, gdy w jej kolejce pozostało 0 osób.
