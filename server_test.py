import socket
import json

SERVER_IP = '127.0.0.1'
SERVER_PORT = 25667
BUFFER_LENGTH = 1024
SIGNUP_CODE = '2'
LOGINUP_CODE = '1'
EXIT_CODE = 3
LEN_BYTES = 4

def creating_socket():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # create socket
    server_adress = (SERVER_IP, SERVER_PORT)
    sock.connect(server_adress) # connects to server

    return sock

def main():
   sock = creating_socket()
   server_msg = sock.recv(BUFFER_LENGTH)
   server_msg = server_msg.decode()
   print(server_msg)
   option = 0
   while(option != EXIT_CODE):
    dict = {}
    Code = LOGINUP_CODE
    option = int(input("Enter 1 for login ,  2 to sign up or 3 to exit: "))

    if(option == int(SIGNUP_CODE)):
        Code = SIGNUP_CODE
        email = input("Enter your email: ")
        dict["email"] = email


    username = input("Enter username: ")
    password = input("Enter your password: ")
    dict["username"] = username
    dict["password"] = password
    buffer = json.dumps(dict)
    msg_len = str(len(buffer))
    len_with_zeros = msg_len.zfill(LEN_BYTES)
    msg = str(Code +  len_with_zeros  + buffer)

    sock.sendall(msg.encode())
    server_msg = sock.recv(BUFFER_LENGTH)
    server_msg = server_msg.decode()
    print(server_msg)

    if(server_msg == "none"):
        print("Bad request")
        sock.close()
        exit();

   wait = input("Press any key to continue...")
   sock.close()

if __name__ == "__main__":
    main()
