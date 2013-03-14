#include <iostream>
#include "BARSoxSound.h"
#include "BARSoxTrack.h"
#include "BARSoxPositionNode.h"

#define INPUT_ERROR     1
#define OUTPUT_ERROR    2

using namespace std;

void display(BARSoxPositionNode* n, sox_sample_t* ref)
{
    if (!n->isLeaf())
    {
        display((BARSoxPositionNode*) n->getLeft(),ref);
    }

    cout << "Node #" << n->getId() << ": pos(" << n->get().pos-ref << ") len(" << n->get().len << ")" << endl;

    if (!n->isLeaf())
    {
        display((BARSoxPositionNode*) n->getRight(),ref);
    }
}

int main()
{
    BARSoxSound snd("bar.wav");

    BARSoxPositionNode* nodo = new BARSoxPositionNode(0, snd.getBuffer(), snd.getFormat()->signal.length);

    cout << "nodo first" << endl;
    display(nodo,nodo->get().pos);
    cout << endl;

    nodo->divideLeaves();
    nodo->divideLeaves();

    cout << "nodo second" << endl;
    display(nodo,nodo->get().pos);
    cout << endl;

    nodo->mergeLeaves();
    cout << "nodo third" << endl;
    display(nodo,nodo->get().pos);
    cout << endl;

    //snd.play();

    return 0;
}

