# Requirements Document

## Introduction

Tato featura přidává HTTP endpoint do ESP32 firmware (REMv2), přes který lze nahrát model profil — tedy strukturovaný seznam skupin (GroupBlock) s přiřazenými bloky (OnOffBlock, ActionBlock, SliderBlock, InputSliderBlock). Nahraný profil nahradí aktuálně načtený profil v paměti zařízení (ModelProvider) a volitelně jej uloží na SD kartu pro přežití restartu.

Aktuálně je profil pevně zakódován v `R18ModelProfile.cpp`. Cílem je umožnit dynamickou výměnu profilu za běhu přes HTTP POST požadavek s JSON tělem.

## Glossary

- **Upload_Endpoint**: HTTP endpoint `/model-profile` přijímající POST požadavky s JSON tělem
- **ModelProvider**: Třída spravující aktuálně aktivní model profil a seznam skupin (`Groups`)
- **GroupBlock**: Objekt reprezentující skupinu bloků se společným typem (`BlockTypeEnum`) a unikátním `id`
- **BasicBlock**: Abstraktní základní třída pro všechny typy bloků (OnOffBlock, ActionBlock, SliderBlock, InputSliderBlock)
- **BlockTypeEnum**: Výčet typů skupin: `controll`, `action`, `slider`, `inputSlider`, `nav`, `status`, `virt`
- **Profile_JSON**: JSON dokument popisující celý model profil — pole skupin, každá se svými bloky
- **Parser**: Komponenta zodpovědná za parsování Profile_JSON na interní objekty GroupBlock/BasicBlock
- **Validator**: Komponenta zodpovědná za validaci struktury a hodnot Profile_JSON před parsováním
- **StorageService**: Existující služba pro čtení a zápis souborů na SD kartu (volitelná závislost — endpoint funguje i bez ní)

---

## Requirements

### Requirement 1: Nahrání model profilu přes HTTP

**User Story:** Jako vývojář nebo operátor, chci nahrát nový model profil do zařízení přes HTTP, abych mohl změnit konfiguraci skupin a bloků bez nutnosti překompilovat a flashovat firmware.

#### Acceptance Criteria

1. WHEN je přijat HTTP POST požadavek na `/model-profile` s validním Profile_JSON tělem, THE Upload_Endpoint SHALL nahradit aktuální skupiny v ModelProvider novými skupinami parsovanými z Profile_JSON.
2. WHEN je přijat HTTP POST požadavek na `/model-profile` s validním Profile_JSON tělem, THE Upload_Endpoint SHALL vrátit HTTP odpověď se stavovým kódem 200 a textovým potvrzením.
3. IF tělo HTTP POST požadavku na `/model-profile` není validní JSON, THEN THE Upload_Endpoint SHALL vrátit HTTP odpověď se stavovým kódem 400 a popisem chyby.
4. IF tělo HTTP POST požadavku na `/model-profile` chybí nebo je prázdné, THEN THE Upload_Endpoint SHALL vrátit HTTP odpověď se stavovým kódem 400 a textem "Missing or empty body".
5. THE Upload_Endpoint SHALL přijímat požadavky s Content-Type `application/json`.
6. THE Upload_Endpoint SHALL přijímat volitelný query parametr `persist` (hodnota `true` nebo `false`); výchozí hodnota je `false`.
7. WHILE query parametr `persist` není přítomen nebo má hodnotu `false`, THE Upload_Endpoint SHALL aplikovat profil pouze v paměti bez jakékoli interakce se StorageService.

---

### Requirement 2: Parsování Profile_JSON

**User Story:** Jako firmware, chci parsovat Profile_JSON do interních objektů, abych mohl pracovat s nahraným profilem stejně jako s pevně zakódovaným.

#### Acceptance Criteria

1. WHEN Parser obdrží validní Profile_JSON, THE Parser SHALL vytvořit odpovídající objekty GroupBlock pro každý záznam v poli `groups`.
2. WHEN Parser zpracovává skupinu s typem `controll`, THE Parser SHALL vytvořit objekty OnOffBlock pro každý blok v poli `blocks` dané skupiny.
3. WHEN Parser zpracovává skupinu s typem `action`, THE Parser SHALL vytvořit objekty ActionBlock pro každý blok v poli `blocks` dané skupiny.
4. WHEN Parser zpracovává skupinu s typem `slider`, THE Parser SHALL vytvořit objekty SliderBlock pro každý blok v poli `blocks` dané skupiny.
5. WHEN Parser zpracovává skupinu s typem `inputSlider`, THE Parser SHALL vytvořit objekty InputSliderBlock pro každý blok v poli `blocks` dané skupiny.
6. THE Parser SHALL mapovat pole `pins` z JSON na vektor pinů každého BasicBlock objektu.
7. THE Parser SHALL mapovat pole `name` z JSON na atribut `name` každého BasicBlock objektu.
8. THE Parser SHALL mapovat pole `id` z JSON na atribut `id` každého GroupBlock objektu.
9. IF Profile_JSON obsahuje neznámý typ skupiny, THEN THE Parser SHALL vrátit chybový stav s popisem neznámého typu.
10. THE Pretty_Printer SHALL serializovat seznam objektů GroupBlock zpět do validního Profile_JSON.
11. FOR ALL validní seznamy GroupBlock objektů, parsování Profile_JSON, jeho serializace zpět na JSON a opětovné parsování SHALL produkovat ekvivalentní seznam GroupBlock objektů (round-trip vlastnost).

---

### Requirement 3: Validace Profile_JSON

**User Story:** Jako firmware, chci validovat strukturu nahraného JSON před parsováním, abych zabránil pádu zařízení při neplatném vstupu.

#### Acceptance Criteria

1. WHEN Validator obdrží Profile_JSON, THE Validator SHALL ověřit, že kořenový element obsahuje pole `groups`.
2. WHEN Validator zpracovává skupinu, THE Validator SHALL ověřit, že každá skupina obsahuje pole `id`, `type` a `blocks`.
3. WHEN Validator zpracovává blok, THE Validator SHALL ověřit, že každý blok obsahuje pole `id`, `name` a `pins`.
4. WHEN Validator zpracovává blok, THE Validator SHALL ověřit, že pole `pins` je neprázdné pole celých čísel.
5. IF validace selže, THEN THE Validator SHALL vrátit popis první nalezené chyby včetně cesty k problematickému poli.
6. WHEN Validator zpracovává skupinu s typem `action`, THE Validator SHALL ověřit, že každý blok obsahuje pole `actionType` s hodnotou odpovídající dostupné akci (`LinearBlink`, `Blink`, `RandomBlink`).

---

### Requirement 4: Volitelná persistence profilu na SD kartě

**User Story:** Jako operátor, chci mít možnost uložit nahraný profil na SD kartu, aby přežil restart zařízení, přičemž toto rozhodnutí chci učinit explicitně při každém nahrání.

#### Acceptance Criteria

1. WHEN je přijat HTTP POST požadavek na `/model-profile` s query parametrem `persist=true` a profil je úspěšně validován, THE Upload_Endpoint SHALL uložit Profile_JSON na SD kartu prostřednictvím StorageService pod názvem souboru `model-profile`.
2. WHEN je přijat HTTP POST požadavek na `/model-profile` s query parametrem `persist=true` a StorageService je dostupná, THE Upload_Endpoint SHALL vrátit HTTP odpověď se stavovým kódem 200 a potvrzením, že profil byl aplikován a uložen.
3. IF je přijat HTTP POST požadavek s query parametrem `persist=true` a StorageService není dostupná, THEN THE Upload_Endpoint SHALL vrátit HTTP odpověď se stavovým kódem 200 s upozorněním, že profil byl aplikován v paměti, ale nebyl uložen na SD kartu.
4. WHEN ModelProvider inicializuje model při startu zařízení, THE ModelProvider SHALL zkontrolovat, zda na SD kartě existuje soubor `model-profile`.
5. WHEN soubor `model-profile` na SD kartě existuje, THE ModelProvider SHALL načíst a parsovat tento soubor místo výchozího R18ModelProfile.
6. IF čtení nebo parsování souboru `model-profile` ze SD karty selže, THEN THE ModelProvider SHALL načíst výchozí R18ModelProfile a zalogovat chybu přes Serial.

---

### Requirement 5: Získání aktuálního profilu přes HTTP

**User Story:** Jako vývojář, chci získat aktuálně aktivní model profil ze zařízení přes HTTP, abych mohl ověřit, co je v zařízení nahráno.

#### Acceptance Criteria

1. WHEN je přijat HTTP GET požadavek na `/model-profile`, THE Upload_Endpoint SHALL vrátit aktuálně aktivní model profil serializovaný jako Profile_JSON.
2. WHEN je přijat HTTP GET požadavek na `/model-profile`, THE Upload_Endpoint SHALL vrátit HTTP odpověď se stavovým kódem 200 a Content-Type `application/json`.
