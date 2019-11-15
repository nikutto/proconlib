#include<ctime>
#include<vector>

namespace ProconLib{

    using myTime_t=double;
    /*
    struct ManagerExample{
        struct State;
        using score_t = double;
        State initialState();
        score_t calcScore(State state);
        State getNeighbor(State state);
        void reset();        
        static bool better(score_t lhs,score_t rhs);
    };
    */
    template<typename Manager>
    class HillClimbing{
        using State = typename Manager::State;
        using score_t = typename Manager::score_t;
        Manager manager;
        public:
        HillClimbing(Manager manager):manager(manager){};
        State operator()(double limit);
        void reset(){manager.reset();}
    };

    template<typename Manager>
    typename Manager::State HillClimbing<Manager>::operator()(double limit){
        clock_t startClock = clock();

        State state = manager.initialState();
        score_t score = manager.calcScore(state);

        #ifdef DEBUG
            cerr<<"Initial State Score: "<<score<<"\n";
            int loopCnt=0;
            int SIZE=1000;
        #endif
        while(true){
            clock_t nowClock = clock();
            myTime_t nowTime = myTime_t(nowClock - startClock)/CLOCKS_PER_SEC;
            if(nowTime>limit) return state;

            State neighbor = manager.getNeighbor(state);
            score_t newScore = manager.calcScore(neighbor);
            if(Manager::better(score,newScore)){
                state = neighbor;
                score = newScore;
            }

            #ifdef DEBUG
                loopCnt++;
                if(loopCnt%SIZE==0) cerr<<loopCnt<<" -th loop: "<<score<<"\n";
            #endif
        }
    }
    
}