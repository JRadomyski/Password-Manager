# Project: Password Manager

## [PL] Projekt koncentrujący się na zbudowaniu minimalnego narzędzia o średnim skomplikowaniu.
### Description
Nie powinniśmy stosować tego samego hasła do różnych portali. Wyciek jednego z nich
naraża nas na utratę danych w wielu miejscach. W związku z tym, aby zminimalizować to
niebezpieczeństwo, powinniśmy stosować uwierzytelnianie dwuetapowe (ang. two-phase
authentication) - 2FA (które nie jest częścią tego projektu) oraz różne hasła. W tym drugim
mogą nam pomóc programy typu Password Manager, takie jak bitwarden czy KeePass.
Projekt polega na stworzeniu aplikacji konsolowej służącej do modyfikowania i czytania z
pliku, w którym będą przechowywane nasze hasła wraz z dodatkowymi informacjami
dotyczącymi różnych portali, których te hasła dotyczą. Będą one zaszyfrowane
pojedynczym hasłem głównym. Aplikacja powinna być uruchamiana z poziomu linii
poleceń (ang. command line). Bazując na komendach czytanych z klawiatury wykonywać
odpowiednie funkcje i zwracać interesujące nas informacje - na zasadzie interfejsu linii
poleceń (ang. command-line interface) - CLI.

Wymagania funkcjonalne:
Po uruchomieniu programu użytkownik powinien mieć możliwość wybrania jednego z
plików znajdujących się w folderze programu lub podania bezpośredniej, absolutnej
ścieżki do pliku. Wybrany plik będziemy nazywać plikiem źródłowym.
Dane w pliku źródłowym są zaszyfrowane. Sposób szyfrowania musi być autorski i w pełni
zrozumiany. Hasło pliku źródłowego ma stanowić nieodzowną cześć procesu szyfrowania i
odszyfrowania. Trudność złamania takiego szyfru nie będzie oceniana, ale otwarcie pliku w
edytorze tekstu i proste metody dedukcyjne nie powinny być wystarczające do
odszyfrowania jego zawartości. To samo się tyczy modyfikacji jego zawartości.
Każda próba odszyfrowania pliku powinna zapisać timestamp takiej operacji. Z uwagi na
to, że sam plik i program nie przechowuje nigdzie informacji o poprawnym haśle, a
timestamp modyfikacji musi być zawsze zmieniany (zarówno podczas nieudanej próby
otwarcia i modyfikacji pliku (podanie innego hasła niż to, którym plik źródłowy jest
zaszyfrowany)), to będzie on jedyną informacją zapisaną jawnie w całym pliku (bez
szyfrowania). W związku z tym musimy znaleźć inny sposób na jego ukrycie.

Jedną z możliwości byłoby rozłożyć tę informację na różne linijki. Początkiem linii 11.
mogłoby być hhDDDD, linii 22. mmDDDD, a 33. ssDDDD, gdzie hh to godzina mm to minuta a ss to
sekunda ostatniej próby odszyfrowania. DDDD to dalsze zaszyfrowane dane, niemające nic
wspólnego z samym timestampem. Każde hasło musi zawierać co najmniej:
Nazwę (Nazwa własna tego wpisu np. “Hasło do Konta1 na Google”);
Tekst reprezentujący samo hasło;
Kategorię.
Każde hasło dodatkowo może zawierać:
Strona WWW / Serwis;
Login.

### Implementacja wszystkich tych elementów jest wymagana, choć nie każde hasło musi zawierać te ostatnie dwie składowe. Mają one być opcjonalne.
### Opis komend
##### Wyszukaj hasła – zwraca hasła, które zawierają konkretne parametry.
##### Posortuj hasła – zwraca posortowaną listę wszystkich haseł. Ma umożliwiać posortowanie po co najmniej 2 różnych parametrach w tym samym czasie, czyli na przykład po nazwie i  kategorii.
##### Dodaj hasło – dodaje nowe hasło do zaszyfrowanego pliku. Użytkownikowi powinna być umożliwiona opcja wpisania własnego hasła i poinformowania go, na ile jest to bezpieczne  hasło i czy nie zostało już wcześniej wykorzystane. Dodatkowo należy zaproponować mu hasło automatycznie wygenerowane dając mu jednocześnie możliwość wybrania pewnych parametrów, takich jak: Ilość znaków; Czy ma zawierać wielkie i małe litery; Czy ma zawierać znaki specjalne.
##### Edytuj hasło – pozwala na edycje danych w istniejącym już haśle.
##### Usuń hasło – usuwa wybrane hasło lub hasła. Przed każdym usunięciem powinniśmy powiadomić o tym użytkownika szczególnie jeżeli usuwane jest więcej niż jedno hasło.
##### Dodaj kategorie – dodaje nową kategorię, którą będziemy mogli wykorzystywać przy tworzeniu nowych haseł.
##### Usuń kategorie – usuwa kategorie wraz ze wszystkimi hasłami, które do tej kategorii są przypisane.
#### Edycja hasła nie może się odbywać za pomocą usuwania oryginalnego rekordu i zastępowania go nowym.