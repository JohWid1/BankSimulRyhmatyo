# group_14

readme_update_1 13.11.2023
automaatin toimintarakennesuunnitelmaa sekä er-kaavion lisäys
arvosanaan 1 tähtäävät toimenpiteet ajalle 13.11-19.11

• Debit kortti toteutettava. Debit kortilla ei ole luottoa eli tili ei saa mennä miinukselle. Jos saldo ei riitä, käyttäjä saa siitä ilmoituksen.  
• Pankkiautomaatille voi kirjautua antamalla kortin id-arvon ja PIN-koodin.  
• Käyttäjä voi katsoa saldonsa.  
• Käyttäjä voi nostaa, joko 20, 40, 50 tai 100 euroa.  
• REST APIin toteutettu kaikki automaatilla tarvittavat toiminnot  

Automaatin toimintarakenne ver 0.5 (karsittu arvosanaan 1 tähtääväksi)


### 1. syötä pin koodi

1.1 koodi oikein siirry kohtaan 2 jos kortilla pääsy usealle tilille. Jos vain 1 tilille niin siirry kohtaan 3.  
1.2.1 koodi väärin -> teksti "Väärä pin, syötä uudelleen"  
1.2.2 koodi väärin uudestaan -> teksti "Väärä pin." 
1.2.3 koodi väärin 3. kerran -> teksti "Väärä pin, poista kortti"


### 2. Välivalikko mikäli kortilla pääsy usealle tilille.

2.1 Valitse oma tili debit jos kortilla tämä ominaisuus ja siirry kohtaan 3. 
2.2 valitse oma tili credit jos kortilla tämä ominaisuus ja siirry kohtaan 3.  
2.3 valitse toisen omistama tili shared account jos kortilla tämä ominaisuus ja siirry kohtaan 3.  
 

### 3. Päävalikko

2.1 katso saldo,  
2.2 katso tapahtumahistoriaa  
2.3 nosta tililtä,  
~~2.4 nosta luotolta.~~ // ~~tulossa myöhemmin~~ Luottovalinta toteutettiin tehtäväksi jo aiemmin.
~~2.5 suorita maksu/tilisiirto~~ // ~~tulossa myöhemmin~~ ei toteutettu. 
~~2.6 talletus ominaisuus~~ // ~~tulossa myöhemmin~~ ei toteutettu. 

jos 2.1 -> näytä saldo

jos 2.2 -> näytä 5 viimeisintä tapahtumaa ja painikkeella joko seuraavat tai edelliset 5 tapahtumaa

jos 2.3 -> valitse näytöllä summa  

2.3.1 20€,  
2.3.2 40€,  
2.3.3 50€,  
2.3.4 80€,
2.3.5 100€,  
2.3.6 150€,
2.3.7 200€,  
2.3.8 muu summa. 

jos 2.3.8 niin voi syöttää summan joka on jaollinen 20€ ja 50€ seteleille

~~5 tähtäävä 2.5 tilinsiirto / maksupääte sekä 2.6 talletus ominaisuus~~ // ~~tulossa myöhemmin~~ Ei toteutettu.

### ER-kaavio:


<img src=ER-kaavio_kuva_ver1.2.png>

