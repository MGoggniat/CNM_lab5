# Définir le compilateur
CXX = g++
NVCC = nvcc

# Noms des exécutables
TARGET = sieve
TARGET_OMP = sieve_omp
TARGET_CUDA = sieve_cuda

# Fichiers source
SOURCES = sieve.cpp
SOURCES_OMP = sieve_omp.cpp
SOURCES_CUDA = sieve_cuda.cu

# Règle par défaut
all: $(TARGET) $(TARGET_OMP) $(TARGET_CUDA)

# Comment construire l'exécutable 'sieve'
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Comment construire l'exécutable 'sieve_omp'
$(TARGET_OMP): $(SOURCES_OMP)
	$(CXX) $(CXXFLAGS) -o $(TARGET_OMP) $(SOURCES_OMP) -fopenmp

# Comment construire l'exécutable 'sieve_cuda'
$(TARGET_CUDA): $(SOURCES_CUDA)
	$(NVCC) $(NVCCFLAGS) -o $(TARGET_CUDA) $(SOURCES_CUDA)

# Règle pour nettoyer les fichiers compilés
clean:
	rm -f $(TARGET) $(TARGET_OMP) $(TARGET_CUDA)
