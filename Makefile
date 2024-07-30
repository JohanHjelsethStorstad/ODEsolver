# Source files
SRCS = src/main.cpp src/IterationScheme.cpp src/Logger.cpp src/PrimeFieldInferation.cpp src/Store.cpp tests/FieldGenerator.cpp tests/TestIteration.cpp tests/Plot.cpp

# Object files directory
OBJDIR = build

# Object files
OBJS = $(SRCS:src/%.cpp=$(OBJDIR)/%.o)

# Executable name
EXEC = $(OBJDIR)/ODESolver

# Compiler flags
NUMPY_INCLUDE = $(shell python3 -c "import numpy; print(numpy.get_include())")
PYTHON_INCLUDE = $(shell python3-config --includes)
CXXFLAGS = -Wall -Wextra -O2 $(PYTHON_INCLUDE) -I $(NUMPY_INCLUDE) -I lib/matplotlib-cpp

# Linker flags
PYTHON_LIBS = $(shell python3-config --ldflags)
LDFLAGS = -lpython3.10

# Default target
all: $(EXEC)

# Rule to build the executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC) $(LDFLAGS)

# Rule to build object files
$(OBJDIR)/%.o: src/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure the build directory exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

clean_store:
	rm -rf store
	mkdir store

# Clean up build files
clean:
	rm -rf $(OBJDIR)