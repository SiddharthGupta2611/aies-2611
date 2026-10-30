#  A college wants to develop a client-server application for string conversion. Write a program 
# in C/C++/Python/Java using UDP socket programming in which the client sends a string to the 
# server, the server converts the string from lowercase to uppercase, and sends the converted 
# string back to the client. 
import socket

# Define server address and port
SERVER_IP = "127.0.0.1"
SERVER_PORT = 12345

# Create a UDP socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_socket.bind((SERVER_IP, SERVER_PORT))

print(f"UDP Server is running and listening on {SERVER_IP}:{SERVER_PORT}...")

try:
    while True:
        # Wait for data from the client
        data, client_address = server_socket.recvfrom(1024)
        received_string = data.decode('utf-8')
        print(f"Received from {client_address}: {received_string}")

        # Check if the client sent the exit command
        if received_string.strip().upper() == "EXIT":
            print("Exit command received. Shutting down server...")
            server_socket.sendto("SERVER_SHUTDOWN".encode('utf-8'), client_address)
            break

        # Convert lowercase (and all characters) to uppercase
        uppercase_string = received_string.upper()

        # Send the converted string back to the client
        server_socket.sendto(uppercase_string.encode('utf-8'), client_address)

except KeyboardInterrupt:
    print("\nServer interrupted by user.")
finally:
    server_socket.close()
    print("Server socket closed.")


