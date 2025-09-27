# Projekt XYZ

Tento repozitár obsahuje zdrojový kód projektu XYZ. Nižšie sú uvedené základné pravidlá pre správu verzovania a commitovanie, aby bola história prehľadná a zrozumiteľná.

---

## Pravidlá pre commitovanie

1. **Jedna zmena na commit**
   - Každý commit by sa mal zamerať na konkrétnu zmenu alebo opravu.
   - Vyhnite sa veľkým commitom typu „zmeny za celý deň“.
   - Príklad správneho commitu:
     ```
     Tokenizer: Changes in Tokenizer interface - input length required
     ```
   - Nesprávny commit:
     ```
     Daily update
     ```

2. **Oddelenie zmien verejných rozhraní**
   - Zmeny v **hlavičkových súboroch** alebo verejných API by mali byť samostatné.
   - Dôvod: uľahčuje sledovanie kompatibility a revíziu kódu.
   - Príklad:
     ```
     Parser: Update public parse() interface
     ```

3. **Formát názvu commitov**
   - Používame formát:  
     ```
     <Celok>: <krátky popis zmeny>
     ```
   - `Celok` je modul alebo časť projektu, kde sa zmena vykonala.
   - `krátky popis zmeny` stručne informuje, čo sa zmenilo.
   - Príklady:
     ```
     Tokenizer: Fix handling of empty strings
     Parser: Improve error messages in parse()
     AST: Add support for new expression type
     ```

---

## Doplnkové odporúčania

- Popisy commitov by mali byť **jasné a konkrétne**, aby aj externý čitateľ vedel, čo sa zmenilo.
- Pre väčšie zmeny vytvorte viacero menších commitov.
- Pre referenciu si môžete pozrieť existujúce commity v tomto repozitári.

---

Týmto spôsobom bude história projektu prehľadná a údržba jednoduchšia.
