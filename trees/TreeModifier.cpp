// Copyright (C) 2005 Daniel Dalevi
// Distributed under the GNU GENERAL PUBLIC LICENSE version 2

#include "TreeModifier.h"
#include "Tree.h"
#include "Node.h"

using namespace trees;


TreeModifier::TreeModifier( Tree* tree )
{
  tree_ = tree;
  tree_->setHeadForTM( this );
}


TreeModifier::TreeModifier( Node* pHead, Tree* tree )
{
  head_ = pHead;
  tree_ = tree;
}
