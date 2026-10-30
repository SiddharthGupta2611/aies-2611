# A college wants to develop a client-server application for sending messages between two 
# computers. Write a program in C/C++/Python/Java using TCP socket programming to send a 
# message from the client to the server and display the received message.
import socket

# Define the server's IP and Port to connect to
SERVER_HOST = '127.0.0.1'
SERVER_PORT = 65432

# Create a TCP socket
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
    # Connect to the running TCP server
    client_socket.connect((SERVER_HOST, SERVER_PORT))
    print(f"Connected to the server at {SERVER_HOST}:{SERVER_PORT}")
    
    # Define the message to send
    message = "Hello Server! This is a message from the Client."
    
    # Encode and send the message
    client_socket.sendall(message.encode('utf-8'))
    print("Message sent successfully.")
