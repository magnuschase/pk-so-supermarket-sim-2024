# Test 1

_Zawsze działają 2 stanowiska kasowe_

### Założenie

Niezależnie od ilości klientów, zawsze powinny być dostępne minimum 2 kasy. Gdy liczba klientów spadnie poniżej 4 dla K = 2, kasa nie powinna się zamknąć.

### Przebieg testu

Ustawiam następującą konfiguracje:

```
QUEUE_PER_CUSTOMER = 10
SHOPPING_TIME_MIN = 10
SHOPPING_TIME_MAX = 15
CUSTOMER_WAIT_MIN = 5
CUSTOMER_WAIT_MAX = 15
FIRE_WAIT_MIN = 1
FIRE_WAIT_MAX = 2
```

Przy takich ustawieniach przynajmniej 1 raz powinna zdarzyc sie sytuacja, w której liczba klientów spadnie ponizej 4.

Logi z przebiegu testu:

```
[18:02:48] pid:28153 >  Ding dong!  Customer entered.  Total customers: 1
[18:03:00] pid:28153 >  Ding dong!  Customer entered.  Total customers: 2
[18:03:02] pid:28153 >  Cashier 0.  Customer queued.  Queue length: 1
[18:03:08] pid:28153 >  Ding dong!  Customer entered.  Total customers: 3
[18:03:12] pid:28153 >  Ding dong!  Customer left.  Total customers: 2
[18:03:13] pid:28153 >  Cashier 0.  Customer queued.  Queue length: 1
[18:03:15] pid:28153 >  Ding dong!  Customer entered.  Total customers: 3
[18:03:22] pid:28153 >  Cashier 0.  Customer queued.  Queue length: 2
[18:03:23] pid:28153 >  Ding dong!  Customer left.  Total customers: 2
[18:03:23] pid:28153 >  Ding dong!  Customer entered.  Total customers: 3
[18:03:29] pid:28153 >  Cashier 0.  Customer queued.  Queue length: 2
[18:03:33] pid:28153 >  Ding dong!  Customer entered.  Total customers: 4
[18:03:35] pid:28153 >  Cashier 1.  Customer queued.  Queue length: 1
[18:03:42] pid:28153 >  Ding dong!  Customer left.  Total customers: 3
[18:03:45] pid:28153 >  Ding dong!  Customer left.  Total customers: 2
[18:03:45] pid:28153 >  Ding dong!  Customer entered.  Total customers: 3
[18:03:46] pid:28153 >  Cashier 0.  Customer queued.  Queue length: 2
[18:03:49] pid:28153 >  Ding dong!  Customer left.  Total customers: 2
[18:03:55] pid:28155 >  DANGER! DANGER!  Fire alarm triggered.
[18:03:56] pid:28083 >  Fire alarm received: Fire alarm!
```

Jak widać, gdy liczba klientów spadła z 4 na 3, nie wyświetlił się komunikat o zamknięciu kasy.

## Wynik testu

Pozytywny! Ilość stanowisk kasowych nigdy nie spadnie ponizej 2.
