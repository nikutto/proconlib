#include<ctime>
#include<vector>
#include<cstdlib>
#include<cmath>

namespace ProconLib{

    using myTime_t=double;
    /*
    class ManagerExample{
        public:
        struct State;
        using score_t = double;
        State initialState();
        score_t calcScore(State state);
        std::vector<State> neighbors(State state);
        void reset();        
        static bool better(score_t lhs,score_t rhs);
    };
    */
    /*
    class TemperatureManagerExample{
        using score_t = double;
        public:
        using temp_t = double;
        private:
        const temp_t startTemp,endTemp;
        public:
        temp_t getTemperature(myTime_t t,myTime_t limit){return startTemp + (endTemp - startTemp) * t / limit;}
        double getProbability(score_t score,score_t newScore,temp_t temp){return exp((newScore-score)/temp);}
    };
    */
    template<typename Manager,typename TemperatureManager>
    class SimulatedAnnealing{
        using State = typename Manager::State;
        using score_t = typename Manager::score_t;
        using temp_t = typename TemperatureManager::temp_t;
        Manager manager;
        TemperatureManager tempManager;
        public:
        SimulatedAnnealing(Manager manager=Manager(),TemperatureManager tempManager=TemperatureManager()):manager(manager),tempManager(tempManager){};
        State operator()(double limit);
        void reset(){manager.reset();}
    };

    

    template<typename Manager,typename TemperatureManager>
    typename Manager::State SimulatedAnnealing<Manager,TemperatureManager>::operator()(double limit){
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
            score_t tmpScore = manager.calcScore(neighbor);
            double temp = tempManager.getTemperature(nowTime,limit);
            double p = tempManager.getProbability(score,tmpScore,temp);
            if(double(rand())/RAND_MAX<p){
                state = neighbor;
                score = tmpScore;
            }
            #ifdef DEBUG
                loopCnt++;
                if(loopCnt%SIZE==0) cerr<<loopCnt<<" -th loop: "<<score<<"\n";
            #endif
        }
    }
    
}