// =============================================================================
// Slot.cpp — Implémentation de la classe Slot
// =============================================================================

#include "Slot.h"
#include <iostream>
#include <iomanip>

// ── Constructeur ──────────────────────────────────────────────────────────────
Slot::Slot(int slotId, const std::string& name,
           int priceInCents, int motorId1, int motorId2)
    : id(slotId),
      productName(name),
      price(priceInCents),
      numProducts(0),
      motor1(nullptr),
      motor2(nullptr)
{
    // Création dynamique du moteur principal
    motor1 = new Motor(motorId1);

    // Création du second moteur uniquement si motorId2 != 0
    if (motorId2 != 0) {
        motor2 = new Motor(motorId2);
    }
}

// ── Destructeur ───────────────────────────────────────────────────────────────
Slot::~Slot() {
    delete motor1;
    motor1 = nullptr;

    if (motor2 != nullptr) {
        delete motor2;
        motor2 = nullptr;
    }
}

// ── drop() ────────────────────────────────────────────────────────────────────
void Slot::drop() {
    if (numProducts <= 0) {
        std::cout << "  [ERREUR] Emplacement " << id
                  << " vide — impossible d'éjecter.\n";
        return;
    }

    std::cout << "\n  [SPIRALE] Activation des moteurs de l'emplacement " << id << " :\n";

    motor1->trigger();
    if (motor2 != nullptr) {
        motor2->trigger();
    }

    numProducts--;

    std::cout << "  [OK] " << productName
              << " livré depuis l'emplacement " << id
              << " (restant : " << numProducts << ")\n";
}

// ── Getters & Setters ─────────────────────────────────────────────────────────
int Slot::getPrice() const                    { return price; }
void Slot::setPrice(int p)                    { price = p; }

int Slot::getNumProducts() const              { return numProducts; }
void Slot::setNumProducts(int n)              { numProducts = (n >= 0) ? n : 0; }

std::string Slot::getProductName() const      { return productName; }
void Slot::setProductName(const std::string& name) { productName = name; }

int Slot::getId() const                       { return id; }

bool Slot::isAvailable() const                { return numProducts > 0; }
