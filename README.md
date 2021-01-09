### UdSP_UES
Universal evidence system in C

----------------------------------------------------------------------------------------------------------------------------------
### Author
- Martin Mišík

----------------------------------------------------------------------------------------------------------------------------------
### ASSIGNMENT
One table stored on server, client works with table on local computer. Client can:
- creating / removing table
- define structure table (column can be string, int, double or boolean data type)
- adding / removing entry
- prinitng all table entries
- printing all table entries, which contains some string
- sorting table by some column

----------------------------------------------------------------------------------------------------------------------------------
### RUNNING APLICATION
## Server translation:
    gcc Server/server.c Server/definitions.c Server/evidence_system.c Server/table.c Server/column.c /Server/structures/linked_list.c /Server/structures/item.c -o server -pthread
## Client translation:
	gcc Client/client.c Client/definitions.c Client/menu.c -o client -pthread

## Running server:
	./Server/server 10000 server
## Running client:
	./Client/client localhost 10000 client
	
----------------------------------------------------------------------------------------------------------------------------------
