#pragma comment(lib,"ws2_32.lib")
#include <winsock2.h>
#include<ws2tcpip.h>
#include"iostream"
#include<Windows.h>
#include<string.h>

using namespace std;

int init_wsa();
int init_sock();
int bind_sock();
int sock_accept();
int send_TCp();
int recive_TCp();

SOCKET socks=SOCKET_ERROR;
SOCKET sock_2;
WSAData wsadata;
sockaddr_in bsock;

int state=0; //0 for server send 1 for server recive
int flag=0;


int main(void)
{
    init_wsa();
    init_sock();
    bind_sock();
    sock_accept();
    while(flag==0){
        if (state==0) send_TCp();
        else if(state==1) recive_TCp();
    }
    WSACleanup();
    closesocket(socks);
    printf("\nSOCKET CLOSED\n");
    return 0;
}

int init_wsa(){
    
    WORD w = MAKEWORD(2,2);
    int error;
    error=WSAStartup(w,&wsadata);
    if(error){
        cout<<"INitilIZAtion oF WSA failed"<<endl;
        WSACleanup();
        return -1;
    }
    else{
        cout<<"Initiated WSA"<<endl;
    }
}

int init_sock(){
    
    socks=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(socks==SOCKET_ERROR){
        cout<<"SOcket Error"<<endl;
        WSACleanup();
        closesocket(socks);
        return -1;
    }
    else cout<<"Socket INiTialized"<<endl;
}

int bind_sock(){
    
    bsock.sin_family = AF_INET;
    bsock.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
    bsock.sin_port=htons(5022);
    if(bind(socks,(SOCKADDR *)&bsock,sizeof(bsock))==SOCKET_ERROR){
        cout<<"BinDIng Failed"<<endl;
        WSACleanup();
        closesocket(socks);
        return -1;
    }
    else cout<<"Binded"<<endl;
}

int sock_accept(){
    // listen 
    if(listen(socks,1)==SOCKET_ERROR){
        cout<<"CAnt Listen"<<endl;
        WSACleanup();
        closesocket(socks);
        return -1;
    }
    else cout<<"LIsteninG"<<endl;
    // accept
    sock_2=accept(socks,NULL,NULL);
    if(sock_2==INVALID_SOCKET){
        cout<<"CAnt Accept"<<endl;
    }
    else{
        cout<<"AccepTEd HAndshake On"<<bsock.sin_port<<endl;
    }
}

int send_TCp(){
    char msg[200];
    while(state==0){
        printf("Enter MSG: ");
        fflush(stdin);
        cin.getline(msg,200);
        if(strcmp(msg,"[e]")==0){
            state=1;
            send(sock_2,msg,200,0);
            printf("[e]\n");
            return -1;
        }
        else if(strcmp(msg,"[E]")==0) {
            flag=1;
            state=1;
            send(sock_2,msg,200,0);
            printf("[E]\n");
            return -1;
        }
        int byte_send = send(sock_2,msg,200,0);
        if(byte_send==0) printf("CANt Send daTa\n");
        else printf("Bytes Sended:%i\n",strlen(msg));
    }

}

int recive_TCp(){
    char msg[200];
    while(state==1){
        int bytes_recv = recv(sock_2,msg,200,0);
        if(strcmp(msg,"[e]")==0){
            state=0;
            printf("Bytes reviVED:%i\n",strlen(msg));
            printf("%s\n",msg);
            return -1;
        }
        else if(strcmp(msg,"[E]")==0) {
            flag=1;
            state=0;
            printf("Bytes reviVED:%i\n",strlen(msg));
            printf("%s\n",msg);
            return -1;
        }
        if(bytes_recv==0) printf("No Byte Revived");
        else {
            printf("Bytes reviVED:%i\n",strlen(msg));
            printf("%s\n",msg);
        }
    }
    
}