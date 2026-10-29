# Define the variables (regions)
regions = ["WA", "NT", "SA", "QLD", "NSW", "VIC"]

# Define the domains (available colors)
colors = ["Red", "Green", "Blue"]

# Define the constraints (adjacency list representing neighboring regions)
neighbors = {
    "WA": ["NT", "SA"],
    "NT": ["WA", "SA", "QLD"],
    "SA": ["WA", "NT", "QLD", "NSW", "VIC"],
    "QLD": ["NT", "SA", "NSW"],
    "NSW": ["SA", "QLD", "VIC"],
    "VIC": ["SA", "NSW"]
}

# Dictionary to hold the assigned colors (e.g., {"WA": "Red"})
assignment = {}

def is_valid(region, color):
    """Check if assigning this color to the region violates any constraints."""
    for neighbor in neighbors[region]:
        if neighbor in assignment and assignment[neighbor] == color:
            return False
    return True

def solve(i):
    
    if i == len(regions):
        return True
        
    current_region = regions[i]
    
    
    for color in colors:
        if is_valid(current_region, color):
            assignment[current_region] = color 
            
            if solve(i + 1):                     
                return True
                
            del assignment[current_region]    
            
    return False


if solve(0):
    print("Solution found:")
    for region, color in assignment.items():
        print(f"{region}: {color}")
else:
    print("No solution")
