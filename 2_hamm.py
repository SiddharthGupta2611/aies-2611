# A bank transmits customer transaction data between two computers. Write a program in 
# C/C++/Python/Java to implement Hamming Code, introduce a single-bit transmission error, detect 
# the error, and correct the corrupted bit at the receiver.
import random

def calculate_parity_bits(data):
    """
    Encodes 4 bits of data into a 7-bit Hamming Code (7, 4).
    Positions: P1  P2  D3  P4  D5  D6  D7
    Indices:   1   2   3   4   5   6   7
    """
    d3, d5, d6, d7 = data[0], data[1], data[2], data[3]
    
    # Even parity calculation
    p1 = d3 ^ d5 ^ d7
    p2 = d3 ^ d6 ^ d7
    p4 = d5 ^ d6 ^ d7
    
    # Construct the 7-bit codeword
    return [p1, p2, d3, p4, d5, d6, d7]

def detect_and_correct(codeword):
    """
    Detects a single-bit error using check bits and corrects it.
    """
    c1 = codeword[0] ^ codeword[2] ^ codeword[4] ^ codeword[6]
    c2 = codeword[1] ^ codeword[2] ^ codeword[5] ^ codeword[6]
    c4 = codeword[3] ^ codeword[4] ^ codeword[5] ^ codeword[6]
    
    # The error position is the decimal value of the parity checks (c4 c2 c1)
    error_position = (c4 << 2) + (c2 << 1) + c1
    
    print(f"[Receiver] Calculating syndrome (c4 c2 c1): {c4}{c2}{c1}")
    
    if error_position == 0:
        print("[Receiver] No error detected. Data is intact.")
        corrected_word = codeword.copy()
    else:
        print(f"[Receiver] ⚠️ Single-bit error detected at position: {error_position}")
        corrected_word = codeword.copy()
        # Flip the corrupted bit (convert 1 to 0 or 0 to 1)
        corrected_word[error_position - 1] ^= 1 
        print(f"[Receiver] ✅ Bit corrected at position {error_position}.")
        
    # Extract the original data bits (positions 3, 5, 6, 7)
    extracted_data = [corrected_word[2], corrected_word[4], corrected_word[5], corrected_word[6]]
    return extracted_data, error_position

# ==========================================
# SIMULATION: Bank Data Transmission
# ==========================================
if __name__ == "__main__":
    # 1. Sender Side
    transaction_data = [1, 0, 1, 1]  # 4-bit transaction segment
    print(f"[Sender] Original transaction data: {transaction_data}")
    
    encoded_codeword = calculate_parity_bits(transaction_data)
    print(f"[Sender] Transmitting 7-bit Hamming codeword: {encoded_codeword}")
    print("-" * 60)
    
    # 2. Transmission Channel (Introduce a random 1-bit error)
    transmitted_codeword = encoded_codeword.copy()
    error_index = random.randint(0, 6)  # Pick a random position (0 to 6) to corrupt
    transmitted_codeword[error_index] ^= 1  # Flip the bit
    
    print(f"[Channel] ⚡ Noise introduced! Bit flipped at position {error_index + 1}")
    print(f"[Channel] Received corrupted codeword: {transmitted_codeword}")
    print("-" * 60)
    
    # 3. Receiver Side
    received_data, detected_pos = detect_and_correct(transmitted_codeword)
    
    print("-" * 60)
    print(f"[Result] Extracted transaction data: {received_data}")
    print(f"[Result] Success: {transaction_data == received_data}")
