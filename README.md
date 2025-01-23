# Systemy operacyjne - projekt 2024/2025

**Imię i nazwisko**: Jakub Kapała

**Numer albumu**: 151885

**Kierunek**: Informatyka, niestacjonarne

**Temat 10 - Supermarket**

## Założenia projektowe (testy)

W pewnym supermarkecie jest łącznie 10 kas. Zasady ich działania przyjęte przez kierownika sklepu
są następujące:

- Zawsze działają min. 2 stanowiska kasowe.
- Na każdych K klientów znajdujących się na terenie supermarketu powinno przypadać min. 1
  czynne stanowisko kasowe.
- Jeśli liczba klientów jest mniejsza niż K\*(N-1), gdzie N oznacza liczbę czynnych kas, to jedna z kas zostaje zamknięta.
- Jeśli w kolejce do kasy czekali klienci (przed ogłoszeniem decyzji o jej zamknięciu) to powinni
  zostać obsłużeni przez tę kasę.
- Klienci przychodzą do supermarketu w losowych momentach czasu i przebywają w nim przez pewien
  określony losowy dla każdego z nich czas. Na sygnał o pożarze – sygnał wysyła strażak - klienci natychmiast opuszczają supermarket bez robienia zakupów, a następnie po wyjściu klientów
  zamykane są wszystkie kasy.

## Ogólny opis kodu

Kod projektu składa się z kilku głównych komponentów:

- [`supermarket.c`](https://github.com/magnuschase/pk-so-supermarket-sim-2024/blob/1a46ec3494b0fa2957a418a8726b28ca4b291870/supermarket.c): Główny plik programu, który inicjalizuje zasoby, uruchamia procesy klientów, menedżera i strażaka oraz zarządza zamykaniem supermarketu.
- [`customer.c`](https://github.com/magnuschase/pk-so-supermarket-sim-2024/blob/1a46ec3494b0fa2957a418a8726b28ca4b291870/customer.c): Symuluje zachowanie klientów, którzy wchodzą do supermarketu, robią zakupy, ustawiają się w kolejce do kasy i opuszczają supermarket.
- [`manager.c`](https://github.com/magnuschase/pk-so-supermarket-sim-2024/blob/1a46ec3494b0fa2957a418a8726b28ca4b291870/manager.c): Zarządza kasami, otwierając i zamykając je w zależności od liczby klientów w sklepie.
- [`firefighter.c`](https://github.com/magnuschase/pk-so-supermarket-sim-2024/blob/1a46ec3494b0fa2957a418a8726b28ca4b291870/firefighter.c): Symuluje strażaka, który po pewnym czasie wysyła sygnał o pożarze, zmuszając klientów do natychmiastowego opuszczenia supermarketu.
- [`shared.c`](https://github.com/magnuschase/pk-so-supermarket-sim-2024/blob/1a46ec3494b0fa2957a418a8726b28ca4b291870/shared.c): Zawiera funkcje wspólne dla wszystkich komponentów, takie jak wyświetlanie tekstu i zapisywanie logów.
- [`supermarket.h`](https://github.com/magnuschase/pk-so-supermarket-sim-2024/blob/1a46ec3494b0fa2957a418a8726b28ca4b291870/supermarket.h): Plik nagłówkowy zawierający definicje i deklaracje używane w projekcie.
- [`ansi-color-codes.h`](https://github.com/magnuschase/pk-so-supermarket-sim-2024/blob/1a46ec3494b0fa2957a418a8726b28ca4b291870/ansi-color-codes.h): Plik nagłówkowy zawierający kody ANSI służące do kolorowania tekstu

## Co udało się zrobić?

- Implementacja wszystkich głównych komponentów projektu zgodnie z założeniami.
- Obsługa dynamicznego otwierania i zamykania kas w zależności od liczby klientów.
- Symulacja losowego przychodzenia klientów do supermarketu i ich losowego czasu przebywania.
- Implementacja sygnału o pożarze, który zmusza klientów do natychmiastowego opuszczenia supermarketu.
- Logowanie zdarzeń w konsoli oraz w pliku logów.
- Zaimplementowanie socketów, mutexów, semaforów i pamięci współdzielonej
- Obsługa błędów za pomocą funkcji perror i errno.

## Napotkane problemy

- Różnice w implementacji funkcji POSIX na różnych systemach operacyjnych (Linux vs macOS), co wymagało warunkowego kompilowania z użyciem `-lrt` na Linuxie.
- Trudności z poprawnym zarządzaniem pamięcią współdzieloną, co wymagało dokładnego zamykania i odmapowywania zasobów.
- Problemy z synchronizacją wątków i procesów, które wymagały dokładnego zarządzania mutexami i semaforami.
- Różnice między profilami kolorów skonfigurowanej powłoki zsh oraz domyślnej powłoki bash.

## Elementy specjalne

- Kolorowe logowanie w konsoli za pomocą kodów ANSI
- Menu, umożliwiające start programu z domyślną konfiguracją, zmianę konfiguracji lub zakończenie działania programu.
- Mechanizm zapisywania logów w folderze `/logs`, umożliwiający analizę działania programu po zakończeniu symulacji, a także porównywanie symulacji o różnej konfiguracji ze sobą.

## Linki do istotnych fragmentów kodu

Linki do istotnych fragmentów kodu, które obrazują wymagane w projekcie użyte konstrukcje:

- Tworzenie i obsługa plików
  - [Inicjalizacja pliku](https://github.com/magnuschase/pk-so-supermarket-sim-2024/blob/1a46ec3494b0fa2957a418a8726b28ca4b291870/shared.c#L86-L92)
  - [Wywołanie inicjalizacji pliku](https://github.com/magnuschase/pk-so-supermarket-sim-2024/blob/1a46ec3494b0fa2957a418a8726b28ca4b291870/supermarket.c#L189-L193)
  - [Zapis do pliku](https://github.com/magnuschase/pk-so-supermarket-sim-2024/blob/1a46ec3494b0fa2957a418a8726b28ca4b291870/shared.c#L67-L80)
  - [Zamykanie pliku](https://github.com/magnuschase/pk-so-supermarket-sim-2024/blob/1a46ec3494b0fa2957a418a8726b28ca4b291870/shared.c#L94-L101)
- Obsługa procesów i sygnałów
  - [Tworzenie procesów](https://github.com/magnuschase/pk-so-supermarket-sim-2024/blob/1a46ec3494b0fa2957a418a8726b28ca4b291870/supermarket.c#L249-L268)
  - [Oczekiwanie na sygnał strażaka](https://github.com/magnuschase/pk-so-supermarket-sim-2024/blob/1a46ec3494b0fa2957a418a8726b28ca4b291870/supermarket.c#L270-L271)
  - [Zamknięcie pozostałych procesów](https://github.com/magnuschase/pk-so-supermarket-sim-2024/blob/1a46ec3494b0fa2957a418a8726b28ca4b291870/supermarket.c#L279-L285)
- Tworzenie i obsługa wątków
  - [Tworzenie wątków klientów](https://github.com/magnuschase/pk-so-supermarket-sim-2024/blob/1a46ec3494b0fa2957a418a8726b28ca4b291870/customer.c#L127-L136)
  - [Obsługa kolejki do kasy przez klienta](https://github.com/magnuschase/pk-so-supermarket-sim-2024/blob/1a46ec3494b0fa2957a418a8726b28ca4b291870/customer.c#L38-L59)
  - [Obsługa kas przez kierownika](https://github.com/magnuschase/pk-so-supermarket-sim-2024/blob/1a46ec3494b0fa2957a418a8726b28ca4b291870/manager.c#L101-L125)
  - [Zamykanie kas](https://github.com/magnuschase/pk-so-supermarket-sim-2024/blob/1a46ec3494b0fa2957a418a8726b28ca4b291870/manager.c#L28-L37)
  - [Zamykanie sklepu po sygnale strażaka](https://github.com/magnuschase/pk-so-supermarket-sim-2024/blob/1a46ec3494b0fa2957a418a8726b28ca4b291870/supermarket.c#L273-L277)
  - [Oczekiwanie na sygnał zamknięcia sklepu przez klienta](https://github.com/magnuschase/pk-so-supermarket-sim-2024/blob/1a46ec3494b0fa2957a418a8726b28ca4b291870/customer.c#L138-L143)
- Segmenty pamięci dzielonej
  - [Tworzenie pamięci dzielonej](https://github.com/magnuschase/pk-so-supermarket-sim-2024/blob/1a46ec3494b0fa2957a418a8726b28ca4b291870/supermarket.c#L206-L234)
  - [Funkcja tworząca pamięć dzielona](https://github.com/magnuschase/pk-so-supermarket-sim-2024/blob/1a46ec3494b0fa2957a418a8726b28ca4b291870/supermarket.c#L121-L142)
  - [Odmapowywanie pamięci dzielonej](https://github.com/magnuschase/pk-so-supermarket-sim-2024/blob/1a46ec3494b0fa2957a418a8726b28ca4b291870/supermarket.c#L302-L320)
  - [Podpięcie pod pamięć dzieloną](https://github.com/magnuschase/pk-so-supermarket-sim-2024/blob/1a46ec3494b0fa2957a418a8726b28ca4b291870/manager.c#L56-L93)
- Obsługa semaforów
  - [Tworzenie nazwanych semaforów](https://github.com/magnuschase/pk-so-supermarket-sim-2024/blob/1a46ec3494b0fa2957a418a8726b28ca4b291870/supermarket.c#L198-L204)
  - [Zamykanie nazwanych semaforów](https://github.com/magnuschase/pk-so-supermarket-sim-2024/blob/1a46ec3494b0fa2957a418a8726b28ca4b291870/supermarket.c#L293-L299)
  - [Wysyłanie sygnałów przez semafor](https://github.com/magnuschase/pk-so-supermarket-sim-2024/blob/1a46ec3494b0fa2957a418a8726b28ca4b291870/customer.c#L32-L33)
  - [Oczekiwanie na semafor](https://github.com/magnuschase/pk-so-supermarket-sim-2024/blob/1a46ec3494b0fa2957a418a8726b28ca4b291870/manager.c#L110-L114)
- Obsługa socketów
  - [Serwer obsługujący sockety](https://github.com/magnuschase/pk-so-supermarket-sim-2024/blob/1a46ec3494b0fa2957a418a8726b28ca4b291870/supermarket.c#L63-L119)
  - [Tworzenie socketów w zewnętrznym procesie](https://github.com/magnuschase/pk-so-supermarket-sim-2024/blob/1a46ec3494b0fa2957a418a8726b28ca4b291870/firefighter.c#L29-L42)
  - [Łączenie z socketem](https://github.com/magnuschase/pk-so-supermarket-sim-2024/blob/1a46ec3494b0fa2957a418a8726b28ca4b291870/firefighter.c#L44-L48)
  - [Wysyłka wiadomości poprzez socket](https://github.com/magnuschase/pk-so-supermarket-sim-2024/blob/1a46ec3494b0fa2957a418a8726b28ca4b291870/firefighter.c#L50-L57)
  - [Zamykanie połączenia z socketem](https://github.com/magnuschase/pk-so-supermarket-sim-2024/blob/1a46ec3494b0fa2957a418a8726b28ca4b291870/firefighter.c#L59)

---

### [Link do repozytorium](https://github.com/magnuschase/pk-so-supermarket-sim-2024)

### Komendy

- `make` - buduje aplikacje
- `make clean` - usuwa poprzedni build aplikacji
- `./build/supermarket` - start aplikacji
