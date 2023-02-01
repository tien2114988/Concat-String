#include "ConcatStringTree.h"

int pow(int num, int exp)
{
    int k = 1;
    while (exp)
    {
        k *= num;
        exp--;
    }
    return k;
}

int strlen(const char *s)
{
    int i = 0;
    while (s[i] != '\0')
    {
        i++;
    }
    return i;
}

char *strsub(const char *s, int from, int to)
{
    char *temp = new char[to - from + 1];
    int len = strlen(s);
    for (int i = from; i < to; i++)
    {
        temp[i - from] = s[i];
    }
    temp[to - from] = '\0';
    return temp;
}

char *strrev(const char *s)
{
    int len = strlen(s);
    char *temp = new char[len + 1];
    for (int i = 0; i < len; i++)
    {
        temp[i] = s[len - i - 1];
    }
    temp[len] = '\0';
    return temp;
}

bool cmp(const char *a, const char *b)
{
    int lena = strlen(a);
    int lenb = strlen(b);
    if (lena != lenb)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < lena; i++)
        {
            if (a[i] != b[i])
            {
                return false;
            }
        }
        return true;
    }
}

struct ConcatStringTree::node
{
    class ParentsTree
    {
    private:
        enum state
        {
            eh,
            lh,
            rh
        };
        struct parentNode
        {
            int key;
            parentNode *left;
            parentNode *right;
            state st;
            parentNode(int key, parentNode *left = nullptr, parentNode *right = nullptr, state st = eh)
            {
                this->key = key;
                this->left = left;
                this->right = right;
                this->st = st;
            }
        };
        void rotRight(parentNode *&root)
        {
            parentNode *rootLeft = root->left;
            root->left = rootLeft->right;
            rootLeft->right = root;
            root = rootLeft;
        }
        void rotLeft(parentNode *&root)
        {
            parentNode *rootRight = root->right;
            root->right = rootRight->left;
            rootRight->left = root;
            root = rootRight;
        }
        bool balanceLeft(parentNode *&root)
        {
            if (root->st == lh)
            {
                if (root->left->st == lh)
                {
                    rotRight(root);
                    root->st = eh;
                    root->right->st = eh;
                    return false;
                }
                else if (root->left->st == eh)
                {
                    rotRight(root);
                    root->st = rh;
                    root->right->st = lh;
                    return true;
                }
                else
                {
                    rotLeft(root->left);
                    rotRight(root);
                    if (root->st == lh)
                    {
                        root->left->st = eh;
                        root->right->st = rh;
                    }
                    else if (root->st = eh)
                    {
                        root->left->st = eh;
                        root->right->st = eh;
                    }
                    else
                    {
                        root->left->st = lh;
                        root->right->st = eh;
                    }
                    root->st = eh;
                    return false;
                }
            }
            else if (root->st == eh)
            {
                root->st = lh;
                return true;
            }
            else
            {
                root->st = eh;
                return false;
            }
        }
        bool balanceRight(parentNode *&root)
        {
            if (root->st == lh)
            {
                root->st = eh;
                return false;
            }
            else if (root->st == eh)
            {
                root->st = rh;
                return true;
            }
            else
            {
                if (root->right->st == lh)
                {
                    rotRight(root->right);
                    rotLeft(root);
                    if (root->st == lh)
                    {
                        root->left->st = eh;
                        root->right->st = rh;
                    }
                    else if (root->st = eh)
                    {
                        root->left->st = eh;
                        root->right->st = eh;
                    }
                    else
                    {
                        root->left->st = lh;
                        root->right->st = eh;
                    }
                    root->st = eh;
                    return false;
                }
                else if (root->right->st = eh)
                {
                    rotLeft(root);
                    root->st = lh;
                    root->left->st = rh;
                    return true;
                }
                else
                {
                    rotLeft(root);
                    root->st = eh;
                    root->left->st = eh;
                    return false;
                }
            }
        }
        bool avlinsert(parentNode *&root, int key)
        {
            if (root)
            {
                if (key < root->key)
                {
                    if (avlinsert(root->left, key))
                    {
                        return balanceLeft(root);
                    }
                }
                else
                {
                    if (avlinsert(root->right, key))
                    {
                        return balanceRight(root);
                    }
                }
                return false;
            }
            else
            {
                root = new parentNode(key);
                return true;
            }
        }
        bool avlremove(parentNode *&root, int key)
        {
            if (root)
            {
                if (key < root->key)
                {
                    if (avlremove(root->left, key))
                    {
                        return !balanceRight(root);
                    }
                    return false;
                }
                else if (key > root->key)
                {
                    if (avlremove(root->right, key))
                    {
                        return !balanceLeft(root);
                    }
                    return false;
                }
                else
                {
                    if (root->left && root->right)
                    {
                        parentNode *maxLeft = root->left;
                        while (maxLeft->right)
                        {
                            maxLeft = maxLeft->right;
                        }
                        root->key = maxLeft->key;
                        if (avlremove(root->left, root->key))
                        {
                            return !balanceRight(root);
                        }
                    }
                    else if (root->left)
                    {
                        parentNode *k = root->left;
                        delete root;
                        root = k;
                    }
                    else if (root->right)
                    {
                        parentNode *k = root->right;
                        delete root;
                        root = k;
                    }
                    else
                    {
                        delete root;
                        root = nullptr;
                    }
                    Size--;
                    return true;
                }
            }
            else
            {
                return false;
            }
        }
        string rtoStringPreOrder(parentNode *root) const
        {
            if (root)
            {
                string n = "(id=" + to_string(root->key) + ");";
                string l = rtoStringPreOrder(root->left);
                string r = rtoStringPreOrder(root->right);
                return n + l + r;
            }
            else
            {
                return "";
            }
        }

    public:
        parentNode *parentRoot;
        int Size;

    public:
        ParentsTree(int key)
        {
            parentRoot = new parentNode(key);
            Size = 1;
        };
        void insert(int key)
        {
            avlinsert(parentRoot, key);
            Size++;
        }
        void remove(int key)
        {
            avlremove(parentRoot, key);
        }
        int size() const
        {
            return Size;
        };
        string toStringPreOrder() const
        {
            string s = "ParentsTree[" + rtoStringPreOrder(parentRoot);
            s.pop_back();
            s += ']';
            return s;
        }
    };

    char *data;
    int leftLength;
    int length;
    node *left;
    node *right;
    ParentsTree *parents;
    static int id;
    int nodeId;

    node(const char *data = nullptr, bool isRoot = true, node *left = nullptr, node *right = nullptr, int leftLength = 0, int length = 0)
    {
        if (id == pow(10, 7))
        {
            throw overflow_error("Id is overflow!");
        }
        id++;
        nodeId = id;
        if (isRoot)
        {
            parents = new ParentsTree(nodeId);
        }
        this->leftLength = leftLength;
        this->left = left;
        this->right = right;
        this->length = length;
        if (data == nullptr)
        {
            this->data = nullptr;
        }
        else
        {
            this->length = strlen(data);
            this->data = new char[this->length + 1];
            for (int i = 0; i <= this->length; i++)
            {
                this->data[i] = data[i];
            }
        }
    }
    ~node()
    {
        delete data;
        delete parents;
    }
};

int ConcatStringTree::node::id = 0;

ConcatStringTree::ConcatStringTree()
{
    this->root = nullptr;
}

ConcatStringTree::ConcatStringTree(const char *s)
{
    root = new node(s);
}

int ConcatStringTree::length() const
{
    return root->length;
}

char ConcatStringTree::rget(node *root, int index) const
{
    if (root->data != nullptr)
    {
        return root->data[index];
    }
    else if (index < root->leftLength)
    {
        return rget(root->left, index);
    }
    else
    {
        return rget(root->right, index - root->leftLength);
    }
}

char ConcatStringTree::get(int index) const
{
    if (index < 0 || index > root->length - 1)
    {
        throw out_of_range("Index of string is invalid!");
    }
    else
    {
        return rget(root, index);
    }
}

int ConcatStringTree::rindexOf(node *root, char c, int len) const
{
    if (root == nullptr)
    {
        return -1;
    }
    else if (root->data != nullptr)
    {
        for (int i = 0; i < root->length; i++)
        {
            if (c == root->data[i])
            {
                return i + len;
            }
        }
        return -1;
    }
    else
    {
        int l = rindexOf(root->left, c, len);
        if (l != -1)
        {
            return l;
        }
        int r = rindexOf(root->right, c, len + root->leftLength);
        if (r != -1)
        {
            return r;
        }
        else
        {
            return -1;
        }
    }
}

int ConcatStringTree::indexOf(char c) const
{
    return rindexOf(root, c, 0);
}

string ConcatStringTree::rtoStringPreOrder(node *root) const
{
    if (root != nullptr)
    {
        string c = "(LL=" + to_string(root->leftLength) + ",L=" + to_string(root->length) + ",";
        if (root->data == nullptr)
        {
            c += "<NULL>";
        }
        else
        {
            string k = root->data;
            c += "\"" + k + "\"";
        }
        c += ");";
        return c + rtoStringPreOrder(root->left) + rtoStringPreOrder(root->right);
    }
    else
    {
        return "";
    }
}

string ConcatStringTree::toStringPreOrder() const
{
    string s = rtoStringPreOrder(root);
    s.pop_back();
    return "ConcatStringTree[" + s + "]";
}

string ConcatStringTree::rtoString(node *root) const
{
    if (root == nullptr)
    {
        return "";
    }
    else if (root->data == nullptr)
    {
        return rtoString(root->left) + rtoString(root->right);
    }
    else
    {
        return root->data;
    }
}

string ConcatStringTree::toString() const
{
    return "ConcatStringTree[\"" + rtoString(root) + "\"]";
}

ConcatStringTree ConcatStringTree::concat(const ConcatStringTree &otherS) const
{
    ConcatStringTree *destination = new ConcatStringTree(nullptr);
    destination->root->left = this->root;
    destination->root->right = otherS.root;
    destination->root->leftLength = this->root->length;
    destination->root->length = this->root->length + otherS.root->length;
    this->root->parents->insert(node::id);
    otherS.root->parents->insert(node::id);
    return *destination;
}

ConcatStringTree::node *ConcatStringTree::rsubString(node *root, int from, int to, int len) const
{
    if (root->data == nullptr)
    {
        node *l = nullptr, *r = nullptr;
        int leftLength = 0, length = 0, parId = 0;
        if (from < root->leftLength + len)
        {
            l = rsubString(root->left, from, to, len);
            leftLength += l->length;
            length += l->length;
        }
        if (to > root->leftLength + len)
        {
            r = rsubString(root->right, from, to, root->leftLength + len);
            length += r->length;
            r->parents = new node::ParentsTree(r->nodeId + 1);
        }
        if (l != nullptr)
        {
            if (r != nullptr)
            {
                l->parents = new node::ParentsTree(r->nodeId + 1);
            }
            else
            {
                l->parents = new node::ParentsTree(l->nodeId + 1);
            }
        }
        return new node(nullptr, false, l, r, leftLength, length);
    }
    else
    {
        from -= len;
        to -= len;
        if (from < 0)
        {
            from = 0;
        }
        if (to > root->length)
        {
            to = root->length;
        }
        return new node(strsub(root->data, from, to), false);
    }
}

ConcatStringTree ConcatStringTree::subString(int from, int to) const
{
    if (from < 0 || from > root->length - 1 || to < 0 || to > root->length)
    {
        throw out_of_range("Index of string is invalid!");
    }
    else if (from >= to)
    {
        throw logic_error("Invalid range!");
    }
    else
    {
        ConcatStringTree *newTree = new ConcatStringTree();
        newTree->root = rsubString(root, from, to);
        newTree->root->parents = new node::ParentsTree(newTree->root->nodeId);
        return *newTree;
    }
}

ConcatStringTree::node *ConcatStringTree::rreverse(node *root) const
{
    if (root == nullptr)
    {
        return nullptr;
    }
    else if (root->data == nullptr)
    {
        int l = 0, ll = 0;
        node *left = rreverse(root->right);
        node *right = rreverse(root->left);
        if (left != nullptr)
        {
            if (right != nullptr)
            {
                left->parents = new node::ParentsTree(right->nodeId + 1);
            }
            else
            {
                left->parents = new node::ParentsTree(left->nodeId + 1);
            }
            l += left->length;
            ll += left->length;
        }
        if (right != nullptr)
        {
            l += right->length;
            right->parents = new node::ParentsTree(right->nodeId + 1);
        }
        return new node(nullptr, false, left, right, ll, l);
    }
    else
    {
        node *newNode = new node(strrev(root->data), false);
        return newNode;
    }
}

ConcatStringTree ConcatStringTree::reverse() const
{
    ConcatStringTree *newTree = new ConcatStringTree();
    newTree->root = rreverse(root);
    newTree->root->parents = new node::ParentsTree(newTree->root->nodeId);
    return *newTree;
}

void ConcatStringTree::rdestructor(node *root) const
{
    if (root && !root->parents->parentRoot)
    {
        if (root->left)
            root->left->parents->remove(root->nodeId);
        if (root->right)
            root->right->parents->remove(root->nodeId);
        rdestructor(root->left);
        rdestructor(root->right);
        delete root;
    }
}

ConcatStringTree::~ConcatStringTree()
{
    root->parents->remove(root->nodeId);
    rdestructor(root);
}

int ConcatStringTree::getParTreeSize(const string &query) const
{
    node *k = root;
    for (int i = 0; i < query.length(); i++)
    {
        if (query[i] == 'l')
        {
            if (!k)
            {
                throw runtime_error("Invalid query: reaching NULL");
            }
            k = k->left;
        }
        else if (query[i] == 'r')
        {
            if (!k)
            {
                throw runtime_error("Invalid query: reaching NULL");
            }
            k = k->right;
        }
        else
        {
            throw runtime_error("Invalid character of query");
        }
    }
    if (!k)
    {
        throw runtime_error("Invalid query: reaching NULL");
    }
    return k->parents->size();
}

string ConcatStringTree::getParTreeStringPreOrder(const string &query) const
{
    node *k = root;
    for (int i = 0; i < query.length(); i++)
    {
        if (query[i] == 'l')
        {
            if (!k)
            {
                throw runtime_error("Invalid query: reaching NULL");
            }
            k = k->left;
        }
        else if (query[i] == 'r')
        {
            if (!k)
            {
                throw runtime_error("Invalid query: reaching NULL");
            }
            k = k->right;
        }
        else
        {
            throw runtime_error("Invalid character of query");
        }
    }
    if (!k)
    {
        throw runtime_error("Invalid query: reaching NULL");
    }
    if (!k)
    {
        throw runtime_error("Invalid query: reaching NULL");
    }
    return k->parents->toStringPreOrder();
}

HashConfig::HashConfig(int p, double c1, double c2, double lambda, double alpha, int initSize)
{
    this->p = p;
    this->c1 = c1;
    this->c2 = c2;
    this->lambda = lambda;
    this->alpha = alpha;
    this->initSize = initSize;
}

struct LitStringHash::LitString
{
    int linkNum;
    char *s;
    LitString(const char *s)
    {
        this->linkNum = 1;
        int len = strlen(s);
        this->s = new char[len + 1];
        for (int i = 0; i <= len; i++)
        {
            this->s[i] = s[i];
        }
    }
    LitString(char *s, int linkNum)
    {
        this->s = s;
        this->linkNum = linkNum;
    }
    ~LitString()
    {
        delete s;
    }
};

int LitStringHash::hashFunc(const char *s)
{
    int h = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        h += s[i] * pow(p, i);
    }
    return h % capacity;
}

int LitStringHash::quadratic_probing(const char *s, int i)
{
    return int(hashFunc(s) + c1 * i + c2 * i * i) % capacity;
}

void LitStringHash::rehashing()
{
    int oldcap = capacity;
    capacity = alpha * capacity;
    LitString **newLs = new LitString *[capacity];
    for (int i = 0; i < capacity; i++)
    {
        newLs[i] = nullptr;
    }
    for (int i = 0; i < oldcap; i++)
    {
        if (ls[i])
        {
            rinsert(newLs, ls[i]->s, ls[i]->linkNum);
            ls[i] = nullptr;
        }
    }
    delete ls;
    ls = newLs;
}

void LitStringHash::rinsert(LitString **ls, char *s, int linkNum)
{
    int index = 0;
    for (int i = 0; i < capacity; i++)
    {
        index = quadratic_probing(s, i);
        if (!ls[index])
        {
            ls[index] = new LitString(s, linkNum);
            return;
        }
    }
    throw runtime_error("No possible slot");
}

int LitStringHash::hinsert(const char *s)
{
    int index = 0;
    for (int i = 0; i < capacity; i++)
    {
        index = quadratic_probing(s, i);
        if (!ls[index])
        {
            ls[index] = new LitString(s);
            return index;
        }
    }
    throw runtime_error("No possible slot");
}

LitStringHash::LitStringHash(const HashConfig &hashConfig)
{
    lastId = -1;
    size = 0;
    capacity = hashConfig.initSize;
    p = hashConfig.p;
    c1 = hashConfig.c1;
    c2 = hashConfig.c2;
    lambda = hashConfig.lambda;
    alpha = hashConfig.alpha;
    ls = new LitString *[capacity];
    for (int i = 0; i < capacity; i++)
    {
        ls[i] = nullptr;
    }
}

int LitStringHash::getLastInsertedIndex() const
{
    return lastId;
}

string LitStringHash::toString() const
{
    string s = "LitStringHash[";
    for (int i = 0; i < capacity; i++)
    {
        if (ls && ls[i])
        {
            string k = ls[i]->s;
            s += "(litS=\"" + k + "\");";
        }
        else
        {
            s += "();";
        }
    }
    if (capacity > 0)
    {
        s.pop_back();
    }
    s += ']';
    return s;
}

int LitStringHash::insert(const char *s)
{
    if (!ls)
    {
        ls = new LitString *[capacity];
        for (int i = 0; i < capacity; i++)
        {
            ls[i] = nullptr;
        }
    }
    int idx = getIdx(s);
    if (idx == -1)
    {
        idx = hinsert(s);
        lastId = idx;
        size++;
        double load_factor = size * 1.0 / capacity;
        if (load_factor > lambda)
        {
            rehashing();
            idx = getIdx(s);
            lastId = idx;
        }
    }
    else
    {
        ls[idx]->linkNum++;
    }
    return idx;
}

void LitStringHash::remove(const char *s)
{
    int idx = getIdx(s);
    ls[idx]->linkNum--;
    if (ls[idx]->linkNum == 0)
    {
        delete ls[idx];
        ls[idx] = nullptr;
        size--;
    }
    if (size == 0)
    {
        delete ls;
        ls = nullptr;
        lastId = -1;
    }
}

int LitStringHash::getIdx(const char *s)
{
    int index = 0;
    for (int i = 0; i < capacity; i++)
    {
        index = quadratic_probing(s, i);
        if (ls[index] && cmp(ls[index]->s, s))
        {
            return index;
        }
    }
    return -1;
}

char *LitStringHash::get(int idx)
{
    return ls[idx]->s;
}

LitStringHash ::~LitStringHash()
{
    delete ls;
}

struct ReducedConcatStringTree::node
{
    class ParentsTree
    {
    private:
        enum state
        {
            eh,
            lh,
            rh
        };
        struct parentNode
        {
            int key;
            parentNode *left;
            parentNode *right;
            state st;
            parentNode(int key, parentNode *left = nullptr, parentNode *right = nullptr, state st = eh)
            {
                this->key = key;
                this->left = left;
                this->right = right;
                this->st = st;
            }
        };
        void rotRight(parentNode *&root)
        {
            parentNode *rootLeft = root->left;
            root->left = rootLeft->right;
            rootLeft->right = root;
            root = rootLeft;
        }
        void rotLeft(parentNode *&root)
        {
            parentNode *rootRight = root->right;
            root->right = rootRight->left;
            rootRight->left = root;
            root = rootRight;
        }
        bool balanceLeft(parentNode *&root)
        {
            if (root->st == lh)
            {
                if (root->left->st == lh)
                {
                    rotRight(root);
                    root->st = eh;
                    root->right->st = eh;
                    return false;
                }
                else if (root->left->st == eh)
                {
                    rotRight(root);
                    root->st = rh;
                    root->right->st = lh;
                    return true;
                }
                else
                {
                    rotLeft(root->left);
                    rotRight(root);
                    if (root->st == lh)
                    {
                        root->left->st = eh;
                        root->right->st = rh;
                    }
                    else if (root->st = eh)
                    {
                        root->left->st = eh;
                        root->right->st = eh;
                    }
                    else
                    {
                        root->left->st = lh;
                        root->right->st = eh;
                    }
                    root->st = eh;
                    return false;
                }
            }
            else if (root->st == eh)
            {
                root->st = lh;
                return true;
            }
            else
            {
                root->st = eh;
                return false;
            }
        }
        bool balanceRight(parentNode *&root)
        {
            if (root->st == lh)
            {
                root->st = eh;
                return false;
            }
            else if (root->st == eh)
            {
                root->st = rh;
                return true;
            }
            else
            {
                if (root->right->st == lh)
                {
                    rotRight(root->right);
                    rotLeft(root);
                    if (root->st == lh)
                    {
                        root->left->st = eh;
                        root->right->st = rh;
                    }
                    else if (root->st = eh)
                    {
                        root->left->st = eh;
                        root->right->st = eh;
                    }
                    else
                    {
                        root->left->st = lh;
                        root->right->st = eh;
                    }
                    root->st = eh;
                    return false;
                }
                else if (root->right->st = eh)
                {
                    rotLeft(root);
                    root->st = lh;
                    root->left->st = rh;
                    return true;
                }
                else
                {
                    rotLeft(root);
                    root->st = eh;
                    root->left->st = eh;
                    return false;
                }
            }
        }
        bool avlinsert(parentNode *&root, int key)
        {
            if (root)
            {
                if (key < root->key)
                {
                    if (avlinsert(root->left, key))
                    {
                        return balanceLeft(root);
                    }
                }
                else
                {
                    if (avlinsert(root->right, key))
                    {
                        return balanceRight(root);
                    }
                }
                return false;
            }
            else
            {
                root = new parentNode(key);
                return true;
            }
        }
        bool avlremove(parentNode *&root, int key)
        {
            if (root)
            {
                if (key < root->key)
                {
                    if (avlremove(root->left, key))
                    {
                        return !balanceRight(root);
                    }
                    return false;
                }
                else if (key > root->key)
                {
                    if (avlremove(root->right, key))
                    {
                        return !balanceLeft(root);
                    }
                    return false;
                }
                else
                {
                    if (root->left && root->right)
                    {
                        parentNode *maxLeft = root->left;
                        while (maxLeft->right)
                        {
                            maxLeft = maxLeft->right;
                        }
                        root->key = maxLeft->key;
                        if (avlremove(root->left, root->key))
                        {
                            return !balanceRight(root);
                        }
                    }
                    else if (root->left)
                    {
                        parentNode *k = root->left;
                        delete root;
                        root = k;
                    }
                    else if (root->right)
                    {
                        parentNode *k = root->right;
                        delete root;
                        root = k;
                    }
                    else
                    {
                        delete root;
                        root = nullptr;
                    }
                    Size--;
                    return true;
                }
            }
            else
            {
                return false;
            }
        }
        string rtoStringPreOrder(parentNode *root) const
        {
            if (root)
            {
                string n = "(id=" + to_string(root->key) + ");";
                string l = rtoStringPreOrder(root->left);
                string r = rtoStringPreOrder(root->right);
                return n + l + r;
            }
            else
            {
                return "";
            }
        }

    public:
        parentNode *parentRoot;
        int Size;

    public:
        ParentsTree(int key)
        {
            parentRoot = new parentNode(key);
            Size = 1;
        };
        void insert(int key)
        {
            avlinsert(parentRoot, key);
            Size++;
        }
        void remove(int key)
        {
            avlremove(parentRoot, key);
        }
        int size() const
        {
            return Size;
        };
        string toStringPreOrder() const
        {
            string s = "ParentsTree[" + rtoStringPreOrder(parentRoot);
            s.pop_back();
            s += ']';
            return s;
        }
    };

    char *data;
    int leftLength;
    int length;
    node *left;
    node *right;
    ParentsTree *parents;
    static int id;
    int nodeId;

    node(bool, char *data = nullptr)
    {
        if (id == pow(10, 7))
        {
            throw overflow_error("Id is overflow!");
        }
        id++;
        nodeId = id;
        parents = new ParentsTree(id);
        this->leftLength = 0;
        this->left = nullptr;
        this->right = nullptr;
        this->data = data;
        if (data != nullptr)
        {
            this->length = strlen(data);
        }
        else
        {
            this->length = length;
        }
    }
    node(const char *data = nullptr, bool isRoot = true, node *left = nullptr, node *right = nullptr, int leftLength = 0, int length = 0)
    {
        if (id == pow(10, 7))
        {
            throw overflow_error("Id is overflow!");
        }
        id++;
        nodeId = id;
        if (isRoot)
        {
            parents = new ParentsTree(id);
        }
        this->leftLength = leftLength;
        this->left = left;
        this->right = right;
        this->length = length;
        if (data == nullptr)
        {
            this->data = nullptr;
        }
        else
        {
            this->length = strlen(data);
            this->data = new char[this->length + 1];
            for (int i = 0; i <= this->length; i++)
            {
                this->data[i] = data[i];
            }
        }
    }
    ~node()
    {
        data = nullptr;
        delete parents;
    }
};

int ReducedConcatStringTree::node::id = 0;

ReducedConcatStringTree::ReducedConcatStringTree()
{
    this->root = nullptr;
}

ReducedConcatStringTree::ReducedConcatStringTree(const char *s, LitStringHash *litStringHash)
{
    this->litStringHash = litStringHash;
    if (s == nullptr)
    {
        root = new node(true);
    }
    else
    {
        int idx = litStringHash->insert(s);
        root = new node(true, litStringHash->get(idx));
    }
}

ReducedConcatStringTree::ReducedConcatStringTree(const char *s)
{
    root = new node(s);
}

int ReducedConcatStringTree::length() const
{
    return root->length;
}

char ReducedConcatStringTree::rget(node *root, int index) const
{
    if (root->data != nullptr)
    {
        return root->data[index];
    }
    else if (index < root->leftLength)
    {
        return rget(root->left, index);
    }
    else
    {
        return rget(root->right, index - root->leftLength);
    }
}

char ReducedConcatStringTree::get(int index) const
{
    if (index < 0 || index > root->length - 1)
    {
        throw out_of_range("Index of string is invalid!");
    }
    else
    {
        return rget(root, index);
    }
}

int ReducedConcatStringTree::rindexOf(node *root, char c, int len) const
{
    if (root == nullptr)
    {
        return -1;
    }
    else if (root->data != nullptr)
    {
        for (int i = 0; i < root->length; i++)
        {
            if (c == root->data[i])
            {
                return i + len;
            }
        }
        return -1;
    }
    else
    {
        int l = rindexOf(root->left, c, len);
        if (l != -1)
        {
            return l;
        }
        int r = rindexOf(root->right, c, len + root->leftLength);
        if (r != -1)
        {
            return r;
        }
        else
        {
            return -1;
        }
    }
}

int ReducedConcatStringTree::indexOf(char c) const
{
    return rindexOf(root, c, 0);
}

string ReducedConcatStringTree::rtoStringPreOrder(node *root) const
{
    if (root != nullptr)
    {
        string l = rtoStringPreOrder(root->left);
        string r = rtoStringPreOrder(root->right);
        string c = "(LL=" + to_string(root->leftLength) + ",L=" + to_string(root->length) + ",";
        if (root->data == nullptr)
        {
            c += "<NULL>";
        }
        else
        {
            string k = root->data;
            c += "\"" + k + "\"";
        }
        c += ");";
        return c + l + r;
    }
    else
    {
        return "";
    }
}

string ReducedConcatStringTree::toStringPreOrder() const
{
    string s = rtoStringPreOrder(root);
    s.pop_back();
    return "ConcatStringTree[" + s + "]";
}

string ReducedConcatStringTree::rtoString(node *root) const
{
    if (root == nullptr)
    {
        return "";
    }
    else if (root->data == nullptr)
    {
        string l = rtoString(root->left);
        string r = rtoString(root->right);
        return l + r;
    }
    else
    {
        return root->data;
    }
}

string ReducedConcatStringTree::toString() const
{
    return "ConcatStringTree[\"" + rtoString(root) + "\"]";
}

ReducedConcatStringTree ReducedConcatStringTree::concat(const ReducedConcatStringTree &otherS) const
{
    ReducedConcatStringTree *destination = new ReducedConcatStringTree(nullptr, litStringHash);
    destination->root->left = this->root;
    destination->root->right = otherS.root;
    destination->root->leftLength = this->root->length;
    destination->root->length = this->root->length + otherS.root->length;
    this->root->parents->insert(node::id);
    otherS.root->parents->insert(node::id);
    return *destination;
}

ReducedConcatStringTree::node *ReducedConcatStringTree::rsubString(node *root, int from, int to, int len) const
{
    if (root->data == nullptr)
    {
        node *l = nullptr, *r = nullptr;
        int leftLength = 0, length = 0, parId = 0;
        if (from < root->leftLength + len)
        {
            l = rsubString(root->left, from, to, len);
            leftLength += l->length;
            length += l->length;
        }
        if (to > root->leftLength + len)
        {
            r = rsubString(root->right, from, to, root->leftLength + len);
            length += r->length;
            r->parents = new node::ParentsTree(r->nodeId + 1);
        }
        if (l != nullptr)
        {
            if (r != nullptr)
            {
                l->parents = new node::ParentsTree(r->nodeId + 1);
            }
            else
            {
                l->parents = new node::ParentsTree(l->nodeId + 1);
            }
        }
        return new node(nullptr, false, l, r, leftLength, length);
    }
    else
    {
        from -= len;
        to -= len;
        if (from < 0)
        {
            from = 0;
        }
        if (to > root->length)
        {
            to = root->length;
        }
        return new node(strsub(root->data, from, to), false);
    }
}

ReducedConcatStringTree ReducedConcatStringTree::subString(int from, int to) const
{
    if (from < 0 || from > root->length - 1 || to < 0 || to > root->length)
    {
        throw out_of_range("Index of string is invalid!");
    }
    else if (from >= to)
    {
        throw logic_error("Invalid range!");
    }
    else
    {
        ReducedConcatStringTree *newTree = new ReducedConcatStringTree();
        newTree->root = rsubString(root, from, to);
        newTree->root->parents = new node::ParentsTree(newTree->root->nodeId);
        return *newTree;
    }
}

ReducedConcatStringTree::node *ReducedConcatStringTree::rreverse(node *root) const
{
    if (root == nullptr)
    {
        return nullptr;
    }
    else if (root->data == nullptr)
    {
        int l = 0, ll = 0;
        node *left = rreverse(root->right);
        node *right = rreverse(root->left);
        if (left != nullptr)
        {
            if (right != nullptr)
            {
                left->parents = new node::ParentsTree(right->nodeId + 1);
            }
            else
            {
                left->parents = new node::ParentsTree(left->nodeId + 1);
            }
            l += left->length;
            ll += left->length;
        }
        if (right != nullptr)
        {
            l += right->length;
            right->parents = new node::ParentsTree(right->nodeId + 1);
        }
        return new node(nullptr, false, left, right, ll, l);
    }
    else
    {
        node *newNode = new node(strrev(root->data), false);
        return newNode;
    }
}

ReducedConcatStringTree ReducedConcatStringTree::reverse() const
{
    ReducedConcatStringTree *newTree = new ReducedConcatStringTree();
    newTree->root = rreverse(root);
    newTree->root->parents = new node::ParentsTree(newTree->root->nodeId);
    return *newTree;
}

void ReducedConcatStringTree::rdestructor(node *root) const
{
    if (root && !root->parents->parentRoot)
    {
        if (root->left)
            root->left->parents->remove(root->nodeId);
        if (root->right)
            root->right->parents->remove(root->nodeId);
        rdestructor(root->left);
        rdestructor(root->right);
        if (root->data)
        {
            litStringHash->remove(root->data);
        }
        delete root;
    }
}

ReducedConcatStringTree::~ReducedConcatStringTree()
{
    root->parents->remove(root->nodeId);
    rdestructor(root);
}

int ReducedConcatStringTree::getParTreeSize(const string &query) const
{
    node *k = root;
    for (int i = 0; i < query.length(); i++)
    {
        if (query[i] == 'l')
        {
            if (!k)
            {
                throw runtime_error("Invalid query: reaching NULL");
            }
            k = k->left;
        }
        else if (query[i] == 'r')
        {
            if (!k)
            {
                throw runtime_error("Invalid query: reaching NULL");
            }
            k = k->right;
        }
        else
        {
            throw runtime_error("Invalid character of query");
        }
    }
    if (!k)
    {
        throw runtime_error("Invalid query: reaching NULL");
    }
    return k->parents->size();
}

string ReducedConcatStringTree::getParTreeStringPreOrder(const string &query) const
{
    node *k = root;
    for (int i = 0; i < query.length(); i++)
    {
        if (query[i] == 'l')
        {
            if (!k)
            {
                throw runtime_error("Invalid query: reaching NULL");
            }
            k = k->left;
        }
        else if (query[i] == 'r')
        {
            if (!k)
            {
                throw runtime_error("Invalid query: reaching NULL");
            }
            k = k->right;
        }
        else
        {
            throw runtime_error("Invalid character of query");
        }
    }
    if (!k)
    {
        throw runtime_error("Invalid query: reaching NULL");
    }
    return k->parents->toStringPreOrder();
}
