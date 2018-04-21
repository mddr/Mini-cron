obj = src/log.c src/main.c src/read.c src/task.c

build : $(obj)
	gcc $(obj) -o build.o