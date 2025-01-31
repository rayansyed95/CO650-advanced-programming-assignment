import socket

# Set up the server
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(("127.0.0.1", 8080))  # IP and port
server_socket.listen(1)

print("Server is listening on 127.0.0.1:8080...")

while True:
    try:
        # Accept connection
        client_socket, addr = server_socket.accept()
        print(f"Connection from {addr} established.")

        # Receive and respond with a confirmation message
        while True:
            try:
                data = client_socket.recv(1024)
                if not data:
                    print(f"Client {addr} disconnected.")
                    break
                
                received_message = data.decode()
                print(f"Received: {received_message}")

                # Create a response message
                confirmation_message = f"Order received successfully! \nSent to the Kitchen for Processing.\nThanks"
                client_socket.sendall(confirmation_message.encode())  # Send confirmation
            
            except ConnectionResetError:
                print(f"Connection lost with {addr}. Client closed the connection unexpectedly.")
                break

    except KeyboardInterrupt:
        print("\nServer shutting down...")
        break

    finally:
        client_socket.close()

server_socket.close()
print("Server closed.")
