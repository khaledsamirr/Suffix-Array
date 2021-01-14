#include <iostream>
#include <algorithm>
using namespace std;
struct Suffix{
    int index;
    int rank[2];
};
int compare(struct Suffix a, struct Suffix b){
    if(a.rank[0]==b.rank[0]){
        if(a.rank[1]<b.rank[1])
            return 1;
        else
            return 0;
    }
    else{
        if(a.rank[0]<b.rank[0])
            return 1;
        else
            return 0;
    }
}
class SuffixArray{
    char* text;
    int length=0;
    int* arr;
public:
    SuffixArray(char* txt){
        text=txt;
        int i=0;
        while(txt[i]!=NULL){
            i++;
            length++;
        }
        arr=new int[length];
    }
    void ConstructUsingPrefixDoubling(){
        struct Suffix sfs[length];
        for(int i=0;i<length;i++){
            sfs[i].index=i;
            sfs[i].rank[0]=text[i]-'a';
            if((i+1)<length){
                sfs[i].rank[1]=text[i+1]-'a';
            }else{
                sfs[i].rank[1]=-1;
            }
        }
        sort(sfs,sfs+length,compare);
        int m[length];
        for(int j=4;j<2*length;j=j*2){
            int rank=0;
            int rankP=sfs[0].rank[0];
            sfs[0].rank[0]=rank;
            m[sfs[0].index]=0;
            for(int i=1;i<length;i++){
                if (sfs[i].rank[0] == rankP &&sfs[i].rank[1] == sfs[i-1].rank[1])
                {
				rankP = sfs[i].rank[0];
				sfs[i].rank[0] = rank;
                }
                else
                {
                    rankP = sfs[i].rank[0];
                    sfs[i].rank[0] = ++rank;
                }
                m[sfs[i].index] = i;
            }
            for(int i=0;i<length;i++){
                int next=sfs[i].index+(j/2);
                if(next<length){
                    sfs[i].rank[1]=sfs[m[next]].rank[0];
                }
                else
                    sfs[i].rank[1]=-1;
            }
            sort(sfs, sfs+length, compare);
        }
        for(int i=0;i<length;i++){
            arr[i]=sfs[i].index;
        }
    }
    void Print(){
        for (int i = 0; i < length; i++)
            cout << arr[i] << " ";
        cout << endl;
    }
};


int main()
{
    SuffixArray t("ACGACTACGATAAC$");
    t.ConstructUsingPrefixDoubling();
    t.Print(); // Prints:  14 11 12  0  6  3  9 13  1  7  4  2  8 10  5
    return 0;
}
