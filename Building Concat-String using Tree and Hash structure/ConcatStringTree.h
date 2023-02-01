#ifndef __CONCAT_STRING_TREE_H__
#define __CONCAT_STRING_TREE_H__

#include "main.h"

int pow(int, int);

int strlen(const char *s);

char *strsub(const char *s, int from, int to);

char *strrev(const char *s);

bool cmp(const char *a, const char *b);

class ConcatStringTree
{
protected:
    struct node;
    char rget(node *root, int index) const;
    int rindexOf(node *root, char c, int len) const;
    string rtoStringPreOrder(node *root) const;
    string rtoString(node *root) const;
    node *rsubString(node *root, int from, int to, int len = 0) const;
    node *rreverse(node *root) const;
    void rdestructor(node *root) const;

protected:
    node *root;

public:
    ConcatStringTree();
    ConcatStringTree(const char *);
    int length() const;
    char get(int index) const;
    int indexOf(char c) const;
    string toStringPreOrder() const;
    string toString() const;
    ConcatStringTree concat(const ConcatStringTree &otherS) const;
    ConcatStringTree subString(int from, int to) const;
    ConcatStringTree reverse() const;
    ~ConcatStringTree();

    int getParTreeSize(const string &query) const;
    string getParTreeStringPreOrder(const string &query) const;
};

class ReducedConcatStringTree; // forward declaration
class LitStringHash;           // forward declaration

class HashConfig
{
private:
    int p;
    double c1, c2;
    double lambda;
    double alpha;
    int initSize;

    friend class ReducedConcatStringTree;
    friend class LitStringHash;

public:
    HashConfig(int p, double c1, double c2, double lambda, double alpha, int initSize);
};

class LitStringHash
{
private:
    struct LitString;
    int hashFunc(const char *s);
    int quadratic_probing(const char *s, int i);
    void rehashing();
    void rinsert(LitString **ls, char *s, int linkNum);
    int hinsert(const char *s);

private:
    int size, capacity;
    int p;
    double c1, c2;
    double lambda;
    double alpha;
    LitString **ls;
    int lastId;

public:
    LitStringHash(const HashConfig &hashConfig);
    int getLastInsertedIndex() const;
    string toString() const;
    int insert(const char *s);
    void remove(const char *s);
    int getIdx(const char *s);
    char *get(int idx);
    ~LitStringHash();
};

class ReducedConcatStringTree /* */
{
protected:
    struct node;
    char rget(node *root, int index) const;
    int rindexOf(node *root, char c, int len) const;
    string rtoStringPreOrder(node *root) const;
    string rtoString(node *root) const;
    node *rsubString(node *root, int from, int to, int len = 0) const;
    node *rreverse(node *root) const;
    void rdestructor(node *root) const;

protected:
    node *root;

public:
    ReducedConcatStringTree(const char *s, LitStringHash *litStringHash);
    LitStringHash *litStringHash;

public:
    ReducedConcatStringTree();
    ReducedConcatStringTree(const char *s);
    int length() const;
    char get(int index) const;
    int indexOf(char c) const;
    string toStringPreOrder() const;
    string toString() const;
    ReducedConcatStringTree concat(const ReducedConcatStringTree &otherS) const;
    ReducedConcatStringTree subString(int from, int to) const;
    ReducedConcatStringTree reverse() const;

    int getParTreeSize(const string &query) const;
    string getParTreeStringPreOrder(const string &query) const;

    ~ReducedConcatStringTree();
};

#endif // __CONCAT_STRING_TREE_H__