// -*- coding: utf-8 -*-
#pragma once

#include <cassert>
#include <climits>
#include <string>
#include <vector>

#include "LRUList.hpp"
#include "common_utils.hpp"
#include "string_tree_limited_ns.hpp"
#include "string_tree_ns.hpp"

namespace NOT_STREAM {
class STreePre : public STreeLimit {
  // protected:
 public:
  LRUList lru;
  STreePre(const std::string& str, unsigned int max_fnode = MAX_FNODE)
      : STreeLimit(str, max_fnode), lru(max_fnode){};

  ~STreePre(){};

  inline unsigned int delIFfull() {
    while (this->isFull()) {
      STree::Node* node = this->getLRUNode();

#ifdef DEBUG
      if (UTIL::DEBUG_LEVEL > 2) {
        this->lru.dump();
      }
#endif
      assert(node->children.size() == 0);
      this->lru.del_unused(node->fid);
      this->delNode(node);
    }
    return 0;  // not full
  }

  inline virtual STree::Node* insertNewNode(unsigned int i, STree::Node* node1, const STree::Node* node2) {
    STree::Node* new_node = this->insertFactorNode(node1, i, node2->depth);
    this->useNode(new_node);
    if (this->stat) {
      assert(this->stat->pos_prev_used[new_node->fid] == UINT_MAX);
      this->stat->pos_prev_used[new_node->fid] = this->stat->len_factors.size() - 1;
    }
    return new_node;
  }

  inline STree::Node* getLRUNode() {
    return this->getFNode(this->lru.back());
  };

  inline virtual void useNode(const STree::Node* node) {
    if (UTIL::DEBUG_LEVEL > 1) {
      std::cerr << "useNode:";
      node->info();
    }
    const STree::Node* cur = node;
    while (cur != this->root) {
      assert(cur != cur->parent);
      if (cur->isFactor()) {
        this->lru.use(cur->fid);
      }
      cur = this->getParent(cur);
    }
  }
};
}  // namespace NOT_STREAM
