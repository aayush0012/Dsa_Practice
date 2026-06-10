class Solution {
public:
int solve(string &text1, string &text2, vector<vector<int>> &dp, int i ,int j ){
    if(i<0 || j<0)return 0; 
    if(dp[i][j]!=-1)return dp[i][j]; 
    if(text1[i] == text2[j]){
        dp[i][j] = 1+solve(text1,text2,dp,i-1,j-1); 
    }
    else {
        dp[i][j]= max(solve(text1,text2,dp,i-1,j),solve(text1,text2,dp,i,j-1)); 
    }
    return dp[i][j]; 
}
    int longestCommonSubsequence(string text1, string text2) {
        int n = text1.length(); 
        int m =text2.length(); 
        vector<vector<int>>dp(n,vector<int>(m,-1)); 
        int ans = solve(text1,text2,dp,n-1,m-1); 
        return ans; 
    }
};
