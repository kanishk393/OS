all: ms mkdir ls cat date rm

ms: ms.c
	gcc ms.c -o ms -lreadline -lpthread

mkdir: mkdir.c
	gcc mkdir.c -o mkdir

ls: ls.c
	gcc ls.c -o ls

cat: cat.c
	gcc cat.c -o cat -lreadline

date: date.c
	gcc date.c -o date

rm: rm.c
	gcc rm.c -o rm

clean:
	rm -f ms mkdir ls cat date rm
