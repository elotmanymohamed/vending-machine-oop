# =============================================================================
# Makefile — Snack Vending Machine C++
# =============================================================================

CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
TARGET   = vending_machine
SRCDIR   = src
OBJDIR   = build

SOURCES  = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS  = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

# Règle principale
all: $(OBJDIR) $(TARGET)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "\n✔ Compilation réussie → ./$(TARGET)\n"

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -rf $(OBJDIR) $(TARGET)
	@echo "Nettoyage terminé."

# Compilation + exécution directe
run: all
	./$(TARGET)

.PHONY: all clean run
