obj = src/log.c src/main.c src/read.c src/tasks.c

build : $(obj)
	gcc $(obj) -o build