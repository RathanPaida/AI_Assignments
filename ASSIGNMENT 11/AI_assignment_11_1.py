districts = {
    "Kuchchh": ["Banaskantha", "Patan", "Surendranagar", "Rajkot"],
    "Banaskantha": ["Kuchchh", "Patan", "Mehsana", "Sabarkantha"],
    "Patan": ["Banaskantha", "Kuchchh", "Surendranagar", "Mehsana"],
    "Mehsana": ["Patan", "Banaskantha", "Sabarkantha", "Gandhinagar", "Ahmedabad", "Surendranagar"],
    "Sabarkantha": ["Banaskantha", "Mehsana", "Gandhinagar", "Kheda", "Panchmahal"],
    "Surendranagar": ["Kuchchh", "Patan", "Mehsana", "Ahmedabad", "Bhavnagar", "Rajkot"],
    "Rajkot": ["Kuchchh", "Surendranagar", "Bhavnagar", "Amreli", "Junagadh", "Porbandar", "Jamnagar"],
    "Jamnagar": ["Rajkot", "Porbandar"],
    "Porbandar": ["Jamnagar", "Rajkot", "Junagadh"],
    "Junagadh": ["Porbandar", "Rajkot", "Amreli"],
    "Amreli": ["Junagadh", "Rajkot", "Bhavnagar"],
    "Bhavnagar": ["Amreli", "Rajkot", "Surendranagar", "Ahmedabad"],
    "Ahmedabad": ["Surendranagar", "Mehsana", "Gandhinagar", "Kheda", "Anand", "Bhavnagar"],
    "Gandhinagar": ["Mehsana", "Sabarkantha", "Kheda", "Ahmedabad"],
    "Kheda": ["Gandhinagar", "Sabarkantha", "Panchmahal", "Vadodara", "Anand", "Ahmedabad"],
    "Anand": ["Ahmedabad", "Kheda", "Vadodara"],
    "Panchmahal": ["Sabarkantha", "Kheda", "Vadodara", "Dahod"],
    "Dahod": ["Panchmahal", "Vadodara"], 
    "Vadodara": ["Anand", "Kheda", "Panchmahal", "Dahod", "Narmada", "Bharuch"],
    "Bharuch": ["Vadodara", "Narmada", "Surat", "Anand"],
    "Narmada": ["Vadodara", "Bharuch", "Surat"],
    "Surat": ["Bharuch", "Narmada", "Navsari", "Dangs"],
    "Navsari": ["Surat", "Dangs", "Valsad"],
    "Dangs": ["Navsari", "Surat"],
    "Valsad": ["Navsari"]
}

colors = ["Red", "Green", "Blue", "Yellow"]

def is_valid_color(district, color, assignments):
    """Check if adjacent districts share the same color."""
    for neighbor in districts.get(district, []):
        if neighbor in assignments and assignments[neighbor] == color:
            return False
    return True

def solve_map_coloring(districts_left, assignments):
    if not districts_left:
        return assignments
    
    current_district = districts_left[0]
    
    for color in colors:
        if is_valid_color(current_district, color, assignments):
            assignments[current_district] = color
            
            result = solve_map_coloring(districts_left[1:], assignments)
            if result is not None:
                return result
            
            del assignments[current_district]
            
    return None

nodes = list(districts.keys())
solution = solve_map_coloring(nodes, {})

print("Map Coloring Assignments (No adjacent districts share a color):")
for district, color in solution.items():
    print(f"{district.ljust(15)} : {color}")