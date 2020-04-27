#ifndef BLAST2D_QUAD_TREE_HPP
#define BLAST2D_QUAD_TREE_HPP

#include "ivector2.hpp"

namespace Blast2D{

    template<typename Data>
    struct Node
    {
        IVector2 pos;
        Data data;
        Node(IVector2 _pos, Data _data)
        {
            pos = _pos;
            data = _data;
        }
    };

    template<typename Data>
    class Quad
    {
        // Hold details of the boundary of this node
        IVector2 topLeft;
        IVector2 botRight;

        // Contains details of node
        Node<Data> *n;

        // Children of this tree
        Quad *topLeftTree;
        Quad *topRightTree;
        Quad *botLeftTree;
        Quad *botRightTree;

    public:
        Quad()
        {
            topLeft = IVector2(0, 0);
            botRight = IVector2(0, 0);
            n = NULL;
            topLeftTree  = NULL;
            topRightTree = NULL;
            botLeftTree  = NULL;
            botRightTree = NULL;
        }
        Quad(IVector2 topL, IVector2 botR)
        {
            n = NULL;
            topLeftTree  = NULL;
            topRightTree = NULL;
            botLeftTree  = NULL;
            botRightTree = NULL;
            topLeft = topL;
            botRight = botR;
        }
        void insert(Node<Data>*);
        Node<Data>* search(IVector2);
        bool inBoundary(IVector2);
    };

    template<typename Data>
    void Quad<Data>::insert(Node<Data> * node) {
        if (node == NULL)
            return;

        if (!inBoundary(node->pos))
            return;


        if (abs(topLeft.x - botRight.x) <= 1 &&
            abs(topLeft.y - botRight.y) <= 1)
        {
            if (n == NULL)
                n = node;
            return;
        }

        if ((topLeft.x + botRight.x) / 2 >= node->pos.x)
        {
            if ((topLeft.y + botRight.y) / 2 >= node->pos.y)
            {
                if (topLeftTree == NULL)
                    topLeftTree = new Quad(
                            IVector2(topLeft.x, topLeft.y),
                            IVector2((topLeft.x + botRight.x) / 2,
                                  (topLeft.y + botRight.y) / 2));
                topLeftTree->insert(node);
            }

            else
            {
                if (botLeftTree == NULL)
                    botLeftTree = new Quad(
                            IVector2(topLeft.x,
                                  (topLeft.y + botRight.y) / 2),
                            IVector2((topLeft.x + botRight.x) / 2,
                                  botRight.y));
                botLeftTree->insert(node);
            }
        }
        else
        {

            if ((topLeft.y + botRight.y) / 2 >= node->pos.y)
            {
                if (topRightTree == NULL)
                    topRightTree = new Quad(
                            IVector2((topLeft.x + botRight.x) / 2,
                                  topLeft.y),
                            IVector2(botRight.x,
                                  (topLeft.y + botRight.y) / 2));
                topRightTree->insert(node);
            }

            else
            {
                if (botRightTree == NULL)
                    botRightTree = new Quad(
                            IVector2((topLeft.x + botRight.x) / 2,
                                  (topLeft.y + botRight.y) / 2),
                            IVector2(botRight.x, botRight.y));
                botRightTree->insert(node);
            }
        }
    }

    template<typename Data>
    Node<Data> *Quad<Data>::search(IVector2 p) {
        // Current quad cannot contain it
        if (!inBoundary(p))
            return NULL;

        if (n != NULL)
            return n;

        if ((topLeft.x + botRight.x) / 2 >= p.x)
        {
            if ((topLeft.y + botRight.y) / 2 >= p.y)
            {
                if (topLeftTree == NULL)
                    return NULL;
                return topLeftTree->search(p);
            }
            else
            {
                if (botLeftTree == NULL)
                    return NULL;
                return botLeftTree->search(p);
            }
        }
        else
        {
            if ((topLeft.y + botRight.y) / 2 >= p.y)
            {
                if (topRightTree == NULL)
                    return NULL;
                return topRightTree->search(p);
            }

            else
            {
                if (botRightTree == NULL)
                    return NULL;
                return botRightTree->search(p);
            }
        }
    }

    template<typename Data>
    bool Quad<Data>::inBoundary(IVector2 p) {
        return (p.x >= topLeft.x &&
                p.x <= botRight.x &&
                p.y >= topLeft.y &&
                p.y <= botRight.y);
    }
}


#endif
