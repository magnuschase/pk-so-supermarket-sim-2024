# Test 3

_Jeśli w kolejce do kasy czekali klienci (przed ogłoszeniem decyzji o jej zamknięciu) to powinni
zostać obsłużeni przez tę kasę._

### Założenie

Gdy liczba klientów spadnie ponizej K\*(N-1), to jedna z kas powinna zostać zamknięta, ale tylko i wyłącznie w wypadku, gdy ostatnia otwarta kasa jest aktualnie pusta.

### Przebieg testu

Używam domyślnej konfiguracji symulacji.

Wycinek logów z przebiegu testu:

```
[18:19:52] pid:47872 >  Ding dong!  Customer entered.  Total customers: 1
[18:20:04] pid:47872 >  Ding dong!  Customer entered.  Total customers: 2
[18:20:17] pid:47872 >  Ding dong!  Customer entered.  Total customers: 3
[18:20:32] pid:47872 >  Ding dong!  Customer entered.  Total customers: 4
[18:20:46] pid:47872 >  Ding dong!  Customer entered.  Total customers: 5
[18:20:46] pid:47873 >  Opened a new cash register. Available cash registers: 3
[18:20:51] pid:47872 >  Cashier 0.  Customer queued.  Queue length: 1
[18:20:52] pid:47872 >  Cashier 2.  Customer queued.  Queue length: 1
[18:20:59] pid:47872 >  Cashier 0.  Customer queued.  Queue length: 2
[18:20:59] pid:47872 >  Ding dong!  Customer entered.  Total customers: 6
[18:21:01] pid:47872 >  Ding dong!  Customer left.  Total customers: 5
[18:21:02] pid:47872 >  Ding dong!  Customer left.  Total customers: 4
[18:21:06] pid:47872 >  Ding dong!  Customer entered.  Total customers: 5
[18:21:19] pid:47872 >  Ding dong!  Customer left.  Total customers: 4
[18:21:19] pid:47872 >  Ding dong!  Customer entered.  Total customers: 5
[18:21:20] pid:47872 >  Cashier 1.  Customer queued.  Queue length: 1
[18:21:23] pid:47872 >  Cashier 0.  Customer queued.  Queue length: 1
[18:21:28] pid:47872 >  Ding dong!  Customer entered.  Total customers: 6
[18:21:30] pid:47872 >  Ding dong!  Customer left.  Total customers: 5
[18:21:33] pid:47872 >  Ding dong!  Customer left.  Total customers: 4
[18:21:36] pid:47872 >  Cashier 2.  Customer queued.  Queue length: 1
[18:21:37] pid:47872 >  Ding dong!  Customer entered.  Total customers: 5
[18:21:45] pid:47872 >  Cashier 0.  Customer queued.  Queue length: 1
[18:21:46] pid:47872 >  Ding dong!  Customer left.  Total customers: 4
[18:21:47] pid:47872 >  Cashier 0.  Customer queued.  Queue length: 2
[18:21:52] pid:47872 >  Ding dong!  Customer entered.  Total customers: 5
[18:21:55] pid:47872 >  Ding dong!  Customer left.  Total customers: 4
[18:22:07] pid:47872 >  Ding dong!  Customer left.  Total customers: 3
[18:22:07] pid:47873 >  Closed a cash register. Available cash registers: 2
[18:22:08] pid:47872 >  Ding dong!  Customer entered.  Total customers: 4
[18:22:09] pid:47872 >  Cashier 0.  Customer queued.  Queue length: 1
```

## Wynik testu

Pozytywny! Trzecia kasa (Cashier 2) nie została zamknięta zanim wszyscy klienci w kolejce zostali obsłużeni, nawet gdy liczba klientów spadła poniżej wymaganego pułapu do tego, by pozostała ona otwarta. Została ona zamknięta dopiero, gdy w jej kolejce pozostało 0 osób.
