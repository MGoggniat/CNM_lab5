# Définir le compilateur
CXX = g++

# Définir les options de compilation
CXXFLAGS = -Wall -g

# Noms des exécutables
TARGET = sieve
TARGET_OMP = sieve_omp

# Fichiers source
SOURCES = sieve.cpp
SOURCES_OMP = sieve_omp.cpp

# Règle par défaut
all: $(TARGET) $(TARGET_OMP)

# Comment construire l'exécutable 'sieve'
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Comment construire l'exécutable 'sieve_omp'
$(TARGET_OMP): $(SOURCES_OMP)
	$(CXX) $(CXXFLAGS) -o $(TARGET_OMP) $(SOURCES_OMP) -fopenmp

# Règle pour nettoyer les fichiers compilés
clean:
	rm -f $(TARGET) $(TARGET_OMP)
