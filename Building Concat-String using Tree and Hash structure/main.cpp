#include "ConcatStringTree.h"

int main()
{
    HashConfig hashConfig(
        2,
        0.5,
        0.5,
        0.75,
        2,
        4);
    LitStringHash *litStringHash = new LitStringHash(hashConfig);
    ReducedConcatStringTree *t1 = new ReducedConcatStringTree("nguyen", litStringHash);
    ReducedConcatStringTree *t2 = new ReducedConcatStringTree("dai", litStringHash);
    ReducedConcatStringTree *t3 = new ReducedConcatStringTree("tien", litStringHash);
    ReducedConcatStringTree *t4 = new ReducedConcatStringTree("_", litStringHash);
    ReducedConcatStringTree *t5 = new ReducedConcatStringTree("_", litStringHash);

    ReducedConcatStringTree *c1 = new ReducedConcatStringTree(t1->concat(*t4));
    ReducedConcatStringTree *c2 = new ReducedConcatStringTree(t2->concat(*t5));
    ReducedConcatStringTree *c3 = new ReducedConcatStringTree(c1->concat(*c2));
    ReducedConcatStringTree *c4 = new ReducedConcatStringTree(c2->concat(*t3));
    ReducedConcatStringTree *c5 = new ReducedConcatStringTree(c3->concat(*c4));
    cout << c5->toString();
    return 0;
}