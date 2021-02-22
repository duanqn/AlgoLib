#pragma once

#include "ITree.hpp"
#include "exception.h"

namespace AlgoLib::DataStructure{
    template<typename NodeData, int Branch>
    class FixedBranchTreeNode : public ITreeNode<NodeData>{
        private:
        static_assert(Branch > 0);
        using Parent = ITreeNode<NodeData>;

        void init(){
            m_numChild = 0;
            for(int i = 0; i < Branch; ++i){
                m_childNodes[i] = nullptr;
            }
        }

        protected:
        int m_numChild;
        FixedBranchTreeNode* m_childNodes[Branch];

        public:
        FixedBranchTreeNode(): Parent(){
            this->init();
        }

        FixedBranchTreeNode(const NodeData &data): Parent(data){
            this->init();
        }

        FixedBranchTreeNode(NodeData&& data): Parent(data){
            this->init();
        }

        virtual ~FixedBranchTreeNode(){
            for(int i = 0; i < Branch; ++i){
                if(m_childNodes[i] != nullptr){
                    delete m_childNodes[i];
                }
            }
        }

        virtual void addChild(ITreeNode<NodeData>* node) override {
            if(m_numChild < Branch){
                m_childNodes[m_numChild++] = dynamic_cast<FixedBranchTreeNode<NodeData, Branch>*>(node);
            }
        }

        virtual void replaceChild(FixedBranchTreeNode<NodeData, Branch>* node, int pos){
            if(pos < 0 || pos >= Branch){
                throw AlgoLib::Exception(AlgoLib::Exception::INDEX_OOB);
            }

            if(m_childNodes[pos] != nullptr){
                delete m_childNodes[pos];
            }

            m_childNodes[pos] = node;
        }
    };

    template<typename NodeData, int Branch>
    class FixedBranchTree : public ITree<NodeData>{
        private:
        protected:
        virtual ITreeNode<NodeData>* makeNode(const NodeData& data) const override {
            return new FixedBranchTreeNode<NodeData, Branch>(data);
        }

        public:
        FixedBranchTree(): ITree<NodeData>(){}
        virtual ~FixedBranchTree(){}

        virtual void insert(const NodeData& data, ITreeNode<NodeData>* parent) override {
            parent->addChild(new FixedBranchTreeNode<NodeData, Branch>(data));
        }

        virtual void setRoot(const NodeData& data){
            this->m_root = new FixedBranchTreeNode<NodeData, Branch>(data);
        }

    };

    template<typename NodeData>
    using BinaryTree = FixedBranchTree<NodeData, 2>;
}