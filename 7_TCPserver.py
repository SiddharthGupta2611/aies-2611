# A college wants to develop a client-server application for sending messages between two 
# computers. Write a program in C/C++/Python/Java using TCP socket programming to send a 
# message from the client to the server and display the received message.
import socket

# Define the server's IP address and Port number
HOST = '127.0.0.1'  # Localhost
PORT = 65432

# Create a TCP socket (AF_INET = IPv4, SOCK_STREAM = TCP)
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
    # Allow reuse of the address to avoid 'Address already in use' errors
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    
    # Bind the socket to the host and port
    server_socket.bind((HOST, PORT))
    
    # Listen for incoming TCP connections
    server_socket.listen(1)
    print(f"Server is listening on {HOST}:{PORT}...")
    
    # Accept a connection from a client (blocking call)
    client_connection, client_address = server_socket.accept()
    with client_connection:
        print(f"Connected successfully to client at: {client_address}")
        
        # Receive data from the client (buffer size 1024 bytes)
        received_bytes = client_connection.recv(1024)
        received_message = received_bytes.decode('utf-8')
        
        print(f"Received message from client: {received_message}")
        
    print("Server connection closed.")

