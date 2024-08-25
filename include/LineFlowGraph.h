#ifndef LINE_FLOW_GRAPH_H
#define LINE_FLOW_GRAPH_H

#include <memory>
#include <list>

#include "Node.h"
#include "Payline.h"

using namespace std;

template<int REELS, int ROWS>
class LineFlowGraph
{
    using RowIdx = int;

    public:
        LineFlowGraph(vector<Payline<REELS, ROWS>> paylinesDef);
        Node<REELS, ROWS>* getRoot();

    protected:
        //methods
        void createGraphSchema(Node<REELS, ROWS> *node, list<Payline<REELS, ROWS>*>& paylines);

        //members
        unique_ptr<Node<REELS, ROWS>> root;
};


template<int REELS, int ROWS>
inline LineFlowGraph<REELS, ROWS>::LineFlowGraph(vector<Payline<REELS, ROWS>> paylinesDef):
    root(new Node<REELS, ROWS>(-1, 0)) // reel -1, because the root is not a representation of any real in a machine
{
    list<Payline<REELS, ROWS>*> paylineList;

    for(auto iter = paylinesDef.begin(); iter != paylinesDef.end(); ++iter)
    {
        paylineList.push_back(&(*iter));
    }

    createGraphSchema(root.get(), paylineList);
}

template <int REELS, int ROWS>
inline Node<REELS, ROWS>* LineFlowGraph<REELS, ROWS>::getRoot()
{
    return root.get();
}

template<int REELS, int ROWS>
void LineFlowGraph<REELS, ROWS>::createGraphSchema(Node<REELS, ROWS> *node, list<Payline<REELS, ROWS>*>& paylines)
{
    node->setLinesCount(paylines.size());
    int nodeReel = node->reel;

    if(nodeReel < REELS)
    {
        for(int row = 0; row < ROWS; ++row)
        {
            list<Payline<REELS, ROWS>*> paylinesSublist;
            for (auto paylineIter = paylines.begin(); paylineIter != paylines.end(); )
            {
                if((*paylineIter)->getRow(node->reel + 1) == row)
                {
                    paylinesSublist.push_back(*paylineIter);
                    paylineIter = paylines.erase(paylineIter);
                }
                else 
                {
                    ++paylineIter;
                }
            }    
            
            if(paylinesSublist.size() > 0)
            {
                Node<REELS, ROWS> *newChild = new Node<REELS, ROWS>(nodeReel+1, row);
                node->addChild(newChild);
                createGraphSchema(newChild, paylinesSublist);  
            }            
        }
    }
}

#endif
