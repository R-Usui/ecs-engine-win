# !!!BE CAREFUL NOT TO INSERT SPACE AT THE END OF THE VARIABLE DEFINITIONS!!!

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# directory configuration

DIR_INC = header# for .hpp files
DIR_SRC = source# for .cpp files

DIR_OUT = out
DIR_DEP = $(DIR_OUT)/dependency# for .d files
DIR_OBJ = $(DIR_OUT)/object# for .o files
DIR_BIN = $(DIR_OUT)/binary# for exe files

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# file list

INCS = $(wildcard $(DIR_INC)/*.hpp)# .hpp files
SRCS = $(wildcard $(DIR_SRC)/*.cpp)# .cpp files

DEPS = $(patsubst $(DIR_SRC)/%.cpp, $(DIR_DEP)/%.d, $(SRCS))# .d files
OBJS = $(patsubst $(DIR_SRC)/%.cpp, $(DIR_OBJ)/%.o, $(SRCS))# .o files

TARGET = exec.out

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# options

CPPFLAGS = -std=c++20 -I $(DIR_INC) -I"C:\Program Files\SFML-2.6.1\include"
LINKS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
CC = g++

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#default command called by only "make"

$(DIR_BIN)/$(TARGET) : $(SRCS) $(INCS)
	cd $(DIR_OBJ) && make
	$(CC) $(OBJS) -o $@ $(LINKS) 

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#optional commands called by "make ***"

.PHONY : clean 
clean :
	del /Q out\binary\* out\object\*.o out\dependency\*.d

.PHONY : run
run:
	$(DIR_BIN)/$(TARGET)

.PHONY : all
all:
	make clean
	make
	make run
	