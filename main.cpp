#include "ConcatStringList.h"

void tc1()
{
    ConcatStringList s1("Hello,_world");
    // test length
    cout << "s1's length: " << s1.length() << endl;
    // test get
    cout << "char at index 2: " << s1.get(2) << endl;
    try
    {
        cout << "char at index 22: " << s1.get(22) << endl;
    }
    catch (out_of_range &ofr)
    {
        cout << "Exception out_of_range: " << ofr.what() << endl;
    }
    // test indexOf
    cout << "in s1, index of 'o': " << s1.indexOf('o') << endl;
    cout << "in s1, index of 'a': " << s1.indexOf('a') << endl;
    // test toString
    cout << "s1 toString: " << s1.toString() << endl;
}

void tc2()
{
    ConcatStringList s1("Hello,");
    ConcatStringList s2("_this_is");
    ConcatStringList s3("_an_assignment");

    // test concat
    ConcatStringList s4 = s1.concat(s2);
    cout << "s4: " << s4.toString() << endl;

    ConcatStringList s5 = s1.concat(s2).concat(s3);
    cout << "s5: " << s5.toString() << endl;

    // test subString
    ConcatStringList s6 = s5.subString(5, 15);
    cout << "s6: " << s6.toString() << endl;

    // test reverse
    ConcatStringList s7 = s5.reverse();
    cout << "s7: " << s7.toString() << endl;
}

void tc3()
{
    ConcatStringList *s1 = new ConcatStringList("Hello");
    ConcatStringList *s2 = new ConcatStringList("_world");
    ConcatStringList *s3 = new ConcatStringList(s1->concat(*s2));

    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;

    cout << "---After deleting s1---" << endl;
    delete s2;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;

    cout << "---After deleting s3---" << endl;
    delete s3;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;

    cout << "---After deleting s2---" << endl;
    delete s1;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
}

void tc4()
{
    ConcatStringList t1 = ConcatStringList("");
    ConcatStringList t2 = ConcatStringList("nguyen");
    ConcatStringList t3 = ConcatStringList("dai");
    ConcatStringList t4 = ConcatStringList("tien");
    ConcatStringList c1 = t1.concat(t2).concat(t3).concat(t4);
    ConcatStringList c2 = t4.concat(t1);
    cout << c1.toString();
}

void tc5()
{
    ConcatStringList *a = new ConcatStringList("nguyen");
    ConcatStringList *b = new ConcatStringList("dai");
    ConcatStringList *c = new ConcatStringList("tien");
    ConcatStringList *d = new ConcatStringList(a->concat(*b));
    ConcatStringList *e = new ConcatStringList(d->reverse());
    delete d;
    delete b;
    delete e;
    cout << ConcatStringList::delStrList.totalRefCountsString();
}

int main()
{
    tc1();
    return 0;
}