# C2-server- Example Demonstration here I just create a directory with my name.txt in the system of whoever try to connect (like ssh) to the bait server (Yup I can do it :) ) 
 
# Reverse Shell Server with Malicious Payload

## Project Overview

This project demonstrates a **Reverse Shell Chat Server** that listens for SSH connections and runs a malicious script on the connecting client, enabling the attacker to execute commands on the victim's machine. This system uses a **custom SSH server imitation** and a **malicious bash script** that gets triggered when the victim connects to the server.

The malicious script is executed using the `nohup` command to keep it running in the background, allowing an attacker to maintain control over the victim's machine.

> **Warning**: This project is for educational purposes only. It demonstrates techniques often used in **penetration testing**, **ethical hacking**, and **Capture the Flag (CTF)** exercises. **Unauthorized use is illegal and unethical.**

---

## Features

- **SSH server imitation**: The server listens on a specific port for SSH connections, imitating an actual SSH service.
- **Payload execution**: Once a client connects, a predefined **malicious bash script** is executed on the client machine.
- **Persistence**: The malicious script runs in the background using `nohup` to maintain persistence even if the client disconnects.
- **Message interaction**: Upon successful connection, the server sends a message to the client indicating that they are "baited".

---

## How it Works

1. **Server Initialization**:
   - The server listens for incoming SSH connections on a specific port.
   - Once a client connects, the server sends a message: "You are baited".
   
2. **Client Connection**:
   - The client connects using an SSH command like `ssh user@target_ip -p 8000`.
   - The server imitates an SSH service and triggers the malicious bash script on the client’s machine.
   
3. **Payload Execution**:
   - The script creates a folder named `Chiranjeet` and writes a message in a file (`Malicious.txt`).
   - The script is run in the background using the `nohup` command, which ensures it persists even after the client disconnects.
   
4. **Outcome**:
   - The attacker gains the ability to execute commands on the victim’s machine through the background process initiated by the malicious bash script.
   - The `nohup` command allows the attacker to keep the payload running even if the SSH connection is closed.

---

## Requirements

- **Linux system** (for both the server and the target machine)
- **gcc**: To compile the C server program
- **Bash**: To run the malicious bash script
- **SSH server**: To handle the connections (configured to use a non-standard port)

---

## Security Implications

This project is an example of how an attacker can take advantage of reverse shells and malicious SSH servers to gain unauthorized access to a system. The nohup command ensures that the malicious payload continues running in the background after the victim disconnects from the server.

**It's important to understand the techniques demonstrated here, but they should only be used for ethical hacking, penetration testing, or CTF challenges with explicit consent.**
