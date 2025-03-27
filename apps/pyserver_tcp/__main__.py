import socket
import threading

bind_ip = "0.0.0.0"
bind_port = 3131


def main():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((bind_ip, bind_port))

    server.listen(5)

    print(f"[+] Listening on port {bind_ip}:{bind_port}")

    while True:
        client, addr = server.accept()
        print(f"[+] Accepted connection from: {addr[0]}:{addr[1]}")

        client_handler = threading.Thread(target=handle_client, args=(client,))
        client_handler.start()


def handle_client(client_socket):
    request = client_socket.recv(1024)
    print(f"[+] Recieved: {request}")

    client_socket.send("Ping".encode())
    client_socket.close()


if __name__ == "__main__":
    main()
