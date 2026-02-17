CC = gcc
CXX = g++
CFLAGS = -Wall -Iinclude
LDFLAGS = -pthread -lrt -fopenmp

COMMON_SRC = src/common/module1.c src/common/module2.c
PTHREAD_SRC = src/pthread/main.c
OPENMP_SRC = src/openmp/main.c
CPP_SRC = src/cpp_version/main.cpp

TARGET_PTHREAD = pr1_pthread
TARGET_OPENMP = pr1_openmp_optimized
TARGET_CPP = pr1_cpp

all: $(TARGET_PTHREAD) $(TARGET_OPENMP) $(TARGET_CPP)

$(TARGET_PTHREAD):
	$(CC) $(CFLAGS) $(PTHREAD_SRC) $(COMMON_SRC) -pthread -o $(TARGET_PTHREAD)

$(TARGET_OPENMP):
	$(CC) $(CFLAGS) -O3 $(OPENMP_SRC) $(COMMON_SRC) -fopenmp -lrt -o $(TARGET_OPENMP)

$(TARGET_CPP):
	$(CXX) $(CFLAGS) -O3 $(CPP_SRC) $(COMMON_SRC) -pthread -o $(TARGET_CPP)

clean:
	rm -f $(TARGET_PTHREAD) $(TARGET_OPENMP) $(TARGET_CPP) *.log