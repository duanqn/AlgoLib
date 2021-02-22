#pragma once

namespace AlgoLib::DataStructure{
    template<typename NodeData>
    class ITreeNode{
        protected:
        NodeData m_data;

        ITreeNode(): m_data(){}
        ITreeNode(const NodeData &data): m_data(data){}
        ITreeNode(NodeData&& data): m_data(data){}

        public:
        virtual ~ITreeNode(){}
        virtual void addChild(ITreeNode<NodeData>* node) = 0;

        virtual const NodeData& data() const {
            return m_data;
        }

        virtual NodeData& data() {
            return m_data;
        }
    };

    template<typename NodeData>
    class ITree{
        protected:
        ITreeNode<NodeData>* m_root;

        virtual ITreeNode<NodeData>* makeNode(const NodeData& data) const = 0;

        public:
        ITree(): m_root(nullptr){}
        virtual ~ITree(){
            if(m_root != nullptr){
                delete m_root;
            }
        }

        ITreeNode<NodeData>* getRoot() const {
            return m_root;
        }

        virtual void insert(const NodeData& data, ITreeNode<NodeData>* parent){
            parent->addChild(makeNode(data));
        }

        virtual void setRoot(const NodeData& data){
            m_root = makeNode(data);
        }
    };
}   // AlgoLib::DataStructure
