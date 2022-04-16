//
// Created by dev on 4/16/22.
//

#ifndef LAB2_RBTREE_ITERATOR_H
#define LAB2_RBTREE_ITERATOR_H

template <typename T>
class RBTree;

template<typename T>
class RBTreeIterator : public std::iterator<std::forward_iterator_tag, T>
{
public:
	T& operator*();
	T* operator->();
	RBTreeIterator next();
	T get() const;
	RBTreeIterator operator++(int); // todo fixme const
	RBTreeIterator& operator++();
	bool operator==(const RBTreeIterator& other);
	bool operator!=(const RBTreeIterator& other);
	void skip();
	operator bool() const;
private:
	std::weak_ptr<Node<T>> node_ptr;
	const RBTree<T> *tree; // fixme
	RBTreeIterator(const NodePtr<T> node_ptr_, const RBTree* tree_) : tree(tree_), node_ptr(node_ptr_) {};
};


#endif //LAB2_RBTREE_ITERATOR_H
