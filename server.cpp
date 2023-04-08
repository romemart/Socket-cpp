#include <bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

#define MAX 500
#define port 5200

int main(int argc, char** argv)
{
	//init socket variables

	struct sockaddr_in serverAddr , clientAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	char MsgRecv[MAX];
	char MsgSend[MAX];
	socklen_t len = sizeof(clientAddr);
	
	//creating a server side socket
	int serverSocket = socket(AF_INET , SOCK_STREAM , 0);
	
	if(serverSocket < 0) 
	{
        cout << "Server socket creation has failed." << endl;
        return 0;
	}

	//binding the server side socket
	int bindStatus = bind(serverSocket , (struct sockaddr*) & serverAddr , sizeof(serverAddr));

	if(bindStatus < 0)
    {
		cout << "Socket binding has failed" << endl;
		return 0;
	}

	//listen to the client while others are waiting in queue of size 5
	int listenStatus = listen(serverSocket , 5);
	if(listenStatus < 0)
    {	// when queue is full listen fails
		cout << "Listner has failed" << endl;
		return 0;
    }
	cout << "...Waiting for connections..."<< endl;

	//accepting the client 
	int connection = accept(serverSocket , (struct sockaddr*) & clientAddr , &len);
	if(connection < 0)
    {
		cout << "Server didn't accept the request." << endl;
		return 0;
	}
	else
    {
		char str[INET_ADDRSTRLEN];
		struct sockaddr_in* pV4Addr = (struct sockaddr_in*)&clientAddr;
		struct in_addr ipAddr = pV4Addr->sin_addr;
		inet_ntop( AF_INET, &ipAddr, str, INET_ADDRSTRLEN );
		cout << "Server accepted the request. " << str << endl;
	}

	//Dialog between server and client
	while(true)
    {
		//receiving message
		int MsgRecvSize = recv(connection , MsgRecv , MAX , 0);
		
		if(MsgRecvSize < 0)
		{
			cout << "Packet recieve failed." << endl;
			return 0;
		}
		else if(MsgRecvSize == 0)
		{
			cout << "Client is off." << endl;
			return 0;
		}
		else{ 
			cout << "received client : " << MsgRecv << endl;
			
			if(MsgRecv[0] == 'b' && MsgRecv[1] == 'y' && MsgRecv[2] == 'e')
			{
				cout << "\nConnection ended...\n" ;
				break;
			}
		}

		cout << "Server : ";
		//sending message 
		cin.getline(MsgSend, MAX);
		send(connection , MsgSend , strlen(MsgSend)+1 , 0);
		if(MsgSend[0] == 'b' && MsgSend[1] == 'y' && MsgSend[2] == 'e'){
			cout << "\nConnection ended...\n" ;
			break;
		}
	}
	close(serverSocket);
	return 0;

}