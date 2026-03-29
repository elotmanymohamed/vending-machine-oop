#pragma once
// =============================================================================
// Motor.h — Classe Motor
// Projet  : Snack Vending Machine — Mini Projet C++ POO
// Auteur  : Mohamed El Otmany | FST Errachidia FA1 2024/2025
// =============================================================================

#ifndef MOTOR_H
#define MOTOR_H

class Motor {
private:
    int id;  // Identifiant unique du moteur (1 à n)

public:
    // Constructeur
    explicit Motor(int motorId);

    // Destructeur
    ~Motor();

    // Getter
    int getId() const;

    // Active le moteur et affiche un message de confirmation
    void trigger();
};

#endif // MOTOR_H
