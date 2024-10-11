# !!!BE CAREFUL NOT TO INSERT SPACE AT THE END OF THE VARIABLE DEFINITIONS!!!

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# directory configuration

DIR_INC = ../../header# for .hpp files
DIR_SRC = ../../source# for .cpp files

DIR_OUT = ..
DIR_DEP = $(DIR_OUT)/dependency# for .d files
#DIR_OBJ = $(DIR_OUT)/object# for .o files
DIR_BIN = $(DIR_OUT)/binary# for exe files

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# file list

INCS = $(wildcard $(DIR_INC)/*.hpp)# .hpp files
SRCS = $(wildcard $(DIR_SRC)/*.cpp)# .cpp files

DEPS = $(patsubst $(DIR_SRC)/%.cpp, $(DIR_DEP)/%.d, $(SRCS))# .d files
OBJS = $(patsubst $(DIR_SRC)/%.cpp, %.o, $(SRCS))# .o files

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# options

CPPFLAGS = -std=c++20 -I $(DIR_INC) -I"C:\Program Files\SFML-2.6.1\include"
CC = g++

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.PHONY : dummy
dummy : $(OBJS)

%.o : $(DIR_SRC)\%.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

# include .d files into this own file
-include $(DEPS)

# generate .d files whose text is like "%.o : %.cpp [depending file list]"
$(DIR_DEP)/%.d : $(DIR_SRC)/%.cpp $(INCS)
	$(CC) $(CPPFLAGS) -MM $< -o $@
