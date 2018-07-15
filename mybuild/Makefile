# Справка
# $@ имя цели правила
# $< имя первой зависимости правила
# $^ список всех зависимостей правила
# 
# <цели> : <зависмости>
# 	<команда1>
# 	<команда2>

CC := g++ #clang++ #g++
# -lxcb for xcb lib
# -lX11 for X11 lib
# -g for include debugging symbols
# -pthread enable multithreading
CCFLAGS := -std=c++11 -g

# список каталогов с исходыми кодами
SRC_DIRS := $(shell find ../src -type d)
TEST_DIRS := $(shell find ../test -type d) $(SRC_DIRS)

# список всех файлов *.cpp
SRC := $(shell find ../src -name *.cpp)
# test files contains all files in ../src and exclude ytcf-main file
TEST_SRC := $(shell find {../test,../src} -name *.cpp | sed '/ytcf-main/d')

# Укороченный вызов функции patsubst
# $(имя_переменной:.старый_суффикс=.новый_суффикс)
# полный вызов выглядит так: OBJS := $(patsubst   %.cpp, %.o, $(SRCS))
# получится список всех объектных файлов *.o разделенный пробелами
#OBJS := $(SRCS:.cpp=.o)
SRC_OBJS := $(notdir $(patsubst %.cpp, %.o, $(SRC)))
TEST_OBJS := $(notdir $(patsubst %.cpp, %.o, $(TEST_SRC)))

all: ytcf ytcf_test

# создание выполняемого файла ytcf
ytcf: $(SRC_OBJS)
	$(CC) $(CCFLAGS) $^ -o $@
	
# создание выполняемого файла test
ytcf_test: $(TEST_OBJS)
	$(CC) $(CCFLAGS) $^ -o $@
	
test: ytcf_test
	@./$<
	
# список каталогов, где шаблонные правила будут искать зависимости
VPATH := $(TEST_DIRS)

# шаблонное правило создания объектных файлов
# флаг -I для того чтобы разрешить компилятору искать заголовочные файлы
# в указанных директориях
# флаг -MMD для создания файлов *.d со списком зависимостей: сам исходный файл,
# и файлы, включаемые с помощью директивы #include "имя_файла"  
%.o: %.cpp
	$(CC) $(CCFLAGS) -c -MMD $(addprefix -I, $(TEST_DIRS)) $<
	@printf "\e[36m$(CC)\e[32m %s\e[0m\n" $@
include $(wildcard *.d)

# очистка	
clean:
	rm -rf *.o *.d ytcf ytcf_test

print:
	echo $(TEST_DIRS)
	
.PHONY: clean

