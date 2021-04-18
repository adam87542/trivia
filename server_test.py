import socket
SERVER_IP = '127.0.0.1'
SERVER_PORT = 25667

def creating_socket():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # create socket
    server_adress = (SERVER_IP, SERVER_PORT)
    sock.connect(server_adress) # connects to server

    return sock

def main():
    sock = creating_socket()

    server_msg = sock.recv(1024)
    server_msg = server_msg.decode()
    print(server_msg)

    if server_msg == 'hello':
        sock.sendall('hello'.encode())

    wait = input("Wait for key")
    sock.close()

if __name__ == "__main__":
    main()
