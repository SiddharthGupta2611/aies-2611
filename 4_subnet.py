# An organization wants to divide the network 192.168.1.0/24 into two subnets. Write a program 
# in C / C++ / Python / Java to calculate the subnet mask and the number of usable host addresses for 
# each subnet.
import math

def calculate_subnets(network_cidr, num_subnets):
    # Extract the base prefix length
    base_prefix = int(network_cidr.split('/')[1])
    
    # Calculate how many bits to borrow
    borrowed_bits = math.ceil(math.log2(num_subnets))
    new_prefix = base_prefix + borrowed_bits
    
    # Calculate total host bits remaining
    host_bits = 32 - new_prefix
    
    # Calculate usable hosts (2^host_bits - 2)
    usable_hosts = (2 ** host_bits) - 2
    
    # Calculate the subnet mask in dotted-quad format
    mask_bits = (0xFFFFFFFF << host_bits) & 0xFFFFFFFF
    subnet_mask = f"{(mask_bits >> 24) & 255}.{(mask_bits >> 16) & 255}.{(mask_bits >> 8) & 255}.{mask_bits & 255}"
    
    return subnet_mask, new_prefix, usable_hosts

# Inputs
network = "192.168.1.0/24"
subnets_needed = 2

# Calculation
mask, prefix, hosts = calculate_subnets(network, subnets_needed)

# Output Results
print(f"Original Network: {network}")
print(f"Number of Subnets: {subnets_needed}\n")
print(f"New Subnet Mask: {mask} (/{prefix})")
print(f"Usable Host Addresses per Subnet: {hosts}")
