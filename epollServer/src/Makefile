SRC=$(wildcard *.c)
DES=$(patsubst %.c,%.o,$(SRC))

CC=gcc
CXXFLAGE=$(INCLUDE) $(LDFLAGE) -g -c#编译时参数
CPPFLAGS=-std=c++11#预处理参数 -E -D编译时定义宏
LDFLAGE=`mysql_config --cflags --libs` -lpthread#链接库参数 -L../lib -l库名
INCLUDE=-I../include
RM=rm -rf
TARGET=server

$(TARGET):$(DES)
	$(CC) $^ $(LDFLAGE) -o $@

%.o:%.c
	$(CC) $(CXXFLAGE) $<

clean:
	$(RM) $(DES)
	$(RM) $(TARGET)

