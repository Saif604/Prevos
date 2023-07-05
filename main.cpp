
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

int vote{};

/*------------------------------SHOW CASTED VOTES----------------------------------------------------*/
void showData(const std::vector<std::vector<int>>& data)
{
    for(int i{0}; i<data.size(); i++)
    {
        for(int j{}; j<data[i].size(); j++)
        {
            std::cout<<data[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

/*----------------------------ROUND WISE PREFERENCE VOTE DATA-------------------------------------------*/
void showFreq(int** freq, int b)
{
    for(int i{}; i<b; i++)
    {
        for(int j{}; j<b; j++)
        {
            std::cout<<freq[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

/*----------------------------FIND VOTE PERCENT---------------------------------------------------------*/
double findPer(int score)
{
    return ((score*100)/vote);
}


/*-----------------------------FIND FIRST ROUND WINNER---------------------------------------------------*/
int findWin(int* freq, int n)
{
    int largest{};
    for(int i{1};i<n; i++)
    {
        if(freq[i]>freq[largest])
        largest = i;
    }
    return largest;
}

/*---------------------------FIND FIRST ROUND RUNNER-----------------------------------------------------*/
int findRun(int* freq, int n)
{
    int res = -1, largest = 0;
    for(int i{1}; i<n; i++)
    {
        if(freq[i]>freq[largest])
        {
            res = largest; 
            largest = i;
        }
        else if(freq[i] <= freq[largest])
        {
            if(res==-1 || freq[i] > freq[res])
            res = i;
        }
    }
    return res;
}


/*-----------------------CANDIDATES FREQUENCY IN BALLOT--------------------------------------------------*/
void candFreq(const std::vector<std::vector<int>>& bal, int** freq)
{
    for(int i{}; i<bal.size(); i++)
    {
        int ballot[bal[0].size()];
        for(int j{}; j<bal[i].size(); j++)
        {
            ballot[bal[j][i]]++;
        }
        freq[i] = ballot;
    }
}

/*--------------------------------------CASTING OF VOTES-------------------------------------------------*/
void castVote(std::vector<std::vector<int>>& eldat, size_t l)
{
    bool flag{false};
    std::cout<<"Enter sign of your preferred candidation in descending order : "<<std::endl;
    while(!flag)
    {
        vote++;
        std::vector<int> ballot;
        for(size_t i{}; i<l; i++)
        {
            size_t chose{};
            std::cin>>chose;
            ballot.push_back(chose);
        }
        eldat.push_back(ballot);

        char cont{};
        std::cout<<"Want to cast again? y : n "<<std::endl;
        std::cin>>cont;

        if(cont=='n'|| cont=='N')
        flag = true;
    }
}

/*-----------------------------CANDIDATES AND THEIR SIGNATURE-------------------------------------------*/
void candSign(const std::vector<std::string>& name)
{
    std::cout<<std::left;
    std::cout<<std::setw(20)<<"NAME"<<std::setw(20)<<"SIGN"<<std::endl;
    for(int i{}; i<name.size(); i++)
    {
        std::cout<<std::setw(20)<<name[i]<<std::setw(20)<<i<<std::endl;
    }
}

/*------------------------------------------CANDIDATE NAME -----------------------------------------------*/
void getCandidates(std::vector<std::string>& cand)
{
    int noc{};
    std::cout<<"Enter number of candidates : ";
    std::cin>>noc;

    std::cout<<"Enter names of candidates : "<<std::endl;
    for(int i{}; i<noc; i++)
    {
        std::string name;
        std::cin>>name;
        cand.push_back(name);
    }
}

/*---------------------------------RESULT CALCULATIONS--------------------------------------------------*/
int resCalc(int** freq, std::vector<int>& topFreq, int c, int fId, int sId)
{
    int res{-1};
    for(int i{1}; i < (c-1); i++)
    {
        if(findPer(topFreq[0])>50)
        {
            res = fId;
            break;
        }

        else if(findPer(topFreq[1])>50)
        {
            res = sId;
            break;
        }

        else if(findPer(topFreq[0]) == 50  && c!=2)
        {
            res = fId;
        }

        else if(findPer(topFreq[1]) == 50  && c!=2)
        {
            res = sId;
        }


        else if((findPer(topFreq[0]) < 50 || findPer(topFreq[1]) < 50) && c!=2 )
        {
            if(freq[i][fId] > freq[i][sId])
            topFreq[0] += topFreq[i+1];

            else if(freq[i][sId] > freq[i][fId])
            topFreq[1] += topFreq[i+1];

            else if(freq[i][fId] == freq[i][sId])
            {
                topFreq[0] += (topFreq[i+1])/2;
                topFreq[1] += (topFreq[i+1])/2;
            }
        }
    }
    return res;
}

/*--------------------------------------DISPLAY FINAL RESULT-------------------------------------------*/
void dispRes(const std::vector<int>& arr,const std::vector<std::string>& name, int f, int s, int widx)
{
    std::cout<<std::setw(20)<<"CANDIDATE"<<std::setw(20)<<"ELECTORAL SYMBOL"<<std::setw(20)<<"VOTE"<<std::setw(20)<<"TOTAL VOTE"<<std::setw(20)<<"PERCENTAGE"<<std::endl;
    if(widx==-1)
    {
        std::cout<<std::setw(20)<<name[f]<<std::setw(20)<<f<<std::setw(20)<<arr[0]<<std::setw(20)<<vote<<std::setw(20)<<findPer(arr[0])<<std::endl;
        std::cout<<std::setw(20)<<name[s]<<std::setw(20)<<s<<std::setw(20)<<arr[1]<<std::setw(20)<<vote<<std::setw(20)<<findPer(arr[1])<<std::endl;
        std::cout<<"RESULT : Election got tied between "<<name[f]<<" and "<<name[s]<<std::endl;
    }
    else if(f==widx)
    {
        std::cout<<std::setw(20)<<name[f]<<std::setw(20)<<f<<std::setw(20)<<arr[0]<<std::setw(20)<<vote<<std::setw(20)<<findPer(arr[0])<<std::endl;
        std::cout<<std::setw(20)<<name[s]<<std::setw(20)<<s<<std::setw(20)<<arr[1]<<std::setw(20)<<vote<<std::setw(20)<<findPer(arr[1])<<std::endl;
        std::cout<<std::endl;
        std::cout<<"WINNER : "<<name[f]<<" has won against "<<name[s]<<" by "<<(arr[0]-arr[1])<<" votes "<<std::endl;
    }
    else if(s==widx)
    {
        std::cout<<std::setw(20)<<name[s]<<std::setw(20)<<s<<std::setw(20)<<arr[1]<<std::setw(20)<<vote<<std::setw(20)<<findPer(arr[1])<<std::endl;
        std::cout<<std::setw(20)<<name[f]<<std::setw(20)<<f<<std::setw(20)<<arr[0]<<std::setw(20)<<vote<<std::setw(20)<<findPer(arr[0])<<std::endl;
        std::cout<<std::endl;
        std::cout<<"WINNER : "<<name[s]<<" has won against "<<name[f]<<" by "<<(arr[1]-arr[0])<<" votes "<<std::endl;
    }
    std::cout<<std::endl;
}





int main()
{
    std::vector<std::string> candidates;
    std::vector<std::vector<int>> ballot;    //store voted data

    getCandidates(candidates);
    candSign(candidates);
    castVote(ballot, candidates.size());

    int** frequency = new int*[candidates.size()];      //To store preference in voted data
    for(int i{}; i<candidates.size(); i++)
    {
        int* arr = new int[candidates.size()]{};
        for(int j{}; j<ballot.size(); j++)
        {
            arr[ballot[j][i]]++;
        }
        frequency[i] = arr;
    }



    int fIdx{findWin(frequency[0], candidates.size())};  //Highest preferred candidate in first round 
    int sIdx{findRun(frequency[0], candidates.size())};  //Second highest preffered candidate in first round


    std::vector<int> topVec{};            //Store seat winner in first round so that the seat get transferred   
                                          //to top two condidate effectively in case of no clear majority in 
                                         //first round
    for(int i{}; i<candidates.size(); i++)
    {
        topVec.push_back(frequency[0][i]);
    }

    std::sort(std::begin(topVec), std::end(topVec),std::greater<int>());  //sort first round seat 

    int wIdx = resCalc(frequency, topVec, candidates.size(), fIdx, sIdx);


//Election result declearation
    std::cout<<"ELECTION RESULT : "<<std::endl;
    std::cout<<"CASTED VOTES : "<<std::endl;
    showData(ballot);
    std::cout<<" PREFERENCE PRECEDENCE : "<<std::endl;
    showFreq(frequency, candidates.size());
    dispRes(topVec, candidates, fIdx, sIdx, wIdx);

    return 0;
}