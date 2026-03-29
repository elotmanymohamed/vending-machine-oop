// =============================================================================
// Automat.cpp — Implémentation de la classe Automat
// =============================================================================

#include "Automat.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

// ── Constructeur ──────────────────────────────────────────────────────────────
Automat::Automat(int maxSlots, int maxProductsPerSlot)
    : numSlots(0),
      capacity(maxSlots),
      numProductsPerSlot(maxProductsPerSlot),
      cached(nullptr)
{
    if (maxSlots <= 0)
        throw std::invalid_argument("Le nombre d'emplacements doit être > 0.");

    slots = new Slot*[capacity];
    for (int i = 0; i < capacity; ++i)
        slots[i] = nullptr;
}

// ── Destructeur ───────────────────────────────────────────────────────────────
Automat::~Automat() {
    for (int i = 0; i < numSlots; ++i) {
        delete slots[i];
        slots[i] = nullptr;
    }
    delete[] slots;
    cached = nullptr;
}

// ── addSlot() ────────────────────────────────────────────────────────────────
void Automat::addSlot(const std::string& productName, int slotId,
                      int price, int motorId1, int motorId2) {
    if (numSlots >= capacity) {
        std::cerr << "  [ERREUR] Capacité maximale atteinte (" << capacity << " emplacements).\n";
        return;
    }
    // Vérifier doublon slotId
    for (int i = 0; i < numSlots; ++i) {
        if (slots[i]->getId() == slotId) {
            std::cerr << "  [ERREUR] L'emplacement " << slotId << " existe déjà.\n";
            return;
        }
    }
    slots[numSlots] = new Slot(slotId, productName, price, motorId1, motorId2);
    ++numSlots;
    std::cout << "  [OK] Emplacement " << slotId
              << " ajouté : " << productName
              << " — " << std::fixed << std::setprecision(2)
              << price / 100.0 << " €\n";
}

// ── searchSlot() — avec cache ─────────────────────────────────────────────────
Slot* Automat::searchSlot(int slotId) {
    // Vérification du cache en premier
    if (cached != nullptr && cached->getId() == slotId) {
        return cached;
    }
    // Recherche linéaire
    for (int i = 0; i < numSlots; ++i) {
        if (slots[i]->getId() == slotId) {
            cached = slots[i];
            return cached;
        }
    }
    return nullptr;  // Non trouvé
}

// ── changeSlot() ──────────────────────────────────────────────────────────────
void Automat::changeSlot(int slotId, const std::string& name, int price) {
    Slot* s = searchSlot(slotId);
    if (!s) {
        std::cerr << "  [ERREUR] Emplacement " << slotId << " introuvable.\n";
        return;
    }
    if (!name.empty()) s->setProductName(name);
    if (price > 0)     s->setPrice(price);
    std::cout << "  [OK] Emplacement " << slotId << " mis à jour : "
              << s->getProductName() << " — "
              << std::fixed << std::setprecision(2) << s->getPrice() / 100.0 << " €\n";
}

// ── getPieces() ───────────────────────────────────────────────────────────────
int Automat::getPieces(int slotId) {
    Slot* s = searchSlot(slotId);
    return s ? s->getNumProducts() : -1;
}

// ── isAvailable() ─────────────────────────────────────────────────────────────
bool Automat::isAvailable(int slotId) {
    Slot* s = searchSlot(slotId);
    return s ? s->isAvailable() : false;
}

// ── getPrice() ────────────────────────────────────────────────────────────────
int Automat::getPrice(int slotId) {
    Slot* s = searchSlot(slotId);
    return s ? s->getPrice() : -1;
}

// ── dropSlot() ────────────────────────────────────────────────────────────────
bool Automat::dropSlot(int slotId) {
    Slot* s = searchSlot(slotId);
    if (!s) {
        std::cerr << "  [ERREUR] Emplacement " << slotId << " introuvable.\n";
        return false;
    }
    if (!s->isAvailable()) {
        std::cout << "  [INFO] Emplacement " << slotId << " est vide.\n";
        return false;
    }
    s->drop();
    return true;
}

// ── fillAll() ─────────────────────────────────────────────────────────────────
void Automat::fillAll() {
    for (int i = 0; i < numSlots; ++i) {
        slots[i]->setNumProducts(numProductsPerSlot);
    }
    std::cout << "  [OK] Tous les emplacements rechargés ("
              << numProductsPerSlot << " produits chacun).\n";
}

// ── fill() ────────────────────────────────────────────────────────────────────
void Automat::fill(int slotId, int numProducts) {
    Slot* s = searchSlot(slotId);
    if (!s) {
        std::cerr << "  [ERREUR] Emplacement " << slotId << " introuvable.\n";
        return;
    }
    int qty = (numProducts > numProductsPerSlot) ? numProductsPerSlot : numProducts;
    s->setNumProducts(qty);
    std::cout << "  [OK] Emplacement " << slotId << " rechargé avec "
              << qty << " produit(s).\n";
}

// ── displayInventory() ────────────────────────────────────────────────────────
void Automat::displayInventory() const {
    std::cout << "\n";
    std::cout << "  ╔══════════════════════════════════════════════════════════╗\n";
    std::cout << "  ║         INVENTAIRE DU DISTRIBUTEUR AUTOMATIQUE          ║\n";
    std::cout << "  ╠════════╦══════════════════════╦══════════╦══════════════╣\n";
    std::cout << "  ║  Slot  ║  Produit             ║  Prix    ║  Stock       ║\n";
    std::cout << "  ╠════════╬══════════════════════╬══════════╬══════════════╣\n";

    for (int i = 0; i < numSlots; ++i) {
        Slot* s = slots[i];
        std::string avail = s->isAvailable() ? "✔" : "✘ VIDE";
        std::cout << "  ║  " << std::setw(4) << s->getId() << "  ║  "
                  << std::left  << std::setw(20) << s->getProductName() << "  ║  "
                  << std::right << std::setw(5)
                  << std::fixed << std::setprecision(2) << s->getPrice() / 100.0 << " €  ║  "
                  << std::left  << std::setw(3) << s->getNumProducts()
                  << "/" << numProductsPerSlot
                  << "  " << avail
                  << std::string(avail == "✔" ? 5 : 1, ' ') << "║\n";
    }

    std::cout << "  ╚════════╩══════════════════════╩══════════╩══════════════╝\n";
    std::cout << "  Total emplacements : " << numSlots << "/" << capacity << "\n\n";
}

// ── displaySlot() ─────────────────────────────────────────────────────────────
void Automat::displaySlot(int slotId) const {
    for (int i = 0; i < numSlots; ++i) {
        if (slots[i]->getId() == slotId) {
            Slot* s = slots[i];
            std::cout << "  ┌─ Slot #" << s->getId() << " ─────────────────────\n";
            std::cout << "  │  Produit  : " << s->getProductName() << "\n";
            std::cout << "  │  Prix     : " << std::fixed << std::setprecision(2)
                      << s->getPrice() / 100.0 << " €\n";
            std::cout << "  │  Stock    : " << s->getNumProducts()
                      << "/" << numProductsPerSlot << "\n";
            std::cout << "  │  Statut   : "
                      << (s->isAvailable() ? "Disponible ✔" : "Épuisé ✘") << "\n";
            std::cout << "  └─────────────────────────────────────\n";
            return;
        }
    }
    std::cout << "  [INFO] Emplacement " << slotId << " non trouvé.\n";
}

int Automat::getNumSlots() const { return numSlots; }
