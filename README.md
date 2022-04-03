# FileSender
Simple C-based client-server app to send file

## How to build

- Run in project root directory
```
make all
```

## How to run

- Run **server** to get file:
```
server [port] [targetFilePath]
for example
./server 8080 ./recievedFile
```
- Run **client** to send file:
```
client [address] [port] [filePath]
for example
./client 127.0.0.1 8080 ./fileToSend
```
- Transfered file will appear in `[targetFilePath]`