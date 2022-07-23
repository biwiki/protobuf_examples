# Protobuf samples
**Simple usages of protobuf**

## Build the project:
```
make
```

## Sample usage of generated code
```
$ out/basic 
Initial has_type() false
IsInitialized() false
ByteSizeLong() 0
set_type() called, now has_type() true
IsInitialized() false
ByteSizeLong() 5
...
```

## Serialization/Deserialization with simple client/server programs:

Start the server and wait for the client to connect
```
$ out/serdes/server
```
Then start the client from another terminal:
```
$ out/serdes/client
```
On the server side, the server should be able to detect the connection from client, and start receiving commands from user.
```
Received data from unknown client!
Hello Adam
Received <Hello> from Adam
Bye Adam
Client disconected!
```
There are also the responses from server received by the client:
```
Type 1, message Unknown
Type 0, message Adam
Type 0, message Adam
Type 0, message Adam
```
