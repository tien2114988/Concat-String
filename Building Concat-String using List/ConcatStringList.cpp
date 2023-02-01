#include "ConcatStringList.h"

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

ConcatStringList::ReferencesList ConcatStringList::refList = ConcatStringList::ReferencesList();
ConcatStringList::DeleteStringList ConcatStringList::delStrList = ConcatStringList::DeleteStringList();

ConcatStringList::ConcatStringList(const char *s)
{
    head = new CharALNode(s);
    tail = head;
    Length = head->len;
    if (!refList.head)
    {
        refList.head = new ReferencesList::ReferencesListNode(head, 2);
        refList.tail = refList.head;
    }
    else
    {
        refList.tail->next = new ReferencesList::ReferencesListNode(head, 2);
        refList.tail->next->pre = refList.tail;
        refList.tail = refList.tail->next;
    }
    refList.Size++;
    refList.sort();
}

ConcatStringList::ConcatStringList(const char *s, int &&num)
{
    head = new CharALNode(s);
    tail = head;
    Length = head->len;
    if (!refList.head)
    {
        refList.head = new ReferencesList::ReferencesListNode(head, 1);
        refList.tail = refList.head;
    }
    else
    {
        refList.tail->next = new ReferencesList::ReferencesListNode(head, 1);
        refList.tail->next->pre = refList.tail;
        refList.tail = refList.tail->next;
    }
    refList.Size++;
}

int ConcatStringList::length() const
{
    return Length;
}

char ConcatStringList::get(int index) const
{
    if (index < 0 || index >= Length)
    {
        throw out_of_range("Index of string is invalid!");
    }
    else
    {
        int preLength = 0;
        int length = 0;
        for (CharALNode *i = head; i != tail->next; i = i->next)
        {
            length += i->len;
            if (index < length)
            {
                return i->CharArrayList[index - preLength];
            }
            preLength = length;
        }
    }
}

int ConcatStringList::indexOf(char c) const
{
    int temp = 0;
    for (CharALNode *i = head; i != tail->next; i = i->next)
    {
        for (int j = temp; j < temp + i->len; j++)
        {
            if (c == i->CharArrayList[j - temp])
            {
                return j;
            }
        }
        temp += i->len;
    }
    return -1;
};

string ConcatStringList::toString() const
{
    string perform = "";
    for (CharALNode *i = head; i != tail->next; i = i->next)
    {
        for (int j = 0; j < i->len; j++)
        {
            perform += i->CharArrayList[j];
        }
    }
    return perform;
}

ConcatStringList ConcatStringList::concat(const ConcatStringList &otherS) const
{
    ConcatStringList *destination = new ConcatStringList;
    destination->Length = this->Length + otherS.Length;
    destination->head = head;
    for (ReferencesList::ReferencesListNode *i = refList.head; i != nullptr; i = i->next)
    {
        if (i->data == head)
        {
            i->referencesNum += 1;
        }
    }
    tail->next = otherS.head;
    destination->tail = otherS.tail;
    for (ReferencesList::ReferencesListNode *i = refList.head; i != nullptr; i = i->next)
    {
        if (i->data == otherS.tail)
        {
            i->referencesNum += 1;
            break;
        }
    }
    refList.sort();
    return *destination;
}

ConcatStringList ConcatStringList::subString(int from, int to) const
{
    int temp = 0;
    int len = Length;
    if (from < 0 || from >= len || to < 0 || to > len)
    {
        throw out_of_range("Index of string is invalid!");
    }
    else if (from >= to)
    {
        throw logic_error("Invalid range");
    }
    else
    {
        for (CharALNode *i = head; i != tail->next; i = i->next)
        {
            int sublen = i->len;
            temp += sublen;
            if (from < temp)
            {
                if (to <= temp)
                {
                    char *s = strsub(i->CharArrayList, from - temp + sublen, to - temp + sublen);
                    ConcatStringList *destination = new ConcatStringList(s);
                    refList.sort();
                    return *destination;
                }
                char *s = strsub(i->CharArrayList, from - temp + sublen, sublen);
                ConcatStringList *destination = new ConcatStringList(s, 1);
                destination->Length = to - from;
                for (CharALNode *j = i->next; j != tail->next; j = j->next)
                {
                    sublen = j->len;
                    temp += sublen;
                    if (to <= temp)
                    {
                        CharALNode *rest = new CharALNode(strsub(j->CharArrayList, 0, to - temp + sublen));
                        destination->tail->next = rest;
                        destination->tail = rest;
                        refList.tail->next = new ReferencesList::ReferencesListNode(destination->tail, 1);
                        refList.tail->next->pre = refList.tail;
                        refList.tail = refList.tail->next;
                        refList.Size++;
                        refList.sort();
                        return *destination;
                    }
                    CharALNode *Nodetemp = new CharALNode(j->CharArrayList);
                    destination->tail->next = Nodetemp;
                    destination->tail = Nodetemp;
                }
            }
        }
    }
}

ConcatStringList ConcatStringList::reverse() const
{
    ConcatStringList *destination = new ConcatStringList(strrev(tail->CharArrayList), 1);
    destination->Length = this->Length;
    if (head == tail)
    {
        refList.tail->referencesNum += 1;
        refList.sort();
        return *destination;
    }
    destination->tail = new CharALNode(strrev(head->CharArrayList));
    CharALNode *temp = destination->tail;
    CharALNode *pnew;
    for (CharALNode *i = head->next; i != tail; i = i->next)
    {
        pnew = new CharALNode(strrev(i->CharArrayList));
        pnew->next = temp;
        temp = pnew;
    }
    destination->head->next = temp;
    refList.tail->next = new ReferencesList::ReferencesListNode(destination->tail, 1);
    refList.tail->next->pre = refList.tail;
    refList.tail = refList.tail->next;
    refList.Size++;
    refList.sort();
    return *destination;
}

ConcatStringList ::~ConcatStringList()
{
    bool traverse = false;
    for (ReferencesList::ReferencesListNode *i = refList.head; i != nullptr; i = i->next)
    {
        if (i->data == head && head == tail)
        {
            i->referencesNum -= 2;
            if (delStrList.head == nullptr)
            {
                delStrList.head = new DeleteStringList::DeleteStringListNode();
                delStrList.tail = delStrList.head;
                delStrList.head->refHead = i;
                delStrList.head->refTail = i;
            }
            else
            {
                delStrList.tail->next = new DeleteStringList::DeleteStringListNode();
                delStrList.tail->next->refHead = i;
                delStrList.tail->next->refTail = i;
                delStrList.tail = delStrList.tail->next;
            }
            break;
        }
        if (i->data == head)
        {
            if (!traverse)
            {
                i->referencesNum -= 1;
                if (delStrList.head == nullptr)
                {
                    delStrList.head = new DeleteStringList::DeleteStringListNode();
                    delStrList.tail = delStrList.head;
                    delStrList.head->refHead = i;
                }
                else
                {
                    delStrList.tail->next = new DeleteStringList::DeleteStringListNode();
                    delStrList.tail->next->refHead = i;
                    delStrList.tail = delStrList.tail->next;
                }
                traverse = true;
            }
            else
            {
                i->referencesNum -= 1;
                delStrList.tail->refHead = i;
                break;
            }
        }
        if (i->data == tail)
        {
            if (!traverse)
            {
                i->referencesNum -= 1;
                if (delStrList.head == nullptr)
                {
                    delStrList.head = new DeleteStringList::DeleteStringListNode();
                    delStrList.tail = delStrList.head;
                    delStrList.head->refTail = i;
                }
                else
                {
                    delStrList.tail->next = new DeleteStringList::DeleteStringListNode();
                    delStrList.tail->next->refTail = i;
                    delStrList.tail = delStrList.tail->next;
                }
                traverse = true;
            }
            else
            {
                i->referencesNum -= 1;
                delStrList.tail->refTail = i;
                break;
            }
        }
    }
    delStrList.Size++;
    head = nullptr;
    tail = nullptr;
    DeleteStringList::DeleteStringListNode *preDel = nullptr;
    bool increase = false;
    for (DeleteStringList::DeleteStringListNode *i = delStrList.head; i != nullptr;)
    {
        increase = false;
        if (i->refHead->referencesNum == 0 && i->refTail->referencesNum == 0)
        {
            if (i->refHead->data != nullptr && i->refTail->data != nullptr)
            {
                CharALNode *cur = i->refHead->data;
                CharALNode *pre = nullptr;
                CharALNode *tailNext = i->refTail->data->next;
                while (cur != tailNext)
                {
                    pre = cur->next;
                    delete cur;
                    cur = pre;
                }
                i->refHead->data = nullptr;
                i->refTail->data = nullptr;
            }

            if (i == delStrList.head)
            {
                if (i == delStrList.tail)
                {
                    delStrList.tail = nullptr;
                }
                i = delStrList.head->next;
                delete delStrList.head;
                delStrList.head = i;
            }
            else
            {
                if (i == delStrList.tail)
                {
                    delStrList.tail = preDel;
                }
                preDel->next = i->next;
                delete i;
                i = preDel->next;
            }
            increase = true;
            delStrList.Size--;
        }
        if (!increase)
        {
            preDel = i;
            i = i->next;
        }
    }

    if (refList.isZero())
    {
        ReferencesList::ReferencesListNode *i = nullptr;
        while (refList.head != nullptr)
        {
            i = refList.head;
            refList.head = refList.head->next;
            delete i;
        }
        refList.Size = 0;
    }
    else
    {
        refList.sort();
    }
}

ConcatStringList::ReferencesList::ReferencesList()
{
    Size = 0;
    head = nullptr;
    tail = nullptr;
}

int ConcatStringList::ReferencesList::size() const
{
    return Size;
}

int ConcatStringList::ReferencesList::refCountAt(int index) const
{
    if (index < 0 || index >= Size)
    {
        throw out_of_range("Index of references list is invalid!");
    }
    else
    {
        int j = 0;
        for (ReferencesListNode *i = head; i != nullptr; i = i->next)
        {
            if (j == index)
            {
                return i->referencesNum;
            }
            j++;
        }
    }
}

std::string ConcatStringList::ReferencesList::refCountsString() const
{
    if (head == nullptr)
    {
        return "RefCounts[]";
    }
    string text = "RefCounts[";
    for (ReferencesListNode *i = head; i != nullptr; i = i->next)
    {
        text += to_string(i->referencesNum) + ',';
    }
    text.pop_back();
    text += ']';
    return text;
}

bool ConcatStringList::ReferencesList::isZero()
{
    for (ReferencesListNode *i = head; i != nullptr; i = i->next)
    {
        if (i->referencesNum)
        {
            return 0;
        }
    }
    return 1;
}

ConcatStringList::ReferencesList::~ReferencesList()
{
    head = nullptr;
    tail = nullptr;
}

void ConcatStringList::ReferencesList::swap(ReferencesListNode *a, ReferencesListNode *b)
{
    ReferencesListNode *aPre = a->pre;
    ReferencesListNode *bNext = b->next;
    ReferencesListNode *aNext = a->next;
    ReferencesListNode *bPre = b->pre;
    if (a != refList.head)
    {
        aPre->next = b;
    }
    else
    {
        refList.head = b;
    }
    if (b != refList.tail)
    {
        bNext->pre = a;
    }
    else
    {
        refList.tail = a;
    }

    if (a->next != b)
    {
        aNext->pre = b;
        bPre->next = a;
        a->pre = bPre;
        b->next = aNext;
    }
    else
    {
        a->pre = b;
        b->next = a;
    }
    a->next = bNext;
    b->pre = aPre;
}

void ConcatStringList::ReferencesList::pushZero(ReferencesListNode *zeroNode)
{
    if (head != tail)
    {
        head = zeroNode->next;
        zeroNode->next->pre = nullptr;
        zeroNode->next = nullptr;
        tail->next = zeroNode;
        zeroNode->pre = tail;
        tail = zeroNode;
    }
}

void ConcatStringList::ReferencesList::sort()
{
    for (ReferencesListNode *i = head; i != nullptr; i = i->next)
    {
        for (ReferencesListNode *j = i->next; j != nullptr; j = j->next)
        {
            if (i->referencesNum > j->referencesNum)
            {
                swap(i, j);
                ReferencesListNode *temp = i;
                i = j;
                j = temp;
            }
        }
    }
    ReferencesListNode *i = head;
    while (i != nullptr && i->referencesNum == 0)
    {
        pushZero(i);
        i = head;
    }
}

ConcatStringList::DeleteStringList::DeleteStringList()
{
    head = nullptr;
    tail = nullptr;
    Size = 0;
}

int ConcatStringList::DeleteStringList::size() const
{
    return Size;
}

std::string ConcatStringList::DeleteStringList::totalRefCountsString() const
{
    if (head == nullptr)
    {
        return "TotalRefCounts[]";
    }
    string text = "TotalRefCounts[";
    for (DeleteStringListNode *i = head; i != nullptr; i = i->next)
    {
        if (i->refHead == i->refTail)
        {
            text += to_string(i->refHead->referencesNum);
        }
        else
        {
            text += to_string(i->refHead->referencesNum + i->refTail->referencesNum);
        }
        text += ',';
    }
    text.pop_back();
    text += ']';
    return text;
}

ConcatStringList::DeleteStringList::~DeleteStringList()
{
    head = nullptr;
    tail = nullptr;
}
