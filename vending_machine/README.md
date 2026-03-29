# 🍟 Snack Vending Machine — Mini Projet C++ POO

> **Auteur :** Mohamed El Otmany  
> **Formation :** FA1 — Finance et Actuariat | FST Errachidia  
> **Module :** Programmation Orientée Objet en C++  
> **Année :** 2024/2025  

---

## 📌 Description

Application console **C++** simulant un distributeur automatique de snacks (*snack vending machine*), développée selon les principes de la **Programmation Orientée Objet**.

Une **interface web interactive** est également fournie (HTML/CSS/JS) pour visualiser le fonctionnement de la machine dans un navigateur.

---

## 🏗️ Architecture du projet

```
vending_machine/
├── include/
│   ├── Motor.h             # Classe Motor — moteur de spirale
│   ├── Slot.h              # Classe Slot  — emplacement produit
│   ├── Automat.h           # Classe Automat — distributeur
│   └── VendingMachine.h    # Classe VendingMachine — interface acheteur
├── src/
│   ├── Motor.cpp
│   ├── Slot.cpp
│   ├── Automat.cpp
│   ├── VendingMachine.cpp
│   └── main.cpp
├── web/
│   └── index.html          # Interface web interactive
├── docs/
│   └── MINIPROJET_FA1.pdf  # Énoncé du projet
├── Makefile
├── .gitignore
└── README.md
```

---

## 📐 Diagramme de classes UML

```
┌──────────────────────────────┐       ┌────────────────────────────────┐
│          Automat             │       │              Slot              │
├──────────────────────────────┤       ├────────────────────────────────┤
│ - slots : Slot**             │ 1   * │ - productName : string         │
│ - numSlots : int             ├───────┤ - id : int                     │
│ - cached : Slot*             │       │ - numProducts : int            │
│ - numProductsPerSlot : int   │       │ - price : int                  │
├──────────────────────────────┤       │ - motor1 : Motor*              │
│ + Automat(int, int)          │       │ - motor2 : Motor*              │
│ + searchSlot(int) : Slot*    │       ├────────────────────────────────┤
│ + addSlot(...)               │       │ + Slot(int, string, int, ...)  │
│ + changeSlot(...)            │       │ + drop()                       │
│ + getPieces(int) : int       │       │ + getPrice() / setPrice()      │
│ + isAvailable(int) : bool    │       │ + getNumProducts() / set...()  │
│ + dropSlot(int) : bool       │       │ + getProductName() / set...()  │
│ + fillAll()                  │       │ + getId() : int                │
│ + fill(int, int)             │       │ + isAvailable() : bool         │
└──────────────────────────────┘       └─────────────────┬──────────────┘
                                                         │ 1..2
                                       ┌─────────────────▼──────────────┐
                                       │             Motor              │
                                       ├────────────────────────────────┤
                                       │ - id : int                     │
                                       ├────────────────────────────────┤
                                       │ + Motor(int)                   │
                                       │ + trigger()                    │
                                       │ + getId() : int                │
                                       └────────────────────────────────┘
```

---

## ⚙️ Fonctionnement du distributeur

1. **Insertion de pièces** — L'acheteur insère des pièces (5, 10, 20, 50 ct, 1€, 2€)
2. **Sélection du produit** — Saisie du numéro d'emplacement sur le clavier
3. **Vérification infrarouge** — Contrôle de disponibilité du bac de sortie
4. **Activation des moteurs** — 1 ou 2 moteurs selon la largeur de la fente
5. **Chute du produit** — Le produit tombe dans le bac de sortie
6. **Rendu de monnaie** — La monnaie est éjectée automatiquement

---

## 🚀 Compilation et exécution

### Prérequis
- Compilateur G++ avec support C++17
- GNU Make (Linux/Mac) ou MinGW (Windows)

### Compilation

```bash
# Compiler
make

# Compiler et exécuter directement
make run

# Nettoyer les fichiers compilés
make clean
```

### Exécution manuelle

```bash
g++ -std=c++17 -Wall -Iinclude src/*.cpp -o vending_machine
./vending_machine
```

### Sur Windows (VS Code)

```bash
g++ -std=c++17 -Wall -Iinclude src/Motor.cpp src/Slot.cpp src/Automat.cpp src/VendingMachine.cpp src/main.cpp -o vending_machine.exe
.\vending_machine.exe
```

---

## 🌐 Interface Web

Ouvre `web/index.html` dans ton navigateur — aucune dépendance requise.

Fonctionnalités de l'interface web :
- Insertion de pièces (boutons)
- Sélection d'emplacement (clic ou saisie)
- Visualisation de l'inventaire en temps réel
- Console système avec logs détaillés
- Animation du bac de sortie

---

## 📋 Emplacements de la machine (d'après Figure 3)

| Slot ID | Produit    | Prix  | Moteurs     | Type fente |
|---------|-----------|-------|-------------|------------|
| 30      | Cheetos   | 1.50€ | M1 + M2     | Large      |
| 32      | Lays      | 1.30€ | M3 + M4     | Large      |
| 34      | Tams      | 1.20€ | M5 + M6     | Large      |
| 36      | Doritos   | 1.40€ | M7 + M8     | Large      |
| 38      | Doritos X | 1.50€ | M9 + M10    | Large      |
| 40      | M&Ms      | 1.00€ | M11         | Étroite    |
| 41      | Oreo      | 1.20€ | M12         | Étroite    |
| 42      | KitKat    | 1.30€ | M13         | Étroite    |
| 46      | Twix      | 1.50€ | M16         | Étroite    |
| ...     | ...       | ...   | ...         | ...        |

---

## 🔑 Menu Administration

Accès via option `[5]` dans le menu principal.  
Mot de passe : `admin123`

Fonctionnalités admin : recharger tous les emplacements, recharger un emplacement, modifier un produit/prix, ajouter un emplacement.

---

## 📄 Licence

Projet académique — FST Errachidia 2024/2025. Usage pédagogique uniquement.
