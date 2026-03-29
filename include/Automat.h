#pragma once
// =============================================================================
// Automat.h — Classe Automat (distributeur automatique)
// =============================================================================

#ifndef AUTOMAT_H
#define AUTOMAT_H

#include <string>
#include "Slot.h"

class Automat {
private:
    Slot** slots;              // Tableau dynamique de pointeurs vers les Slots
    int    numSlots;           // Nombre d'emplacements actuellement utilisés
    int    capacity;           // Capacité maximale du tableau
    int    numProductsPerSlot; // Nombre maximum de produits par emplacement
    Slot*  cached;             // Cache : dernier emplacement accédé

public:
    // Constructeur
    Automat(int numSlots, int numProductsPerSlot);

    // Destructeur
    ~Automat();

    // ── Gestion des emplacements ──────────────────────────────────────────
    void  addSlot(const std::string& productName, int slotId,
                  int price, int motorId1, int motorId2 = 0);

    Slot* searchSlot(int slotId);

    void  changeSlot(int slotId, const std::string& name, int price);

    // ── Accesseurs produits ───────────────────────────────────────────────
    int   getPieces(int slotId);
    bool  isAvailable(int slotId);
    int   getPrice(int slotId);

    // ── Actions distributeur ──────────────────────────────────────────────
    bool  dropSlot(int slotId);
    void  fillAll();
    void  fill(int slotId, int numProducts);

    // ── Affichage console ─────────────────────────────────────────────────
    void  displayInventory() const;
    void  displaySlot(int slotId) const;
    int   getNumSlots() const;
};

#endif // AUTOMAT_H
