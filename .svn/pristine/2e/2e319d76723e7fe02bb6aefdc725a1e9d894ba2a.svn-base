CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall -g
LIBS = `pkg-config --libs gtk+-3.0`
TESTFLAGS = -fprofile-arcs -ftest-coverage
BUILD_DIR = build/
SRC = src

TEST_OUT_DIR = tests/

# Liste des fichiers objets
OBJ = $(BUILD_DIR)game.o $(BUILD_DIR)ai.o $(BUILD_DIR)aiV1.o $(BUILD_DIR)interaction.o $(BUILD_DIR)matrice.o $(BUILD_DIR)network.o $(BUILD_DIR)traitement.o

# Liste des fichiers de test
TEST = $(BUILD_DIR)ai.test.o $(BUILD_DIR)network.test.o $(BUILD_DIR)traitement.test.o $(BUILD_DIR)interaction.test.o $(BUILD_DIR)matrice.test.o $(BUILD_DIR)game.test.o $(BUILD_DIR)ai.o $(BUILD_DIR)aiV1.o $(BUILD_DIR)interaction.o $(BUILD_DIR)matrice.o $(BUILD_DIR)network.o $(BUILD_DIR)traitement.o

# Exécutables
EXEC = game
EXEC_TEST = test

all: clean $(EXEC) test_all docs_all open_firefox

$(EXEC): $(OBJ)
	$(CC) $(OBJ) $(LIBS) -o $(BUILD_DIR)$(EXEC)

$(BUILD_DIR)game.o : $(SRC)/gui/game.c
	$(CC) $(CFLAGS) -c $(SRC)/gui/game.c -o $(BUILD_DIR)game.o

$(BUILD_DIR)ai.o : $(SRC)/headers/ai.c $(SRC)/headers/ai.h
	$(CC) $(CFLAGS) -c $(SRC)/headers/ai.c -o $(BUILD_DIR)ai.o

$(BUILD_DIR)aiV1.o : $(SRC)/headers/aiV1.c $(SRC)/headers/aiV1.h 
	$(CC) $(CFLAGS) -c $(SRC)/headers/aiV1.c -o $(BUILD_DIR)aiV1.o

$(BUILD_DIR)interaction.o : $(SRC)/headers/interaction.c $(SRC)/headers/interaction.h
	$(CC) $(CFLAGS) -c $(SRC)/headers/interaction.c -o $(BUILD_DIR)interaction.o

$(BUILD_DIR)matrice.o : $(SRC)/headers/matrice.c $(SRC)/headers/matrice.h
	$(CC) $(CFLAGS) -c $(SRC)/headers/matrice.c -o $(BUILD_DIR)matrice.o

$(BUILD_DIR)network.o : $(SRC)/headers/network.c $(SRC)/headers/network.h
	$(CC) $(CFLAGS) -c $(SRC)/headers/network.c -o $(BUILD_DIR)network.o

$(BUILD_DIR)traitement.o : $(SRC)/headers/traitement.c $(SRC)/headers/traitement.h
	$(CC) $(CFLAGS) -c $(SRC)/headers/traitement.c -o $(BUILD_DIR)traitement.o

# Compilation des fichiers de test
$(BUILD_DIR)interaction.test.o : $(SRC)/tests/interaction.test.c $(SRC)/tests/interaction.test.h
	$(CC) $(TESTFLAGS) -c $(SRC)/tests/interaction.test.c -o $(BUILD_DIR)interaction.test.o

$(BUILD_DIR)matrice.test.o : $(SRC)/tests/matrice.test.c $(SRC)/tests/matrice.test.h
	$(CC) $(TESTFLAGS) -c $(SRC)/tests/matrice.test.c -o $(BUILD_DIR)matrice.test.o

$(BUILD_DIR)network.test.o : $(SRC)/tests/network.test.c $(SRC)/tests/network.test.h
	$(CC) $(TESTFLAGS) -c $(SRC)/tests/network.test.c -o $(BUILD_DIR)network.test.o

$(BUILD_DIR)traitement.test.o : $(SRC)/tests/traitement.test.c $(SRC)/tests/traitement.test.h
	$(CC) $(TESTFLAGS) -c $(SRC)/tests/traitement.test.c -o $(BUILD_DIR)traitement.test.o

$(BUILD_DIR)ai.test.o : $(SRC)/tests/ai.test.c $(SRC)/tests/ai.test.h
	$(CC) $(TESTFLAGS) -c $(SRC)/tests/ai.test.c -o $(BUILD_DIR)ai.test.o

$(BUILD_DIR)game.test.o : $(SRC)/game.test.c
	$(CC) $(TESTFLAGS) -c $(SRC)/game.test.c -o $(BUILD_DIR)game.test.o

test: $(TEST)
	@echo "Compiling test executable..."
	$(CC) $(TESTFLAGS) $(SRC)/game.test.c $(SRC)/headers/ai.c $(SRC)/headers/aiV1.c $(SRC)/headers/interaction.c $(SRC)/headers/matrice.c $(SRC)/headers/network.c $(SRC)/headers/traitement.c $(SRC)/tests/interaction.test.c $(SRC)/tests/matrice.test.c $(SRC)/tests/network.test.c $(SRC)/tests/traitement.test.c $(SRC)/tests/ai.test.c -o $(BUILD_DIR)$(EXEC_TEST)
	@echo "Running test executable..."
	$(BUILD_DIR)$(EXEC_TEST)
	@echo "Generating coverage report..."
	lcov --capture --directory build --output-file build/couverture.info	
	genhtml build/couverture.info --output-directory $(TEST_OUT_DIR)
	firefox $(TEST_OUT_DIR)index.html

test_all: $(TEST)
	@echo "Compiling test executable..."
	$(CC) $(TESTFLAGS) $(SRC)/game.test.c $(SRC)/headers/ai.c $(SRC)/headers/aiV1.c $(SRC)/headers/interaction.c $(SRC)/headers/matrice.c $(SRC)/headers/network.c $(SRC)/headers/traitement.c $(SRC)/tests/interaction.test.c $(SRC)/tests/matrice.test.c $(SRC)/tests/network.test.c $(SRC)/tests/traitement.test.c $(SRC)/tests/ai.test.c -o $(BUILD_DIR)$(EXEC_TEST)
	@echo "Running test executable..."
	$(BUILD_DIR)$(EXEC_TEST)
	@echo "Generating coverage report..."
	lcov --capture --directory build --output-file build/couverture.info	
	genhtml build/couverture.info --output-directory $(TEST_OUT_DIR)

docs: Doxyfile
	@echo "Generating documentation with Doxygen..."
	doxygen Doxyfile
	@echo "Opening documentation..."
	firefox docs/html/index.html

docs_all: Doxyfile
	@echo "Generating documentation with Doxygen..."
	doxygen Doxyfile

Doxyfile:
	@if [ ! -f Doxyfile ]; then \
		doxygen -g Doxyfile; \
		sed -i 's/PROJECT_NAME           = "My Project"/PROJECT_NAME           = "Jeu des carrés"/' Doxyfile; \
		sed -i 's|OUTPUT_DIRECTORY       =|OUTPUT_DIRECTORY       = docs|' Doxyfile; \
		sed -i 's|INPUT                  =|INPUT                  = src|' Doxyfile; \
		sed -i 's/RECURSIVE              = NO/RECURSIVE              = YES/' Doxyfile; \
		sed -i 's/EXTRACT_ALL            = NO/EXTRACT_ALL            = YES/' Doxyfile; \
		sed -i 's/EXTRACT_PRIVATE        = NO/EXTRACT_PRIVATE        = YES/' Doxyfile; \
		sed -i 's/EXTRACT_STATIC         = NO/EXTRACT_STATIC         = YES/' Doxyfile; \
		sed -i 's/OPTIMIZE_OUTPUT_FOR_C  = NO/OPTIMIZE_OUTPUT_FOR_C  = YES/' Doxyfile; \
		sed -i 's|GENERATE_TAGFILE      =|GENERATE_TAGFILE      = docs/jeu_des_carres.tag|' Doxyfile; \
		sed -i 's|TAGFILES              =|TAGFILES              = other_project_docs/other_project.tag=other_project_docs/html|' Doxyfile; \
		sed -i 's|USE_MDFILE_AS_MAINPAGE =|USE_MDFILE_AS_MAINPAGE = README.md|' Doxyfile; \
		fi

open_firefox:
	@echo "Opening documentation..."
	firefox docs/html/index.html
	@echo "Opening coverage report..."
	firefox $(TEST_OUT_DIR)index.html

clean:
	rm -f $(BUILD_DIR)*.o $(BUILD_DIR)$(EXEC) $(BUILD_DIR)$(EXEC_TEST) $(BUILD_DIR)*.gcda $(BUILD_DIR)*.gcno $(BUILD_DIR)*.info
	rm -rf tests/*
	rm -rf docs/*
	@if [ -f Doxyfile ]; then \
		rm Doxyfile; \
	fi

rebuild: clean all
