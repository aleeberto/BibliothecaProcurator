# BibliothecaProcurator
Project for the course "Programmazione ad Oggetti"

### Come Compilare e Eseguire il progetto.

Per evitare di eseguire singolarmente ogni volta ogni comando per la pulizia dei file di build, la compilazione e l' esecuzione del progetto esiste il file build.sh. Per eseguire lo script sh con il comando `chmod +x build.sh` aggiungo i permessi di esecuzione del file, poi con `./build.sh` eseguo lo script

## Compilaizone ed esecuzione del progetto tramite docker

La compilazione del progetto tramite docker risulta piú lunga seppur restando semplice. Innanzi tutto necessita di  docker installato e un programma come XcXsrv che permette di eseguire applicazioni graviche da ambienti linux sul sistema Windows.

### Albero del Progetto

```
BibliothecaProcurator/
│
├── docker/
│
├── relazione/
│
├── resources/
│   ├── data/
│   ├── icon/
│   └── img/
│
├── src/
│   ├── logic/
│   ├── services/
│   ├── ui/
│   └── main.cpp
│
├── build/
├── .gitignore
├── BibliothecaProcurator.pro
├── build.sh
└── README.md        
```

### Albero delle Classi

```
Media
│
├── Series
│   ├── Anime
│   └── Serie TV
│
├── Film
│
├── Libri
│   └── Manga
│
└── Cd
```

#### TODO 

1. Semplificare esecuzione tramite docker
2. Scrivere sul readme le istruzioni per l' esecuzione tramite docker
3. Inserire icone luna e sole