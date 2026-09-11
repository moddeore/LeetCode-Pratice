class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        int totaleven=0;
        vector <int> digitcount(10,0);
        for(int i=0;i<digits.size();i++){
            digitcount[digits[i]]++;
        }

        for(int i=1;i<=9;i++){
            if(digitcount[i]==0){
                continue;
            }
            digitcount[i]--;

            for(int j=0;j<=9;j++){
            if(digitcount[j]==0){
                continue;
            }
            digitcount[j]--;

            for(int k=0;k<=8;k+=2){
                if(digitcount[k]==0){
                    continue;
                }
                totaleven++;
            }
            digitcount[j]++;

            }
            digitcount[i]++;
        }
        return totaleven;

    }
};