// =============================================================================
// Motor.cpp — Implémentation de la classe Motor
// =============================================================================

#include "Motor.h"
#include <iostream>

Motor::Motor(int motorId) : id(motorId) {}

Motor::~Motor() {}

int Motor::getId() const {
    return id;
}

void Motor::trigger() {
    std::cout << "  [MOTEUR] Moteur " << id << " est activé (rotation 360°)\n";
}
