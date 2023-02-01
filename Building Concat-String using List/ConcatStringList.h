#ifndef __CONCAT_STRING_LIST_H__
#define __CONCAT_STRING_LIST_H__

#include "main.h"

int strlen(const char *);
char *strsub(const char *, int, int);
char *strrev(const char *);

class ConcatStringList
{
public:
    class ReferencesList;   // forward declaration
    class DeleteStringList; // forward declaration

public:
    static ReferencesList refList;
    static DeleteStringList delStrList;

    // TODO: may provide some attributes
protected:
    int Length;
    struct CharALNode
    {
        int len;
        char *CharArrayList;
        CharALNode *next;
        CharALNode(const char *s)
        {
            len = strlen(s);
            CharArrayList = new char[len + 1];
            for (int i = 0; i <= len; i++)
            {
                CharArrayList[i] = s[i];
            }
            next = nullptr;
        }
        CharALNode()
        {
        }
        ~CharALNode()
        {
            delete CharArrayList;
        }
    } * head, *tail;

public:
    ConcatStringList(const char *, int &&);
    ConcatStringList(){};
    ConcatStringList(const char *);
    int length() const;
    char get(int index) const;
    int indexOf(char c) const;
    std::string toString() const;
    ConcatStringList concat(const ConcatStringList &otherS) const;
    ConcatStringList subString(int from, int to) const;
    ConcatStringList reverse() const;
    ~ConcatStringList();

public:
    class ReferencesList
    {
        // TODO: may provide some attributes
    public:
        int Size;
        struct ReferencesListNode
        {
            int referencesNum;
            ReferencesListNode *next;
            ReferencesListNode *pre;
            CharALNode *data;
            ReferencesListNode(CharALNode *node, int referencesNum)
            {
                this->referencesNum = referencesNum;
                next = nullptr;
                pre = nullptr;
                data = node;
            }
        } * head, *tail;

    public:
        ReferencesList();
        int size() const;
        int refCountAt(int index) const;
        std::string refCountsString() const;
        bool isZero();
        void swap(ReferencesListNode *, ReferencesListNode *);
        void pushZero(ReferencesListNode *);
        void sort();
        ~ReferencesList();
    };

    class DeleteStringList
    {
        // TODO: may provide some attributes
    public:
        int Size;
        struct DeleteStringListNode
        {
            ReferencesList::ReferencesListNode *refHead;
            ReferencesList::ReferencesListNode *refTail;
            DeleteStringListNode *next;
            DeleteStringListNode()
            {
                this->refHead = nullptr;
                this->refTail = nullptr;
                next = nullptr;
            }
        } * head, *tail;

    public:
        DeleteStringList();
        int size() const;
        std::string totalRefCountsString() const;
        ~DeleteStringList();
    };
};

#endif // __CONCAT_STRING_LIST_H__