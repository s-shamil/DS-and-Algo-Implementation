#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <climits>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

#define ll long long
#define ull unsigned long long
#define bug printf("hello\n");

vector<string> wordlist[2]; //0 for insert set , 1 for search set

int N = 10000; //number of words , 10000
int M = 10000; //no of slots in hashtable
int num_of_chars = 5; //number of characters in the generated words

int bugi;

void generate_wordlist()
{
    for(int xx = 0; xx<2; xx++)
    {
        for (int index=0; index<N; index++)
        {
            string str;
            for (int i = 0; i < num_of_chars; ++i)
            {
                int randomChar = rand()%(26); // 26 k 62 korle A-Z and 0-9 shoho ashbe
                if (randomChar < 26)
                    str += 'a' + randomChar;
                else if (randomChar < 26+26)
                    str += 'A' + randomChar - 26;
                else
                    str += '0' + randomChar - 26 - 26;
            }
            wordlist[xx].push_back(str);
        }
    }
}


class Hash
{
public:
    int hash1(string s)  //normal
    {
        ull hashh = 0, R = 'z' + 1;
        for(int i = 0; i<s.length(); i++)
        {
            hashh = (R * hashh + s[i]) ;
        }
        return hashh%M;
    }
    int hash2(string s)  //djb2 xor
    {
        ull hashh = 5381;
        for(int i = 0; i<s.length(); i++)
        {
            hashh = (((hashh<<5) + hashh) ^ s[i]); /* hash * 33 ^ c */
        }
        return hashh%M;
    }
    int hash3(string s)  //sdbm //djb2 addition
    {
//        ull hashh = 0;
//        for(int i = 0; i<s.length(); i++){
//            hashh = (s[i] + (hashh << 6) + (hashh << 16) - hashh)%M;
//        }
//        return hashh;

        ull hashh = 5381;
        for(int i = 0; i<s.length(); i++)
        {
            hashh = (((hashh<<5) + hashh) + s[i]) ; /* hash * 33 + c */
        }
        return hashh%M;
    }
    int selectHash(int x, string s)  //which hash to call and the key
    {
        if(x==1) return hash1(s);
        if(x==2) return hash2(s);
        if(x==3) return hash3(s);
    }
};
//Chaining Class Starts here
struct ItemChain
{
    char * key;
    int val;
    struct ItemChain * prev;
    struct ItemChain * next;

} typedef Citem;

class ChainHash : public Hash
{
    vector<Citem *> Clist;
    //Citem ** Clist;
    int sz, hashID, collisions;
public:
    ChainHash(int M, int h)
    {
        sz = M;
        Clist.reserve(sz);
        //Clist = (Citem **) malloc(sz * sizeof(Citem *));
        hashID = h;
        collisions = 0;
        for(int i = 0; i<sz; i++){
            Clist[i] = 0;
        }
    }
    //return 1 if inserted, 0 if already existed and so discarded (in this case the sent value should be used again by the next to be inserted key
    int insertItem(string key, int val)
    {
        //search if the key is already inserted, return 0 if found
        int found = this->searchItem(key);

        //cout<<found<<"*&*"<<endl;

        if(found!=-1) return 0;
        //insert the key, return 0 as success
        int i = this->selectHash(hashID, key);

        Citem * newItem;
        newItem = (Citem *) malloc(sizeof(Citem));
        newItem->key = (char *) malloc(num_of_chars * sizeof(char));
        strcpy(newItem->key, key.c_str());
        newItem->val = val;
        //bug
        if(Clist[i]==0){
            //inserting the first item

            newItem->next = 0;
            newItem->prev = 0;
            Clist[i] = newItem;
        }
        else{
                //bug
            //collision occurred
            collisions++;
            newItem->next = Clist[i];
            Clist[i]->prev = newItem;
            newItem->prev = 0;
            Clist[i] = newItem;
        }
        return 1;
    }

    int searchItem(string key)
    {
        int i = this->selectHash(hashID, key);
        Citem * temp;
        temp = Clist[i];
        while(temp!=0){
            if(string(temp->key)==key) return temp->val;
            temp = temp->next;
        }
        return -1; //not found
    }

    void deleteItem(string key)
    {
        int i = this->selectHash(hashID, key);
        Citem * temp, *del;
        if(Clist[i]==0) return;
        if(string(Clist[i]->key)==key){
            //delete first element
            del = Clist[i];
            Clist[i] = Clist[i]->next;
            if(Clist[i]!=0){
               Clist[i]->prev = 0;
            }
            free(del);
        }
        //not first element
        temp = Clist[i];
        while(temp!=0){
            if(string(temp->key)==key){
                del = temp;
                del->prev->next = del->next;
                if(del->next!=0){
                    del->next->prev = del->prev;
                }
                free(del);
                break;
            }
        }
    }

    int getCol()
    {
        return collisions;
    }
};



//Linear Probing Class Starts here
struct itemLinProb
{
    string key;
    int val;
} typedef Litem;

class LinProbHash : public Hash
{
    vector<Litem> LPlist;
    int sz, hashID, collisions;
public:
    LinProbHash(int M, int h)
    {
        sz = M;
        hashID = h;
        collisions = 0;
        for(int i = 0; i<sz; i++)
        {
            //bug
            Litem Lx;
            Lx.key = "$blank";
            Lx.val = -1;
            LPlist.push_back(Lx);
        }
    }
    //return 1 if inserted, 0 if already existed and so discarded (in this case the sent value should be used again by the next to be inserted key
    int insertItem(string key, int val)
    {
        int idx = this->selectHash(hashID, key);
        //cout<<endl<<idx<<"##"<<endl;
        if(LPlist[idx].key!="$blank" && LPlist[idx].key!="$deleted") collisions++;

        for( ; ; idx = (idx+1) %M)
        {
            if(LPlist[idx].key=="$blank" || LPlist[idx].key=="$deleted")
            {
                break;
            }
            if(LPlist[idx].key == key)
            {
                //bug
                return 0;
            }
            //collisions++;
        }
        LPlist[idx].key = key;
        LPlist[idx].val = val;
        return 1;
        //bugi = idx;
    }

    int searchItem(string key)
    {
        int idx = this->selectHash(hashID, key);
        //cout<<endl<<idx<<"##"<<endl;
        for( ; ; idx = (idx+1) %M)
        {
            if(LPlist[idx].key=="$blank")
            {
                break; // thakle ekhane thakto
            }
            else if(LPlist[idx].key == key)
            {
                return LPlist[idx].val;
            }
        }
        return -1; //not found
    }

    void deleteItem(string key)
    {
        int idx = this->selectHash(hashID, key);
        //cout<<endl<<idx<<"##"<<endl;
        for( ; ; idx = (idx+1) %M)
        {
            if(LPlist[idx].key=="$blank")
            {
                return; //thakle ekhane thakto, nai mane del korte hbe na
            }
            else if(LPlist[idx].key == key)
            {
                //found
                LPlist[idx].key = "$deleted";
                LPlist[idx].val = -1;
                return;
            }
        }
    }


    //test func
    void printAT(int x)
    {
        cout<<LPlist[x].key<<" ||| "<<LPlist[x].val<<endl;
    }
    int getCol()
    {
        return collisions;
    }
};
int main()
{

    generate_wordlist();

    printf("\t\t\t\t  Number of collisions\tTIme elapsed (in milliseconds)\n");
    //Separate Chaining hashing method
    for(int hh = 1; hh<=3; hh++)
    {
        ChainHash C1(M, hh);
        //inserting
        int val = 1;
        for(int i = 0; i<N; i++)
        {
            //cout<<wordlist[0][i]<<C1.selectHash(hh, wordlist[0][i]);
            int succ = C1.insertItem(wordlist[0][i], val);
            if(succ) val++;
        }
        int cCH = C1.getCol();
        //bug;cout<<val;

        //searching
        const clock_t begin_CH = clock();

        for(int i = 0; i<N; i++)
        {
            //int fnd = LP1.searchItem(wordlist[1][i]);
            C1.searchItem(wordlist[1][i]);
        }

        int tCH = (clock() - begin_CH) * 1000 / CLOCKS_PER_SEC;

        printf("Separate Chaining | Hash Method %d: ", hh);
        printf("\t %d\t\t\t%d\n", cCH, tCH);
    }

    //int milisec = (clock() - begin_time) * 1000 / CLOCKS_PER_SEC;
    //cout << "Time elapsed (in milliseconds): "<<milisec<<endl;



//      for(int i = 200; i<210; i++) cout<<wordlist[0][i]<<endl;
//    //for(int i = 9990; i<10000; i++) cout<<wordlist[0][i]<<endl;
//    cout<<endl;
//    for(int i = 0; i<10; i++) cout<<wordlist[1][i]<<endl;
//    //for(int i = 9990; i<10000; i++) cout<<wordlist[1][i]<<endl;

    //linear prob hashing method
    for(int hh = 1; hh<=3; hh++)
    {
        LinProbHash LP1(M, hh);
        //inserting
        int val = 1;
        for(int i = 0; i<N; i++)
        {
            int succ = LP1.insertItem(wordlist[0][i], val);
            if(succ) val++;
        }
        int cLpH = LP1.getCol();
        //bug;cout<<val;

        //searching
        const clock_t begin_LpH = clock();

        for(int i = 0; i<N; i++)
        {
            //int fnd = LP1.searchItem(wordlist[1][i]);
            LP1.searchItem(wordlist[1][i]);
        }

        int tLpH = (clock() - begin_LpH) * 1000 / CLOCKS_PER_SEC;

        printf("Linear Probing | Hash Method %d:", hh);
        printf("\t\t %d\t\t\t%d\n", cLpH, tLpH);
    }



    //cout<<bugi<<endl;
    //LP1.printAT(bugi);

    return 0;
}
