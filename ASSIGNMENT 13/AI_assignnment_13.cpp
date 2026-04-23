#include <bits/stdc++.h>
using namespace std;

// ================= SYMBOL CLASS =================
class Symbol {
public:
    char name;
    Symbol(char n) { name = n; }
};

// ================= HELPER FUNCTIONS =================

bool isVariable(char c) {
    return isalpha(c);
}

// precedence
int precedence(string op) {
    if (op == "~") return 3;
    if (op == "&") return 2;
    if (op == "|") return 1;
    if (op == "->") return 0;
    if (op == "<->") return 0;
    return -1;
}

// tokenize string into operators + variables
vector<string> tokenize(string s) {
    vector<string> tokens;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ' ') continue;

        if (isalpha(s[i])) {
            tokens.push_back(string(1, s[i]));
        }
        else if (s[i] == '~' || s[i] == '&' || s[i] == '|' || s[i] == '(' || s[i] == ')') {
            tokens.push_back(string(1, s[i]));
        }
        else if (s[i] == '-') {  // ->
            tokens.push_back("->");
            i++;
        }
        else if (s[i] == '<') {  // <->
            tokens.push_back("<->");
            i += 2;
        }
    }
    return tokens;
}

// ================= INFIX TO POSTFIX =================
vector<string> infixToPostfix(vector<string> tokens) {
    stack<string> st;
    vector<string> output;

    for (auto token : tokens) {

        if (isalpha(token[0])) {
            output.push_back(token);
        }
        else if (token == "(") {
            st.push(token);
        }
        else if (token == ")") {
            while (!st.empty() && st.top() != "(") {
                output.push_back(st.top());
                st.pop();
            }
            st.pop();
        }
        else {
            while (!st.empty() && precedence(st.top()) >= precedence(token)) {
                output.push_back(st.top());
                st.pop();
            }
            st.push(token);
        }
    }

    while (!st.empty()) {
        output.push_back(st.top());
        st.pop();
    }

    return output;
}

// ================= POSTFIX EVALUATION =================
bool evalPostfix(vector<string> postfix, map<char,bool> val) {
    stack<bool> st;

    for (auto token : postfix) {
        if (isalpha(token[0])) {
            st.push(val[token[0]]);
        }
        else if (token == "~") {
            bool a = st.top(); st.pop();
            st.push(!a);
        }
        else {
            bool b = st.top(); st.pop();
            bool a = st.top(); st.pop();

            if (token == "&") st.push(a && b);
            else if (token == "|") st.push(a || b);
            else if (token == "->") st.push(!a || b);
            else if (token == "<->") st.push(a == b);
        }
    }

    return st.top();
}

// ================= GET VARIABLES =================
vector<char> getVars(vector<string> tokens) {
    set<char> s;
    for (auto t : tokens) {
        if (isalpha(t[0])) s.insert(t[0]);
    }
    return vector<char>(s.begin(), s.end());
}

// ================= TRUTH TABLE =================
void printTruthTable(string expr) {

    vector<string> tokens = tokenize(expr);
    vector<string> postfix = infixToPostfix(tokens);
    vector<char> vars = getVars(tokens);

    int n = vars.size();
    int rows = 1 << n;

    cout << "\nExpression: " << expr << "\n";

    for (char v : vars) cout << v << " ";
    cout << "| Result\n";

    for (int i = 0; i < rows; i++) {
        map<char,bool> val;

        for (int j = 0; j < n; j++) {
            bool bit = (i >> (n-j-1)) & 1;
            val[vars[j]] = bit;
            cout << (bit ? "T" : "F") << " ";
        }

        bool res = evalPostfix(postfix, val);
        cout << "| " << (res ? "T" : "F") << "\n";
    }
}

// ================= MAIN =================
int main() {

    vector<string> expressions = {
        "~P->Q",
        "~P&~Q",
        "~P|~Q",
        "~P->~Q",
        "~P<->~Q",
        "(P|Q)&(~P->Q)",
        "((P|Q)->~R)",
        "(((P|Q)->~R)<->((~P&~Q)->~R))",
        "(((P->Q)&(Q->R))->(Q->R))",
        "((P->(Q|R))->(~P&~Q&~R))"
    };

    for (auto expr : expressions) {
        printTruthTable(expr);
    }

    return 0;
}