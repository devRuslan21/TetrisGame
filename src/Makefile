CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -I brick_game/tetris -I gui/cli -Wpedantic
POSIX = -D_POSIX_C_SOURCE=200809L

TESTS = $(wildcard ./unit_tests/*.c)
OBJ_FSM = tetris.o tetris_fsm.o tetris_backend.o
OBJ_CLI = brick_game_frontend.o

INSTALL_DIR = ./bin
VERSION = 1.0
TARGET = tetris
DIST_DIR = $(TARGET)-$(VERSION)
DIST_SOURCES = ./Makefile ./unit_tests ./gui ./brick_game ./Doxyfile

all: clean tetris

install: clean tetris
	mkdir -p $(INSTALL_DIR)
	cp tetris $(INSTALL_DIR)

uninstall:
	rm -rf $(INSTALL_DIR)

dist: clean 
	mkdir -p $(DIST_DIR)
	cp -r $(DIST_SOURCES) $(DIST_DIR)
	tar -czf $(DIST_DIR).tar.gz $(DIST_DIR)
	rm -rf $(DIST_DIR)

dvi:
	doxygen Doxyfile

clean:
	rm -rf *.a *.o *.gcno *.gcda unit_test *.css *.html *.gcov tetris highscore_tetris.txt html latex report

rebuild: clean all

tetris: tetris.a $(OBJ_CLI) main.o
	$(CC) $(CFLAGS) $(POSIX) $^ -o $@ tetris.a -lncurses

%.o: brick_game/tetris/%.c
	$(CC) $(CFLAGS) $(POSIX) -c $< -o $@

%.o: gui/cli/%.c
	$(CC) $(CFLAGS) $(POSIX) -c $< -o $@

main.o: main.c
	$(CC) $(CFLAGS) $(POSIX) -c $< -o $@

tetris.a: $(OBJ_FSM)
	ar rc tetris.a $(OBJ_FSM)
	ranlib tetris.a

test: clean
	$(CC) $(CFLAGS) $(POSIX) -c $(TESTS)
	$(CC) $(CFLAGS) $(POSIX) -o unit_test *.o ./brick_game/tetris/*.c --coverage -lcheck -lsubunit -lm
	chmod +x unit_test
	./unit_test

gcov_report: clean test
	mkdir -p report
	gcovr -r . --html --html-details -o report/report.html --exclude unit_tests