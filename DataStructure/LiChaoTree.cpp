
namespace ProconLib{

    template<typename _Comp>
    struct IntOption{
        using Comp = _Comp;
        template<typename T>
        static bool isLeaf(T x){
            return x<=1;
        };
    };
    template<typename Line,class Option>
    struct LiChaoTreeNode{
        using value_t=typename Line::value_t;
        using Comp=typename Option::Comp;
        Line line;
        LiChaoTreeNode* lch;
        LiChaoTreeNode* rch;
        void add(value_t lb,value_t ub,Line l);
        value_t get(value_t lb,value_t ub,value_t x);
        LiChaoTreeNode(Line line):line(line){};
    };

    template<typename Line,class Option>
    void LiChaoTreeNode<Line,Option>::add(value_t lb,value_t ub,Line l){
        auto CompEq=[](value_t x,value_t y){
            return Comp()(x,y) || x==y;
        };
        value_t pre_v[2]={line.f(lb),line.f(ub)};
        value_t add_v[2]={l.f(lb),l.f(ub)};
        if(CompEq(add_v[0],pre_v[0]) && CompEq(add_v[1],pre_v[1])){
            line=l;
            return;
        }
        if(CompEq(pre_v[0],add_v[0]) && CompEq(pre_v[1],add_v[1])){
            return;
        }
        if(Option::isLeaf(ub-lb)){
            if(Comp()(add_v[0],pre_v[0])) line=l;
            return;
        }
        value_t mid = (lb+ub)/2;
        if(lch==nullptr) lch=new LiChaoTreeNode(line);
        if(rch==nullptr) rch=new LiChaoTreeNode(line);
        lch->add(lb,mid,l),rch->add(mid,ub,l);
    }

    template<typename Line,class Option>
    typename LiChaoTreeNode<Line,Option>::value_t LiChaoTreeNode<Line,Option>::get(value_t lb,value_t ub,value_t x){
        value_t mid=(lb+ub)/2;
        value_t sc=line.f(x);
        value_t ret;
        if(mid<=x){
            if(rch==nullptr) return sc;
            ret=rch->get(mid,ub,x);
        }
        else{
            if(lch==nullptr) return sc;
            ret=lch->get(lb,mid,x);
        }
        return Comp()(sc,ret) ? sc : ret;
    }
    
    template<typename _value_t>
    struct L{
        using value_t=_value_t;
        value_t a,b;
        value_t f(value_t x){return a*x+b;}
    };
    template<typename value_t,class Option>
    class LiChaoTree{
        using Line=L<value_t>;
        value_t lb,ub;
        LiChaoTreeNode<L<value_t>,Option>* root;
        bool hasLine=false;
        public:
        LiChaoTree(value_t lb,value_t ub):lb(lb),ub(ub){};
        void add(value_t a,value_t b);
        value_t get(value_t x);
    };

    template<typename value_t,class Option>
    void LiChaoTree<value_t,Option>::add(value_t a,value_t b){
        L<value_t> l={a,b};
        if(!hasLine) root=new LiChaoTreeNode<L<value_t>,Option>(l),hasLine=true;
        else root->add(lb,ub,l);
    }

    template<typename value_t,class Option>
    value_t LiChaoTree<value_t,Option>::get(value_t x){
        return root->get(lb,ub,x);
    }

}