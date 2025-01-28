#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>

const int PLUS = -1;
const int MINUS = -2;

using namespace std;

struct Node {
    int type;
    Node *lhs;
    Node *rhs;
};

Node *parse(vector<int> &tokens, int &l);
Node *term(vector<int> &tokens, int &l);

Node *parse(vector<int> &tokens, int &l)
{
    // if (l >= tokens.size()) return nullptr;

    Node *lhs = term(tokens, l);
    int op = tokens[l++];
    Node *rhs = term(tokens, l);

    return new Node{op, lhs, rhs};
}

Node *term(vector<int> &tokens, int &l)
{
    if (tokens[l] >= 0) {
        l++;
        return new Node{0, nullptr, nullptr};
    }

    return parse(tokens, l);
}

void print(Node *node, int indent=0)
{
    for (int i = 0; i < indent; ++i)
        cout << " ";

    if (node->type == 0) {
        cout << "x\n";
        return;
    }

    if (node->type == PLUS)
        cout << "+\n";
    else if (node->type == MINUS)
        cout << "-\n";

    print(node->lhs, indent+2);
    print(node->rhs, indent+2);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;

    // vector<bool> plus(n-1, false);
    vector<int> tokens;

    for (int i = 0; i < n-1; ++i) {
        string s;
        cin >> s;

        tokens.push_back(i+1);

        if (s == "+") {
            tokens.push_back(PLUS);
            // plus[i] = true;
        } else {
            tokens.push_back(MINUS);
        }
    }
    tokens.push_back(n);

    for (auto t: tokens) {
        if (t == PLUS) {
            cout << " + ";
        } else if (t == MINUS) {
            cout << " - ";
        } else {
            cout << t;
        }
    }
    cout << "\n";

    int l = 0;
    Node *node = parse(tokens, l);
    print(node);

    return 0;
}
