from socket import *
serverPort = 12000
serverSocket = socket(AF_INET,SOCK_DGRAM)
serverSocket.bind(("DESKTOP-BM2ADLD",serverPort))
print("The user is ready to receive")
while 1:
    sentence,clientAddress = serverSocket.recvfrom(2048)
    file = open(sentence,"r")
    l = file.read(2048)
    serverSocket.sendto(bytes(l,"utf-8"),clientAddress)
    print("sent to client")
    file.close()

    
