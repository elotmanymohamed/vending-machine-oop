#pragma once
// =============================================================================
// VendingMachine.h — Classe principale : interface acheteur complète
// Gère l'insertion de pièces, la sélection, l'éjection, le rendu de monnaie
// =============================================================================

#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H

#include "Automat.h"
#include <string>

class VendingMachine {
private:
    Automat* automat;        // Distributeur interne
    int      insertedAmount; // Montant inséré en centimes
    bool     running;        // État de la machine

    // ── Helpers affichage ─────────────────────────────────────────────────
    void printHeader()  const;
    void printDivider() const;
    void printDisplay() const;
    void printMenu()    const;

    // ── Étapes du processus d'achat ───────────────────────────────────────
    void handleInsertCoin();
    void handleSelectProduct();
    void handleCancelAndReturn();
    void handleAdminMenu();
    void returnChange();

public:
    VendingMachine();
    ~VendingMachine();

    // Point d'entrée principal
    void run();
};

#endif // VENDINGMACHINE_H
