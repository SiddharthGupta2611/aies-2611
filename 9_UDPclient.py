#  A college wants to develop a client-server application for string conversion. Write a program 
# in C/C++/Python/Java using UDP socket programming in which the client sends a string to the 
# server, the server converts the string from lowercase to uppercase, and sends the converted 
# string back to the client. 
import socket

# Define the server's IP and port to connect to
SERVER_IP = "127.0.0.1"
SERVER_PORT = 12345

# Create a UDP socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

print("UDP Client is ready. Type your text below.")
print("Type 'EXIT' to shut down both the client and the server.")
print("-" * 50)

try:
    while True:
        # Get string input from the user continuously
        message = input("\nEnter a string to send: ")

        # Skip empty inputs
        if not message.strip():
            continue

        # Send the string to the server (encoded to bytes)
        client_socket.sendto(message.encode('utf-8'), (SERVER_IP, SERVER_PORT))

        # Receive the response from the server
        data, server_address = client_socket.recvfrom(1024)
        response_text = data.decode('utf-8')

        # Check if server acknowledged shutdown
        if response_text == "SERVER_SHUTDOWN":
            print("Server acknowledged shutdown. Closing client...")
            break

        # Print the converted result from the server
        print(f"Received from server: {response_text}")

        # If the user typed EXIT, break the loop
        if message.strip().upper() == "EXIT":
            print("Exiting client application...")
            break

except KeyboardInterrupt:
    print("\nClient interrupted by user.")
finally:
    # Close the socket safely
    client_socket.close()
    print("Client socket closed.")
