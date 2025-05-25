CC = g++
CPPFLAGS = -Wall -Werror -Wextra -std=c++17 -lstdc++
OBJ_MODEL = model/*.cc
OBJ_MODEL_TEST = model/parser.cc model/affinetransformation.cc
OBJ_CONTROLLER = controller/*.cc
OBJ_TEST = tests/test.cc
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
  	OPEN_CMD = xdg-open
	LEAKS_CMD = valgrind --tool=memcheck --leak-check=yes
	PATH_APP = 3d_Viewer/3d_Viewer_2_0
	ADD_LIB = -lgtest -lpthread -lm
	GCOV_FLAGS = 
endif

ifeq ($(UNAME_S),Darwin)
	OPEN_CMD = open -a "Google Chrome"
	LEAKS_CMD = leaks -atExit --
	PATH_APP = 3DViewer/3d_Viewer_2_0.app/Contents/MacOS/3d_Viewer_2_0
	ADD_LIB = -lgtest -lm
	GCOV_FLAGS = 
endif

all: install

install:
	@rm -rf 3DViewer
	@mkdir 3DViewer
	@cd 3DViewer && qmake ../view/3d_Viewer_2_0.pro && make -j6 && make clean && rm -rf Makefile .qmake.stash

uninstall:
	@rm -rf 3DViewer

dist: install
	@rm -rf dist
	@mkdir dist
	@cp -R $(PATH_APP) model view controller tests Makefile dvi.md dist
	@cd dist && tar cvzf 3DViewer_v2.0.tgz * && rm -rf controller model tests view 3d_Viewer_2_0 Makefile dvi.md
	@rm -rf 3DViewer_v2.0

dvi:
	@$(OPEN_CMD) ../dvi/README.html

tests: clean
	@$(CC) $(CPPFLAGS) $(OBJ_TEST) $(OBJ_MODEL_TEST) -o test $(ADD_LIB)
	@./test

test_leaks: clean
	@$(CC) $(CPPFLAGS) $(OBJ_TEST) $(OBJ_MODEL_TEST) -o test_leaks $(ADD_LIB)
	@$(LEAKS_CMD) ./test_leaks

gcov: clean
	@$(CC) $(CPPFLAGS) --coverage $(OBJ_TEST) $(OBJ_MODEL_TEST) -o test $(ADD_LIB)
	@./test
	@rm -rf test-test.gcda test-test.gcno
	@lcov -t "s21_test" -o fizzbuzz.info -c -d . $(GCOV_FLAGS)
	@genhtml -o report fizzbuzz.info
	@$(OPEN_CMD) report/index.html

style:
	@clang-format -style=Google -i */*.h */*.cc 

clean:
	@-rm -rf *.o *.gcno *.gcda *.info *.gcov *.a *.dSYM report test test_leaks *.out
