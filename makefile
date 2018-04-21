obj = src/log.c src/main.c src/read.c src/task.c
taskTest = tests/taskTest.c src/task.c

build : $(obj)
	gcc $(obj) -o build.o

build-task-test : $(taskTest)
	gcc $(taskTest) -o taskTest.o