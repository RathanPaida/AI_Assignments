# ---------- BACKWARD CHAINING ----------

def backward_chaining(rules, facts, goal, visited=None):
    if visited is None:
        visited = set()

    if goal in facts:
        print(f"{goal} is a fact")
        return True

    if goal in visited:
        return False

    visited.add(goal)

    for premises, conclusion in rules:
        if conclusion == goal:
            print(f"Trying to prove {goal} using {premises}")
            if all(backward_chaining(rules, facts, p, visited) for p in premises):
                return True

    return False


# -------- CASE 1 --------
rules1 = [
    (['P'], 'Q'),
    (['R'], 'Q'),
    (['A'], 'P'),
    (['B'], 'R')
]

facts1 = ['A', 'B']
query1 = 'Q'

print("\nBackward Chaining Case 1:")
print("Result:", backward_chaining(rules1, facts1, query1))


# -------- CASE 2 --------
rules2 = [
    (['A'], 'B'),
    (['B', 'C'], 'D'),
    (['E'], 'C')
]

facts2 = ['A', 'E']
query2 = 'D'

print("\nBackward Chaining Case 2:")
print("Result:", backward_chaining(rules2, facts2, query2))