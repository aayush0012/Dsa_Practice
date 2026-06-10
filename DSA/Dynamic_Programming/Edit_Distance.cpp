class Solution {
public:
int solve(vector<vector<int>> &dp, string &word1,string &word2, int i,int j ){
         if (i==word1.length() && j==word2.length())return 0; 
         if(i == word1.length()) return word2.length() - j;
         if(j == word2.length()) return word1.length() - i;
        if(dp[i][j]!=10000)return dp[i][j]; 
        // first option is to keep the word 
        if(word1[i]==word2[j]){
            dp[i][j]=solve(dp,word1,word2,i+1,j+1); 
        }
        else{
            int del1 = 1+solve(dp,word1,word2,i+1,j); 
            int del2 = 1+solve(dp,word1,word2,i,j+1); 
            int del3 = 1+solve(dp,word1,word2,i+1,j+1);
            dp[i][j]=min(del1,min(del2,del3)); 
        }
        return dp[i][j]; 
    }
    int minDistance(string word1, string word2) {
         int n =word1.length(); 
        int m =word2.length() ;
        vector<vector<int>>dp(n,vector<int>(m,10000)); 
        int ans = solve(dp,word1,word2,0,0); 
        return ans ; 
    }
};
