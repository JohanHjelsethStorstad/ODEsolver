# Source files
SRCS = src/main.cpp src/IterationScheme.cpp src/Logger.cpp src/PrimeFieldInferation.cpp tests/FieldGenerator.cpp tests/TestIteration.cpp

# Object files directory
OBJDIR = build

# Object files
OBJS = $(SRCS:src/%.cpp=$(OBJDIR)/%.o)

# Executable name
EXEC = $(OBJDIR)/MyExecutable

# Compiler flags
CXXFLAGS = -Wall -Wextra -O2

# Default target
all: $(EXEC)

# Rule to build the executable
$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC)

# Rule to build object files
$(OBJDIR)/%.o: src/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure the build directory exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean up build files
clean:
	rm -rf $(OBJDIR)