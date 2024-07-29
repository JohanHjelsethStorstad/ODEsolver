# Source files
SRCS = src/main.cpp src/IterationScheme.cpp src/Logger.cpp src/PrimeFieldInferation.cpp tests/FieldGenerator.cpp tests/TestIteration.cpp tests/Plot.cpp

# Object files directory
OBJDIR = build

# Object files
OBJS = $(SRCS:src/%.cpp=$(OBJDIR)/%.o)

# Executable name
EXEC = $(OBJDIR)/ODESolver

# Compiler flags
NUMPY_INCLUDE = $(shell python3 -c "import numpy; print(numpy.get_include())")
CXXFLAGS = -Wall -Wextra -O2 -I /usr/include/python3.10 -I $(NUMPY_INCLUDE)

# Linker flags
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

# Clean up build files
clean:
	rm -rf $(OBJDIR)