# Test 2

_Na każdych K klientów znajdujących się na terenie supermarketu powinno przypadać min. 1 czynne stanowisko kasowe._

_Jeśli liczba klientów jest mniejsza niż K\*(N-1), gdzie N oznacza liczbę czynnych kas, to jedna z kas zostaje zamknięta._

### Założenie

W supermarkecie jest łącznie 10 kas. Dla K = 2, maksymalna ilość otwartych kas powinna zostać osiągnięta przy 20 klientach. Przy kazdej nieparzystej liczbie klientów większej bądź równej 5 powinna być otwierana nowa kasa. Gdy liczba klientów spada ponizej K\*(N-1), gdzie N to liczba czynnych kas, jedna z kas powinna zostać zamknięta.

### Przebieg testu

Ustawiam następującą konfiguracje:

```
QUEUE_PER_CUSTOMER = 10
SHOPPING_TIME_MIN = 5
SHOPPING_TIME_MAX = 10
CUSTOMER_WAIT_MIN = 1
CUSTOMER_WAIT_MAX = 2
FIRE_WAIT_MIN = 1
FIRE_WAIT_MAX = 2
```

Przy takich ustawieniach liczba klientów powinna szybko rosnąć, co pomoze nam zobrazować dostępne kasy.

Logi z przebiegu testu:

```
[18:10:18] pid:31990 >  Ding dong!  Customer entered.  Total customers: 1
[18:10:19] pid:31990 >  Ding dong!  Customer entered.  Total customers: 2
[18:10:20] pid:31990 >  Ding dong!  Customer entered.  Total customers: 3
[18:10:21] pid:31990 >  Ding dong!  Customer entered.  Total customers: 4
[18:10:22] pid:31990 >  Ding dong!  Customer entered.  Total customers: 5
[18:10:22] pid:31991 >  Opened a new cash register. Available cash registers: 3
[18:10:23] pid:31990 >  Ding dong!  Customer entered.  Total customers: 6
[18:10:24] pid:31990 >  Ding dong!  Customer entered.  Total customers: 7
[18:10:24] pid:31991 >  Opened a new cash register. Available cash registers: 4
[18:10:25] pid:31990 >  Ding dong!  Customer entered.  Total customers: 8
[18:10:26] pid:31990 >  Ding dong!  Customer entered.  Total customers: 9
[18:10:26] pid:31991 >  Opened a new cash register. Available cash registers: 5
[18:10:27] pid:31990 >  Cashier 0.  Customer queued.  Queue length: 1
[18:10:27] pid:31990 >  Cashier 2.  Customer queued.  Queue length: 1
[18:10:27] pid:31990 >  Cashier 3.  Customer queued.  Queue length: 1
[18:10:27] pid:31990 >  Ding dong!  Customer entered.  Total customers: 10
[18:10:28] pid:31990 >  Cashier 2.  Customer queued.  Queue length: 2
[18:10:28] pid:31990 >  Ding dong!  Customer entered.  Total customers: 11
[18:10:28] pid:31991 >  Opened a new cash register. Available cash registers: 6
[18:10:29] pid:31990 >  Cashier 3.  Customer queued.  Queue length: 2
[18:10:29] pid:31990 >  Ding dong!  Customer entered.  Total customers: 12
[18:10:30] pid:31990 >  Ding dong!  Customer entered.  Total customers: 13
[18:10:30] pid:31991 >  Opened a new cash register. Available cash registers: 7
[18:10:31] pid:31990 >  Cashier 3.  Customer queued.  Queue length: 3
[18:10:31] pid:31990 >  Cashier 0.  Customer queued.  Queue length: 2
[18:10:31] pid:31990 >  Ding dong!  Customer entered.  Total customers: 14
[18:10:32] pid:31990 >  Ding dong!  Customer entered.  Total customers: 15
[18:10:32] pid:31991 >  Opened a new cash register. Available cash registers: 8
[18:10:33] pid:31990 >  Cashier 5.  Customer queued.  Queue length: 1
[18:10:33] pid:31990 >  Ding dong!  Customer entered.  Total customers: 16
[18:10:34] pid:31990 >  Ding dong!  Customer entered.  Total customers: 17
[18:10:34] pid:31991 >  Opened a new cash register. Available cash registers: 9
[18:10:35] pid:31990 >  Cashier 1.  Customer queued.  Queue length: 1
[18:10:35] pid:31990 >  Cashier 0.  Customer queued.  Queue length: 3
[18:10:35] pid:31990 >  Ding dong!  Customer entered.  Total customers: 18
[18:10:36] pid:31990 >  Cashier 2.  Customer queued.  Queue length: 3
[18:10:36] pid:31990 >  Cashier 4.  Customer queued.  Queue length: 1
[18:10:36] pid:31990 >  Cashier 6.  Customer queued.  Queue length: 1
[18:10:36] pid:31990 >  Ding dong!  Customer entered.  Total customers: 19
[18:10:36] pid:31991 >  Opened a new cash register. Available cash registers: 10
[18:10:37] pid:31990 >  Ding dong!  Customer left.  Total customers: 18
[18:10:37] pid:31990 >  Ding dong!  Customer left.  Total customers: 17
[18:10:37] pid:31991 >  Closed a cash register. Available cash registers: 9
[18:10:37] pid:31990 >  Ding dong!  Customer left.  Total customers: 16
[18:10:37] pid:31990 >  Cashier 2.  Customer queued.  Queue length: 3
[18:10:37] pid:31990 >  Ding dong!  Customer entered.  Total customers: 17
[18:10:38] pid:31990 >  Ding dong!  Customer entered.  Total customers: 18
[18:10:39] pid:31990 >  Cashier 3.  Customer queued.  Queue length: 3
[18:10:39] pid:31990 >  Ding dong!  Customer entered.  Total customers: 19
[18:10:39] pid:31991 >  Opened a new cash register. Available cash registers: 10
[18:10:40] pid:31990 >  Cashier 3.  Customer queued.  Queue length: 4
[18:10:40] pid:31990 >  Ding dong!  Customer entered.  Total customers: 20
[18:10:41] pid:31990 >  Cashier 9.  Customer queued.  Queue length: 1
[18:10:41] pid:31990 >  Cashier 4.  Customer queued.  Queue length: 2
[18:10:41] pid:31990 >  Ding dong!  Customer entered.  Total customers: 21
[18:10:42] pid:31990 >  Cashier 7.  Customer queued.  Queue length: 1
[18:10:42] pid:31990 >  Ding dong!  Customer entered.  Total customers: 22
[18:10:43] pid:31990 >  Ding dong!  Customer left.  Total customers: 21
[18:10:43] pid:31990 >  Cashier 3.  Customer queued.  Queue length: 5
[18:10:43] pid:31990 >  Ding dong!  Customer entered.  Total customers: 22
[18:10:44] pid:31990 >  Cashier 5.  Customer queued.  Queue length: 1
[18:10:44] pid:31990 >  Ding dong!  Customer entered.  Total customers: 23
[18:10:45] pid:31990 >  Ding dong!  Customer left.  Total customers: 22
[18:10:45] pid:31990 >  Ding dong!  Customer entered.  Total customers: 23
[18:10:46] pid:31990 >  Ding dong!  Customer left.  Total customers: 22
[18:10:46] pid:31990 >  Ding dong!  Customer left.  Total customers: 21
[18:10:46] pid:31990 >  Cashier 6.  Customer queued.  Queue length: 1
[18:10:46] pid:31990 >  Cashier 5.  Customer queued.  Queue length: 2
[18:10:46] pid:31990 >  Ding dong!  Customer entered.  Total customers: 22
[18:10:47] pid:31990 >  Ding dong!  Customer entered.  Total customers: 23
[18:10:48] pid:31990 >  Ding dong!  Customer left.  Total customers: 22
[18:10:48] pid:31990 >  Ding dong!  Customer entered.  Total customers: 23
[18:10:49] pid:31990 >  Ding dong!  Customer left.  Total customers: 22
[18:10:49] pid:31990 >  Cashier 5.  Customer queued.  Queue length: 3
[18:10:49] pid:31990 >  Cashier 5.  Customer queued.  Queue length: 4
[18:10:49] pid:31990 >  Cashier 4.  Customer queued.  Queue length: 2
[18:10:49] pid:31990 >  Ding dong!  Customer entered.  Total customers: 23
[18:10:50] pid:31990 >  Cashier 8.  Customer queued.  Queue length: 1
[18:10:50] pid:31990 >  Ding dong!  Customer entered.  Total customers: 24
[18:10:51] pid:31990 >  Ding dong!  Customer left.  Total customers: 23
[18:10:51] pid:31990 >  Ding dong!  Customer left.  Total customers: 22
[18:10:51] pid:31990 >  Cashier 2.  Customer queued.  Queue length: 3
[18:10:51] pid:31990 >  Ding dong!  Customer entered.  Total customers: 23
[18:10:52] pid:31990 >  Ding dong!  Customer left.  Total customers: 22
[18:10:52] pid:31990 >  Ding dong!  Customer entered.  Total customers: 23
[18:10:53] pid:31990 >  Cashier 8.  Customer queued.  Queue length: 2
[18:10:53] pid:31990 >  Ding dong!  Customer entered.  Total customers: 24
[18:10:54] pid:31990 >  Ding dong!  Customer left.  Total customers: 23
[18:10:54] pid:31990 >  Ding dong!  Customer entered.  Total customers: 24
[18:10:55] pid:31990 >  Cashier 8.  Customer queued.  Queue length: 3
[18:10:55] pid:31990 >  Cashier 7.  Customer queued.  Queue length: 1
[18:10:55] pid:31990 >  Ding dong!  Customer entered.  Total customers: 25
[18:10:56] pid:31990 >  Ding dong!  Customer left.  Total customers: 24
[18:10:56] pid:31990 >  Cashier 7.  Customer queued.  Queue length: 2
[18:10:56] pid:31990 >  Ding dong!  Customer entered.  Total customers: 25
[18:10:57] pid:31990 >  Cashier 9.  Customer queued.  Queue length: 1
[18:10:57] pid:31990 >  Cashier 1.  Customer queued.  Queue length: 1
[18:10:57] pid:31990 >  Ding dong!  Customer entered.  Total customers: 26
[18:10:58] pid:31990 >  Ding dong!  Customer entered.  Total customers: 27
[18:10:59] pid:31990 >  Cashier 2.  Customer queued.  Queue length: 4
[18:10:59] pid:31990 >  Cashier 9.  Customer queued.  Queue length: 2
[18:10:59] pid:31990 >  Ding dong!  Customer entered.  Total customers: 28
[18:11:00] pid:31990 >  Ding dong!  Customer left.  Total customers: 27
[18:11:00] pid:31990 >  Cashier 0.  Customer queued.  Queue length: 2
[18:11:00] pid:31990 >  Ding dong!  Customer entered.  Total customers: 28
[18:11:01] pid:31990 >  Ding dong!  Customer left.  Total customers: 27
[18:11:01] pid:31990 >  Ding dong!  Customer left.  Total customers: 26
[18:11:01] pid:31990 >  Ding dong!  Customer entered.  Total customers: 27
[18:11:02] pid:31990 >  Cashier 8.  Customer queued.  Queue length: 3
[18:11:02] pid:31990 >  Cashier 3.  Customer queued.  Queue length: 4
[18:11:02] pid:31990 >  Ding dong!  Customer entered.  Total customers: 28
[18:11:03] pid:31990 >  Ding dong!  Customer entered.  Total customers: 29
[18:11:04] pid:31990 >  Ding dong!  Customer entered.  Total customers: 30
[18:11:05] pid:31990 >  Ding dong!  Customer left.  Total customers: 29
[18:11:05] pid:31990 >  Ding dong!  Customer left.  Total customers: 28
[18:11:05] pid:31990 >  Cashier 2.  Customer queued.  Queue length: 5
[18:11:05] pid:31990 >  Ding dong!  Customer entered.  Total customers: 29
[18:11:06] pid:31990 >  Ding dong!  Customer left.  Total customers: 28
[18:11:06] pid:31990 >  Ding dong!  Customer left.  Total customers: 27
[18:11:06] pid:31990 >  Cashier 5.  Customer queued.  Queue length: 3
[18:11:06] pid:31990 >  Cashier 2.  Customer queued.  Queue length: 5
[18:11:06] pid:31990 >  Cashier 1.  Customer queued.  Queue length: 2
[18:11:06] pid:31990 >  Ding dong!  Customer entered.  Total customers: 28
[18:11:07] pid:31990 >  Ding dong!  Customer left.  Total customers: 27
[18:11:07] pid:31990 >  Ding dong!  Customer left.  Total customers: 26
[18:11:07] pid:31990 >  Ding dong!  Customer left.  Total customers: 25
[18:11:07] pid:31990 >  Ding dong!  Customer entered.  Total customers: 26
[18:11:08] pid:31990 >  Cashier 7.  Customer queued.  Queue length: 2
[18:11:08] pid:31990 >  Ding dong!  Customer entered.  Total customers: 27
[18:11:09] pid:31990 >  Ding dong!  Customer left.  Total customers: 26
[18:11:09] pid:31990 >  Ding dong!  Customer left.  Total customers: 25
[18:11:09] pid:31990 >  Cashier 0.  Customer queued.  Queue length: 2
[18:11:09] pid:31990 >  Ding dong!  Customer entered.  Total customers: 26
[18:11:10] pid:31990 >  Cashier 6.  Customer queued.  Queue length: 1
[18:11:10] pid:31990 >  Ding dong!  Customer entered.  Total customers: 27
[18:11:11] pid:31990 >  Cashier 5.  Customer queued.  Queue length: 4
[18:11:11] pid:31990 >  Cashier 9.  Customer queued.  Queue length: 2
[18:11:11] pid:31990 >  Cashier 4.  Customer queued.  Queue length: 1
[18:11:11] pid:31990 >  Ding dong!  Customer entered.  Total customers: 28
[18:11:12] pid:31990 >  Ding dong!  Customer entered.  Total customers: 29
[18:11:13] pid:31990 >  Ding dong!  Customer left.  Total customers: 28
[18:11:13] pid:31990 >  Cashier 6.  Customer queued.  Queue length: 2
[18:11:13] pid:31990 >  Ding dong!  Customer entered.  Total customers: 29
[18:11:14] pid:31990 >  Cashier 3.  Customer queued.  Queue length: 4
[18:11:14] pid:31990 >  Ding dong!  Customer entered.  Total customers: 30
[18:11:15] pid:31990 >  Cashier 4.  Customer queued.  Queue length: 2
[18:11:15] pid:31990 >  Ding dong!  Customer entered.  Total customers: 31
[18:11:16] pid:31990 >  Ding dong!  Customer left.  Total customers: 30
[18:11:16] pid:31990 >  Ding dong!  Customer entered.  Total customers: 31
[18:11:17] pid:31990 >  Cashier 6.  Customer queued.  Queue length: 3
[18:11:17] pid:31990 >  Ding dong!  Customer entered.  Total customers: 32
[18:11:18] pid:31990 >  Cashier 8.  Customer queued.  Queue length: 3
[18:11:18] pid:31990 >  Ding dong!  Customer entered.  Total customers: 33
[18:11:19] pid:31990 >  Ding dong!  Customer left.  Total customers: 32
[18:11:19] pid:31990 >  Ding dong!  Customer left.  Total customers: 31
[18:11:19] pid:31990 >  Cashier 0.  Customer queued.  Queue length: 3
[18:11:19] pid:31990 >  Ding dong!  Customer entered.  Total customers: 32
[18:11:20] pid:31990 >  Ding dong!  Customer left.  Total customers: 31
[18:11:20] pid:31990 >  Ding dong!  Customer left.  Total customers: 30
[18:11:20] pid:31990 >  Ding dong!  Customer left.  Total customers: 29
[18:11:20] pid:31990 >  Cashier 7.  Customer queued.  Queue length: 2
[18:11:20] pid:31990 >  Ding dong!  Customer entered.  Total customers: 30
[18:11:21] pid:31990 >  Ding dong!  Customer left.  Total customers: 29
[18:11:21] pid:31990 >  Ding dong!  Customer left.  Total customers: 28
[18:11:21] pid:31990 >  Ding dong!  Customer entered.  Total customers: 29
[18:11:22] pid:31990 >  Cashier 7.  Customer queued.  Queue length: 3
[18:11:22] pid:31990 >  Ding dong!  Customer entered.  Total customers: 30
[18:11:23] pid:31990 >  Cashier 5.  Customer queued.  Queue length: 4
[18:11:23] pid:31990 >  Ding dong!  Customer entered.  Total customers: 31
[18:11:24] pid:31990 >  Cashier 4.  Customer queued.  Queue length: 2
[18:11:24] pid:31990 >  Ding dong!  Customer entered.  Total customers: 32
[18:11:25] pid:31992 >  DANGER! DANGER!  Fire alarm triggered.
[18:11:26] pid:31832 >  Fire alarm received: Fire alarm!
```

## Wynik testu

Pozytywny! Ilość stanowisk kasowych zawsze wynosiła przynajmniej 1 na K klientów obecnych w sklepie. Ponadto kasa została zamknięta wyłącznie w jednym przypadku - gdy liczba klientów spadła z 20 na 17, dzięki czemu jedna z nich mogła się zwolnić.
