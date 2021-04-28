import socket
import json

SERVER_IP = '127.0.0.1'
SERVER_PORT = 25667
SIGNUP_CODE = '2'
LOGINUP_CODE = '1'
LEN_BYTES = 4

def creating_socket():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # create socket
    server_adress = (SERVER_IP, SERVER_PORT)
    sock.connect(server_adress) # connects to server

    return sock

def main():
    dict = {}
    Code = LOGINUP_CODE
    option = int(input("Enter 2 to sign up , or 1 for login: "))

    if(option == 2):
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

    sock = creating_socket()
    server_msg = sock.recv(1024)
    server_msg = server_msg.decode()
    print(server_msg)

    sock.sendall(msg.encode())

    server_msg = sock.recv(1024)
    server_msg = server_msg.decode()
    print(server_msg)
    if(server_msg == "none"):
        print("Bad request")

    wait = input("Wait for key")
    sock.close()

if __name__ == "__main__":
    main()
