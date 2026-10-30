# A college wants to develop a client-server application to perform mathematical calculations 
# remotely. Write a program in C/C++/Python/Java using TCP socket programming in which the 
# client sends two numbers and an arithmetic operator (+, −, ×, ÷) to the server. The server 
# performs the calculation and sends the result back to the client.
import socket

# Server's address and port to connect to
HOST = '127.0.0.1'
PORT = 65432

# Get mathematical inputs from the user
num1 = input("Enter first number: ")
num2 = input("Enter second number: ")
operator = input("Enter operator (+, -, *, /): ")

# Create a TCP socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    # Connect to the remote server
    client_socket.connect((HOST, PORT))
    
    # Package inputs into a single comma-separated string
    payload = f"{num1},{num2},{operator}"
    
    # Send data to server
    client_socket.sendall(payload.encode('utf-8'))
    
    # Receive the calculated result back from the server
    result = client_socket.recv(1024).decode('utf-8')
    print(f"Result from Server: {result}")

finally:
    # Always close the socket connection
    client_socket.close()
