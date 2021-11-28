# Ukol_pro_pana_Mojzise
Ukol pro pana Mojzise - CSVReader

Program se kompiluje prikazem: g++ main.cpp -std=c++17 -o csvreader

A odpovida zadani:

z konfiguračního souboru test.conf si načte hodnoty proměnných:

 

log_file=test.log

input_file=input.data

output_file=output.data

attr_cnt=5

 

ze vstupního CSV souboru s názvem input.data bude načítat jednotlivé řádky

do logovacího souboru  s názvem test.log bude zapisovat ty řádky, jejichž počet atributů neodpovídá počtu definovaném v parametru attr_cnt ve formátu: Datum čas(ISO8601 formát),číslo_řádku,[jednotlivé,prvky,řádku]

do výstupního CSV souboru s názvem output.data bude zapisovat ty řádky, jejichž počet atributů odpovídá počtu definovaném v parametru attr_cnt a mají sudý první atribut > avšak tento atribut zvětší o +1

 

Příklad souborů:

 

 

test.conf:

log_file=test.log

input_file=input.data

output_file=output.data

attr_cnt=3

 

input.data:

1,jedna,x

2,dva,y

3,tri,z,neco_navic

4,ctyri

 

test.log:

2021-24-11T14:01:07,3,[3,tri,z,neco_navic]

2021-24-11T14:01:07,4,[4,ctyri]

 

output.data:

3,dva,y

 

program musí hledat ve stejné složce, ve které je spuštěn

program musí obsahovat reference na proměnné v souboru test.conf - ty musí být reflektované při změně a následném spuštění

program musí hledat vstupy v souboru dle odkazu z konfiguračního souboru

program musí zapisovat výstupy do souboru (a logu) dle odkazu z konfiguračního souboru

program musí zohledňovat počet atributů dle odkazu...

v případě neexistence vstupu, vypíše do logu hlášku, že vstup definovnaý v konfiguračním souboru neexistuje

v případě prázdného vstupu vypíše do logu, že není co zpracovat

po dokončení načítání dat napíše program do logu kolik zpracoval validních a nevalidních řádků,jaká byla hodnota prvního a posledního zpracovávaného řádku na pozici 1, a vypíše jak dlouho trvalo zpracování a jaké načetl hodnoty z konfiguračního souboru

v případě neexistence konfiguračního souboru program nespadne a seběhne na defaultních hodnotách:

log_file=default.log

input_file=input.default

output_file=output.default

attr_cnt=2
