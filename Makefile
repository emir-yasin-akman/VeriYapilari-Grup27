all:
	gcc main.c graph/graph.c hash/hash.c queue/queue.c trie/trie.c models/property.c -o app

run:
	./app