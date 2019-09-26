from socket import *
serverName = "10.124.7.86"
serverPort = 12000
clientSocket = socket(AF_INET,SOCK_DGRAM)
sentence = input("Enter file name")
clientSocket.sendto(bytes(sentence,"utf-8"),(serverName,serverPort))
filecontents,serverAddress = clientSocket.recvfrom(2048)
print("from server:",filecontents)
clientSocket.close()
