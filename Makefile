# derleyici
CC = gcc

# derleme bayrakları (uyarıları açıyoruz)
CFLAGS = -Wall

# tüm projeyi derle
all:
	$(CC) src/*.c -Iinclude -o app

# programı çalıştır
run:
	./app

# Derleme sonrası oluşan dosyaları temizle 
clean:
	rm -f app