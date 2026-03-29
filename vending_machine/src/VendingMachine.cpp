// =============================================================================
// VendingMachine.cpp — Interface complète du distributeur
// =============================================================================

#include "VendingMachine.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

// ── Constructeur — initialise la machine avec les produits de la Figure 3 ──
VendingMachine::VendingMachine()
    : insertedAmount(0), running(true)
{
    // 20 emplacements, max 5 produits par emplacement
    automat = new Automat(25, 5);

    // ── Rangée 1 : fentes larges (double moteur) — Slots 30-38 ────────────
    // Motor IDs pairs: 1-2, 3-4, 5-6, 7-8, 9-10 (première rangée)
    automat->addSlot("Cheetos",   30, 150, 1, 2);
    automat->addSlot("Lays",      32, 130, 3, 4);
    automat->addSlot("Tams",      34, 120, 5, 6);
    automat->addSlot("Doritos",   36, 140, 7, 8);
    automat->addSlot("Doritos X", 38, 150, 9, 10);

    // ── Rangée 2 : fentes étroites (simple moteur) — Slots 40-49 ─────────
    automat->addSlot("M&Ms",      40, 100, 11);
    automat->addSlot("Oreo",      41, 120, 12);
    automat->addSlot("KitKat",    42, 130, 13);
    automat->addSlot("Bounty",    43, 140, 14);
    automat->addSlot("Snickers",  44, 150, 15);
    automat->addSlot("Twix",      46, 150, 16);
    automat->addSlot("Mars",      47, 140, 17);
    automat->addSlot("Milka",     48, 160, 18);
    automat->addSlot("Nuts",      49, 130, 19);

    // Remplissage initial
    automat->fillAll();
}

// ── Destructeur ──────────────────────────────────────────────────────────────
VendingMachine::~VendingMachine() {
    delete automat;
}

// ── Affichage Header ─────────────────────────────────────────────────────────
void VendingMachine::printHeader() const {
    std::cout << "\n";
    std::cout << "  ╔══════════════════════════════════════════════╗\n";
    std::cout << "  ║    🍫  SNACK VENDING MACHINE  v1.0  🍟      ║\n";
    std::cout << "  ║    FST Errachidia — FA1 POO C++ 2024/2025   ║\n";
    std::cout << "  ╚══════════════════════════════════════════════╝\n";
}

void VendingMachine::printDivider() const {
    std::cout << "  ──────────────────────────────────────────────\n";
}

void VendingMachine::printDisplay() const {
    std::cout << "\n  ┌─ AFFICHAGE ───────────────────────────────┐\n";
    std::cout << "  │  Montant inséré : "
              << std::fixed << std::setprecision(2)
              << insertedAmount / 100.0 << " €"
              << std::string(22, ' ') << "│\n";
    std::cout << "  └───────────────────────────────────────────┘\n";
}

void VendingMachine::printMenu() const {
    printDisplay();
    std::cout << "\n  MENU PRINCIPAL\n";
    printDivider();
    std::cout << "  [1] Insérer une pièce\n";
    std::cout << "  [2] Sélectionner un produit\n";
    std::cout << "  [3] Annuler / Récupérer monnaie\n";
    std::cout << "  [4] Voir l'inventaire\n";
    std::cout << "  [5] Menu Administration\n";
    std::cout << "  [0] Quitter\n";
    printDivider();
    std::cout << "  Votre choix : ";
}

// ── Insertion de pièces ───────────────────────────────────────────────────────
void VendingMachine::handleInsertCoin() {
    std::cout << "\n  ┌─ INSERTION PIÈCE ─────────────────────────┐\n";
    std::cout << "  │  Valeurs acceptées (en centimes) :        │\n";
    std::cout << "  │  5  10  20  50  100  200                  │\n";
    std::cout << "  └───────────────────────────────────────────┘\n";
    std::cout << "  Entrez la valeur de la pièce (centimes) : ";

    int coin;
    std::cin >> coin;

    int valid[] = {5, 10, 20, 50, 100, 200};
    bool accepted = false;
    for (int v : valid) {
        if (coin == v) { accepted = true; break; }
    }

    if (accepted) {
        insertedAmount += coin;
        std::cout << "  [OK] Pièce de "
                  << std::fixed << std::setprecision(2) << coin / 100.0
                  << " € acceptée. Total : "
                  << insertedAmount / 100.0 << " €\n";
    } else {
        std::cout << "  [ERREUR] Pièce non reconnue. Veuillez réessayer.\n";
    }
}

// ── Sélection produit ─────────────────────────────────────────────────────────
void VendingMachine::handleSelectProduct() {
    if (insertedAmount == 0) {
        std::cout << "  [INFO] Veuillez insérer des pièces d'abord.\n";
        return;
    }

    std::cout << "\n  Entrez le numéro d'emplacement : ";
    int slotId;
    std::cin >> slotId;

    // Vérification existence
    Slot* s = automat->searchSlot(slotId);
    if (!s) {
        std::cout << "  [ERREUR] Emplacement " << slotId << " introuvable.\n";
        return;
    }

    automat->displaySlot(slotId);

    // Vérification disponibilité
    if (!s->isAvailable()) {
        std::cout << "  [INFO] Produit épuisé. Choisissez un autre emplacement.\n";
        return;
    }

    // Vérification du solde
    int price = s->getPrice();
    if (insertedAmount < price) {
        std::cout << "  [INFO] Solde insuffisant. Il manque "
                  << std::fixed << std::setprecision(2)
                  << (price - insertedAmount) / 100.0 << " €\n";
        return;
    }

    // ── Éjection du produit ──────────────────────────────────────────────
    std::cout << "\n  [INFRAROUGE] Vérification du bac de sortie...\n";
    std::cout << "  [INFRAROUGE] Bac libre — éjection autorisée.\n";

    automat->dropSlot(slotId);

    // Rendu de monnaie
    int change = insertedAmount - price;
    insertedAmount = 0;

    if (change > 0) {
        std::cout << "\n  ┌─ RENDU MONNAIE ───────────────────────────┐\n";
        std::cout << "  │  Monnaie rendue : "
                  << std::fixed << std::setprecision(2)
                  << change / 100.0 << " €"
                  << std::string(18, ' ') << "│\n";
        std::cout << "  └───────────────────────────────────────────┘\n";
    }

    std::cout << "\n  ✔ Merci pour votre achat ! Bonne dégustation.\n";
}

// ── Annulation et remboursement ───────────────────────────────────────────────
void VendingMachine::handleCancelAndReturn() {
    if (insertedAmount == 0) {
        std::cout << "  [INFO] Aucun montant à rembourser.\n";
        return;
    }
    returnChange();
}

void VendingMachine::returnChange() {
    std::cout << "\n  ┌─ ANNULATION ──────────────────────────────┐\n";
    std::cout << "  │  Remboursement : "
              << std::fixed << std::setprecision(2)
              << insertedAmount / 100.0 << " €"
              << std::string(19, ' ') << "│\n";
    std::cout << "  └───────────────────────────────────────────┘\n";
    insertedAmount = 0;
    std::cout << "  [OK] Transaction annulée. Monnaie éjectée.\n";
}

// ── Menu Administration ───────────────────────────────────────────────────────
void VendingMachine::handleAdminMenu() {
    std::string password;
    std::cout << "\n  Mot de passe admin : ";
    std::cin >> password;

    if (password != "admin123") {
        std::cout << "  [ACCÈS REFUSÉ] Mot de passe incorrect.\n";
        return;
    }

    int choice;
    do {
        std::cout << "\n  ╔══ MENU ADMIN ═══════════════════════════╗\n";
        std::cout << "  ║  [1] Recharger tous les emplacements    ║\n";
        std::cout << "  ║  [2] Recharger un emplacement           ║\n";
        std::cout << "  ║  [3] Modifier un produit                ║\n";
        std::cout << "  ║  [4] Ajouter un emplacement             ║\n";
        std::cout << "  ║  [0] Retour                             ║\n";
        std::cout << "  ╚═════════════════════════════════════════╝\n";
        std::cout << "  Choix : ";
        std::cin >> choice;

        if (choice == 1) {
            automat->fillAll();

        } else if (choice == 2) {
            int sid, qty;
            std::cout << "  Numéro d'emplacement : "; std::cin >> sid;
            std::cout << "  Quantité : ";             std::cin >> qty;
            automat->fill(sid, qty);

        } else if (choice == 3) {
            int sid, price;
            std::string name;
            std::cout << "  Numéro d'emplacement : ";       std::cin >> sid;
            std::cin.ignore();
            std::cout << "  Nouveau nom produit : ";        std::getline(std::cin, name);
            std::cout << "  Nouveau prix (centimes, 0=inchangé) : "; std::cin >> price;
            automat->changeSlot(sid, name, price);

        } else if (choice == 4) {
            int sid, price, mid1, mid2;
            std::string name;
            std::cout << "  Slot ID : ";    std::cin >> sid;
            std::cin.ignore();
            std::cout << "  Produit : ";   std::getline(std::cin, name);
            std::cout << "  Prix (ct) : "; std::cin >> price;
            std::cout << "  Motor ID 1 : "; std::cin >> mid1;
            std::cout << "  Motor ID 2 (0=simple) : "; std::cin >> mid2;
            automat->addSlot(name, sid, price, mid1, mid2);
        }

    } while (choice != 0);
}

// ── Boucle principale ─────────────────────────────────────────────────────────
void VendingMachine::run() {
    printHeader();
    std::cout << "\n  Initialisation de la machine...\n";

    int choice;
    while (running) {
        printMenu();
        std::cin >> choice;

        // Gestion des saisies invalides
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "  [ERREUR] Saisie invalide.\n";
            continue;
        }

        switch (choice) {
            case 1: handleInsertCoin();      break;
            case 2: handleSelectProduct();   break;
            case 3: handleCancelAndReturn(); break;
            case 4: automat->displayInventory(); break;
            case 5: handleAdminMenu();       break;
            case 0:
                std::cout << "\n  Au revoir ! Machine arrêtée.\n\n";
                running = false;
                break;
            default:
                std::cout << "  [ERREUR] Option invalide. Réessayez.\n";
        }
    }
}
