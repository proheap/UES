# UES
![C](https://img.shields.io/badge/C-00599C?style=flat-square&logo=c&logoColor=white)
[![Latest 1.0](https://img.shields.io/badge/latest-v1.0-red.svg?style=flat-square)]()  
Universal evidence system in C

----
### AUTHOR
- Martin Mišík

### VERSION
- 1.0
---

### ASSIGNMENT
One table stored on server, client works with table on local computer. Client can:
- create / remove table
- define structure table (column can be string, int, double or boolean data type)
- add / remove entry
- print all table entries
- print all table entries, which contains some string
- sort table by some column

---
### RUNNING APLICATION
#### Server translation:
	gcc server/server.c server/definitions.c server/evidence_system.c server/table.c server/column.c server/structures/linked_list.c server/structures/item.c -o server -pthread
#### Client translation:
	gcc client/client.c client/definitions.c client/menu.c -o client -pthread

#### Running server:
	./server/server 10000 server
#### Running client:
	./client/client localhost 10000 client
