#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

#define INF INT_MAX
#define rep(n, i) for (auto i = 0; i < n; ++i)

typedef vector<pair<int, int>> Cards;


struct Node {
    Node *parent = NULL;
    Node *left = NULL;
    Node *right = NULL;
    int leaf = -1;
    bool xx=false, xy=false, yx=false, yy=false;
    int l=-1;
    int r=-1;
};

vector<Node*> leaves;

Node *construct(Cards &cards, int l, int r, Node *parent = NULL)
{
    
    Node *node = new Node;
    node->parent = parent;
    node->l = l;
    node->r = r;
    
    if (l >= r) {
        // cout << l << "\n";
        node->leaf = l;
        leaves[node->leaf] = node;

        auto &a = cards[node->leaf*2];
        auto &b = cards[node->leaf*2 + 1];
        node->xx = a.first <= b.first;
        node->xy = a.first <= b.second;
        node->yx = a.second <= b.first;
        node->yy = a.second <= b.second;
    } else {
        node->left = construct(cards, l, (l+r)/2, node);
        node->right = construct(cards, (l+r)/2 + 1, r, node);

        int i = (l+r)/2;
        int xi = cards[i*2+1].first;
        int yi = cards[i*2+1].second;
        int xj = cards[(i+1)*2].first;
        int yj = cards[(i+1)*2].second;

        //cout << xi << "," << yi << "  " << xj<<","<<yj<<"\n";

        auto tl = node->left;
        auto tp = node->right;

        node->xx = (tl->xx && tp->xx && xi <= xj) ||
                   (tl->xx && tp->yx && xi <= yj) ||
                   (tl->xy && tp->xx && yi <= xj) ||
                   (tl->xy && tp->yx && yi <= yj);

        node->xy = (tl->xx && tp->xy && xi <= xj) ||
                   (tl->xx && tp->yy && xi <= yj) ||
                   (tl->xy && tp->xy && yi <= xj) ||
                   (tl->xy && tp->yy && yi <= yj);

        node->yx = (tl->yx && tp->xx && xi <= xj) ||
                   (tl->yx && tp->yx && xi <= yj) ||
                   (tl->yy && tp->xx && yi <= xj) ||
                   (tl->yy && tp->yx && yi <= yj);
        
        node->yy = (tl->yx && tp->xy && xi <= xj) ||
                   (tl->yx && tp->yy && xi <= yj) ||
                   (tl->yy && tp->xy && yi <= xj) ||
                   (tl->yy && tp->yy && yi <= yj);
    }

    return node;
}

void compute(Node *node, Cards &cards)
{
    if (node->left == NULL) {
        auto &a = cards[node->leaf*2];
        auto &b = cards[node->leaf*2 + 1];
        node->xx = a.first <= b.first;
        node->xy = a.first <= b.second;
        node->yx = a.second <= b.first;
        node->yy = a.second <= b.second;
    } else {
        compute(node->left, cards);
        compute(node->right, cards);
        
        int l = node->left->l;
        int r = node->right->r;
        int i = (l+r)/2;
        int xi = cards[i*2+1].first;
        int yi = cards[i*2+1].second;
        int xj = cards[(i+1)*2].first;
        int yj = cards[(i+1)*2].second;

        //cout << xi << "," << yi << "  " << xj<<","<<yj<<"\n";

        auto tl = node->left;
        auto tp = node->right;

        node->xx = (tl->xx && tp->xx && xi <= xj) ||
                   (tl->xx && tp->yx && xi <= yj) ||
                   (tl->xy && tp->xx && yi <= xj) ||
                   (tl->xy && tp->yx && yi <= yj);

        node->xy = (tl->xx && tp->xy && xi <= xj) ||
                   (tl->xx && tp->yy && xi <= yj) ||
                   (tl->xy && tp->xy && yi <= xj) ||
                   (tl->xy && tp->yy && yi <= yj);

        node->yx = (tl->yx && tp->xx && xi <= xj) ||
                   (tl->yx && tp->yx && xi <= yj) ||
                   (tl->yy && tp->xx && yi <= xj) ||
                   (tl->yy && tp->yx && yi <= yj);
        
        node->yy = (tl->yx && tp->xy && xi <= xj) ||
                   (tl->yx && tp->yy && xi <= yj) ||
                   (tl->yy && tp->xy && yi <= xj) ||
                   (tl->yy && tp->yy && yi <= yj);
    }
}

void compute_up(Node *node, Cards &cards)
{
    if (node->left == NULL) {
        auto &a = cards[node->leaf*2];
        auto &b = cards[node->leaf*2 + 1];
        node->xx = a.first <= b.first;
        node->xy = a.first <= b.second;
        node->yx = a.second <= b.first;
        node->yy = a.second <= b.second;
    } else {

        int l = node->left->l;
        int r = node->right->r;
        int i = (l+r)/2;
        int xi = cards[i*2+1].first;
        int yi = cards[i*2+1].second;
        int xj = cards[(i+1)*2].first;
        int yj = cards[(i+1)*2].second;

        //cout << xi << "," << yi << "  " << xj<<","<<yj<<"\n";

        auto tl = node->left;
        auto tp = node->right;

        node->xx = (tl->xx && tp->xx && xi <= xj) ||
                   (tl->xx && tp->yx && xi <= yj) ||
                   (tl->xy && tp->xx && yi <= xj) ||
                   (tl->xy && tp->yx && yi <= yj);

        node->xy = (tl->xx && tp->xy && xi <= xj) ||
                   (tl->xx && tp->yy && xi <= yj) ||
                   (tl->xy && tp->xy && yi <= xj) ||
                   (tl->xy && tp->yy && yi <= yj);

        node->yx = (tl->yx && tp->xx && xi <= xj) ||
                   (tl->yx && tp->yx && xi <= yj) ||
                   (tl->yy && tp->xx && yi <= xj) ||
                   (tl->yy && tp->yx && yi <= yj);
        
        node->yy = (tl->yx && tp->xy && xi <= xj) ||
                   (tl->yx && tp->yy && xi <= yj) ||
                   (tl->yy && tp->xy && yi <= xj) ||
                   (tl->yy && tp->yy && yi <= yj);
    }

    if (node->parent != NULL) {
        compute_up(node->parent, cards);
    }
}

void print(Cards &cards, Node *node, int indent=0)
{
    if (node->left == NULL) {

        int rx = cards[node->leaf*2 + 1].first;
        int ry = cards[node->leaf*2 + 1].second;
        int lx = cards[node->leaf*2].first;
        int ly = cards[node->leaf*2].second;

        rep(indent+6, i) {
            cout << " ";
        }
        cout << rx << "," << ry << "\n";

        rep(indent, i) {
            cout << " ";
        }
        cout << node->xx << node->xy << node->yx << node->yy << "\n";

        rep(indent+6, i) {
            cout << " ";
        }
        cout << lx << "," << ly << "\n";
    } else {
        print(cards, node->right, indent + 6);
        rep(indent, i) {
            cout << " ";
        }
        cout << node->xx << node->xy << node->yx << node->yy << "\n";
        print(cards, node->left, indent + 6);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    unsigned int n;
    cin >> n;

    leaves.resize(n);

    Cards cards(2*n, {INF, INF});
    rep(n, i) {
        cin >> cards[i].first >> cards[i].second;
    }

    Node *node = construct(cards, 0, n - 1);

    // for (auto l: leaves) {
    //     cout << l << "\n";
    // }

    // print(cards, node);
    // cout << "\n\n\n";

    int m;
    cin >> m;
    rep(m, i) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        {
            auto t = cards[a];
            cards[a] = cards[b];
            cards[b] = t;
        }

        // compute(node, cards);

        compute_up(leaves[a/2], cards);
        compute_up(leaves[b/2], cards);

        // print(cards, node);
        // cout << "\n\n\n";

        bool yes = node->xx || node->xy || node->yx || node->yy;
        cout << (yes ? "TAK" : "NIE") << "\n";
    }

    return 0;
}
