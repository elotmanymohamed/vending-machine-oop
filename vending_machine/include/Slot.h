#pragma once
// =============================================================================
// Slot.h — Classe Slot (emplacement produit)
// =============================================================================

#ifndef SLOT_H
#define SLOT_H

#include <string>
#include "Motor.h"

class Slot {
private:
    std::string productName;  // Nom du produit
    int         id;           // Identifiant de l'emplacement (numéro clavier)
    int         numProducts;  // Nombre de produits actuellement stockés
    int         price;        // Prix en centimes (ex: 200 = 2.00 €)
    Motor*      motor1;       // Moteur principal (spirale 1)
    Motor*      motor2;       // Moteur optionnel (spirale 2, NULL si fente étroite)

public:
    // Constructeur
    // motorId2 = 0 → pas de second moteur (fente étroite)
    Slot(int slotId, const std::string& productName,
         int price, int motorId1, int motorId2 = 0);

    // Destructeur — libère la mémoire des moteurs
    ~Slot();

    // Éjecte un produit : active les moteurs + message console
    void drop();

    // ── Getters & Setters ──────────────────────────────────────────────────
    int         getPrice()       const;
    void        setPrice(int p);

    int         getNumProducts() const;
    void        setNumProducts(int n);

    std::string getProductName() const;
    void        setProductName(const std::string& name);

    int         getId()          const;

    // Retourne true si numProducts > 0
    bool        isAvailable()    const;
};

#endif // SLOT_H
