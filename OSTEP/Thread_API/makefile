
ARG :=thread_create.c thread_create_with_ret.c

RMV :=${ARG:.c=}

thread_create:thread_create.c
	gcc thread_create.c -o thread_create -lpthread
thread_create_with_ret:thread_create_with_ret.c
	gcc thread_create_with_ret.c -o thread_create_with_ret -lpthread -I ../include
clean:
	rm -f ${RMV}