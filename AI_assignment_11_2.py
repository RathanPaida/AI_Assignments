import itertools

def solve_cryptarithmetic():
    letters = ('S', 'E', 'N', 'D', 'M', 'O', 'R', 'Y')
    
    digits = range(10)

    for perm in itertools.permutations(digits, len(letters)):
        S, E, N, D, M, O, R, Y = perm
        
        if S == 0 or M == 0:
            continue
            
        send_val  = 1000 * S + 100 * E + 10 * N + D
        more_val  = 1000 * M + 100 * O + 10 * R + E
        money_val = 10000 * M + 1000 * O + 100 * N + 10 * E + Y
        
        if send_val + more_val == money_val:
            print("Cryptarithmetic Solution Found!")
            print("-" * 30)
            print(f"   {send_val}  (SEND)")
            print(f"+  {more_val}  (MORE)")
            print("-" * 15)
            print(f"  {money_val} (MONEY)")
            print("-" * 30)
            
            print("Variable Mappings:")
            for letter, val in zip(letters, perm):
                print(f"{letter} = {val}")
            
            # return
        # for letter, val in zip(letters, perm):
        #         print(f"{letter} = {val}", end=" ")
        # print(":Failed")

solve_cryptarithmetic()