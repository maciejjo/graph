TARGET   = graph 

CC       = g++
CXXFLAGS   = -Wall -Wextra -pedantic -g

LINKER   = g++ -o
LFLAGS   = -Wall -Wextra -pedantic -g
SRCDIR   = src
OBJDIR   = obj

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
rm       = rm -f

$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(LFLAGS) $(OBJECTS)
	@echo "Zakończono linkowanie!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CC) $(CXXFLAGS) -c $< -o $@
	@echo "Skompilowano "$<" pomyślnie!"

.PHONEY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Wyczyszczono!"

.PHONEY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Usunięto plik wykonywalny!"

