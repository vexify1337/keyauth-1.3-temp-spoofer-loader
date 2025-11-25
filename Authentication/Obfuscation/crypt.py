#!/usr/bin/env python3
"""
AES-256-CBC File Encryption Script
Encrypts a file and outputs the IV and AES key in hex format.
Usage: python crypt.py <file_path>
"""

import os
import sys
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import padding
import secrets


def generate_random_key():
    """Generate a random 256-bit (32-byte) AES key."""
    return secrets.token_bytes(32)


def generate_random_iv():
    """Generate a random 128-bit (16-byte) IV."""
    return secrets.token_bytes(16)


def encrypt_file(file_path):
    """Encrypt a file using AES-256-CBC and return encrypted data, key, and IV."""
    # Read the file
    if not os.path.exists(file_path):
        print(f"Error: File '{file_path}' not found.", file=sys.stderr)
        sys.exit(1)
    
    with open(file_path, 'rb') as f:
        plaintext = f.read()
    
    # Generate key and IV
    key = generate_random_key()
    iv = generate_random_iv()
    
    # Create cipher
    cipher = Cipher(algorithms.AES(key), modes.CBC(iv), backend=default_backend())
    encryptor = cipher.encryptor()
    
    # Apply PKCS7 padding (same as BCRYPT_BLOCK_PADDING in Windows)
    padder = padding.PKCS7(128).padder()  # 128 bits = 16 bytes (AES block size)
    padded_data = padder.update(plaintext)
    padded_data += padder.finalize()
    
    # Encrypt
    encrypted_data = encryptor.update(padded_data)
    encrypted_data += encryptor.finalize()
    
    return encrypted_data, key, iv


def bytes_to_hex(byte_data):
    """Convert bytes to hex string (uppercase, no separators)."""
    return byte_data.hex().upper()


def main():
    if len(sys.argv) != 2:
        print("Usage: python crypt.py <file_path>", file=sys.stderr)
        sys.exit(1)
    
    file_path = sys.argv[1]
    
    # Encrypt the file
    try:
        encrypted_data, key, iv = encrypt_file(file_path)
    except Exception as e:
        print(f"Error during encryption: {e}", file=sys.stderr)
        sys.exit(1)
    
    # Convert to hex strings (matching the format expected by the C++ code)
    key_hex = bytes_to_hex(key)
    iv_hex = bytes_to_hex(iv)
    
    # Write encrypted data to output file (same name with .encrypted extension)
    output_path = file_path + ".encrypted"
    try:
        with open(output_path, 'wb') as f:
            f.write(encrypted_data)
    except Exception as e:
        print(f"Error writing encrypted file: {e}", file=sys.stderr)
        sys.exit(1)
    
    # Output the key and IV (to be used in the C++ application)
    print(f"AES Key (hex): {key_hex}")
    print(f"IV (hex): {iv_hex}")
    print(f"Encrypted file saved to: {output_path}")


if __name__ == "__main__":
    main()

