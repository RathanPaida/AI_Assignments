# ---------- FORWARD CHAINING ----------

def forward_chaining(kb_rules, facts, goal):
    # Initialize inferred dictionary
    inferred = {}

    # Collect all symbols
    symbols = set()
    for premises, conclusion in kb_rules:
        symbols.update(premises)
        symbols.add(conclusion)
    for f in facts:
        symbols.add(f)

    # Initially all symbols are not inferred
    for s in symbols:
        inferred[s] = False

    # Count of remaining premises for each rule
    count = []
    for premises, conclusion in kb_rules:
        count.append(len(premises))

    # Queue (using list instead of deque)
    queue = list(facts)

    print("Initial Queue:", queue)

    # Algorithm
    while len(queue) > 0:
        p = queue.pop(0)   # FIFO (remove first element)
        print("\nProcessing:", p)

        if p == goal:
            return True

        if not inferred[p]:
            inferred[p] = True

            for i in range(len(kb_rules)):
                premises, conclusion = kb_rules[i]

                if p in premises:
                    count[i] -= 1
                    print(f"Updated count for {premises}->{conclusion}: {count[i]}")

                    if count[i] == 0:
                        print(f"All premises satisfied -> Adding {conclusion}")
                        queue.append(conclusion)

    return False


# -------- CASE 1 --------
rules1 = [
    (['P'], 'Q'),
    (['L', 'M'], 'P'),
    (['A', 'B'], 'L')
]

facts1 = ['A', 'B', 'M']
query1 = 'Q'

print("\nForward Chaining Case 1:")
print("Result:", forward_chaining(rules1, facts1, query1))


# -------- CASE 2 --------
rules2 = [
    (['A'], 'B'),
    (['B'], 'C'),
    (['C'], 'D'),
    (['D', 'E'], 'F')
]

facts2 = ['A', 'E']
query2 = 'F'

print("\nForward Chaining Case 2:")
print("Result:", forward_chaining(rules2, facts2, query2))