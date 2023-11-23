/*
MIT License

Permission is hereby granted, free of charge, to any person obtaining
a copy of this softwareand associated documentation files(the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and /or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions :

The above copyright noticeand this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Copyright(c) 2023 - 2023 KyungHwan Lee

*/

#include <bits/stdc++.h>
using namespace std;
#define endl "\n"

int tc, n, x, cnt;
string s;


class Node {
public:
    int key, l_height, r_height, l_num, r_num;
    Node* left_child;
    Node* right_child;
    Node* par;
    Node(int k) {
        key = k;
        left_child = NULL;
        right_child = NULL;
        par = NULL;
        // 왼쪽 서브 트리 높이
        l_height = 1;
        // 오른쪽 서브 트리 높이
        r_height = 1;
        // 왼쪽 서브 트리 노드 개수
        l_num = 0;
        // 오른쪽 서브 트리 노드 개수
        r_num = 0;
    }
};

Node* root;

// 해당 노드의 높이를 구하는 함수
int get_height(Node* node) {
    if (node == NULL)return 0;
    return max(node->l_height, node->r_height);
}

// 노드를 찾는 함수
Node* find_node(int x, bool d, bool ins) {
    Node* cur_node = root;
    int depth = 0;
    while (true) {
        if (cur_node->key == x) {
            if (d) cout << depth << " ";
            return cur_node;
        }
        else {
            if (cur_node->key > x) {
                if (ins) cur_node->l_num += 1;
                if (cur_node->left_child == NULL) {
                    if (d) cout << 0 << " ";
                    return cur_node;
                }
                cur_node = cur_node->left_child;
            }
            else if (cur_node->key < x) {
                if (ins) cur_node->r_num += 1;
                if (cur_node->right_child == NULL) {
                    if (d) cout << 0 << " ";
                    return cur_node;
                }
                cur_node = cur_node->right_child;
            }
        }
        depth++;
    }
    return NULL;
}

// minimum x
void find_min(int x) {
    Node* cur_node = find_node(x, false, false);
    while (true) {
        if (cur_node->left_child == NULL)break;
        cur_node = cur_node->left_child;
    }
    cout << cur_node->key << " ";
    find_node(cur_node->key, true, false);
    return;
}

// maximum x
void find_max(int x) {
    Node* cur_node = find_node(x, false, false);
    while (true) {
        if (cur_node->right_child == NULL)break;
        cur_node = cur_node->right_child;
    }
    cout << cur_node->key << " ";
    find_node(cur_node->key, true, false);
    return;
}

// Rotations
void ll_rotation(Node* z, Node* y, Node* x) {

    Node* node3 = y->right_child;
    Node* node4 = z->right_child;

    // 포인터 정보 변경
    if (root == z)root = y;
    if (z->par != NULL) {
        if (z == z->par->left_child) {
            z->par->left_child = y;
        }
        else z->par->right_child = y;
    }
    y->par = z->par;
    y->right_child = z;
    z->par = y;
    z->left_child = node3;
    if (node3 != NULL) {
        node3->par = z;
    }

    // 서브트리 변경에 따른 정보 변경
    z->l_num -= (y->l_num + 1);
    y->r_num += z->r_num + 1;

    // 높이 정보 갱신
    z->l_height = get_height(node3) + 1;
    z->r_height = get_height(node4) + 1;
    y->r_height = get_height(z) + 1;

    Node* cur = y;
    while (true) {
        if (cur->par == NULL)break;
        if (cur == cur->par->left_child) {
            cur->par->l_height = get_height(cur) + 1;
        }
        else {
            cur->par->r_height = get_height(cur) + 1;
        }
        cur = cur->par;
    }

    return;
}

void rr_rotation(Node* z, Node* y, Node* x) {
    Node* node1 = z->left_child;
    Node* node2 = y->left_child;

    // 포인터 정보 변경
    if (root == z)root = y;
    if (z->par != NULL) {
        if (z == z->par->left_child) {
            z->par->left_child = y;
        }
        else z->par->right_child = y;
    }
    y->par = z->par;
    y->left_child = z;
    z->par = y;
    z->right_child = node2;
    if (node2 != NULL) {
        node2->par = z;
    }

    // 서브트리 변경에 따른 정보 변경
    z->r_num -= (y->r_num + 1);
    y->l_num += (z->l_num + 1);

    // 높이 정보 갱신
    z->l_height = get_height(node1) + 1;
    z->r_height = get_height(node2) + 1;
    y->l_height = get_height(z) + 1;

    Node* cur = y;
    while (true) {
        if (cur->par == NULL)break;
        if (cur == cur->par->left_child) {
            cur->par->l_height = get_height(cur) + 1;
        }
        else {
            cur->par->r_height = get_height(cur) + 1;
        }
        cur = cur->par;
    }
    return;
}

void lr_rotation(Node* z, Node* y, Node* x) {

    Node* node2 = x->left_child;
    Node* node3 = x->right_child;

    // 포인터 정보 변경
    if (root == z)root = x;
    if (z->par != NULL) {
        if (z == z->par->left_child) {
            z->par->left_child = x;
        }
        else z->par->right_child = x;
    }
    x->par = z->par;
    x->left_child = y;
    y->par = x;
    x->right_child = z;
    z->par = x;
    y->right_child = node2;
    if (node2 != NULL) {
        node2->par = y;
    }
    z->left_child = node3;
    if (node3 != NULL) {
        node3->par = z;
    }

    // 서브트리 변경에 따른 정보 변경
    y->r_num -= (x->r_num + 1);
    z->l_num -= (x->l_num + 1 + y->l_num + 1);
    x->l_num += (y->l_num + 1);
    x->r_num += (z->r_num + 1);

    y->r_height = get_height(node2) + 1;
    z->l_height = get_height(node3) + 1;
    x->l_height = get_height(y) + 1;
    x->r_height = get_height(z) + 1;

    // 높이 정보 갱신
    Node* cur = x;
    while (true) {
        if (cur->par == NULL)break;
        if (cur == cur->par->left_child) {
            cur->par->l_height = get_height(cur) + 1;
        }
        else {
            cur->par->r_height = get_height(cur) + 1;
        }
        cur = cur->par;
    }

    return;
}

void rl_rotation(Node* z, Node* y, Node* x) {

    Node* node2 = x->left_child;
    Node* node3 = x->right_child;

    // 포인터 정보 변경
    if (root == z)root = x;
    if (z->par != NULL) {
        if (z == z->par->left_child) {
            z->par->left_child = x;
        }
        else z->par->right_child = x;
    }
    x->par = z->par;
    x->left_child = z;
    z->par = x;
    x->right_child = y;
    y->par = x;
    z->right_child = node2;
    if (node2 != NULL) {
        node2->par = z;
    }
    y->left_child = node3;
    if (node3 != NULL) {
        node3->par = y;
    }

    // 서브트리 변경에 따른 정보 변경
    y->l_num -= (x->l_num + 1);
    z->r_num -= (x->r_num + 1 + y->r_num + 1);
    x->l_num += (z->l_num + 1);
    x->r_num += (y->r_num + 1);

    // 높이 정보 갱신
    z->r_height = get_height(node2) + 1;
    y->l_height = get_height(node3) + 1;
    x->l_height = get_height(z) + 1;
    x->r_height = get_height(y) + 1;

    Node* cur = x;
    while (true) {
        if (cur->par == NULL)break;
        if (cur == cur->par->left_child) {
            cur->par->l_height = get_height(cur) + 1;
        }
        else {
            cur->par->r_height = get_height(cur) + 1;
        }
        cur = cur->par;
    }

    return;
}

// 불균형이 일어난 부분을 찾기
void find_unbalance(int val) {

    Node* x = find_node(val, false, false);
    Node* y = x->par;
    if (y == NULL)return;
    Node* z = y->par;
    if (z == NULL)return;

    int l, r;
    // 불균형이 일어나는 최초의 노드 찾기
    while (true) {
        l = z->l_height;
        r = z->r_height;
        if (max(l, r) - min(l, r) > 1)break;
        if (z->par == NULL)break;
        x = y;
        y = z;
        z = z->par;
    }


    l = z->l_height;
    r = z->r_height;
    // 불균형이 발생하지 않은 경우
    if (max(l, r) - min(l, r) <= 1)return;

    // z, y, x 배치에 따른 rotation 
    if ((y == z->left_child) && (x == y->left_child))ll_rotation(z, y, x);
    else if ((y == z->right_child) && (x == y->right_child))rr_rotation(z, y, x);
    else if ((y == z->left_child) && (x == y->right_child))lr_rotation(z, y, x);
    else if ((y == z->right_child) && (x == y->left_child))rl_rotation(z, y, x);


    return;
}

// 삽입 함수
void insert(int x) {
    Node* new_node = new Node(x);
    if (cnt == 0) {
        root = new_node;
    }
    else {

        Node* par = find_node(x, false, true);
        new_node->par = par;
        if (par->key > x) {
            par->left_child = new_node;
        }
        else {
            par->right_child = new_node;
        }

        // 높이 정보 갱신
        Node* cur_node = new_node;
        while (true) {
            cur_node = cur_node->par;

            if (cur_node == NULL)break;
            if (cur_node->left_child != NULL) {
                cur_node->l_height = get_height(cur_node->left_child) + 1;
            }
            if (cur_node->right_child != NULL) {
                cur_node->r_height = get_height(cur_node->right_child) + 1;
            }
        }
        find_unbalance(x);

    }

    find_node(x, true, false);
    cnt++;
    return;
}

// rank 함수 
void node_rank(int x) {
    Node* node = find_node(x, true, false);

    //cout << "info for node :" << node->l_num << " " << node->r_num << " " << node->l_height << " " << node->r_height << " ";

    // rank 계산
    if (node->key == x) {
        int ans = 0;
        // 본인과 본인의 왼쪽 서브트리 노드 개수
        ans += node->l_num + 1;
        // root까지 올라가면서 본인보다 rank 낮은 노드 개수 더해주기
        while (true) {
            if (node->par == NULL)break;
            if (node == node->par->right_child) ans += node->par->l_num + 1;
            node = node->par;
        }
       
        cout << ans << " ";
       
    }
    
}

//erase 후 불균형 찾기
void find_unbalance2(Node* node) {
    if (node == NULL)return;
    Node* z = node;

    // z 찾아주기
    int l, r;
    while (true) {
        l = z->l_height;
        r = z->r_height;
        if (max(l, r) - min(l, r) > 1)break;
        if (z->par == NULL)break;
        z = z->par;
    }

    l = z->l_height;
    r = z->r_height;
    // 불균형이 발생하지 않은 경우
    if (max(l, r) - min(l, r) <= 1)return;

    // y, x 찾아주기
    Node* y;
    Node* x;
    if (z->left_child == NULL && z->right_child == NULL)return;
    if (get_height(z->left_child) >= get_height(z->right_child)) {
        y = z->left_child;
    }
    else {
        y = z->right_child;
    }
    if (y->left_child == NULL && y->right_child == NULL)return;
    // y의 두 자식의 높이가 같을 경우 연산이 적은 방향으로 진행
    if (get_height(y->left_child) == get_height(y->right_child)) {
        // LL rotation
        if (y == z->left_child) {
            x = y->left_child;
        }
        // RR rotation
        else {
            x = y->right_child;
        }
    }
    else {
        if (get_height(y->left_child) > get_height(y->right_child)) {
            x = y->left_child;
        }
        else {
            x = y->right_child;
        }
    }

    // z, y, x 배치에 따른 rotation 
    if ((y == z->left_child) && (x == y->left_child))ll_rotation(z, y, x);
    else if ((y == z->right_child) && (x == y->right_child))rr_rotation(z, y, x);
    else if ((y == z->left_child) && (x == y->right_child))lr_rotation(z, y, x);
    else if ((y == z->right_child) && (x == y->left_child))rl_rotation(z, y, x);

}

// erase 하는 node가 leaf인 경우
void node_erase_leaf(Node* node) {
    Node* par = node->par;
    // 삭제 하는 node가 root 였던 경우
    if (par == NULL) {
        root = NULL;
        return;
    }
    // 삭제된 노드의 관계 제거
    if (node == par->left_child) {
        par->left_child = NULL;
        par->l_num = 0;
        par->l_height = 1;
    }
    else {
        par->right_child = NULL;
        par->r_num = 0;
        par->r_height = 1;
    }

    // root 까지 올라가며 정보 갱신
    Node* cur = par;
    par = par->par;
    while (true) {
        if (par == NULL)break;
        //cur 이 par의 왼쪽 자식
        if (cur == par->left_child) {
            par->l_num--;
            par->l_height = get_height(cur) + 1;
        }
        //cur이 par의 오른쪽 자식
        else {
            par->r_num--;
            par->r_height = get_height(cur) + 1;
        }
        cur = par;
        par = par->par;
    }
    find_unbalance2(node->par);
    delete node;
}

// erase 하는 node의 child가 1개
void node_erase_one_child(Node* node) {
    Node* par = node->par;
    // 삭제 하는 node가 root 였던 경우
    // 삭제하는 node가 root이면서 자식이 1개인 경우는 전체에 노드가 2개인 경우 뿐이다
    if (par == NULL) {
        if (node->left_child != NULL) {
            root = node->left_child;
            node->left_child->par = NULL;
        }
        else {
            root = node->right_child;
            node->right_child->par = NULL;
        }
        return;
    }
    // 삭제하는 노드의 부모가 있는 경우
    else {
        // 왼쪽 자식만 있을 경우
        if (node->left_child != NULL) {
            node->left_child->par = node->par;
            if (node == par->right_child) {
                par->right_child = node->left_child;
                par->r_height--;
                par->r_num--;
            }
            else {
                par->left_child = node->left_child;
                par->l_height--;
                par->l_num--;
            }
        }
        // 오른쪽 자식만 있을 경우
        else {
            node->right_child->par = node->par;
            if (node == par->right_child) {
                par->right_child = node->right_child;
                par->r_height--;
                par->r_num--;
            }
            else {
                par->left_child = node->right_child;
                par->l_height--;
                par->l_num--;
            }
        }

        // root 까지 올라가며 정보 갱신
        Node* cur = par;
        par = par->par;
        while (true) {
            if (par == NULL)break;
            //cur 이 par의 왼쪽 자식
            if (cur == par->left_child) {
                par->l_num--;
                par->l_height = get_height(cur) + 1;
            }
            //cur이 par의 오른쪽 자식
            else {
                par->r_num--;
                par->r_height = get_height(cur) + 1;
            }
            cur = par;
            par = par->par;
        }
        find_unbalance2(node->par);
    }

    delete node;
    return;
}

// erase 하는 node의 child가 2개
void node_erase_two_child(Node* node) {
    // 후임자 찾기
    Node* successor = node->right_child;
    while (true) {
        if (successor->left_child == NULL)break;
        successor = successor->left_child;
    }

    node->key = successor->key;

    // 후임자는 left_child가 없을 때까지 내려가기 때문에 자식이 무조건 0개 or 1개
    if (successor->left_child == NULL && successor->right_child == NULL) {
        node_erase_leaf(successor);
    }
    else  {
        node_erase_one_child(successor);
    }
    //delete successor;
}

// erase 함수  
void node_erase(int x) {
    Node* node = find_node(x, true, false);
    // 리프 노드
    if (node->left_child == NULL && node->right_child == NULL) {
        node_erase_leaf(node);
    }
    else if (node->left_child == NULL || node->right_child == NULL) {
        node_erase_one_child(node);
    }
    else {
        node_erase_two_child(node);
    }
    cnt--;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> tc;

    while (tc--) {
        cnt = 0;
        root = NULL;

        cin >> n;
        // 메인 쿼리 처리
        while (n--) {
            cin >> s;
            if (s == "minimum") {
                cin >> x;
                find_min(x);
            }
            else if (s == "maximum") {
                cin >> x;
                find_max(x);
            }
            else if (s == "empty") {
                if (cnt == 0)cout << 1;
                else cout << 0;
            }
            else if (s == "size") {
                cout << cnt;
            }
            else if (s == "find") {
                cin >> x;
                find_node(x, true, false);
            }
            else if (s == "insert") {
                cin >> x;
                insert(x);
            }
            else if (s == "rank") {
                cin >> x;
                node_rank(x);
            }
            else if (s == "erase") {
                cin >> x;
                node_erase(x);
            }
            cout << endl;
        }
    }

    return 0;
}