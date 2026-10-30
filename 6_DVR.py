# A company connects three branch offices through routers. Write a program in 
# C/C++/Python/Java to simulate the Distance Vector Routing Algorithm and find the shortest 
# path between routers.
class Router:
    def __init__(self, name, num_routers):
        self.name = name
        self.distance_vector = [float('inf')] * num_routers
        self.next_hop = [-1] * num_routers

def distance_vector_routing():
    num_routers = 3
    router_names = ["Branch_A", "Branch_B", "Branch_C"]
    
    # Fully corrected network topology matrix (cost to self is 0)
    # Direct links: A-B = 2, B-C = 4, A-C = 7
    cost_matrix = [
        [0, 2, 7],
        [2, 0, 4],
        [7, 4, 0]
    ]
    
    routers = [Router(router_names[i], num_routers) for i in range(num_routers)]
    
    # Step 1: Initialize routing tables with direct physical costs
    for i in range(num_routers):
        for j in range(num_routers):
            routers[i].distance_vector[j] = cost_matrix[i][j]
            if cost_matrix[i][j] != float('inf') and i != j:
                routers[i].next_hop[j] = j
            else:
                routers[i].next_hop[j] = i

    # Step 2: Simulate vector exchange until convergence
    updated = True
    while updated:
        updated = False
        for i in range(num_routers):        # For every source router
            for j in range(num_routers):    # For every destination router
                for k in range(num_routers):# Check paths via neighbor 'k'
                    # Only look through valid intermediate direct neighbors
                    if cost_matrix[i][k] != float('inf') and i != k:
                        new_cost = cost_matrix[i][k] + routers[k].distance_vector[j]
                        if routers[i].distance_vector[j] > new_cost:
                            routers[i].distance_vector[j] = new_cost
                            routers[i].next_hop[j] = k
                            updated = True

    # Step 3: Print final converged routing tables
    for i in range(num_routers):
        print(f"\n--- Routing Table for {routers[i].name} ---")
        print(f"{'Destination':<15}{'Cost':<10}{'Next Hop'}")
        for j in range(num_routers):
            next_hop_name = router_names[routers[i].next_hop[j]] if i != j else "-"
            print(f"{router_names[j]:<15}{routers[i].distance_vector[j]:<10}{next_hop_name}")

if __name__ == "__main__":
    distance_vector_routing()
