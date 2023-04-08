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
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAddr.sin_port = htons(port);
	char MsgSend[MAX];
	char MsgRecv[MAX];

	//creating a client side socket
	int clientSocket = socket(AF_INET , SOCK_STREAM , 0);

	if(clientSocket < 0) 
	{
		cout << "Client socket creation has failed" << endl;
		return 0;
    }

	//connecting the client side socket
	if(connect(clientSocket ,  (struct sockaddr*) & serverAddr , sizeof(serverAddr)) < 0)
	{
		cout << "Connection Error..." << endl;
		return 0;
	}
	else
	{
		cout << "...Connection Established...\n\n";
	}

	//Dialog between server and client
	while(true)
	{
		cout << "Client : ";
		//sending message 
		cin.getline(MsgSend,MAX);
		send(clientSocket , MsgSend , strlen(MsgSend)+1 , 0);
		if(MsgSend[0] == 'b' && MsgSend[1] == 'y' && MsgSend[2] == 'e'){
			cout << "\nConnection ended...\n" ;
			break;
		}

		//receiving message
		int MsgRecvSize = recv(clientSocket , MsgRecv , MAX , 0);
		
		if(MsgRecvSize < 0)
		{
			cout << "Packet recieve failed." << endl;
			return 0;
		}
		else if(MsgRecvSize == 0)
		{
			cout << "Server is off." << endl;
			return 0;
		}
		else{
			cout << "received server : " << MsgRecv <<endl;
		
			if(MsgRecv[0] == 'b' && MsgRecv[1] == 'y' && MsgRecv[2] == 'e')
			{
				cout << "\nConnection ended...\n" ;
				break;
			}
		}
	}
	close(clientSocket);
	return 0;
}
