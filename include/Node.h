#ifndef NODE_H
#define NODE_H

#include <memory>
#include <list>

/* Node for line flow graphs*/

template<int REELS, int ROWS>
class Node 
{
	public:
		using NodeType = Node<REELS, ROWS>;
		using NodePtr = std::unique_ptr<Node<REELS, ROWS>>;

		Node(int reel, int row);
		void addChild(Node<REELS, ROWS>* childNode);
		void setLinesCount(int linesCount);
		std::list<NodePtr>& getChildren();
		int getLinesCount();

		const int reel;
		const int row;
		
	protected:	
		unsigned linesCount;
		std::list<NodePtr> children;			
};


template<int REELS, int ROWS>
Node<REELS, ROWS>::Node(int reel, int row):
	linesCount(0),
	reel(reel),
	row(row)
{
}


template <int REELS, int ROWS>
inline void Node<REELS, ROWS>::addChild(Node *childNode)
{
	children.push_back(std::unique_ptr<Node<REELS, ROWS>>(childNode));
}

template <int REELS, int ROWS>
inline void Node<REELS, ROWS>::setLinesCount(int linesCount)
{
	this->linesCount = linesCount;
}

template <int REELS, int ROWS>
inline std::list<std::unique_ptr<Node<REELS, ROWS>>> &Node<REELS, ROWS>::getChildren()
{
    return this->children;
}

template <int REELS, int ROWS>
inline int Node<REELS, ROWS>::getLinesCount()
{
    return this->linesCount;
}

#endif