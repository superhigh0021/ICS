Client=echoclient.c ../csapp.so
Server=echoserverpre.c echo_cnt.c sbuf.c ../csapp.so

all:
	gcc $(Client) -o client -lpthread
	gcc $(Server) -o server -lpthread