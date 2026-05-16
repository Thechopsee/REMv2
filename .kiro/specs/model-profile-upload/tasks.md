# Implementační plán: model-profile-upload

## Přehled

Implementace dynamického nahrávání model profilů přes HTTP do ESP32 firmware REMv2. Zahrnuje validátor, parser, pretty-printer, rozšíření ModelProvider a HTTP endpoint.

## Úkoly

- [x] 1. Implementace ProfileValidator
  - Vytvořit `src/modelprofiles/ProfileValidator.hh` a `ProfileValidator.cpp`
  - Statická metoda `validate(const JsonDocument& doc)` vrací `std::string` — prázdný při úspěchu, jinak popis první chyby s cestou
  - Ověřit přítomnost kořenového pole `groups`
  - Pro každou skupinu ověřit přítomnost `id`, `type`, `blocks`
  - Pro každý blok ověřit přítomnost `id`, `name`, `pins` (neprázdné pole intů)
  - Pro skupiny typu `action` ověřit přítomnost `actionType` s hodnotou `LinearBlink`, `Blink` nebo `RandomBlink`
  - _Požadavky: 3.1, 3.2, 3.3, 3.4, 3.5, 3.6_

- [x] 2. Implementace ProfileParser
  - Vytvořit `src/modelprofiles/ProfileParser.hh` a `ProfileParser.cpp`
  - Statická metoda `parse(const JsonDocument& doc, std::string& error)` vrací `std::vector<GroupBlock*>`
  - Mapovat `type` na příslušnou třídu bloku: `controll` → `OnOffBlock`, `action` → `ActionBlock`, `slider` → `SliderBlock`, `inputSlider` → `InputSliderBlock`
  - Mapovat `pins` na vektor pinů každého `BasicBlock`
  - Mapovat `name` na atribut `name` každého `BasicBlock`
  - Mapovat `id` na atribut `id` každého `GroupBlock`
  - Pro `ActionBlock` mapovat `actionType` na příslušnou třídu akce (`LinearBlinkAction`, `BlinkAction`, `RandomBlinkAction`)
  - Pro `InputSliderBlock` mapovat volitelné `maxValue`
  - Při neznámém typu skupiny nastavit `error` a vrátit prázdný vektor
  - _Požadavky: 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9_

- [x] 3. Implementace ProfilePrettyPrinter
  - Vytvořit `src/modelprofiles/ProfilePrettyPrinter.hh` a `ProfilePrettyPrinter.cpp`
  - Statická metoda `serialize(const std::vector<GroupBlock*>& groups)` vrací `std::string` s Profile_JSON
  - Serializovat každou skupinu včetně `id`, `type`, `blocks`
  - Pro každý blok serializovat `id`, `name`, `pins`
  - Pro `ActionBlock` přidat `actionType`, pro `InputSliderBlock` přidat `maxValue`
  - _Požadavky: 2.10, 5.1, 5.2_

- [x] 4. Checkpoint — ověřit kompilaci nových komponent
  - Ujistit se, že všechny nové soubory se kompilují bez chyb, zeptat se uživatele na případné otázky.

- [x] 5. Přidání metody `writeFile` do StorageService
  - Přidat deklaraci `writeFile(const std::string& name, const std::string& data)` do `StorageService.hh`
  - Implementovat v `StorageService.cpp` — otevřít soubor v režimu `FILE_WRITE` (přepis), zapsat data, zavřít
  - _Požadavky: 4.1_

- [x] 6. Rozšíření ModelProvider
  - Přidat metodu `freeGroups()` do `modelprovider.hh` a implementovat v `modelprovider.cpp` — projít `Groups`, zavolat `delete` na každý `BasicBlock` i `GroupBlock`
  - Přidat metodu `LoadFromJson(const std::string& json)` — parsovat JSON přes `ArduinoJson`, zavolat `ProfileValidator::validate()`, pak `ProfileParser::parse()`, při úspěchu zavolat `freeGroups()` a nahradit `Groups`; vrátit `""` při úspěchu nebo popis chyby
  - Rozšířit `LoadModel()` o kontrolu existence souboru `model-profile` na SD kartě přes `StorageService`; pokud existuje, načíst obsah a zavolat `LoadFromJson()`; při chybě čtení nebo parsování zalogovat přes `Serial` a načíst výchozí `R18ModelProfile`
  - _Požadavky: 1.1, 4.4, 4.5, 4.6_

- [x] 7. Registrace HTTP endpointu `/model-profile` v main.cpp
  - Přidat `AsyncCallbackWebHandler` s body handlerem pro POST `/model-profile`
  - POST handler: zkontrolovat prázdné tělo (400 `"Missing or empty body"`), zavolat `modelProvider->LoadFromJson()`, při chybě vrátit 400 s popisem; pokud `persist=true`, zavolat `storageService->writeFile("model-profile", body)`; vrátit 200 s potvrzením
  - GET handler: zavolat `ProfilePrettyPrinter::serialize(modelProvider->GetGroups())`, vrátit 200 s `Content-Type: application/json`
  - Ošetřit případ `persist=true` a nedostupná SD karta — vrátit 200 s upozorněním
  - _Požadavky: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 4.1, 4.2, 4.3, 5.1, 5.2_

- [x] 8. Finální checkpoint — ověřit kompilaci celého projektu
  - Ujistit se, že celý projekt se kompiluje bez chyb a všechny komponenty jsou správně propojeny, zeptat se uživatele na případné otázky.
