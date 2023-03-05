Ahoj fiksáku,

tohle je první FIKS CTF (Capture The Flag).
V tomto CTF tě čeká pět ukrytých tajných vlajek (hesel).
Vlajky jsou vždy ve formátu `fiks{.*?}` (regex) např. `fiks{nejaky_text}`.

Za každou nalezenou vlajku dostaneš body (ne všechny vlajky jsou za stejně bodů).

CTF je diverzní a zkouší vynalézavost v několika směrech.
Je docela pravděpodobné, že ho nedokončíš celé, ale to nevadí, s tím se počítá.

Vlajky se do sfinx odevzdávají v textovém souboru, každá vlajka na samostatném řádku.
Součástí zipu je soubor `checker.py`, kterým si můžeš ověřit, zda jsou tvé vlajky správné.

UPOZORNĚNÍ: Odevzdání je myšleno jedno na celé kolo.
Vlajky jsou randomizované pro každý vygenerovaný vstup.
Pokud se rozhodneš teď odevzdat dvě vlajky s tím, že zbytek odevzdáš později,
při dalším vygenerování budou vlajky jiné a ty staré ti nebudou uznány.
Proto máš k dispozici checker, kterým si je můžeš ověřit u sebe.

Budeme rádi, když nám po skončení vyplníš `feedback.txt`.

Hodně štěstí!

PS: Soubory `.seed.txt` a `.hashes.txt` nejsou potřeba na nalezení žádné vlajky, slouží pouze na kontrolu.
