CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -Isrc/ -Ideps/Unity/src/ -Ideps/Unity/extras/fixture/src #-I (headers)
LFLAGS =   # -L (lib path)
LIBS =   # -l (lib name)

SRCS = src/bst.c
SRC_MAIN = src/main.c
OBJS = $(SRCS:.c=.o) 
OBJ_MAIN = $(SRC_MAIN:.c=.o)
EXEC = bst

TEST_UNITY = deps/Unity/src/unity.c deps/Unity/extras/fixture/src/unity_fixture.c
TEST_SRCS = $(TEST_UNITY) tests/test.c tests/all_tests.c tests/test_runner.c
TEST_OBJS = $(TEST_SRCS:.c=.o)
TEST_EXEC = bst_test

.PHONY: clean test

all: $(EXEC) $(TEST_EXEC)
	./$(TEST_EXEC)

test: $(TEST_EXEC)
	./$(TEST_EXEC)

$(EXEC): $(OBJS) $(OBJ_MAIN)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(EXEC) $(OBJS) $(OBJ_MAIN) $(LFLAGS) $(LIBS)

$(TEST_EXEC): $(OBJS) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(INCLUES) -o $(TEST_EXEC) $(OBJS) $(TEST_OBJS) $(LFLAGS) $(LIBS) 

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) src/*.o tests/*.o *~ $(EXEC) $(TEST_EXEC)

