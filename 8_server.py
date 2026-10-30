# A college wants to develop a client-server application to perform mathematical calculations 
# remotely. Write a program in C/C++/Python/Java using TCP socket programming in which the 
# client sends two numbers and an arithmetic operator (+, −, ×, ÷) to the server. The server 
# performs the calculation and sends the result back to the client. 
import socket

# Configure server address and port
HOST = '127.0.0.1'  # Localhost
PORT = 65432        # Arbitrary non-privileged port

# Create a TCP socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((HOST, PORT))
server_socket.listen(1)

print(f"Server is running and listening on {HOST}:{PORT}...")

# Accept incoming client connection
conn, addr = server_socket.accept()
print(f"Connected successfully by {addr}")

try:
    # Receive data from the client (up to 1024 bytes) and decode it
    data = conn.recv(1024).decode('utf-8')
    if data:
        # Expected format from client: "num1,num2,operator"
        num1_str, num2_str, operator = data.split(',')
        num1 = float(num1_str)
        num2 = float(num2_str)
        
        # Perform math operation based on the operator
        if operator == '+':
            result = num1 + num2
        elif operator == '-':
            result = num1 - num2
        elif operator == '*':
            result = num1 * num2
        elif operator == '/':
            if num2 == 0:
                result = "Error: Division by zero"
            else:
                result = num1 / num2
        else:
            result = "Error: Invalid operator"
            
        # Send the result back as a string encoded in bytes
        conn.sendall(str(result).encode('utf-8'))

finally:
    # Clean up the connections
    conn.close()
    server_socket.close()
    print("Server shut down cleanly.")
