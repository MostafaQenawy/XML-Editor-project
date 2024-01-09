#include "Network_Analysis.h"

string mostInfluencerUser(vector<User> users){
    int temp;
    int count = 0 ;
    string influncer;
    string result ;
    for (User user : users)
        if (user.followers.size() > count )
        {
            count = user.followers.size();
            influncer = user.name;
        }
     result = "The Most influncer user is " + influncer + "\n";
    return result;
}

string mostActiveUser(vector<User> users){
    vector<int> idfollowers;
    int count[15] = {0};
    string result;
    int temp =0 ;
    int id ;
    for (User user : users)
        for(int followerID: user.followers)
        {
            auto it = find(idfollowers.begin(),idfollowers.end(), followerID);
            if(it != idfollowers.end())
                count[followerID] = count[followerID]+ 1;
            else
            {
                idfollowers.push_back(followerID);
                count[followerID] = 1 ;
            }
        }
    for(int i = 0 ; i < 15; i++)
    {
        if(count[i] > temp)
        {
            temp = count[i];
            id = i;
        }
    }
    for (User user : users)
        if(id == user.ID)
            result = "The Most Active user is " + user.name + "\n";
    return result;
}

string mutualFollowers(vector<User> users){
    vector<int> idfollowers;
    int count[30] = {0};
    string result;
    int temp =0 ;
    int id ;
    for (User user : users)
        for(int followerID: user.followers)
        {
            auto it = find(idfollowers.begin(),idfollowers.end(), followerID);
            if(it != idfollowers.end())
                count[followerID] = count[followerID]+ 1;
            else
            {
                idfollowers.push_back(followerID);
                count[followerID] = 1 ;
            }
        }
    for(int i = 0 ; i < 30; i++)
    {

        if(count[i] > 1)
        {
            for (User user : users)
                if(i == user.ID)
                    result += user.name + " is mutual friend for :\n" ;
            for (User user : users)
                for(int followerID: user.followers)
                    if(i == followerID)
                        result +=  " - " + user.name + "\n";
        }
    }

    return result;
}

void SuggestedFollowers(vector<User> users){
    vector<int> idfollowers;
    for (User user : users)
    {
        for(int followerID: user.followers)
            for (User follower : users)
            {
                if(followerID == follower.ID)
                    for(int followerOfFollowers: follower.followers)
                    {
                        auto it = find(idfollowers.begin(),idfollowers.end(), followerOfFollowers);
                        if(it == idfollowers.end() && followerOfFollowers != user.ID)
                            idfollowers.push_back(followerOfFollowers);
                    }
            }

        int z =0 ;
        int x =1 ;
        for(int i = 0 ; i < idfollowers.size() ;i++)
        {
            int flag = 0;
            for(int ID : user.followers)
                if( idfollowers[i] == ID)
                    flag = 1 ;
            if (!flag)
            {
                for(User follower : users)
                    if(idfollowers[i] == follower.ID)
                    {
                        if(!z)
                        {
                            z++;
                            cout <<  "  ..............." << user.name <<"..............\n"<< endl;
                        }
                        cout <<  x++ << " - suggested friend : " << follower.name << "\n" << endl;
                    }
            }
        }
        if (z == 0)
        {
            cout <<  "................. " << user.name <<" ..............\n" << endl;
            cout <<  "                 No suggestion            \n" << endl;
        }
        idfollowers.clear();
    }
    return;
}
