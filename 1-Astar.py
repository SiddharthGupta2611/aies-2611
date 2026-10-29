from queue import PriorityQueue

def read():
    print("Enter a 3x3 grid line by line (space-separated numbers, 0 for empty):")
    return tuple(tuple(map(int, input().split())) for _ in range(3))

def h(s, goal):
    count = 0
    for i in range(3):
        for j in range(3):
            if s[i][j] != 0 and s[i][j] != goal[i][j]:
                count += 1
    return count

def astar(start, goal):
    pq = PriorityQueue()
    counter = 0  # Tie-breaker to prevent matrix comparisons
    
    # Store format: (f_score, g_score, unique_id, state)
    pq.put((h(start, goal), 0, counter, start))
    visited = set()
    
    while not pq.empty():
        f, g, _, s = pq.get()
        
        if s in visited:
            continue
        visited.add(s)
        
        print("Visited State:")
        for row in s:
            print(list(row))
        print(f"f = {f}, g = {g}, h = {h(s, goal)}\n")
        
        if s == goal:
            print("Goal Reached!")
            return
            
        # Locate blank spot (0)
        x, y = 0, 0
        for i in range(3):
            for j in range(3):
                if s[i][j] == 0:
                    x, y = i, j
                    
        moves = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        for dx, dy in moves:
            nx, ny = x + dx, y + dy
            if 0 <= nx < 3 and 0 <= ny < 3:
                # Convert to list to modify elements easily
                new_list = [list(row) for row in s]
                new_list[x][y], new_list[nx][ny] = new_list[nx][ny], new_list[x][y]
                # Convert back to tuple for set membership optimization
                new_tuple = tuple(tuple(row) for row in new_list)
                
                if new_tuple not in visited:
                    ng = g + 1
                    nh = h(new_tuple, goal)
                    counter += 1
                    pq.put((ng + nh, ng, counter, new_tuple))
                    
    print("No Solution Found")

if __name__ == "__main__":
    print("--- Enter Initial State ---")
    start = read()
    print("--- Enter Goal State ---")
    goal = read()
    
    print("\nStarting A* Search...\n")
    astar(start, goal)
#O(n)