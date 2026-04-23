def negate(literal):
    return literal[1:] if literal.startswith('~') else '~' + literal


def resolve(ci, cj):
    resolvents = []
    for di in ci:
        for dj in cj:
            if di == negate(dj):
                new_clause = (ci - {di}) | (cj - {dj})
                resolvents.append(new_clause)
    return resolvents


def resolution(kb, query):
    clauses = [set(c) for c in kb]
    clauses.append({negate(query)})

    print("Initial clauses:", clauses)

    while True:
        new = []
        for i in range(len(clauses)):
            for j in range(i + 1, len(clauses)):
                resolvents = resolve(clauses[i], clauses[j])
                for r in resolvents:
                    print("Resolving:", clauses[i], clauses[j], "->", r)
                    if not r:
                        return True
                    new.append(r)

        if all(r in clauses for r in new):
            return False

        clauses.extend(new)


kb1 = [
    {'P', 'Q'},        # P ∨ Q
    {'~P', 'R'},       # P -> R
    {'~Q', 'S'},       # Q -> S
    {'~R', 'S'}        # R -> S
]

query1 = 'S'

print("\nResolution Case 1:")
print("Result:", resolution(kb1, query1))


kb2 = [
    {'~P', 'Q'},       # P -> Q
    {'~Q', 'R'},       # Q -> R
    {'~S', '~R'},      # S -> ~R
    {'P'}
]

query2 = 'S'

print("\nResolution Case 2:")
print("Result:", resolution(kb2, query2))