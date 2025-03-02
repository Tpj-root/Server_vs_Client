import socket

def send_sab_message(message, address='127.0.0.1', port=12345):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sab_message = f"sab://{message}"
    sock.sendto(sab_message.encode(), (address, port))
    sock.close()

send_sab_message("Hello, SAB!")

